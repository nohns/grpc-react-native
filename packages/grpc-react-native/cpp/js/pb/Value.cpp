//
//  Value.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 29/03/2023.
//

#include "Value.h"
#include "../../grpc-rn-utils.h"

namespace grpcrn {
namespace js {
namespace pb {

Value::Value() {}

ValueType Value::getType() {
    return type_;
}

/// Message field with a JS String type
StringValue::StringValue(std::string val): Value(), val_(val) {}

jsi::Value StringValue::get(jsi::Runtime& runtime) {
    return jsi::Value(jsi::String::createFromUtf8(runtime, val_));
}

void StringValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isString()) {
        throw IncompatibleSetValueException(runtime);
    }
    
    val_ = val.getString(runtime).utf8(runtime);
}

std::string StringValue::getString() {
    return val_;
}



/// Message field with a JS Number type
NumberValue::NumberValue(double val): Value(), doubleVal_(val) {}
NumberValue::NumberValue(float val): Value(), doubleVal_(static_cast<double>(val)) {}
NumberValue::NumberValue(int32_t val): Value(), doubleVal_(static_cast<double>(val)) {}
NumberValue::NumberValue(int64_t val): Value(), doubleVal_(static_cast<double>(val)) {}
NumberValue::NumberValue(uint32_t val): Value(), doubleVal_(static_cast<double>(val)) {}
NumberValue::NumberValue(uint64_t val): Value(), doubleVal_(static_cast<double>(val)) {}

jsi::Value NumberValue::get(jsi::Runtime& runtime) {
    return jsi::Value(doubleVal_);
}

void NumberValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    
    if (!val.isNumber()) {
        throw IncompatibleSetValueException(runtime);
    }
    
    doubleVal_ = val.getNumber();
}

double NumberValue::getNumber() {
    return doubleVal_;
}



/// Message field with a JS Boolean type
BooleanValue::BooleanValue(bool val): Value(), val_(val) {}

jsi::Value BooleanValue::get(jsi::Runtime& runtime) {
    return jsi::Value(val_);
}

void BooleanValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isBool()) {
        throw IncompatibleSetValueException(runtime);
    }
    
    val_ = val.getBool();
}

bool BooleanValue::getBoolean() {
    return val_;
}


/// Message field with a JS ArrayBuffer type
ArrayBufferValue::ArrayBufferValue(uint8_t* buf, size_t size): Value(), buf_(buf), size_(size) {}

jsi::Value ArrayBufferValue::get(jsi::Runtime& runtime) {
    auto obj = GrpcRN::Utils::copyBufferToJsiArrayBuffer(runtime, buf_, size_);
    return jsi::Value(std::move(obj));
}

void ArrayBufferValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isObject() || !val.asObject(runtime).isArrayBuffer(runtime)) {
        throw IncompatibleSetValueException(runtime);
    }
    
    // Get buffer from arguments
    // @TODO: Not sure about this one chief
    auto arrayBuf = val.asObject(runtime).getArrayBuffer(runtime);
    buf_ = std::move(arrayBuf.data(runtime));
    size_ = arrayBuf.size(runtime);
}

uint8_t* ArrayBufferValue::getArrayBuffer() {
    return buf_;
}

size_t ArrayBufferValue::getSize() {
    return size_;
}


ObjectValue::ObjectValue(jsi::Object& val): Value(), val_(val) {}

jsi::Value ObjectValue::get(jsi::Runtime& runtime) {
    return jsi::Value(std::move(val_));
}

void ObjectValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    if (!val.isObject()) {
        throw IncompatibleSetValueException(runtime);
    }
    
    val_ = val.getObject(runtime);
}

jsi::Object& ObjectValue::getObject() {
    return val_;
}


ArrayValue::ArrayValue(): Value() {}

jsi::Value ArrayValue::get(jsi::Runtime& runtime) {
    auto jsArray = jsi::Array(runtime, vals_.size());
    for(int i = 0; i < vals_.size(); i++) {
        jsArray.setValueAtIndex(runtime, i, vals_[i].get(runtime));
    }
    
    return jsi::Value(std::move(jsArray));
}

void ArrayValue::set(jsi::Runtime &runtime, const jsi::Value& val) {
    // Unimplemented
    throw IncompatibleSetValueException(runtime);
}

std::vector<Value>& ArrayValue::getArray() {
    return vals_;
}

void ArrayValue::push(Value& val) {
    vals_.push_back(std::move(val));
}


}}}
