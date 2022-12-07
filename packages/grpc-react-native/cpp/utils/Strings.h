//
//  Strings.h
//  grpc-react-native
//
//  Created by Asger Nohns on 24/03/2022.
//

#ifndef grpcrn_utils_Strings_h
#define grpcrn_utils_Strings_h

#include <vector>
#include <string>

namespace grpcrn {
namespace utils {

class Strings {
public:
    static void split(std::string& subject, const char delimiter, std::vector<std::string> &out);
};

}
}

#endif /* grpcrn_utils_Strings_h */
