#include <iostream>
#include <string>

using namespace std;

int longestNonRepeatSubString(string s) {
    int n = s.length();
    if (n == 0) return 0; 

    int char_index[256];
    for (int i = 0; i < 256; i++) {
        char_index[i] = -1; 
    }

    int max_len = 0, start = 0;

    for (int i = 0; i < n; i++) {
        if (char_index[s[i]] >= start) { 
            start = char_index[s[i]] + 1; 
        }
        char_index[s[i]] = i;
        max_len = max(max_len, i - start + 1); 
    }
    
    return max_len;
}

int main()  {
    string s = "abc";
    
    cout << longestNonRepeatSubString(s);
    return 0;
}