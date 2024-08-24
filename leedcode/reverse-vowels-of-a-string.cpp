int laNguyenAm(char kyTu) {
    kyTu = tolower(kyTu);
    if (kyTu == 'a' || kyTu == 'e' || kyTu == 'i' || kyTu == 'o' || kyTu == 'u') {
        return 1; 
    } else {
        return 0; 
    }
}

class Solution {
public:
    string reverseVowels(string s) {
        int i = 0;
        int j = s.length() - 1;
        while(i < j){
            if(!laNguyenAm(s[i])){
                i++;
            }
            if(!laNguyenAm(s[j])){
                j--;
            }
            if(laNguyenAm(s[i]) && laNguyenAm(s[j])){
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
                i++;
                j--;
            }
        }
        return s;
    }
};