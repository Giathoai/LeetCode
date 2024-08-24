#include<bits/stdc++.h>

using namespace std;


void test1(){
int G[20][20];
int G2[20][20];
int BFValue[20];
int BFPrev[20];
fin.open("inMat1.txt");
int n=8;
for(int i=0;i<n;i++){
BFValue[i]=-1;
BFPrev[i]=-1;
for(int j=0;j<n;j++){
fin>>G[i][j];
}
}

fin.open("inMat2.txt");
for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
fin>>G2[i][j];
}
}
for(int i=0;i<n;i++){
if(i%2)
BF(G,n,'D',BFValue,BFPrev);
else
BF(G2,n,'D',BFValue,BFPrev);
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
fin.close();
//--------------------------
}

void test2(){
int G[20][20];
int BFValue[20];
int BFPrev[20];
fin.open("inMat2.txt");
int n=8;
for(int i=0;i<n;i++){
BFValue[i]=-1;
BFPrev[i]=-1;
for(int j=0;j<n;j++){
fin>>G[i][j];
}
}
cout<<BF_Path(G,n,'A','E');
fin.close();
}

int main(){
    return 0
}