#include<bits/stdc++.h>
#include <algorithm>

using namespace std;


void BF(int graph[][20], int n, char startVertex, int* BFValue, int* BFPrev){

    int startNode = startVertex - 'A';
    BFValue[startNode] = 0;

    for(int i = 0; i < n; i++){
        if(BFValue[i] == -1){
            BFValue[i] = 2147483647;
        }
    }
    
    for(int v = 0; v < n; v++){
        for(int s = 0; s < n; s++){
            if(graph[s][v] != 0 && BFValue[s] != 2147483647 && BFValue[s] + graph[s][v] < BFValue[v]){
                BFValue[v] = BFValue[s] + graph[s][v];
                BFPrev[v] = s;
            }
        }
    }               
    //    string str;
    //    for(int i = 0, j = strlen(str); i < strlen(str), j >= 0; i++, j--){

    //    }
}




void BF(int graph[20][20], int num_vertices, char start_vertex, int BFValue[], int BFPrev[])
{

    int copyArr[20];
    const int INF = 1000000;

    for (int i = 0; i < num_vertices; i++)
    {
        if (BFValue[i] == -1)
        {
            BFValue[i] = INF;
        }
    }
    BFValue[start_vertex - 'A'] = 0;

    for (int i = 0; i < num_vertices; i++)
    {
        copyArr[i] = BFValue[i];
    }

    int min = INF;

    for (int i = 0; i < num_vertices - 1; i++)
    {
        for (int v = 0; v < num_vertices; v++)
        {
            for (int u = 0; u < num_vertices; u++)
            {
                if (copyArr[u] + graph[u][v] < BFValue[v])
                {
                    min = copyArr[u] + graph[u][v];
                    BFPrev[v] = u;
                }
            }
            if (min == INF)
                continue;
            else
            {
                BFValue[v] = min;
            }

            min = INF;
        }
    }
}

void BF(int graph[20][20], int num_vertices, char start_vertex, int BFValue[], int BFPrev[])
{
        for(int u = 0; u < n; u++){
            for(int v = 0; v < n; v++){
                if(graph[v][u] != 0 && BFValue[v] != 2147483647 && BFValue[v] + graph[v][u] < BFValue[u]){
                    BFValue[u] = BFValue[v] + graph[v][u];
                    BFPrev[u] = v;
                }
            }
        }  
}
int main(){
    int G[20][20];
    int G2[20][20];
    int BFValue[20];
    int BFPrev[20];
    int n=8;
    for(int i=0;i<n;i++){
         BFValue[i]=-1;
         BFPrev[i]=-1;
        for(int j=0;j<n;j++){
            cin >>G[i][j];
        }
    }


    // BF(G,n,'D',BFValue,BFPrev);
    // cout << endl;
    // for(int j=0;j<n;j++){
    //     cout<<BFValue[j]<<" ";
    // }

for(int i=0;i<n;i++){
if(i%2){
    cout << i << " ";
BF(G,n,'D',BFValue,BFPrev);
}
// else
// BF(G2,n,'D',BFValue,BFPrev);
cout<<"step"<<i<<":"<<endl;
for(int j=0;j<n;j++){
cout<<BFValue[j]<<" ";
}
cout<<endl;
for(int j=0;j<n;j++){
cout<<BFPrev[j]<<" ";
}
cout<<endl;
}
    return 0;
}