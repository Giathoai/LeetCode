//Kéo xuống dưới để thêm file
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

//in-out function
void readFile(
    const std::string& filename,
    int& HP1,
    int& HP2,
    int& EXP1,
    int& EXP2,
    int& M1,
    int& M2,
    int& E1,
    int& E2,
    int& E3
);
void writeOutput(
    const std::string& filename,
    int& result1,
    int& result2,
    int& result3
);
//task function
int firstMeet(int & exp1, int & exp2, int e1);
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2);
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3);

// main()
int main() 
{
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;   
    readFile("testcase.inp", HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3);
    int result1 = firstMeet(EXP1, EXP2, E1),
        result2 = traceLuggage(HP1, EXP1, M1, E2),
        result3 = chaseTaxi(HP1, EXP2, HP2, M2, E3);
    writeOutput("yourAnswer.out", result1, result2, result3);
    return 0;
}

//Read file input
void readFile(
    const std::string& filename,
    int& HP1,
    int& HP2,
    int& EXP1,
    int& EXP2,
    int& M1,
    int& M2,
    int& E1,
    int& E2,
    int& E3
)
{
    std::ifstream inp(filename);
    inp >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
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

/*
TỪ ĐÂY SẼ LÀ PHẦN CODE CẦN TEST
HOẶC DÁN CẢ PHẦN KHAI BÁO CỦA BẢN THÂN
HOẶC CHỈ DÁN MỖI CODE
*/

// Task 1
void checkexp(int &x) {
    if(x > 600) x = 600;
    if(x < 0) x = 0;
}

void checkhp(int &x){
    if(x > 666) x = 666;
    if(x < 0) x = 0;
}

void check(int& HP1, int& HP2, int& EXP1, int& EXP2, int& M1, int& M2, int& E1, int& E2, int& E3) {
            if (HP1 < 0)
                HP1 = 0;
            if (HP1 > 666)
                HP1 = 666;
            if (HP2 < 0)
                HP2 = 0;
            if (HP2 > 666)
                HP2 = 666;
            if (EXP1 < 0)
                EXP1 = 0;
            if (EXP1 > 600)
                EXP1 = 600;
            if (EXP2 < 0)
                EXP2 = 0;
            if (EXP2 > 600)
                EXP2 = 600;
            if (M1 < 0)
                M1 = 0;
            if (M1 > 3000)
                M1 = 3000;
            if (M2 < 0)
                M2 = 0;
            if (M2 > 3000)
                M2 = 3000;
        }

int TH1(int& EXP1, int& EXP2, int E1) {
    int D = 0;
    switch (E1) {
        case 0:
            EXP2 += 29;
            break;
        case 1:
            EXP2 += 45;
            break;
        case 2:
            EXP2 += 75;
            break;
        case 3:
            EXP2 += (29 + 45 + 75);
            break;
    }
    
    D = E1 * 3 + EXP1 * 7;

    
    checkexp(EXP1);
    checkexp(EXP2);
    if(D % 2 == 0){
        EXP1 = ceil((float)EXP1 + (float)(D) / 200);
    }else{
        EXP1 = ceil((float)EXP1 - (float)(D) / 100);
    }
    checkexp(EXP1);
    checkexp(EXP2);
    return EXP1 + EXP2;
}

int TH2(int& EXP1, int& EXP2, int E1){
    if(E1 >= 4 && E1 <=19){
        EXP2 = EXP2 + ceil(((float)(E1) / 4) + 19);
    }
    if(E1 >= 20 && E1 <=49){
        EXP2 = EXP2 + ceil(((float)(E1) / 9) + 21);
    }
    if(E1 >= 50 && E1 <= 65){
        EXP2 = EXP2 + ceil(((float)(E1) / 16) + 17);
    }
    if(E1 >= 66 && E1 <= 79){
        EXP2 = EXP2 + ceil(((float)(E1) / 4) + 19);
        if(EXP2 > 200){
            EXP2 = EXP2 + ceil(((float)(E1) / 9) + 21);
        }
    }
    if(E1 >= 80 && E1 <= 99){
        EXP2 = EXP2 + ceil(((float)(E1) / 4) + 19);
        EXP2 = EXP2 + ceil(((float)(E1) / 9) + 21);
        if(EXP2 > 400){
            EXP2 = EXP2 + ceil(((float)(E1) / 16) + 17);
            EXP2 = ceil((float)(EXP2) * 1.15);
        }               
    }
    EXP1 -= E1;
    
    checkexp(EXP1);
    checkexp(EXP2);
    
    return EXP1 + EXP2;
}

int chinhphuong(int EXP1){
    int temp = round(sqrt((float)EXP1));
    return temp * temp;
}
//task1-------------------------------------------------------------
int firstMeet(int& EXP1, int& EXP2, int E1) {
    int HP1 = 0;
    int HP2 = 0;
    int E2 = 0;
    int E3 = 0;
    int M1 = 0;
    int M2 = 0;
    check(HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3);
    float exp1 = EXP1;
    float exp2 = EXP2;
    if (E1 < 0 || E1 > 99) {
        return -99;
    }
    if (E1 >= 0 && E1 <= 3) {
        return TH1(EXP1, EXP2, E1);
    }
    if(E1 >= 4 && E1 <= 99){
        return TH2(EXP1, EXP2, E1);
    }
}
//task2
float Road1(int EXP1){
    int S = chinhphuong(EXP1);
    float P1;
    if(EXP1 >= S){
        P1 = 100;
    }else{
        P1 = (((float)(EXP1) / S + 80) / 123) * 100; 
    }
    return P1;
}

int eatfood(int &HP1, int &M1, int &cost){
    if(HP1 < 200){
        HP1 = ceil((float)(HP1) * 1.3);
        M1 -= 150;
        cost -= 150;
        return 150;
    }else if(HP1 >= 200){
        HP1 = ceil((float)(HP1) * 1.1);
        M1 -= 70;
        cost -= 70;
        checkhp(HP1); 
        return 70;
    }
}

int travel(int &EXP1, int &M1, int &cost){
    EXP1 =ceil((float)(EXP1) * 1.13);
    if(EXP1 < 400){
        M1 -= 200;
        cost -= 200;
        return 200;
    }else{
        M1 -= 120;
        cost -= 120;
        checkexp(EXP1);
        return 120;
    }
}

int human(int &EXP1, int &M1, int &cost){
    EXP1 = ceil((float)(EXP1) * 0.9);
    if(EXP1 < 300){
        M1 -= 100;
        cost -= 100;
        return 100;
    }else{
        M1 -= 120;
        cost -= 120;
        return 120;
    }
}

float Road2(int &HP1, int &EXP1,int &M1, int E2){
    float P2;
    int cost = M1 / 2;
    if(E2 % 2 == 1){
        while(1){
          if(cost - eatfood(HP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            checkexp(EXP1);
            checkhp(HP1);
            break;
          }

          if(cost - travel(EXP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            checkexp(EXP1);
            checkhp(HP1);
            break;
          }   
              
          if(cost - human(EXP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            checkexp(EXP1);
            checkhp(HP1);
            break;
          }
        }
    }else{
        if(M1 - eatfood(HP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            M1 = 0;
            P2 = Road1(EXP1);  
            checkexp(EXP1);
            checkhp(HP1);
            return P2;
          }
          if(M1 - travel(EXP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            M1 = 0;
            P2 = Road1(EXP1);  
            checkexp(EXP1);
            checkhp(HP1);
            return P2;
          }   
          if(M1 - human(EXP1, M1, cost) < 0){
            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            M1 = 0;
            P2 = Road1(EXP1);  
            checkexp(EXP1);
            checkhp(HP1);  
            return P2;
          }

            EXP1 = ceil((float)(EXP1) * 1.17);
            HP1 = ceil((float)(HP1) * 0.83);
            checkexp(EXP1);
            checkhp(HP1); 
    }
    P2 = Road1(EXP1);  
  
    return P2;
}

float Road3 (int E2){
    int P[11]={32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    if(E2 >= 0 && E2 <=9){
        return P[E2];
    }else{
        int num = 0;
        while(E2 > 9){
            num += E2 % 10;
            E2 = E2 / 10;
        }
        num += E2;
        if(num > 9){
            return P[num % 10];
        }else{
            return num;
        }
    }
}
// Task 2--------------------------------------
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    float P1 = Road1(EXP1);
    float P2 = Road2(HP1, EXP1, M1, E2);
    float P3 = Road3(E2);
    if(P1 == 100 && P2 == 100 && P3 == 100){
        EXP1 = ceil((float)(EXP1) * 0.75);
    }else{
        float ans = (P1 + P2 + P3) / 3;
        if(ans < 50){
            HP1 = ceil((float)(HP1) * 0.85);
            EXP1 = ceil((float)(EXP1) * 1.15);
        }else{
            HP1 = ceil((float)(HP1) * 0.9);
            EXP1 = ceil((float)(EXP1) * 1.2);
        }
    }
        checkexp(EXP1);
        checkhp(HP1);
    return HP1 + EXP1 + M1;
}

int kq(int x){
    int temp = 0;
    while(x > 9){
        temp += x % 10;
        x = x / 10;
    }
    temp += x;
    return temp;
}



int duongcheo(int *arr[], int x, int y){
    int max = arr[x][y];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if ((i - x == j - y) || (i - x == y - j)) {
                if(max < arr[i][j]){
                    max == arr[i][j];
                } 
            }
        }
    }
    return max;
}

// Task 3-----------------------------------------
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    int arr[10][10] = {};
    int x = 0;
    int y = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            arr[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if(arr[i][j] > E3 * 2) x++;
            if(arr[i][j] < -E3) y++;
        }
    }
    while(x > 9){
        x = kq(x);
    }
    while(y > 9){
        y =kq(y);
    }

    int max = arr[x][y];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
                    if ((i - x == j - y) || (i - x == y - j)) {
                      if(max < arr[i][j]){
                        max = arr[i][j];
                } 
            }
        }
    }
   
    int taxi = abs(arr[x][y]);

    if(taxi > abs(max)){
        HP1 = ceil((float)(HP1) * 0.9);
        EXP1 = ceil((float)(EXP1) * 0.88);
        HP2 = ceil((float)(HP2) * 0.9);
        EXP2 = ceil((float)(EXP2) * 0.88);
        checkexp(EXP1);
        checkexp(EXP2);
        checkhp(HP1);
        checkhp(HP2);
        return arr[x][y];
    }else{
        HP1 = ceil((float)(HP1) * 1.1);
        EXP1 = ceil((float)(EXP1) * 1.12);
        HP2 = ceil((float)(HP2) * 1.1);
        EXP2 = ceil((float)(EXP2) * 1.12); 
        checkexp(EXP1);
        checkexp(EXP2);
        checkhp(HP1);
        checkhp(HP2);
        return max;
    } 
}

