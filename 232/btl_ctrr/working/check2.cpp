#include <bits/stdc++.h>

using namespace std;


void reset(int* arr, int n){
    for (int i = 0; i < n; i++){
        if (arr[i] == 2147483647){
            arr[i] = -1;
        }
    }
}

void BF(int graph[20][20], int num_vertices, char start_vertex, int* BFValue, int* BFPrev){
    int start_index = start_vertex - 'A';
    const int INF = 2147483647;
    int min = INF;
    bool flag;
    long long arr[26];
    for (int i = 0; i < num_vertices; i++)
    {
        flag = (BFValue[i] == -1) ? 1 : flag;
        BFValue[i] = (BFValue[i] == -1) ? INF : BFValue[i];
        if(flag) BFValue[start_index] = 0;
    }
    copy(BFValue, BFValue + num_vertices, arr);
    for (int i = 0; i < num_vertices - 1; i++){
        for (int v = 0; v < num_vertices; v++){
            for (int u = num_vertices - 1; u >= 0; u--){
                if (arr[u] + graph[u][v] < BFValue[v] && graph[u][v] > 0){
                    min = arr[u] + graph[u][v];
                    BFPrev[v] = u;
                }
            }
            BFValue[v] = (min == INF) ? BFValue[v] : min;
            min = INF;
        }
    }
        for (int i = 0; i < num_vertices; i++){
            if (BFValue[i] == INF){
                BFValue[i] = -1;
            }
        }
}

const int INF = 1e6;

void pre(int* BFValue,int* arr, int n){
    for (int i = 0; i < n; i++) {
        if (BFValue[i] == -1) {
            BFValue[i] = INF;
        }
        arr[i] = BFValue[i];
    }
}
void BF(int c[20][20], int n, char first, int BFValue[], int BFPrev[]) {
    if(BFValue[first - 'A'] == -1) BFValue[first - 'A'] = 0;
    int Arr[20];
    pre(BFValue, Arr, n);
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (c[u][v] != 0 &&  Arr[u] + c[u][v] < BFValue[v] ) {
                BFValue[v] = Arr[u] + c[u][v];
                BFPrev[v] = u;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (BFValue[i] == INF) BFValue[i] = -1;
    }
}