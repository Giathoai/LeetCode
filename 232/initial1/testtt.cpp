#include <iostream>
#include <cstring>

using namespace std;

// Hàm sắp xếp mảng các con trỏ chuỗi
void bubbleSort(char* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sử dụng strcmp để so sánh chuỗi
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Hoán đổi các con trỏ nếu chuỗi j lớn hơn chuỗi j+1
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int tansuat(char* arr[], int n, char* P[]){
    int mang[n] = {1};
    int dem = 1;
    char* hientai = arr[0];
    for(int i = 1; i < n; i++){
        mang[i] = 1;
        if(hientai == arr[i]){
            dem++;
        }else{
            mang[i - 1] = dem;
            dem = 1;
            hientai = arr[i];
        }
    }
    int max = mang[0];
    char* maxstring = arr[0];
    for(int i = 0; i < n; i++){
        if(max < mang[i]){
            max = mang[i];
            maxstring = arr[i];
        }
        if(max == mang[i] && strlen(maxstring) < strlen(arr[i])){
            maxstring = arr[i];
        }
    } 
    for(int i = 0; i < n; i++){
        if(strcmp(maxstring, P[i]) == 0){
            return i;
        }
    }
    return 0;
}

int array_size(const char **arr) {
    int size = 0;
    while (arr[size] != NULL) {
        size++;
    }
    return size;
}


int main() {
    const char* arr_pwds[7] = {"123xyz", "pink#pink", "pink123", "xxxx@xxxx", "pink#pink", "pink123", "pink123"};
     int n = 0;
    
   while (arr_pwds[n][0] != '\0') {
        n++;
        cout << n << endl;
        cout << sizeof(arr_pwds[n]) << endl;
    }
    
 
    const char* arr1[n] = {};
    
    for(int i = 0; i < n; i++){
        arr1[i] = arr_pwds[i];
    }
    cout << n << endl;
    cout << "Mảng sau khi sắp xếp:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << endl;
    }

    bubbleSort(const_cast<char**>(arr1), n); // Ép kiểu từ const char* sang char* để truyền vào hàm bubbleSort

    cout << "Mảng sau khi sắp xếp:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << endl;
    }

    cout << tansuat(const_cast<char**>(arr1), n, const_cast<char**>(arr_pwds));
    return 0;
}