#include <iostream>
#include <bitset>
#include <climits>
#include <cstring>
#include <math.h>
#include <vector>   
#include <algorithm>
using namespace std;

int main() {
    int n,x;
    cin >> n >> x;
    int price[n];
    int pages[n];
    for(auto &i : price) cin >> i;

    for(int j = 0; j < n; j++) cin >> pages[j];


    int dp[n + 1][x + 1];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i][j] = 0;
        }
    }


    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x ; j++){
            dp[i][j] = dp[i - 1][j];
            if(j - price[i - 1] >= 0){
                dp[i][j] = max(dp[i][j],dp[i -1][j - price[i - 1]] + pages[i - 1]);
            }
        }
    }
   // for(auto &i : price) cout << " " << i;
   // for(auto &i : pages) cout << " " << i;
   
    cout << dp[n][x];
    return 0;
}