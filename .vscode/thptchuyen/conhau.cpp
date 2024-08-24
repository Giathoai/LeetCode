#include <bits/stdc++.h>

using namespace std;

int col[10], d1[10], d2[10], X[10];

void quaylui(int i, int arr[9][9], int &max){
    
    int temp = 0;
    for(int j = 1; j <= 8; j++){
        
        if(col[j] == 0 && d1[i - j + 8] == 0 && d2[i + j - 1] == 0){
            X[i] = j;
            col[j] = d1[i - j + 8] = d2[i + j - 1] = 1;
            if(i == 8){
                for(int z = 1; z <= 8; z++){
                    temp = temp + arr[z][X[z]];
                
                }
                if (max < temp){
                    max = temp;
                }
            }else{
                quaylui((i + 1),arr, max);
            }
            col[j] = d1[i - j + 8] = d2[i + j -1] = 0;
        }
    }
}

int main(){
    int arr[9][9];
    int max = 0;
    memset(col, 0, sizeof(col));
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));
    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            cin >> arr[i][j];
        }
    }
    quaylui(1, arr, max);
    cout << max;

    return 0;
}