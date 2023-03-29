//
//  Message.h
//  grpc-react-native
//
//  Created by Asger Nohns on 28/03/2023.
//

#ifndef grpcrn_js_pb_ProtobufRegister_h
#define grpcrn_js_pb_ProtobufRegister_h

#include <map>
#include <string>
#include <google/protobuf/descriptor.h>

namespace grpcrn {
namespace js {
namespace pb {

class ProtobufRegister {
public: 
    static void registerProtobufs();

private:
    static std::map<std::string, google::protobuf::Reflection*> reflections_;
};  

} 
}
}

#endif /* grpcrn_js_pb_ProtobufRegister_h */
