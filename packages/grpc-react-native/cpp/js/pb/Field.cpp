//
//  Field.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 16/03/2022.
//

#include "Field.h"
#include "../../grpc-rn-utils.h"

namespace grpcrn {
namespace js {
namespace pb {


Field::Field(int index, std::string camelCaseName): index_(index), camelCaseName_(camelCaseName) {}

bool Field::has() {
    return has_;
}

void Field::setHas(bool hasField) {
    has_ = hasField;
}

std::string Field::getName() {
    return camelCaseName_;
}

int Field::getIndex() {
    return index_;
}


/// Message field with a JS String type
StringField::StringField(int index, std::string camelCaseName, std::string val): Field(index, camelCaseName), val_(val) {}

Value StringField::getValue() {
    return val_;
}


/// Message field with a JS Number type
NumberField::NumberField(int index, std::string camelCaseName, double val): Field(index, camelCaseName), val_(val) {}
NumberField::NumberField(int index, std::string camelCaseName, float val): Field(index, camelCaseName), val_(val) {}
NumberField::NumberField(int index, std::string camelCaseName, int32_t val): Field(index, camelCaseName), val_(val) {}
NumberField::NumberField(int index, std::string camelCaseName, int64_t val): Field(index, camelCaseName), val_(val) {}
NumberField::NumberField(int index, std::string camelCaseName, uint32_t val): Field(index, camelCaseName), val_(val) {}
NumberField::NumberField(int index, std::string camelCaseName, uint64_t val): Field(index, camelCaseName), val_(val) {}

Value NumberField::getValue() {
    return val_;
}


/// Message field with a JS Boolean type
BooleanField::BooleanField(int index, std::string camelCaseName, bool val): Field(index, camelCaseName), val_(val) {}

Value BooleanField::getValue() {
    return val_;
}


/// Message field with a JS ArrayBuffer type
ArrayBufferField::ArrayBufferField(int index, std::string camelCaseName, uint8_t* buf, size_t size): Field(index, camelCaseName), val_(buf, size) {}

Value ArrayBufferField::getValue() {
    return val_;
}


/// Message field with a JS Object type
ObjectField::ObjectField(int index, std::string camelCaseName, jsi::Object& val): Field(index, camelCaseName), val_(val) {}

Value ObjectField::getValue() {
    return val_;
}


/// Message field with a JS Array type
ArrayField::ArrayField(int index, std::string camelCaseName): Field(index, camelCaseName) {}

Value ArrayField::getValue() {
    return val_;
}

void ArrayField::push(Value val) {
    val_.push(val);
}

}}}
