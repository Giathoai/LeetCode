#ifndef BELLMAN_H
#define BELLMAN_H

#include<iostream>
#include <algorithm>
using namespace std;

void reset(int* arr, int n);
void BF(int graph[20][20], int num_vertices, char start_vertex, int* BFValue, int* BFPrev);
string BF_Path(int graph[20][20], int n, char startVertex, char endVertex);

#endif //BELL_NAM_H