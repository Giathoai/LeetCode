class Solution {
public:
    string reverseWords(string s) {
        char arr[10000];
        for(int i = 0; i < s.length(); i++){
            arr[i] = s[i];
        }
        arr[s.length()] = '\0';

        char* token = strtok(arr, " "); 
        char ans[10000] = ""; 

        while(token != NULL){
            char temp[10000];
            strcpy(temp, token);
            strcat(temp, " ");
            strcat(temp, ans);
            strcpy(ans, temp);
        
            token = strtok(NULL, " ");
        }
        if (strlen(ans) > 0 && ans[strlen(ans) - 1] == ' ') {
            ans[strlen(ans) - 1] = '\0';
        }
    return string(ans);
    }
};