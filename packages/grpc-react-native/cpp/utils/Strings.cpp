//
//  Strings.cpp
//  grpc-react-native
//
//  Created by Asger Nohns on 24/03/2022.
//

#include "Strings.h"

namespace grpcrn {
namespace utils {

void Strings::split(std::string& subject, const char delimiter, std::vector<std::string>& out) {
    size_t start;
    size_t end = 0;
    
    while ((start = subject.find_first_not_of(delimiter, end)) != std::string::npos)
    {
        end = subject.find(delimiter, start);
        out.push_back(subject.substr(start, end - start));
    }
}

}}
