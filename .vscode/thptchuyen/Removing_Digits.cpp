#include <iostream>
#include <math.h>
#include <vector>   

using namespace std;



int maxdigit(int x){
    int maxdigit = 0;
    while(x > 0){
        int temp = x % 10;
        x = x / 10;
        if(maxdigit < temp){
            maxdigit = temp;
        }
    }
    return maxdigit;
}

int main() {
  //  vector<int>dp;
    int n;
    cin >> n;
  //  dp[0] = n;
    if(n == 0){
        return 0;
    }
    int count = 0;
    while(n > 0){
        n -= maxdigit(n);
        count++;
    }





    cout << count;
  //  cout << dp.size() - 1;
    return 0;
}