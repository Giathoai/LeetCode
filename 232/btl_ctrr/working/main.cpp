#include "tsm.h"
#include <iostream>
#include "bellman.h"

using namespace std;
int main()
{
    int G[20][20] = {{0, 72, 89, 77, 2, 58, 13, 69},
                     {77, 0, 69, 31, 57, 93, 83, 48},
                     {52, 21, 0, 62, 8, 77, 32, 14},
                     {33, 1, 40, 0, 72, 99, 72, 59},
                     {89, 24, 1, 61, 0, 12, 78, 63},
                     {36, 91, 98, 79, 26, 0, 28, 1},
                     {18, 77, 49, 36, 98, 77, 0, 45},
                     {75, 9, 59, 7, 77, 65, 45, 0}};

    int BFValue[20];
    int BFPrev[20];

    int n = 8;

    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

///////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Bellman-Ford calculation: " << endl;
    for (int i = 0; i < n; i++)
    {

        BF(G, n, 'D', BFValue, BFPrev);

        cout << "step" << i + 1 << ":" << endl;

        for (int j = 0; j < n; j++)
        {
            cout << BFValue[j] << " ";
        }
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << BFPrev[j] << " ";
        }
        cout << endl;
    }

///////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Bellman-Ford path: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << BF_Path(G, n, char(i + 'A'), char(j + 'A')) << endl;
        }
    }


///////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Travelling sale man path calculation: " << endl;
    cout << Traveling(G, n, 'H') << endl;

    return 0;

     /*USE g++ -o main main.cpp bellman.cpp tsm.cpp -I . -std=c++11;./main TO RUN*/
}