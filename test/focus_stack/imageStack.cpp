#include "imageStack.h"
#include "core/buffers/bufferFactory.h"
#include "core/fileformats/bmpLoader.h"

#include <core/filesystem/folderScanner.h>

ImageStack::ImageStack(pair<int, int> dimensions)
{
    height = dimensions.first;
    width = dimensions.second;
    mergedImage = new RGB24Buffer(height, width);
}

ImageStack::ImageStack(ImageStack * imageStack) {
    ImageStack({imageStack->height, imageStack->width});
    loadStack(imageStack->imageStack);
}

ImageStack::~ImageStack() {
    for (size_t i = 0; i < imageStack.size(); i++) {
        delete_safe(imageStack[i]);
    }
    delete_safe(mergedImage);
}

bool ImageStack::addImageToStack(RGB24Buffer & image)
{
    if (checkDimensions(image))
    {
        imageStack.push_back(new RGB24Buffer(image));
        return true;
    }
    return false;
}

bool ImageStack::removeImageFromStack(int index)
{
    if (index < imageStack.size() && index >= 0) {
        delete_safe(imageStack[index]);
        imageStack.erase(imageStack.begin() + index);
        return true;
    }
    return false;
}

pair<int, int> ImageStack::getDimensions(RGB24Buffer & image)
{
    return pair<int, int>(image.h, image.w);
}

ImageStack * ImageStack::loadStack(vector<RGB24Buffer*> images)
{
    if (images.empty()) {
        return nullptr;
    }

    pair<int, int> dimensions = getDimensions(*images[0]);

    for (size_t i = 0; i < images.size(); i++) {
        if (!checkDimensions(*images[i], dimensions)) {
            return nullptr;
        }
    }

    ImageStack * imageStack = new ImageStack(dimensions);

    for (size_t i = 0; i < images.size(); i++) {
        imageStack->imageStack.push_back(new RGB24Buffer(images[i]));
    }
    return imageStack;
}

ImageStack * ImageStack::loadStack(const string &pathToFolder)
{
    std::vector<std::string> extentions = BufferFactory::getInstance()->extentionsRGB24();
    for (std::string str : extentions)
    {
        cout << str << endl;
    }

    std::vector<std::string> childern;
    bool res = FolderScanner::scan(pathToFolder, childern);

    for (std::string str : childern)
    {
        cout << str << endl;
    }

    if (childern.empty()) {
        return nullptr;
    }

    RGB24Buffer * image = BufferFactory::getInstance()->loadRGB24Bitmap(childern[0]);
    if (image == nullptr) {
        return nullptr;
    }
    pair<int, int> dimensions = getDimensions(*image);

    ImageStack * imageStack = new ImageStack(dimensions);
    imageStack->imageStack.push_back(image);

    for(size_t i = 1; i < childern.size(); i++)
    {
        std::string name = childern[i];
        RGB24Buffer * image = BufferFactory::getInstance()->loadRGB24Bitmap(name);
        if (image == nullptr || !imageStack->checkDimensions(*image)) {
            delete_safe(imageStack);
            if (image != nullptr)
            {
                delete_safe(image);
            }
            return nullptr;
        }
        else
        {
            imageStack->imageStack.push_back(image);
        }
    }

    return imageStack;
}

void ImageStack::saveStack(string pathToDir)
{
    for (size_t i = 0; i < imageStack.size(); i++)
    {
        std::ostringstream imageNum;
        imageNum << i;
        BufferFactory::getInstance()->saveRGB24Bitmap(imageStack[i], pathToDir + "/" + imageNum.str() + ".bmp");
    }
}

void ImageStack::saveMergedImage(string pathToDir) {
    BufferFactory::getInstance()->saveRGB24Bitmap(mergedImage, pathToDir + "/" + "merged.bmp");
}

void ImageStack::focus_stack(FSAlgorithm & algo)
{
    algo.doStacking(imageStack, mergedImage);
}

bool ImageStack::checkDimensions(RGB24Buffer & image)
{
    pair<int, int> dimensions(height, width);
    return checkDimensions(image, dimensions);
}

bool ImageStack::checkDimensions(RGB24Buffer & image, pair<int, int> & dimensions)
{
    return image.h == dimensions.first && image.w == dimensions.second;
}

