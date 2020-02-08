//
// Created by Myasnikov Vladislav on 17.10.2019.
//

#ifndef DXF_SUPPORT_DXFCODES_H
#define DXF_SUPPORT_DXFCODES_H

#include <map>
#include <vector>
#include <string>
#include <list>
#include <iostream>

namespace corecvs {

enum class DxfElementType {
    DXF_LAYER, DXF_LINE_TYPE, DXF_BLOCK_RECORD, DXF_LINE, DXF_LW_POLYLINE, DXF_POLYLINE, DXF_VERTEX, DXF_UNKNOWN_TYPE, DXF_SEQ_END, DXF_CIRCLE,
    DXF_ARC, DXF_ELLIPSE, DXF_POINT, DXF_BLOCK, DXF_END_BLOCK, DXF_INSERT
};

enum class DxfDrawingUnits {
    UNITLESS, INCHES, FEET, MILES, MILLIMETERS, CENTIMETERS, METERS, KILOMETERS, MICROINCHES, MILS, YARDS,
    ANGSTROMS, NANOMETERS, MICRONS, DECIMETERS, DECAMETERS, HECTOMETERS, GIGAMETERS, ASTRONOMICAL, LIGHT_YEARS, PARSECS
};

class DxfCodes {
public:
    static const int DXF_INT16 = 0;
    static const int DXF_INT32 = 1;
    static const int DXF_INT64 = 2;
    static const int DXF_DOUBLE = 3;
    static const int DXF_STRING = 4;
    static const int DXF_UNKNOWN_TYPE = 1000;

    static const int DXF_ENTITY_SEPARATOR_CODE = 0;
    static const int DXF_ELEMENT_NAME_CODE = 2;
    static const int DXF_HANDLE_CODE = 5;
    static const int DXF_LINE_TYPE_NAME_CODE = 6;
    static const int DXF_LAYER_NAME_CODE = 8;
    static const int DXF_VARIABLE_CODE = 9;
    static const int DXF_THICKNESS_CODE = 39;
    static const int DXF_RADIUS_CODE = 40;
    static const int DXF_BULGE_CODE = 42;
    static const int DXF_START_ANGLE_CODE = 50;
    static const int DXF_END_ANGLE_CODE = 51;
    static const int DXF_OBJECT_VISIBILITY_CODE = 60;
    static const int DXF_COLOR_NUMBER_CODE = 62;
    static const int DXF_FLAGS_CODE = 70;
    static const int DXF_BLOCK_SCALABILITY_CODE = 281;
    static const int DXF_OWNER_DICTIONARY_HANDLE_CODE = 330;
    static const int DXF_BLOCK_RECORD_HANDLE_CODE = 330;

    static const std::string DXF_LINE_TYPE_NAME_DEFAULT;
    static const int DXF_COLOR_NUMBER_DEFAULT = 256;

    static std::vector<int> getVariableCodes(std::string const &name) {
        if (VARIABLE_CODES.count(name) == 1) {
            return VARIABLE_CODES[name];
        }
        return {};
    }

    static int getCodeType(int code) {
        for (int *range : CODE_RANGES) {
            if (code >= range[0] && code <= range[1]) {
                return range[2];
            }
        }
        return DXF_UNKNOWN_TYPE;
    }

    static DxfElementType getElementType(std::string const &name) {
        if (ELEMENT_TYPES.count(name) == 1) {
            return ELEMENT_TYPES[name];
        }
        return DxfElementType::DXF_UNKNOWN_TYPE;
    }

    static std::vector<uint8_t> getRGB(int number) {
        if (number >= 0 && number <= 255) {
            return DXF_COLORS[number];
        } else return DXF_COLORS[0];
    }

    static DxfDrawingUnits getDrawingUnits(int value) {
        if (DRAWING_UNITS.count(value) == 1) {
            return DRAWING_UNITS[value];
        }
        return DxfDrawingUnits::UNITLESS;
    }

private:
    static std::map<std::string, std::vector<int>> VARIABLE_CODES;
    static std::map<std::string, DxfElementType> ELEMENT_TYPES;
    static std::vector<std::vector<uint8_t>> DXF_COLORS;
    static std::map<int, DxfDrawingUnits> DRAWING_UNITS;
    static int CODE_RANGES[27][3];
};

} // namespace corecvs

#endif //DXF_SUPPORT_DXFCODES_H
