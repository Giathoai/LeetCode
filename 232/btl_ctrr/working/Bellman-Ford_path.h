#include<bits/stdc++.h>
#include <algorithm>

using namespace std;


void BF(int graph[][20], int n, char startVertex, int* BFValue, int* BFPrev){
    int startNode = startVertex - 'A';
    for(int i = 0; i < n; i++){
        BFValue[i] = 2147483647;
        BFPrev[i] = -1;
    }
    BFValue[startNode] = 0;
    for(int i = 0; i < n - 1; i++){
        for(int u = 0; u < n; u++){
            for(int v = 0; v < n; v++){
                if(graph[u][v] != 0 && BFValue[u] != 2147483647 && BFValue[u] + graph[u][v] < BFValue[v]){
                    BFValue[v] = BFValue[u] + graph[u][v];
                    BFPrev[v] = u;
                }
            }
        }            
    }
}

string BF_Path(int graph[][20], int n, char startVertex, char endVertex){
    int BFValue[20];
    int BFPrev[20];
    for(int i=0;i<n;i++){
        BFValue[i]=-1;
        BFPrev[i]=-1;
    }    
    BF(graph,n,startVertex, BFValue, BFPrev);
    int i = endVertex - 'A';
    string ans ="";
    while(BFPrev[i] != -1){
        ans += (i + 'A');
        ans += " ";
        i = BFPrev[i];
    }
    ans += startVertex;
    reverse(ans.begin(), ans.end());
    return ans;
}

