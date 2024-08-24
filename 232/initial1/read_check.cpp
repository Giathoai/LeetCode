#include <fstream>
#include <string>
#include <iostream>
#include "study_in_pink1.h"
#include <vector>

fstream infile ("testcase01.txt");
fstream outfile ("ans01.txt");


using namespace std;

int main () {
    bool flag = true;
    vector <int> test;
    vector<int> vars (9);
    test.resize(10000,0);
    int count = 0;
    int temp;
    int count_2 = 0;
    int temp_2;
    while (outfile >> temp_2){
        test[count_2] = temp_2;
        count_2++;
    }
    count_2 = 0;
    while (infile >> temp) {
        vars[count] = temp;
        count++;
        if (count == 9) {
            int HP1 = vars[0], HP2=vars[1], EXP1= vars[2], EXP2= vars[3], M1= vars[4], M2= vars[5], E1= vars[6], E2= vars[7], E3= vars[8]; 
            int ans = firstMeet(EXP1,EXP2,E1) ;
            if (ans != test[count_2]){
                cout <<"Error at here: "<<"\n"
                    <<"EXP1: " <<EXP1<<" "
                    <<"EXP2: " <<EXP2<<" "
                    <<"E1: " <<E1<<"\n"
                    <<"Expected Output: "<< test[count_2]<<"\n"
                    <<"Actual Output: "<<ans<<"\n";
                    flag = false;
            }
            count_2++;
            count = 0;
    }
}
    if (flag) cout << "Success, no error was found at here !"<<"\n";
    system("pause");
    infile.close ();
    outfile.close();
  return 0;
}

