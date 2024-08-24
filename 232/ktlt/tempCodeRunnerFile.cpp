#include <bits/stdc++.h>

using namespace std;

#define div(a,b) a / b
void func(int a){
    while(a){
        a--;
        cout << a;
    }
    }
class A {
public:
void printLn() {
cout << "Class_A";
}
};
class B : public A {
public:
void printLn() {
cout << "Class_B";
}
};
int sum(int &a, int b) {
a += b;
return a;
}

int sum(int a[], int size) {
int s = 0;
if (size > 0) s = a[0] + sum(a + 1, size - 1);
else s = a[0];
return s;
}


int main() {
int arr[] = {1 ,2 ,3 ,4 ,5};
int a =sum(arr, 5);
cout << a;
}