#include <iostream>
#include <math.h>
#include <vector>   

using namespace std;

int main() {
    int n;
    cin >> n;
    char cc;
    int arr[n][n];
    long long dp[n][n];


    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> cc;
            if(cc == '.'){
                arr[i][j] = 1;
            }else{
                arr[i][j] = 0;
            }
            dp[i][j] = 0;
        }
    }


    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        if(!arr[0][i]){
            break;
        }else{
            dp[0][i] = 1;
        }
    }


    for(int i = 0; i < n; i++){
        if(!arr[i][0]){
            break;
        }else{
            dp[i][0] = 1;
        }
    }


    for(int i = 1; i < n; i++){
        for(int j = 1; j < n ;j++){
            if(arr[i][j] == 1){
                (dp[i][j] = dp[i - 1][j] + dp[i][j -1]) %= (int)(1e9 + 7);
            }
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n ;j++){
           cout << dp[i][j] << " ";
        }
        cout << endl;
    }


    cout << dp[n - 1][n - 1] % (int)(1e9 + 7);
    return 0;
}