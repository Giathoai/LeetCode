#include<bits/stdc++.h>

using namespace std;

int dequy(int x, int n){
    if (x == 0) {
        return 1;
    }
    if (x < 0 || n < 1) {
        return 0;
    }
    int include = dequy(x - n * n, n - 1);
    int exclude = dequy(x, n - 1);

    return include + exclude;

}

int countWaySumOfSquare(int x)
{
    if (x <= 0) {
        return 0;
    }
	int n = (int)sqrt(x);
    int ans = 0;
    return dequy(x, n);
}


int main(){
    cout << countWaySumOfSquare(100);
}