//
//  Value.h
//  grpc-react-native
//
//  Created by Asger Nohns on 29/03/2023.
//

#ifndef grpcrn_js_pb_Value_h
#define grpcrn_js_pb_Value_h

#include <jsi/jsi.h>
#include <google/protobuf/descriptor.h>

#include "../../utils/Strings.h"

namespace grpcrn {
namespace js {
namespace pb {

using namespace facebook;

enum ValueType { UNDEFINED, STRING, NUMBER, BOOLEAN, ARRAY_BUFFER, ARRAY, OBJECT };

class Value {
public:
    Value();
    
    virtual jsi::Value get(jsi::Runtime& runtime);
    virtual void set(jsi::Runtime& runtime, const jsi::Value& val);
    
    ValueType getType();
private:
    ValueType type_ = ValueType::UNDEFINED;
};



/// StringValue is intended to translate protobuf strings to js string.
class StringValue: public Value {
public:
    StringValue(std::string val);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    std::string getString();
private:
    ValueType type_ = ValueType::STRING;
    std::string val_;
};



/// NumberValue is intended to translate protobuf integer and floating point variants to js number.
class NumberValue: public Value {
public:
    NumberValue(double val);
    NumberValue(float val);
    NumberValue(int32_t val);
    NumberValue(int64_t val);
    NumberValue(uint32_t val);
    NumberValue(uint64_t val);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    double getNumber();
private:
    ValueType type_ = ValueType::NUMBER;
    double doubleVal_;
};



/// BooleanValue is intended to translate protobuf booleans to js booleans.
class BooleanValue: public Value {
public:
    BooleanValue(bool val);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    bool getBoolean();
private:
    ValueType type_ = ValueType::BOOLEAN;
    bool val_;
};



/// ArrayBufferValue is intended to translate protobuf bytes to js array buffer.
class ArrayBufferValue: public Value {
public:
    ArrayBufferValue(uint8_t* buf, size_t size);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    uint8_t* getArrayBuffer();
    size_t getSize();
private:
    ValueType type_ = ValueType::ARRAY_BUFFER;
    uint8_t* buf_;
    size_t size_;
};

/// ObjectValue is intended to translate protobuf messages to js object.
class ObjectValue: public Value {
public:
    ObjectValue(jsi::Object& val);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    jsi::Object& getObject();
private:
    ValueType type_ = ValueType::OBJECT;
    jsi::Object& val_;
};

/// ArrayValue is intended to translate protobuf messages to js object.
class ArrayValue: public Value {
public:
    ArrayValue(jsi::Array& val);
    
    // Base Field virtual methods
    jsi::Value get(jsi::Runtime& runtime) override;
    void set(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    jsi::Array& getArray();
private:
    ValueType type_ = ValueType::ARRAY;
    jsi::Array& val_;
};

class IncompatibleSetValueException : public std::exception {
public:
    virtual const char* type() {
        return "JavaScript value type is incompatible with protobuf type";
    }
};

}}}

#endif /* grpcrn_js_pb_Value_h */
