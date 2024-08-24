#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void resetarr(int* arr){
        for(int i = 0; i < 256; i++){
            arr[i] = 0;
        }
    }

    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        if(s.length() == 1) return 1;
        if(s.length() == 0) return 0;
        for(int i = 0; i < s.length() ; i++){
            int count = 0;
            int arr[256];
            resetarr(arr);
            for(int j = i; j < s.length() ; j++){
                arr[(int)s[j]]++;
                if(arr[(int)s[j]] > 1){
                    ans = max(count, ans);
                    break;
                }else count++;
            }
            
            ans = max(ans, count);
        }
        return ans;
    }
};