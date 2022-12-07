//
//  Message.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 16/03/2022.
//

#include <Message.h>


namespace grpcrn {
namespace js {
namespace pb {


void Message::parseFromProto(google::protobuf::Message* msg) {
    
    // Find all of the fields in in the message
    auto refl = msg->GetReflection();
    std::vector<const google::protobuf::FieldDescriptor*> fields;
    refl->ListFields(*msg, &fields);
    
    // Go through each of the fields and convert values to js kind.
    for (auto field_it = fields.begin(); field_it != fields.end(); field_it++) {
        const google::protobuf::FieldDescriptor* pField = *field_it;
        
        switch (pField->type()) {
            case FieldDescriptor::Type::TYPE_DOUBLE: {
                // JS type variant is number...
                fields_[pField->index()] = new NumberField(pField->index(), pField->camelcase_name(), refl->GetDouble(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_FLOAT: {
                // JS type variant is number...
                
                fields_[pField->index()] = new NumberField(pField->index(), pField->camelcase_name(), refl->GetDouble(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_INT32:
            case FieldDescriptor::Type::TYPE_UINT32:
            case FieldDescriptor::Type::TYPE_SINT32:
            case FieldDescriptor::Type::TYPE_FIXED32:
            case FieldDescriptor::Type::TYPE_SFIXED32: {
                // JS type variant is number...
                fields_[pField->index()] = new NumberField(pField->index(), pField->camelcase_name(), refl->GetDouble(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_INT64:
            case FieldDescriptor::Type::TYPE_UINT64:
            case FieldDescriptor::Type::TYPE_SINT64:
            case FieldDescriptor::Type::TYPE_FIXED64:
            case FieldDescriptor::Type::TYPE_SFIXED64: {
                // JS type variant is number...
                fields_[pField->index()] = new NumberField(pField->index(), pField->camelcase_name(), refl->GetDouble(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_STRING: {
                // JS type variant is string...
                fields_[pField->index()] = new StringField(pField->index(), pField->camelcase_name(), refl->GetString(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_BOOL: {
                // JS type variant is boolean...
                fields_[pField->index()] = new BooleanField(pField->index(), pField->camelcase_name(), refl->GetBool(*msg, pField));
                break;
            }
            case FieldDescriptor::Type::TYPE_BYTES: {
                // JS type array buffer...
                auto str = refl->GetString(*msg, pField);
                uint8_t* buf = reinterpret_cast<uint8_t*>(&str[0]);
                fields_[pField->index()] = new ArrayBufferField(pField->index(), pField->camelcase_name(), buf, (size_t)str.length());
                break;
            }
            default: {
                throw MessageUnknownFieldTypeException();
                break;
            }
        }
        
        // Assign relevant information to the field
        bool hasField = refl->HasField(*msg, pField);
        fields_[pField->index()]->setHas(hasField);
    }
    
}

void Message::mergeObjectIntoProto(jsi::Runtime& runtime, google::protobuf::Message *protoMsg, jsi::Object& obj) {
    
    auto refl = protoMsg->GetReflection();
    std::vector<const google::protobuf::FieldDescriptor*> protoFields;
    refl->ListFields(*protoMsg, &protoFields);
    
    // Go over every proto message field and find the corresponding value in the js object
    for (auto f_it = protoFields.begin(); f_it != protoFields.end(); f_it++) {
        const google::protobuf::FieldDescriptor* pField = *f_it;
        
        // Get jsi value of the js object property name corresponding to the field name
        jsi::Value jsVal = obj.getProperty(runtime, jsi::PropNameID::forUtf8(runtime, pField->camelcase_name()));
        
        // Set field value on the passed proto message, based on the JS type of the property
        if (jsVal.isString()) {
            refl->SetString(protoMsg, pField, jsVal.getString(runtime).utf8(runtime));
        }
        else if (jsVal.isNumber()) {
            refl->SetDouble(protoMsg, pField, jsVal.getNumber());
        }
        else if (jsVal.isBool()) {
            refl->SetBool(protoMsg, pField, jsVal.getBool());
        }
        else if (jsVal.isObject() && jsVal.getObject(runtime).isArrayBuffer(runtime)) {
            auto arrBuf = jsVal.getObject(runtime).getArrayBuffer(runtime);
            std::string bufStr(reinterpret_cast<const char*>(std::move(arrBuf.data(runtime))), arrBuf.size(runtime));
            refl->SetString(protoMsg, pField, bufStr);
        }
    }
}

jsi::Value Message::get(jsi::Runtime& runtime, const jsi::PropNameID& name) {
    std::string pName = name.utf8(runtime);
    
    for(auto it = fields_.begin(); it != fields_.end(); it++) {
        Field* f = it->second;
        
        // Convert name to PascalCase of field
        std::string name = f->getName();
        name[0] = ascii_toupper(name[0]);
        
        if (pName == name) {
            return f->getValue(runtime);
        }
        
        // Check if a getter is requested. I.e "getUsername" or "getPassword"
        /*std::string getterName = "get" + name;
        if (mName == getterName) {
            return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, getterName), 0, [f](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                
                // Return the JS value of the field
                return f->getValue(runtime);
            });;
        }
        
        // Check if a setter is requested. I.e "setUsername" or "setPassword"
        std::string setterName = "set" + name;
        if (mName == setterName) {
            return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, setterName), 1, [f](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                
                // Set the JS value for the field.
                f->setValue(runtime, &args[0]);
                return jsi::Value::undefined();
            });;
        }
        
        // Check if a "has" method is requested. I.e "hasUsername" or sat "hasPassword"
        std::string hasMethodName = "has" + name;
        if (mName == hasMethodName) {
            return jsi::Function::createFromHostFunction(runtime, jsi::PropNameID::forAscii(runtime, setterName), 1, [f](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                
                // Get the "has field" state.
                return jsi::Value(f->has());
            });;
        }*/
    }
    
    
    return jsi::Value::undefined();
}

void Message::set(jsi::Runtime&, const jsi::PropNameID& name, const jsi::Value& value) {}

std::vector<jsi::PropNameID> Message::getPropertyNames(jsi::Runtime& runtime) {
    
    std::vector<jsi::PropNameID> props;
    
    // Loop through all fields to add every method for each field to the final list of properties...
    for(auto it = fields_.begin(); it != fields_.end(); it++) {
        Field* f = it->second;
        
        // Convert name to PascalCase of field
        std::string name = f->getName();
        name[0] = ascii_toupper(name[0]);
        
        // Add all method names to property name list
        std::string getterName = "get" + name;
        std::string setterName = "set" + name;
        std::string hasMethodName = "has" + name;
        props.push_back(jsi::PropNameID::forUtf8(runtime, getterName));
        props.push_back(jsi::PropNameID::forUtf8(runtime, setterName));
        props.push_back(jsi::PropNameID::forUtf8(runtime, hasMethodName));
    }
    
    return props;
}

}}}
