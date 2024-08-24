#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    int sqrt_n = static_cast<int>(sqrt(n));
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int specialCells(int arr[][1000], int row, int col) {
    int count = 0;  // Đếm số ô HN3

    // Tính tổng của từng hàng và cột
    vector<int> rowSum(row), colSum(col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            rowSum[i] += arr[i][j];
            colSum[j] += arr[i][j];
        }
    }

    // Kiểm tra các ô HN3
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int currRowSum = rowSum[i];  // Tổng hàng không bao gồm ô hiện tại
            int currColSum = colSum[j];  // Tổng cột không bao gồm ô hiện tại

            if (isPrime(currRowSum) && isPrime(currColSum)) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    int row, col;
    cout << "Nhap so hang va so cot: ";
    cin >> row >> col;

    int arr[1000][1000];
    cout << "Nhap cac phan tu cua mang: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> arr[i][j];
        }
    }

    int result = specialCells(arr, row, col);
    cout << "So o HN3 trong mang la: " << result << endl;

    return 0;
}