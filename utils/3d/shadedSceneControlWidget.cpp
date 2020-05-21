#include "shadedSceneControlWidget.h"
#include "ui_shadedSceneControlWidget.h"

ShadedSceneControlWidget::ShadedSceneControlWidget(QWidget *parent) :
    ParametersControlWidgetBase(parent),
    ui(new Ui::ShadedSceneControlWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->edgeComboBox , SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(ui->faceComboBox , SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(ui->pointComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(ui->genericParams, SIGNAL(paramsChanged()), this, SIGNAL(paramsChanged()));


    QObject::connect(ui->applyButton, SIGNAL(released()), this, SLOT(applyPressed()));
    QObject::connect(ui->presetComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(presetChanged()));

    reloadShaders("shaders");
    reloadShaders(":/new/shaders/shaders");

    presetChanged();
}

ShadedSceneControlWidget::~ShadedSceneControlWidget()
{
    delete_safe(ui);
}

ShadedSceneControlParameters *ShadedSceneControlWidget::createParameters() const
{
    ShadedSceneControlParameters *result = new ShadedSceneControlParameters();
    getParameters(*result);
    return result;
}


void ShadedSceneControlWidget::getShaderPreset(ShaderPreset &preset, const QComboBox *combo) const
{
    if        (combo->currentIndex() == 0) {
        preset.type = ShaderPreset::NONE;
    } else if (combo->currentIndex() == 1) {
        preset.type = ShaderPreset::PRESET;
    } else if (combo->currentIndex() == 2) {
        preset.type = ShaderPreset::PRESET1;
    } else {
        QString name = combo->currentText();
        if (!shaderCache.contains(name)) {
            preset.type = ShaderPreset::NONE;
        } else {
            preset = shaderCache[name];
        }
    }
}

void ShadedSceneControlWidget::getParameters(ShadedSceneControlParameters &params) const
{
    ui->genericParams->getParameters(params);

    getShaderPreset(params.edge,  ui->edgeComboBox );
    getShaderPreset(params.face,  ui->faceComboBox );
    getShaderPreset(params.point, ui->pointComboBox);
}

void ShadedSceneControlWidget::setParameters(const ShadedSceneControlParameters &input)
{
    ui->genericParams->setParameters(input);

    if ( input.edge.type == ShaderPreset::NONE) {
        ui->edgeComboBox->setCurrentIndex(0);
    } else {
        ui->edgeComboBox->setCurrentIndex(1);
    }

    if ( input.face.type == ShaderPreset::NONE) {
        ui->faceComboBox->setCurrentIndex(0);
    } else {
        ui->faceComboBox->setCurrentIndex(1);
    }

    if ( input.point.type == ShaderPreset::NONE) {
        ui->pointComboBox->setCurrentIndex(0);
    } else {
        ui->pointComboBox->setCurrentIndex(1);
    }

    int i = 0;
    for (; i < ui->faceComboBox->count(); i++)
    {
        if (ui->faceComboBox->itemText(i) == input.face.name)
        {
            break;
        }
    }
    if (i == ui->faceComboBox->count()) {
        shaderCache[input.face.name] = input.face;
        ui->faceComboBox->addItem(input.face.name);

        ui->presetComboBox->insertItem(ui->presetComboBox->count(), input.face.name);
    }
    ui->faceComboBox->setCurrentIndex(i);

}

void ShadedSceneControlWidget::setParametersVirtual(void *input)
{
    // Modify widget parameters from outside
    ShadedSceneControlParameters *inputCasted = static_cast<ShadedSceneControlParameters *>(input);
    setParameters(*inputCasted);
}

void ShadedSceneControlWidget::applyPressed()
{
    int index = ui->presetComboBox->currentIndex();
    if (index == 0) {
        return;
    }
    QString name = ui->presetComboBox->currentText();
    if (!shaderCache.contains(name)) {
        return;
    }

    shaderCache[name].fragment = ui->fragmentShaderTextEdit->toPlainText();
    shaderCache[name].vertex   = ui->vetrexShaderTextEdit->toPlainText();

#if 0
    std::cout << "We would apply new shader code for <" << name.toStdString() << ">" << std::endl;
    std::cout << "Vertex:" << std::endl;
    std::cout << shaderCache[name].vertex.toStdString() << std::endl;
    std::cout << "Fragment:" << std::endl;
    std::cout << shaderCache[name].fragment.toStdString() << std::endl;
#endif

    emit paramsChanged();
}

void ShadedSceneControlWidget::reloadShaders(QString path)
{
    QDir shaderPath(path);
    if (shaderPath.exists()) {
        qDebug() << "Enumerating shaders at <" << path << ">";
        QStringList shadersFiles = shaderPath.entryList(QStringList("*.vsh"));
        for (QString shaderFile : shadersFiles)
        {
            ShaderPreset shaderPreset;
            shaderPreset.load(shaderFile, shaderPath);
            shaderCache.insert(shaderPreset.name, shaderPreset);

            ui->presetComboBox->insertItem(ui->presetComboBox->count(), shaderPreset.name);

            ui->pointComboBox->insertItem(ui->presetComboBox->count(), shaderPreset.name);
            ui->edgeComboBox ->insertItem(ui->presetComboBox->count(), shaderPreset.name);
            ui->faceComboBox ->insertItem(ui->presetComboBox->count(), shaderPreset.name);

            qDebug() << "Loaded shader <"  << shaderPreset.name << ">" << endl;
        }
    }
}

void ShadedSceneControlWidget::presetChanged()
{
    int index = ui->presetComboBox->currentIndex();
    if (index == 0) {
        ui->applyButton->setEnabled(false);
        ui->fragmentShaderTextEdit->setEnabled(false);
        ui->vetrexShaderTextEdit->setEnabled(false);
        return;
    }

    ui->applyButton->setEnabled(true);
    ui->fragmentShaderTextEdit->setEnabled (true);
    ui->vetrexShaderTextEdit->setEnabled (true);

    QString name = ui->presetComboBox->currentText();
    ui->fragmentShaderTextEdit->setText(shaderCache[name].fragment);
    ui->vetrexShaderTextEdit->setText(shaderCache[name].vertex);

}

void ShaderPreset::load(const QString &shaderFile, const QDir &shaderPath)
{
    QString shaderName = shaderFile.left(shaderFile.length() - 4);
    QString shaderFileF = shaderName + ".fsh";

    qDebug() << "Checking shader <" << shaderName << ">"
             << " <" << shaderFile  << "> "
             << " <" << shaderFileF << "> ";

    QFile vsh(shaderPath.filePath(shaderFile ));
    QFile fsh(shaderPath.filePath(shaderFileF));
    if (!vsh.exists() || !fsh.exists())
    {
        return;
    }

    vsh.open(QIODevice::ReadOnly);
    QString shaderText;
    QTextStream shaderStream(&vsh);
    shaderText.append(shaderStream.readAll());
    vsh.close();

    fsh.open(QIODevice::ReadOnly);
    QString shaderTextF;
    QTextStream shaderStreamF(&fsh);
    shaderTextF.append(shaderStreamF.readAll());
    fsh.close();

    this->fragment = shaderTextF;
    this->name     = shaderName;
    this->vertex   = shaderText;
    this->type     = ShaderType::SAVEABLE;

}
