#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;
int main()
{
    float n;
    int p, no, a;
    cin >> a;
    p = 0;
    no = 0;
    for(int i = 0; i < a; i++ ){
        cin >> n;
        if(n >= 0){
            p++;
        }else{
            no++;
        }
    }
    cout << p << ' ' << no;
}