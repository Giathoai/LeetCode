#include <bits/stdc++.h>

using namespace std;



void quaylui(int i, int m, int check[], int arr[], int n){
    
    for(int j = arr[i]; j <= m; j = j + arr[i]){
        if(check[j] == 1){
            check[j] = 0;
            if(i == n){
                
            }else{
                quaylui((i + 1), m, check, arr, n);
            }
            
        }
    }
}

int main(){
    int n, m;
    int arr[n];
    int check[m];
    memset(check, 1, sizeof(check));
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }



return 0;
}