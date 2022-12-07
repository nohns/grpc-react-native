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

FieldType Field::getType() {
    return type_;
}

/// Message field with a JS String type
StringField::StringField(int index, std::string camelCaseName, std::string val): Field(index, camelCaseName), val_(val) {}

jsi::Value StringField::getValue(jsi::Runtime& runtime) {
    return jsi::Value(jsi::String::createFromUtf8(runtime, val_));
}

void StringField::setValue(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isString()) {
        throw IncompatibleFieldSetValueException();
    }
    
    val_ = val.getString(runtime).utf8(runtime);
}

std::string StringField::getString() {
    return val_;
}



/// Message field with a JS Number type
NumberField::NumberField(int index, std::string camelCaseName, double val): Field(index, camelCaseName), doubleVal_(val) {}

jsi::Value NumberField::getValue(jsi::Runtime& runtime) {
    return jsi::Value(doubleVal_);
}

void NumberField::setValue(jsi::Runtime &runtime, const jsi::Value& val) {
    
    if (!val.isNumber()) {
        throw IncompatibleFieldSetValueException();
    }
    
    doubleVal_ = val.getNumber();
}

double NumberField::getNumber() {
    return doubleVal_;
}



/// Message field with a JS Boolean type
BooleanField::BooleanField(int index, std::string camelCaseName, bool val): Field(index, camelCaseName), val_(val) {}

jsi::Value BooleanField::getValue(jsi::Runtime& runtime) {
    return jsi::Value(val_);
}

void BooleanField::setValue(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isBool()) {
        throw IncompatibleFieldSetValueException();
    }
    
    val_ = val.getBool();
}

bool BooleanField::getBoolean() {
    return val_;
}


/// Message field with a JS ArrayBuffer type
ArrayBufferField::ArrayBufferField(int index, std::string camelCaseName, uint8_t* buf, size_t size): Field(index, camelCaseName), buf_(buf), size_(size) {}

jsi::Value ArrayBufferField::getValue(jsi::Runtime& runtime) {
    auto obj = GrpcRN::Utils::copyBufferToJsiArrayBuffer(runtime, buf_, size_);
    return jsi::Value(std::move(obj));
}

void ArrayBufferField::setValue(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isObject() || !val.asObject(runtime).isArrayBuffer(runtime)) {
        throw IncompatibleFieldSetValueException();
    }
    
    // Get buffer from arguments
    // @TODO: Not sure about this one chief
    auto arrayBuf = val.asObject(runtime).getArrayBuffer(runtime);
    buf_ = std::move(arrayBuf.data(runtime));
    size_ = arrayBuf.size(runtime);
}

uint8_t* ArrayBufferField::getArrayBuffer() {
    return buf_;
}

size_t ArrayBufferField::getSize() {
    return size_;
}


}}}
