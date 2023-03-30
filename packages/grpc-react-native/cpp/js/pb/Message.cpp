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



#define PARSE_FIELD_TYPE_CASE_BASE(UPPERCASE, JS_TYPE, BODY)   \
    case FieldDescriptor::Type::TYPE_##UPPERCASE: {      \
        BODY                                             \
        break;                                           \
    }
#define PARSED_FIELD_TYPE_CASE_BODY_SINGULAR(JS_TYPE, PASCALCASE)          \
    fields_[pField->index()] = new JS_TYPE##Field(pField->index(), pField->camelcase_name(), refl->Get##PASCALCASE(msg, pField));
#define PARSED_FIELD_TYPE_CASE_BODY_REPEATED(JS_TYPE, PASCALCASE, INDEXVAR)   \
    repeatedField->push(JS_TYPE##Value(refl->GetRepeated##PASCALCASE(msg, pField, INDEXVAR)));
#define PARSED_FIELD_TYPE_CASE_SINGULAR(UPPERCASE, JS_TYPE, PASCALCASE)    \
    PARSE_FIELD_TYPE_CASE_BASE(UPPERCASE, JS_TYPE, PARSED_FIELD_TYPE_CASE_BODY_SINGULAR(JS_TYPE, PASCALCASE))
#define PARSED_FIELD_TYPE_CASE_REPEATED(UPPERCASE, JS_TYPE, PASCALCASE, INDEXVAR) \
    PARSE_FIELD_TYPE_CASE_BASE(UPPERCASE, JS_TYPE, PARSED_FIELD_TYPE_CASE_BODY_REPEATED(JS_TYPE, PASCALCASE, INDEXVAR))

Message::~Message() {
    for (auto field_ptr = fields_.begin(); field_ptr != fields_.end(); field_ptr++) {
        delete field_ptr->second;
    }
}

void Message::parseFromProto(jsi::Runtime& runtime, const google::protobuf::Message& msg) {
    
    // Find all of the fields in in the message
    auto refl = msg.GetReflection();
    std::vector<const google::protobuf::FieldDescriptor*> fields;
    refl->ListFields(msg, &fields);
    
    // Go through each of the fields and convert values to js kind.
    for (auto field_it = fields.begin(); field_it != fields.end(); field_it++) {
        const google::protobuf::FieldDescriptor* pField = *field_it;
        
        // If is repeated field, then loop over each value an add to the the repeated field map
        if (pField->is_repeated()) {
            ArrayField* repeatedField = new ArrayField(pField->index(), pField->camelcase_name());
            int fieldLen = refl->FieldSize(msg, pField);
            for(int i = 0; i < fieldLen; i++) {
                switch (pField->type()) {
                        // Number cases
                        PARSED_FIELD_TYPE_CASE_REPEATED(DOUBLE, Number, Double, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(FLOAT, Number, Float, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(INT32, Number, Int32, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(INT64, Number, Int64, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(UINT32, Number, UInt32, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(UINT64, Number, UInt64, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(SINT32, Number, Int32, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(SINT64, Number, Int64, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(FIXED32, Number, UInt64, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(FIXED64, Number, UInt64, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(SFIXED32, Number, Int32, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(SFIXED64, Number, Int64, i)
                        
                        // Other cases...
                        PARSED_FIELD_TYPE_CASE_REPEATED(STRING, String, String, i)
                        PARSED_FIELD_TYPE_CASE_REPEATED(BOOL, Boolean, Bool, i)
                        
                        // Special cases...
                    case FieldDescriptor::Type::TYPE_BYTES: {
                        // JS type array buffer...
                        auto str = refl->GetRepeatedString(msg, pField, i);
                        uint8_t* buf = reinterpret_cast<uint8_t*>(&str[0]);
                        repeatedField->push(ArrayBufferValue(buf, (size_t)str.length()));
                        break;
                    }
                    case FieldDescriptor::Type::TYPE_ENUM: {
                        // Simply use a string value when dealing with enums
                        const EnumValueDescriptor* enumVal = refl->GetRepeatedEnum(msg, pField, i);
                        repeatedField->push(StringValue(enumVal->name()));
                        break;
                    }
                    case FieldDescriptor::Type::TYPE_MESSAGE: {
                        // Transform protobuf message into 
                        const google::protobuf::Message& msgVal = refl->GetRepeatedMessage(msg, pField, i);
                        
                        // Create host object representation of protobuf message
                        std::shared_ptr<grpcrn::js::pb::Message> pbMsg;
                        pbMsg->parseFromProto(runtime, msgVal);
                        
                        // Create js object value from representation
                        jsi::Object msgObj =  jsi::Object::createFromHostObject(runtime, pbMsg);
                        repeatedField->push(ObjectValue(msgObj));
                        break;
                    }
                    default: {
                        throw MessageUnknownFieldTypeException();
                        break;
                    }
                        
                }
                
            }
            
            // Add index to map
            fields_[pField->index()] = std::move(repeatedField);
            continue;
        }
        
        
        switch (pField->type()) {
                // Number cases
                PARSED_FIELD_TYPE_CASE_SINGULAR(DOUBLE, Number, Double)
                PARSED_FIELD_TYPE_CASE_SINGULAR(FLOAT, Number, Float)
                PARSED_FIELD_TYPE_CASE_SINGULAR(INT32, Number, Int32)
                PARSED_FIELD_TYPE_CASE_SINGULAR(INT64, Number, Int64)
                PARSED_FIELD_TYPE_CASE_SINGULAR(UINT32, Number, UInt32)
                PARSED_FIELD_TYPE_CASE_SINGULAR(UINT64, Number, UInt64)
                PARSED_FIELD_TYPE_CASE_SINGULAR(SINT32, Number, Int32)
                PARSED_FIELD_TYPE_CASE_SINGULAR(SINT64, Number, Int64)
                PARSED_FIELD_TYPE_CASE_SINGULAR(FIXED32, Number, UInt64)
                PARSED_FIELD_TYPE_CASE_SINGULAR(FIXED64, Number, UInt64)
                PARSED_FIELD_TYPE_CASE_SINGULAR(SFIXED32, Number, Int32)
                PARSED_FIELD_TYPE_CASE_SINGULAR(SFIXED64, Number, Int64)
                
                // Other cases...
                PARSED_FIELD_TYPE_CASE_SINGULAR(STRING, String, String)
                PARSED_FIELD_TYPE_CASE_SINGULAR(BOOL, Boolean, Bool)
                
                // Special cases...
            case FieldDescriptor::Type::TYPE_BYTES: {
                // JS type array buffer...
                auto str = refl->GetString(msg, pField);
                uint8_t* buf = reinterpret_cast<uint8_t*>(&str[0]);
                fields_[pField->index()] = new ArrayBufferField(pField->index(), pField->camelcase_name(), buf, (size_t)str.length());
                break;
            }
            case FieldDescriptor::Type::TYPE_ENUM: {
                // Simply use a string value when dealing with enums
                const EnumValueDescriptor* enumVal = refl->GetEnum(msg, pField);
                fields_[pField->index()] = new StringField(pField->index(), pField->camelcase_name(), enumVal->name());
                break;
            }
            case FieldDescriptor::Type::TYPE_MESSAGE: {
                // Transform protobuf message into
                const google::protobuf::Message& msgVal = refl->GetMessage(msg, pField);
                
                // Create host object representation of protobuf message
                std::shared_ptr<grpcrn::js::pb::Message> pbMsg;
                pbMsg->parseFromProto(runtime, msgVal);
                
                // Create js object value from representation
                jsi::Object msgObj =  jsi::Object::createFromHostObject(runtime, pbMsg);
                fields_[pField->index()] = new ObjectField(pField->index(), pField->camelcase_name(), msgObj);
                break;
            }
            default: {
                throw MessageUnknownFieldTypeException();
                break;
            }
        }
        
        // Assign relevant information to the field
        fields_[pField->index()]->setHas(refl->HasField(msg, pField));
    }
    
}

std::string Message::fieldTypeAsString(FieldDescriptor::Type type) {
    // Initialize field type enum map
    if (fieldTypeMap_.size() == 0) {
        fieldTypeMap_[FieldDescriptor::Type::TYPE_DOUBLE] = "Double";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_FLOAT] = "Float";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_INT32] = "Int32";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_INT64] = "Int64";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_UINT32] = "UInt32";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_UINT64] = "UInt64";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_SINT32] = "SInt32";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_SINT64] = "SInt64";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_FIXED32] = "UInt32";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_FIXED64] = "UInt64";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_SFIXED32] = "Int32";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_SFIXED64] = "Int64";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_BOOL] = "Bool";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_BYTES] = "Bytes";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_STRING] = "String";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_ENUM] = "Enum";
        fieldTypeMap_[FieldDescriptor::Type::TYPE_MESSAGE] = "Message";
    }
    
    return fieldTypeMap_[type];
}


/**
 * Static: Merge a JS Object (given in jsi::Object format) into a protobuf message
 * Useful when filling out request data in unary calls.
 */
void Message::mergeObjectIntoProto(jsi::Runtime& runtime, google::protobuf::Message* protoMsg, jsi::Object& obj) {
    
    auto refl = protoMsg->GetReflection();
    std::vector<const google::protobuf::FieldDescriptor*> protoFields;
    refl->ListFields(*protoMsg, &protoFields);
    
    // Go over every proto message field and find the corresponding value in the js object
    for (auto f_it = protoFields.begin(); f_it != protoFields.end(); f_it++) {
        const google::protobuf::FieldDescriptor* pField = *f_it;
        
        // Get jsi value of the js object property name corresponding to the field name
        jsi::Value jsVal = obj.getProperty(runtime, jsi::PropNameID::forUtf8(runtime, pField->camelcase_name()));
        
        if (jsVal.isString()) {
            // STRING
            
            if (pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "string", protobufType);
            }
            
            auto str = jsVal.getString(runtime).utf8(runtime);
            switch (pField->type()) {
                case FieldDescriptor::Type::TYPE_ENUM: {
                    auto enumVal = protoMsg->GetDescriptor()->FindEnumValueByName(str);
                    refl->SetEnum(protoMsg, pField, enumVal);
                    break;
                }
                case FieldDescriptor::Type::TYPE_STRING: {
                    refl->SetString(protoMsg, pField, str);
                    break;
                }
                default: {
                    throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "string", Message::fieldTypeAsString(pField->type()));
                    break;
                }
            }
        }
        else if (jsVal.isNumber()) {
            if (pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "number", protobufType);
            }
            
            double num = jsVal.getNumber();
            
            switch (pField->type()) {
                case FieldDescriptor::Type::TYPE_DOUBLE: {
                    refl->SetDouble(protoMsg, pField, num);
                    break;
                }
                case FieldDescriptor::Type::TYPE_FLOAT: {
                    refl->SetFloat(protoMsg, pField, static_cast<float>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_INT32: {
                    refl->SetInt32(protoMsg, pField, static_cast<int32_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_INT64: {
                    refl->SetInt64(protoMsg, pField, static_cast<int64_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_UINT32: {
                    refl->SetUInt32(protoMsg, pField, static_cast<uint32_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_UINT64: {
                    refl->SetUInt64(protoMsg, pField, static_cast<uint64_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_SINT32: {
                    refl->SetInt32(protoMsg, pField, static_cast<int32_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_SINT64: {
                    refl->SetInt64(protoMsg, pField, static_cast<int64_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_FIXED32: {
                    refl->SetUInt32(protoMsg, pField, static_cast<uint32_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_FIXED64: {
                    refl->SetUInt64(protoMsg, pField, static_cast<uint64_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_SFIXED32: {
                    refl->SetUInt64(protoMsg, pField, static_cast<int32_t>(num));
                    break;
                }
                case FieldDescriptor::Type::TYPE_SFIXED64: {
                    refl->SetUInt64(protoMsg, pField, static_cast<int64_t>(num));
                    break;
                }
                default: {
                    throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "number", Message::fieldTypeAsString(pField->type()));
                    break;
                }
            }
        }
        else if (jsVal.isBool()) {
            if (pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "boolean", protobufType);
            }
            refl->SetBool(protoMsg, pField, jsVal.getBool());
        }
        else if (jsVal.isObject() && jsVal.getObject(runtime).isArrayBuffer(runtime)) {
            // ARRAY BUFFER
    
            if (pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "ArrayBuffer", protobufType);
            }
            if (pField->type() != FieldDescriptor::Type::TYPE_BYTES) {
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "ArrayBuffer", Message::fieldTypeAsString(pField->type()));
            }
            
            auto arrBuf = jsVal.getObject(runtime).getArrayBuffer(runtime);
            std::string bufStr(reinterpret_cast<const char*>(std::move(arrBuf.data(runtime))), arrBuf.size(runtime));
            refl->SetString(protoMsg, pField, bufStr);
        }
        else if (jsVal.isObject() && jsVal.getObject(runtime).isArray(runtime)) {
            // ARRAY
            
            if (!pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("non-repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "array", protobufType);
            }
            auto arr = jsVal.getObject(runtime).getArray(runtime);
            
            for (int i = 0; i < arr.size(runtime); i++) {
                auto val = arr.getValueAtIndex(runtime, i);
                
                refl->SetRepeatedFloat(protoMsg, pField, i, 1.0f);
            }
        }
        else if (jsVal.isObject() && !jsVal.getObject(runtime).isArray(runtime) && !jsVal.getObject(runtime).isFunction(runtime)) {
            // PLAIN OBJECT
            
            if (!pField->is_repeated()) {
                auto protobufType = grpcrn::utils::Strings::format("non-repeated %s", Message::fieldTypeAsString(pField->type()));
                throw IncompatibleFieldSetValueException(runtime, pField->camelcase_name(), "object", protobufType);
            }
        }
    }
}

jsi::Value Message::get(jsi::Runtime& runtime, const jsi::PropNameID& propertyName) {
    std::string pName = propertyName.utf8(runtime);
    
    for(auto it = fields_.begin(); it != fields_.end(); it++) {
        Field* field = it->second;
        
        std::string fieldName = field->getName();
        if (pName == fieldName) {
            return field->getValue().get(runtime);
        }
    }
    
    return jsi::Value::undefined();
}

void Message::set(jsi::Runtime& runtime, const jsi::PropNameID& propertyName, const jsi::Value& value) {
    std::string pName = propertyName.utf8(runtime);
    
    for(auto it = fields_.begin(); it != fields_.end(); it++) {
        Field* field = it->second;
        
        std::string fieldName = field->getName();
        if (pName == fieldName) {
            field->setHas(!value.isUndefined() && !value.isNull());
            field->getValue().set(runtime, value);
            break;
        }
    }
}

std::vector<jsi::PropNameID> Message::getPropertyNames(jsi::Runtime& runtime) {
    
    std::vector<jsi::PropNameID> props;
    
    // Loop through all fields to add every method for each field to the final list of properties...
    for(auto it = fields_.begin(); it != fields_.end(); it++) {
        Field* field = it->second;
        props.push_back(jsi::PropNameID::forUtf8(runtime, field->getName()));
    }
    
    return props;
}

}}}
