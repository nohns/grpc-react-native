//
//  Field.h
//  grpc-react-native
//
//  Created by Asger Nohns on 16/03/2022.
//

#ifndef grpcrn_js_pb_Field_h
#define grpcrn_js_pb_Field_h

#include <jsi/jsi.h>

namespace grpcrn {
namespace js {
namespace pb {

using namespace facebook;

enum FieldType { undefined, string, number, boolean, arrayBuffer };

class Field {
public:
    Field(int index, std::string camelCaseName);
    
    virtual jsi::Value getValue(jsi::Runtime& runtime);
    virtual void setValue(jsi::Runtime& runtime, const jsi::Value& val);
    
    bool has();
    void setHas(bool hasField);
    std::string getName();
    int getIndex();
    
    FieldType getType();
private:
    int index_;
    std::string camelCaseName_;
    bool has_;
    FieldType type_ = undefined;
};



/// StringField is intended to translate protobuf strings to js string.
class StringField: public Field {
public:
    StringField(int index, std::string camelCaseName, std::string val);
    
    // Base Field virtual methods
    jsi::Value getValue(jsi::Runtime& runtime) override;
    void setValue(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    std::string getString();
private:
    
    FieldType type_ = string;
    std::string val_;
};



/// NumberField is intended to translate protobuf integer and floating point variants to js number.
class NumberField: public Field {
public:
    NumberField(int index, std::string camelCaseName, double val);
    
    // Base Field virtual methods
    jsi::Value getValue(jsi::Runtime& runtime) override;
    void setValue(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    double getNumber();
private:
    FieldType type_ = number;
    double doubleVal_;
};



/// BooleanField is intended to translate protobuf booleans to js booleans.
class BooleanField: public Field {
public:
    BooleanField(int index, std::string camelCaseName, bool val);
    
    // Base Field virtual methods
    jsi::Value getValue(jsi::Runtime& runtime) override;
    void setValue(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    bool getBoolean();
private:
    FieldType type_ = boolean;
    bool val_;
};



/// ArrayBufferField is intended to translate protobuf bytes to js array buffer.
class ArrayBufferField: public Field {
public:
    ArrayBufferField(int index, std::string camelCaseName, uint8_t* buf, size_t size);
    
    // Base Field virtual methods
    jsi::Value getValue(jsi::Runtime& runtime) override;
    void setValue(jsi::Runtime& runtime, const jsi::Value& val) override;
    
    // Type specific methods
    uint8_t* getArrayBuffer();
    size_t getSize();
private:
    FieldType type_ = arrayBuffer;
    uint8_t* buf_;
    size_t size_;
};

class IncompatibleFieldSetValueException : public std::exception {
public:
    virtual const char* type() {
        return "jsi::value given to a setter, is not compatible with the protobuf field type";
    }
};

}}}


#endif /* grpcrn_js_pb_Field_h */
