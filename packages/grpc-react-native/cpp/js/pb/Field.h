//
//  Field.h
//  grpc-react-native
//
//  Created by Asger Nohns on 16/03/2022.
//

#ifndef grpcrn_js_pb_Field_h
#define grpcrn_js_pb_Field_h

#include <format>

#include <jsi/jsi.h>
#include <google/protobuf/descriptor.h>

#include "Value.h"
#include "../../utils/Strings.h"

namespace grpcrn {
namespace js {
namespace pb {

using namespace facebook;

class Field {
public:
    Field(int index, std::string camelCaseName);
    
    virtual Value getValue();
    
    bool has();
    void setHas(bool hasField);
    std::string getName();
    int getIndex();
private:
    int index_;
    std::string camelCaseName_;
    bool has_;
};



/// StringField is intended to translate protobuf strings to js string.
class StringField: public Field {
public:
    StringField(int index, std::string camelCaseName, std::string val);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
private:
    StringValue val_;
};



/// NumberField is intended to translate protobuf integer and floating point variants to js number.
class NumberField: public Field {
public:
    NumberField(int index, std::string camelCaseName, double val);
    NumberField(int index, std::string camelCaseName, float val);
    NumberField(int index, std::string camelCaseName, int32_t val);
    NumberField(int index, std::string camelCaseName, int64_t val);
    NumberField(int index, std::string camelCaseName, uint32_t val);
    NumberField(int index, std::string camelCaseName, uint64_t val);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
private:
    NumberValue val_;
};



/// BooleanField is intended to translate protobuf booleans to js booleans.
class BooleanField: public Field {
public:
    BooleanField(int index, std::string camelCaseName, bool val);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
private:
    BooleanValue val_;
};



/// ArrayBufferField is intended to translate protobuf bytes to js array buffer.
class ArrayBufferField: public Field {
public:
    ArrayBufferField(int index, std::string camelCaseName, uint8_t* buf, size_t size);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
private:
    ArrayBufferValue val_;
};

/// ObjectField is intended to translate protobuf messages to js object.
class ObjectField: public Field {
public:
    ObjectField(int index, std::string camelCaseName, jsi::Object& val);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
private:
    ObjectValue val_;
};

class ArrayField: public Field {
public:
    ArrayField(int index, std::string camelCaseName);
    
    // MARK: - Base Field virtual methods
    
    Value getValue() override;
    
    // MARK: - Array specific methods
    
    void push(Value);
    
private:
    ArrayValue val_;
};

class IncompatibleFieldSetValueException : public jsi::JSError {
public:
    // Default constructor
    IncompatibleFieldSetValueException(jsi::Runtime& runtime) : jsi::JSError(runtime, "JavaScript type given to a setter, is not compatible with the protobuf field type") {}
    // Constructor with field name and expected jsi type
    IncompatibleFieldSetValueException(jsi::Runtime& runtime, std::string field, std::string jsType, std::string protobufType): jsi::JSError(runtime, grpcrn::utils::Strings::format("JavaScript type %s for field '%s', is not compatible with the protobuf field type %s", jsType, field, protobufType)) {
        
    }
};

}}}


#endif /* grpcrn_js_pb_Field_h */
