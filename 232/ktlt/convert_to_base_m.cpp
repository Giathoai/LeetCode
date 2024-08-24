#include <bits/stdc++.h>

using namespace std;


int convertToBase2(int decimal) {
    if (decimal == 0) return 0; // Handle the case when decimal is 0
    
    int ans = 0, i = 1;
    
    while (decimal != 0) {
        ans += (decimal % 2) * i;
        decimal /= 2;
        i *= 10;
    }
    
    return ans;
}
int convertToBase4(int decimal) {
    if (decimal == 0) return 0; // Handle the case when decimal is 0
    
    int ans = 0, i = 1;
    
    while (decimal != 0) {
        ans += (decimal % 4) * i;
        decimal /= 4;
        i *= 10;
    }
    
    return ans;
}

int convertToBase8(int decimal) { 
    if (decimal == 0) return 0; // Handle the case when decimal is 0
    
    int ans = 0, i = 1;
    
    while (decimal != 0) {
        ans += (decimal % 8) * i;
        decimal /= 8;
        i *= 10;
    }
    
    return ans;
}

int convertToBaseM(int n, int m = 2) {

    if(m == 2){
        return convertToBase2(n);
    }else if(m == 4){
        return convertToBase4(n);
    }else if(m == 8){
        return convertToBase8(n);
    }

    return 0;
}
int main(){
int n;
cin >> n;
cout << convertToBaseM(n, 4) << '\n';
cout << convertToBaseM(n, 8) << '\n';
cout << convertToBaseM(n);
}