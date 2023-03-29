//
//  Message.h
//  grpc-react-native
//
//  Created by Asger Nohns on 16/03/2022.
//

#ifndef grpcrn_js_pb_Message_h
#define grpcrn_js_pb_Message_h

#include <vector>
#include <map>

#include <jsi/jsi.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>


#include "Field.h"

namespace grpcrn {
namespace js {
namespace pb {
    
using namespace facebook;
using namespace google::protobuf;

class JSI_EXPORT Message: public jsi::HostObject {
public:
    
    // Proto/JSI object initialization methods
    /// Protobuf  initializer for message host object. This is used to communicate with js
    void parseFromProto(jsi::Runtime& runtime, const google::protobuf::Message& msg);
    
    // Implement host object methods for communicating with JS
    /// Defines which getters, setters etc. exists for each field of the original protobuf message, for the jsi runtime.
    jsi::Value get(jsi::Runtime&, const jsi::PropNameID& name) override;
    /// Should not be used. Please refer to the "setter" methods created in Messsage::get
    void set(jsi::Runtime&, const jsi::PropNameID& name, const jsi::Value& value) override;
    /// Returns all methods exposed by message. Depends on which protobuf message it represents, which produced the accessible fields.
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
    
    // MARK: - Static methods
    
    /// Takes a request protobuf and merges in values from a given js object, by the camelCased names of all the protobuf fields.
    static void mergeObjectIntoProto(jsi::Runtime& runtime, google::protobuf::Message* msg, jsi::Object& obj);
    static std::string fieldTypeAsString(FieldDescriptor::Type type);
private:
    
    // @TODO: Is a map here necessary?
    std::unordered_map<int, Field*> fields_;
    std::unordered_map<int, std::vector<Field*>> repeatedFields_;
    
    // MARK: - Static attributes

    static std::unordered_map<FieldDescriptor::Type, std::string> fieldTypeMap_;
};


class MessageUnknownFieldTypeException : public std::exception {
public:
    virtual const char* type() {
        return "Encountered unexpected field type when reading message. Field type either not support or malformed";
    }
};

}
}
}


#endif /* grpcrn_js_pb_Message_h */
