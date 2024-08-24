#include "tsm.h"
#include <iostream>
#include "bellman.h"

using namespace std;
int main()
{
    int G[20][20] = {{0, 55, 34, 78, 91, 67, 12, 24},
               {55, 0, 48, 32, 19, 84, 60, 71},
               {34, 48, 0, 27, 73, 95, 44, 53},
               {78, 32, 27, 0, 85, 40, 66, 59},
               {91, 19, 73, 85, 0, 62, 47, 38},
               {67, 84, 95, 40, 62, 0, 23, 81},
               {12, 60, 44, 66, 47, 23, 0, 54},
               {24, 71, 53, 59, 38, 81, 54, 0}};

    int BFValue[20];
    int BFPrev[20];

    int n = 8;

    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

//__________________________________________________________________________________________________

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

//__________________________________________________________________________________________________

    cout << "Bellman-Ford path: " << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << BF_Path(G, n, char(i + 'A'), char(j + 'A')) << endl;
        }
    }


//__________________________________________________________________________________________________
    cout << "Travelling sale man path calculation: " << endl;
    cout << Traveling(G, n, 'H') << endl;

    return 0;

     /*USE g++ -o main main.cpp bellman.cpp tsm.cpp -I . -std=c++11;./main TO RUN*/
}