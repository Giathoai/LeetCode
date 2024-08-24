#ifndef TSM_H
#define TSM_H

#include<iostream>
#include <algorithm>
using namespace std;

void tsm(int i, int n, int G[][20], bool* visited, int* X, int current_cost, int& bestcost, int* best_path, int cmin, int start);
string Traveling(int G[][20],int n,char start);

#endif //TSM_H