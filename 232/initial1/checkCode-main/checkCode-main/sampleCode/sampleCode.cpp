#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//in-out function
void readFile(
    const std::string& filename,
    int& hp1,
    int& hp2,
    int& exp1,
    int& exp2,
    int& m1,
    int& m2,
    int& e1,
    int& e2,
    int& e3
);
void writeOutput(
    const std::string& filename,
    int& result1,
    int& result2,
    int& result3
);
//task function
int firstMeet(int & exp1, int & exp2, int e1);
int traceLuggage(int & hp1, int & exp1, int & m1, int e2);
int chaseTaxi(int & hp1, int & exp1, int & hp2, int & exp2, int e3);

//main()
int main() 
{
    int hp1, hp2, exp1, exp2, m1, m2, e1, e2, e3;   
    readFile("testcase.inp", hp1, hp2, exp1, exp2, m1, m2, e1, e2, e3);
    int result1 = firstMeet(exp1, exp2, e1),
        result2 = traceLuggage(hp1, exp1, m1, e2),
        result3 = chaseTaxi(hp1, exp2, hp2, exp2, e3);

    writeOutput("sampleCode.out", result1, result2, result3);
    return 0;
}


//Read file input
void readFile(
    const std::string& filename,
    int& hp1,
    int& hp2,
    int& exp1,
    int& exp2,
    int& m1,
    int& m2,
    int& e1,
    int& e2,
    int& e3
)
{
    std::ifstream inp(filename);
    inp >> hp1 >> hp2 >> exp1 >> exp2 >> m1 >> m2 >> e1 >> e2 >> e3;
}

//Output file
void writeOutput(
    const std::string& filename,
    int& result1,
    int& result2,
    int& result3
)
{
    std::ofstream out(filename);
    out << result1 << " " << result2 << " " << result3;
}

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) 
{
    if (e1 < 0 || e1 > 99) return -99;
    if (e1 <= 3) 
    {
        switch (e1)
        {
            case 3: exp2 += 74;
            case 2: exp2 += 30;
            case 1: exp2 += 16;
            case 0: exp2 += 29;
        }
        int d = e1*3 + exp1*7;
        if ((d)%2) exp1 -= std::floor(float(d/100.0));
        else exp1 += std::ceil(float(d/200.0));
        if (exp1 < 0) exp1 = 0;
        if (exp1 > 600) exp1 = 600;
        if (exp2 > 600) exp2 = 600;
    }
    else
    {
        if (e1 <= 19) exp2 += std::ceil(float(e1/4.0)) + 19;
        if (e1 > 19 && e1 <= 49) exp2 += std::ceil(float(e1/9.0)) + 21;
        if (e1 > 49 && e1 <= 65) exp2 += std::ceil(float(e1/16.0)) + 17;
        if (e1 > 65 && e1 <= 79) 
        {
            exp2 += std::ceil(float(e1/4.0)) + 19;
            if (exp2 > 200) exp2 += std::ceil(float(e1/9.0)) + 21;
        }
        if (e1 > 79) 
        {
            exp2 += std::ceil(float(e1/4.0)) + std::ceil(float(e1/9.0)) + 40;
            if (exp2 > 400) 
            {
                exp2 += std::ceil(float(e1/16.0)) + 17;
                exp2 = std::ceil(float(exp2*1.15));
            }
        }
        exp1 -= e1;
        if (exp1 < 0) exp1 = 0;
        if (exp2 > 600) exp2 = 600;
    }
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & hp1, int & exp1, int & m1, int e2) 
{
    if (e2 < 0 || e2 > 99) return -99;
    int p1 = 100, p2 = 100, p3 = 100, loopCount = 0;
    while (p1 == 100 && p2 == 100 && p3 == 100)
    {
        if (loopCount++) exp1 = std::ceil(float(exp1*0.75));

        //Road 1
        int n = sqrt(exp1);
        if (exp1 - n*n < (n+1)*(n+1) - exp1) p1 = 100;
        else p1 = std::ceil(float((exp1/double((n+1)*(n+1)) + 80)/1.23));
        //Road 2
        if (e2 % 2)
        {
            int fund = std::ceil(float(m1*0.5)), spent = 0, event = 2;
            while (spent < fund)
            {
                switch (event = ++event % 3)
                {
                    case 0: //event 1
                        if (hp1 < 200) 
                        {
                            hp1 = std::ceil(float(hp1*1.3)); 
                            m1 -= 150;
                            spent += 150;
                        }                       
                        else 
                        {
                            hp1 = std::ceil(float(hp1*1.1)); 
                            m1 -= 70;
                            spent +=70;
                        }
                        if (hp1 > 666) hp1 = 666;
                        if (m1 < 0) m1 = 0;
                        break;
                    case 1: //event 2
                        if (exp1 < 400) 
                        {
                            m1 -= 200;
                            spent += 200;
                        }
                        else 
                        {
                            m1 -= 120;
                            spent += 120;
                        }
                        exp1 = std::ceil(float(exp1*1.13));
                        if (exp1 > 600) exp1 = 600;
                        if (m1 < 0) m1 = 0;
                        break;
                    case 2: //event 3
                        if (exp1 < 300) 
                        {
                            m1 -= 100;
                            spent += 100;
                        }
                        else 
                        {
                            m1 -= 120;
                            spent += 120;
                        }
                        exp1 = std::ceil(float(exp1*0.9));
                        if (m1 < 0) m1 = 0; 
                }
            }
        }
        else
        {
            int event = 0;
            while (m1 != 0 && event != 3)
            {
                switch (event++)
                {
                    case 0: //event 1
                        if (hp1 < 200) {hp1 = std::ceil(float(hp1*1.3)); m1 -= 150;}                       
                        else {hp1 = std::ceil(float(hp1*1.1)); m1 -= 70;}
                        if (hp1 > 666) hp1 = 666;
                        if (m1 < 0) m1 = 0;
                        break;
                    case 1: //event 2
                        if (exp1 < 400) m1 -= 200;
                        else m1 -= 120;
                        exp1 = std::ceil(float(exp1*1.13));
                        if (exp1 > 600) exp1 = 600;
                        if (m1 < 0) m1 = 0;
                        break;
                    case 2: //event 3
                        if (exp1 < 300) m1 -= 100;
                        else m1 -= 120;
                        exp1 = std::ceil(float(exp1*0.9));
                        if (m1 < 0) m1 = 0; 
                }
            }
        }
        hp1 = std::ceil(float(hp1*0.83));
        exp1 = std::ceil(float(exp1*1.17));
        if (exp1 > 600) exp1 = 600;
        n = sqrt(exp1);
        if (exp1 - n*n < (n+1)*(n+1) - exp1) p2 = 100;
        else p2 = std::ceil(float((exp1/double((n+1)*(n+1)) + 80)/1.23));

        //Road 3
        int i = (e2/10 + e2%10)%10;
        int chance[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
        p3 = chance[i];
    }
    int p = std::ceil(float((p1+p2+p3)/3.0));
    if (p < 50) {hp1 = std::ceil(float(hp1*0.85)); exp1 = std::ceil(float(exp1*1.15));}
    else {hp1 = std::ceil(float(hp1*0.9)); exp1 = std::ceil(float(exp1*1.2));}
    if (exp1 > 600) exp1 = 600;
    return hp1 + exp1 + m1;
}

// Task 3
int chaseTaxi(int & hp1, int & exp1, int & hp2, int & exp2, int e3) 
{
    if (e3 < 0 || e3 > 99) return -99;
    int taxi[10][10], holmes[10][10];
    std::vector<int> left(19, -8020), right(19, -8020);
    int x = 0, y = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            taxi[i][j] = ((e3*j + i*2)*(i-j));
            left[i - j + 9] = std::max(left[i - j + 9], taxi[i][j]);
            right[i + j] = std::max(right[i + j], taxi[i][j]);
            if (taxi[i][j] > 2*e3) ++x;
            if (taxi[i][j] < -e3) ++y;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) 
        {
            holmes[i][j] = abs(std::max(left[i - j + 9], right[i + j]));
        }
    }
    x = x/10 + x%10; x = x/10 + x%10;
    y = y/10 + y%10; y = y/10 + y%10; 
    if (abs(taxi[x][y]) > holmes[x][y]) 
    {
        exp1 = ceil(float(exp1*0.88)); 
        hp1 = ceil(float(hp1*0.9));
        exp2 = ceil(float(exp2*0.88)); 
        hp2 = ceil(float(hp2*0.9));
        return taxi[x][y];
    }
    else
    {
        if ((exp1 = ceil(float(exp1*1.12))) > 600) exp1 = 600;
        if ((hp1 = ceil(float(hp1*1.1))) > 666) hp1 = 666;
        if ((exp2 = ceil(float(exp2*1.12))) > 600) exp2 = 600;
        if ((hp2 = ceil(float(hp2*1.1))) > 666) hp2 = 666;
        return holmes[x][y];
    }
}