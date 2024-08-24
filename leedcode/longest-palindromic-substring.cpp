#include <iostream>
#include <string>

using  namespace std;




class Solution {
public:
    string longestPalindrome(string s) {
    int maxlen = 1;
    int start = 0;
    for (int i = 0; i < s.length();) {
        int j = i, k = i;
        while (k < s.length() - 1 && s[k] == s[k + 1]) k++;
        i = k + 1;
        while (k < s.length() - 1 && j > 0 && s[k + 1] == s[j - 1]) {
            k++;
            j--;
        }
        if (maxlen < (k - j + 1)) {
            maxlen = k - j + 1;
            start = j;
        }
    }
    return s.substr(start, maxlen);
    }
};