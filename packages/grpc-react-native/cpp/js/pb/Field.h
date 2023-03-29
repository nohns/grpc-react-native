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
    
    // Base Field virtual methods
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
    
    // Base Field virtual methods
    Value getValue() override;
private:
    NumberValue val_;
};



/// BooleanField is intended to translate protobuf booleans to js booleans.
class BooleanField: public Field {
public:
    BooleanField(int index, std::string camelCaseName, bool val);
    
    // Base Field virtual methods
    Value getValue() override;
private:
    BooleanValue val_;
};



/// ArrayBufferField is intended to translate protobuf bytes to js array buffer.
class ArrayBufferField: public Field {
public:
    ArrayBufferField(int index, std::string camelCaseName, uint8_t* buf, size_t size);
    
    // Base Field virtual methods
    Value getValue() override;
private:
    ArrayBufferValue val_;
};

/// ObjectField is intended to translate protobuf messages to js object.
class ObjectField: public Field {
public:
    ObjectField(int index, std::string camelCaseName, jsi::Object& val);
    
    // Base Field virtual methods
    Value getValue() override;
private:
    ObjectValue val_;
};

class ArrayField: public Field {
public:
    ArrayField(int index, std::string camelCaseName, jsi::Array& val);
    
    // Base Field virtual methods
    Value getValue() override;
private:
    ArrayValue val_;
};

class IncompatibleFieldSetValueException : public std::exception {
public:
    // Default constructor
    IncompatibleFieldSetValueException() : formattedError_(nullptr) {}
    // Constructor with field name and expected jsi type
    IncompatibleFieldSetValueException(std::string field, std::string jsType, std::string protobufType) {
        formattedError_ = grpcrn::utils::Strings::format("JavaScript type %s for field '%s', is not compatible with the protobuf field type %s", jsType, field, protobufType).c_str();
    }
    
    virtual const char* type() {
        if (formattedError_ != nullptr) {
            return formattedError_;
        }
        return "JavaScript type given to a setter, is not compatible with the protobuf field type";
    }
private:
    const char* formattedError_;
};

}}}


#endif /* grpcrn_js_pb_Field_h */
