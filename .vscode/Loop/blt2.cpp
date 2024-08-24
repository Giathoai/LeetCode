#include <cmath>
#include <iostream>
#include <string>
using namespace std;
/******************************************************************************
 * Support Functions: these functions below are optional. If you want your code
                      to be clearer, you can implement them. However if you
                      dont know how to use funtion in programming, dont worry, 
                      you dont have to implement them, and you just add a comment 
                      in each of them.
*******************************************************************************/
float move(string moves,long &x,long &y)
{
    
    for (int i=0;i< moves.length();i++){
        if(moves[i] > 60){
            int c = 0;
            if(moves[i] == 'U'){
                int a = i + 1;
                c = 0;
               while((int)moves[a] < 60 && a <  moves.length() ){
                    c = c * 10 + (moves[a] - 48);
                    a++;                          
                }
                y = y + c;
            }

            if(moves[i] == 'D'){
                int a = i + 1;
                 c = 0;
                while((int)moves[a] < 60 && a <  moves.length() ){
                    c = c * 10 + (moves[a] - 48);
                    a++;                              
                }
                    y = y - c;
            }

            if(moves[i] == 'L'){
                int a = i + 1;
                 c = 0;
                while((int)moves[a] < 60 && a <  moves.length() ){
                    c = c * 10 + (moves[a] - 48);
                    a++;                              
                }
                    x = x - c;
            }
            
            if(moves[i] == 'R'){
                int a = i + 1;
                 c = 0;
                while((int)moves[a] < 60 && a <  moves.length() ){
                    c = c * 10 + (moves[a] - 48);
                    a++;                              
                }
                    x = x + c;
            }

        }
    }
     x = abs(x);
     y = abs(y);
return sqrt((x * x) + (y * y));
}
bool isPrime(int n)
{
     if (n < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
    
}
bool isSquared(int n)
{
int i = 0;
	while(i*i <= n){
		if(i*i == n){
			return 1;
		}
		++i;
	}
    return 0;
}
int main()
{
    string moves;
    float distance;
    bool primality, squared;
    long x=0,y=0;
    getline(cin,moves);
    
    distance = move(moves, x, y);
   
  
    cout << "Khoang cach xe da di chuyen tu vi tri ban dau toi diem hien tai: "
        << round(distance) << '\n';
    if(distance != 0){
    if (isPrime( round(distance) )) {
        cout << "So " <<  round(distance) << " la so nguyen to\n";
    }
    if (isSquared( round(distance) )) {
        cout << "So " <<  round(distance)  << " la so chinh phuong\n";
    }
    }
    return 0;
}
