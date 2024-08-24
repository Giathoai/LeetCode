#include<iostream>
#include<iomanip>
#include<stdlib.h>


using namespace std;
int main()
{
    int n;
    double x;
    cin >> n;
    cin >> x;
    float a, b;
    if (n == 0){
        a = 1;
        b = 1;
    }else if(n == 1){
        a = x;
        b = 1 / x;
    }
    else{
    for(int i = 2; i <= n; i++){
        x *= x;
     
    }
    b = 1 / x;
    }
    cout << setprecision(2) << fixed << a << " " << b;
    return 0;
    
}