#include<bits/stdc++.h>

using namespace std;

void mostFrequentCharacter(char* str, char& res, int& freq) {
    int arr[26];
    for (int i = 0; i < 26; i++) {
        arr[i] = 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'a' && str[i] <= 'z'){
            arr[str[i] - 'a']++;
        }else if (str[i] >= 'A' && str[i] <= 'Z') {
            arr[str[i] - 'A']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (arr[i] > freq) {
            freq = arr[i];
            res = 'a' + i;
        }
    }
}

int main(){
int n;
cin >> n;
char* str = new char[n+1];
for(int i = 0; i < n; i++) cin >> str[i];
str[n] = 0;
char res = 0;
int freq = 0;
mostFrequentCharacter(str, res, freq);
cout << res << ' ' << freq;
delete[] str;
}