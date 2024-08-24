#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        int size = flowerbed.size();
        for(int i = 0; i < size; i++){
            if(flowerbed[max(0,i - 1)] == 0 && flowerbed[i] == 0 && flowerbed[min(size - 1, i + 1)] == 0){
                count++;
                flowerbed[i] = 1;
            }
        }
        if(count >= n) return 1;
        return 0;
    }
};