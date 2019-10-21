#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> brcg(unsigned int n) {
    if (n == 0) {
        vector<string> code;
        code.push_back("0");
        return code;
    }
    if (n == 1) {
        vector<string> code;
        code.push_back("0");
        code.push_back("1");
        return code;
    }
    vector<string> v1 = brcg(n - 1);
    v1.reserve(v1.size() << 1);
    vector<string> v2;
    v2.reserve(v1.size());
    reverse_copy(v1.begin(), v1.end(), back_inserter(v2));
    for (size_t i = 0; i < v1.size(); ++i) {
        v1[i] = "0" + v1[i];
        v2[i] = "1" + v2[i];
    }
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}