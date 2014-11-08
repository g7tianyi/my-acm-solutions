#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;


int main() {
   
    string s;
    cin>>s;
     
    int flag = 0;
    
    int count[26];
    memset(count, 0, sizeof(count));
    std::string::const_iterator pos;
    for (pos = s.begin(); pos != s.end(); ++pos) {
        ++count[*pos - 'a'];
    }
    
    int odd_char_count = 0;
    for (int i = 0; i < 26; ++i) {
        odd_char_count += (count[i] & 0x1u);
    }
    
    flag = odd_char_count < 2 ? 1 : 0;
    
    // Assign Flag a value of 0 or 1 depending on whether or not you find what you are looking for, in the given string 
    if(flag==0)
        cout<<"NO";
    else
        cout<<"YES";
    return 0;
}

