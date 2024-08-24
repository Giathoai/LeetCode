#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

void addElement(int*& arr, int n, int val, int index) {
    int* temp = new int[n + 1];
    for(int i = n + 1; i > index; i--){
        temp[i] = arr[i - 1];
    }
    for(int i = 0;  i < index; i++){
        temp[i] = arr[i];
    }
    temp[index] =  val;
    delete[] arr;
    arr = new int[n + 1];
    arr = temp;
}


int main()
{
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int val, index;
    cin >> val >> index;
    addElement(arr, n, val, index);
    for(int i = 0; i < n + 1; i++){
        cout << arr[i] << " ";
    }


    return 0;
}