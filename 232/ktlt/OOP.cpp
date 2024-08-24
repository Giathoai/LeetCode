#include<bits/stdc++.h>

using namespace std;

struct SCP {
    int id;
    int objClass;
    string speConProcedures;
    string description;
    string* addendums;
    int numAddendums;
};



class ClockType
{
public:
    ClockType(int, int, int);
    ClockType();    
    void printTime() const;
    void setTime(int, int, int);
    
    void getTime(int& hours, int& minutes, int& seconds) const;
    

private:
    int hr;
    int min;
    int sec;
};

void ClockType::printTime() const
{
   if (hr < 10)
      cout << "0";
   cout << hr << ":";
   if (min < 10)
      cout << "0";
   cout << min << ":";
   if (sec < 10)
      cout << "0";
   cout << sec;
}

void ClockType::getTime(int& h, int& m, int& s) const{
    h = hr;
    m = min;
    s = sec;
}
void ClockType::getTime(int& h, int& m, int& s) const{
    h = hr;
    m = min;
    s = sec;
}

class Room{

private:
    float length;
    float breadth;
    float height;

public:
    Room(int l, int b, int h) : length(l), breadth(b), height(h){}
    float calculateArea() const{
        return length * breadth;
    }
    float calculateVolume() const{
        return length * breadth * height;
    }
};

class Integer {
private:
    int val;

public:
    Integer(int v) : val(v) {}
    void setValue(int v) {
        val = v;
    }
    int getValue() const {
        return val;
    }

};

#include<iostream>

using namespace std;

class Course {
    private:
        int ID;
        int numOfStudent;
        int numOfTeacher;
        int numOfTA;
    public:
        void getinfo();
        void disinfo();
};

void Course::getinfo() {
   cout << "ID: ";
   cin >> ID;
   cout << "Number of Students: ";
   cin >> numOfStudent;
   cout << "Number of Teachers: ";
   cin >> numOfTeacher;
   cout << "Number of TAs: ";
   cin >> numOfTA;
}

void Course::disinfo()
{
   cout<<endl;
   cout<< "CourseID = "<< ID << endl;
   cout<< "Number of student = " << numOfStudent << endl;
   cout<< "Number of teacher = " << numOfTeacher << endl;
   cout<< "Number of TA = " << numOfTA<< endl;
}


int main() {
    int n;
    cin >> n;
    Course *arr = new Course[2];
    for(int i = 0; i < n; i++){
        arr[i].getinfo();
        arr[i].disinfo();
    }
    
    return 0;
}

SCP** sortDatabase(SCP** arr, int n) {
    for(int i = 0; i < n - 1; i++){
        if(arr[i]->id > arr[i + 1]->id) swap(arr[i], arr[i + 1]);
    }
    return arr;
}

int main(){
    int n = 3;
SCP** data = new SCP* [n];
data[0] = new SCP {2, 1, "SCP-002 is to remain connected to a suitable power supply at all times.", "SCP-002 resembles a tumorous, fleshy growth with a volume of roughly 60 cubed meter.", nullptr, 0};
data[1] = new SCP {55, 2, "Object is kept within a five (5) by five (5) by two point five (2.5) meter square room.", "All known information about the object is that it is not round.", nullptr, 0};
data[2] = new SCP {49, 1, "SCP-049 is contained within a Standard Secure Humanoid Containment Cell in Research Sector-02 at Site-19.", "SCP-049 is a humanoid entity, roughly 1.9 meters in height, which bears the appearance of a medieval plague doctor.", nullptr, 0};

data = sortDatabase(data, n);

for (int i = 0; i < n; i++) cout << data[i]->id << " ";

for (int i = 0; i < n; i++) {
    delete [] data[i]->addendums;
    delete data[i];
}
delete [] data;

}