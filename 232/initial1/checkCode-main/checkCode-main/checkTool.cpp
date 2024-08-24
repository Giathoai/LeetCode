#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

int main()
{
    srand(time(NULL));
    int testSpace = 100;
    for (int iTest = 1; iTest <= testSpace; iTest++)
    {
        //file input
        std::ofstream inp("testcase.inp");
        //hp1 & hp2
        inp << rand() % 667 << " " << rand() % 667 << std::endl
        //exp1 & exp2
            << rand() % 601 << " " << rand() % 601 << std::endl
        //m1 & m2
            << rand() % 3001 << " " << rand () % 3001 << std::endl
        //e1 & e2 & e3
            << rand() % 100 << " " << rand () % 100 << " " << rand () % 100;
        inp.close();
        system("d:/working/cpp/sampleCode/sampleCode.exe");
        system("d:/working/cpp/yourAnswer/yourAnswer.exe");
        if (system("fc sampleCode.out yourAnswer.out") != 0)
        {
            std::cout << "Test " << iTest << "/" << testSpace << " incorrect!" << std::endl;
            return 0;
        }
        std::cout << "Test " << iTest << "/" << testSpace << " correct!" << std::endl;
    }
    std::cout << "ACCEPTED CODE!!!! <333";
    return 0;
}
