#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;

        int i = 0, length = path.length();
        while (i < length) {
            while (path[i] == '/' && i < length) {
                i++;
            }
            if (i == length) {
                break;
            }

            int start = i;
            while (path[i] != '/' && i < length) {
                i++; //decide the end boundary
            }
            int end = i - 1;
            string subpath = path.substr(start, end - start + 1);
            if (subpath == "..") {
                if (stack.size() > 0) {
                    stack.pop_back();
                }
            } else if (subpath != ".") {
                stack.push_back(subpath);
            }
        }

        if (stack.empty()) {
            return "/";
        }

        string result;
        for (int i = 0; i < stack.size(); i++) {
            result += ("/" + stack[i]);
        }
        return result;
    }
};

Solution solu;

int main() {

    std::cout << solu.simplifyPath("/home/") << std::endl;
    std::cout << solu.simplifyPath("/a/./b/../../c/") << std::endl;

    return 0;
}

