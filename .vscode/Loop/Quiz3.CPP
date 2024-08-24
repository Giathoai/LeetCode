#include<iostream>
#include<iomanip>
#include<string.h>

using namespace std;

const int MAX = 100;

struct student{
    char name[20];
    long int rollno;
    char sex;
    float height;
    float weight;
};

int main() {
    student cls[MAX];
    int i,n;
    cout << "How many names ? \n";
    cin >> n;
    float sum1, sum2;
    for (i = 0; i <= n-1; ++i){
        cout << "record = "<< i+1 << endl;
        cout << "name : "; cin>> cls[i].name;
        cout << "rollno : "; cin>> cls[i].rollno;
        cout << "sex : "; cin>> cls[i].sex;
        cout << "height : "; cin>> cls[i].height;
        cout << "weight : "; cin>> cls[i].weight;
        cout << endl;
    }
    cout << setw(20) << left << "Name" << setw(20) <<left <<  "Rollno" << setw(20) << left << "Sex" << setw(20) << left << "Height" << setw(20) <<left <<  "Weight" << endl;
   for (i = 0; i <= n-1; ++i){
       cout << setw(20) << left << cls[i].name <<setw(20) << left << cls[i].rollno << setw(20) << left << cls[i].sex <<setw(20) << left << setprecision(2) << fixed << cls[i].height << setw(20) << left << setprecision(2) << fixed << cls[i].weight << endl;
    sum1 +=cls[i].height;
    sum2 +=cls[i].weight;
    }
    cout << setprecision(5) << fixed << (sum1 / n) << " ";
    cout << setprecision(5) << fixed << (sum2 / n);

    return 0;
}