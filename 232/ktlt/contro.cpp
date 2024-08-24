#include<bits/stdc++.h>
using namespace std;

int findMax(int *ptr, int n)
{

    int max = ptr[0];
    for (int i = 1; i < n; i++)
    {
        if (ptr[i] > max)
        {
            max = ptr[i];
        }
    }
    return max;
}

void reverse(int *ptr, int n)
{
    for(int i = 0; i < n / 2; i++)
    {
        swap(*(ptr + i), *(ptr + n - i - 1));
    }
    
}

bool isSymmetry(int *head, int *tail)
{
    while (head < tail)
    {
        if (*head != *tail)
        {
            return false;
        }
        head++;
        tail--;
    }
    return true;
}

int** insertCol(int**& matrix, int r, int c, int* colArr, int col) {
    int** temp = new int*[r];
    for(int i = 0; i < c + 1; i++){
        temp[i] = new int[c + 1];
    }
    for(int i = 0; i < r; i++){
        int k = 0;
        for(int j = 0; j < c + 1; j++){
            if(j != col){
                temp[i][k] = matrix[i][j];
                k++;
            }else{
                temp[i][k] = colArr[i];
                k++;
            }

        }
    }
    return temp;
}

bool deleteRow(int**& matrix, int r, int c, int row) {
    if(r == 1){
    delete[] matrix[0];
    matrix = nullptr;
    return 0;
    }


    int** temp = new int*[r - 1];
    for(int i = 0; i < r - 1; i++){
        temp[i] = new int[c];
    }
    int k = 0;
    for(int i = 0; i < r; i++){
        if(i != row){
            for(int j = 0; j < c; j++){
                temp[k][j] = matrix[i][j];
            }
            k++;
        }
    }
    for(int i = 0; i < r; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = temp;
    return matrix;
}

    

int main(){
int r, c;
cin >> r >> c;
int col;
cin >> col;
int* arr[] = {(1, 2, 3),
(4, 5, 6)};
int* colArr={(7, 8)};
insertCol(arr, r, c, colArr, 2);
cout << 
}
