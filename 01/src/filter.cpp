#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <filter.hpp>

namespace filter {
    std::string Filter(const std::string& comment) {
        const std::vector<char> banned = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        std::string ans = "";
        for (char c: comment) {
            if (std::find(banned.begin(), banned.end(), c) == banned.end()) {
                ans.push_back(c);
            }
        }
        return ans;
    }
}
