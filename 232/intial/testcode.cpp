
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;




class Position {
private:
    int r;
    int c; 
public:
    static const Position npos; 
    
    Position(int r=0, int c=0);
    Position(const string & str_pos);

    int getRow() const{
        return r;
    }
    int getCol() const{
        return c;
    }
    void setRow(int r){
        this->r = r; 
    }
    void setCol(int c){
        this->c = c;
    }

    string str() const{
        return "(" + to_string(r) + "," + to_string(c) + ")";
    }

    bool isEqual(int in_r, int in_c) const;
};



class Configuration {
public:
    Configuration(const string& filepath) {
        ifstream file(filepath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                int pos = line.find('=');
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                if (key == "MAP_NUM_ROWS") {
                    map_num_rows = stoi(value);
                } else if (key == "MAP_NUM_COLS") {
                    map_num_cols = stoi(value);
                } else if (key == "MAX_NUM_MOVING_OBJECTS") {
                    max_num_moving_objects = stoi(value);
                } else if (key == "ARRAY_WALLS") {
                    getArray(value, arr_walls, num_walls);
                } else if (key == "ARRAY_FAKE_WALLS") {
                    getArray(value, arr_fake_walls, num_fake_walls);
                } else if (key == "SHERLOCK_MOVING_RULE") {
                    sherlock_moving_rule = value;
                } else if (key == "SHERLOCK_INIT_POS") {
                    getPosition(value, sherlock_init_pos);
                } else if (key == "SHERLOCK_INIT_HP") {
                    sherlock_init_hp = stoi(value);
                } else if (key == "SHERLOCK_INIT_EXP") {
                    sherlock_init_exp = stoi(value);
                } else if (key == "WATSON_MOVING_RULE") {
                    watson_moving_rule = value;
                } else if (key == "WATSON_INIT_POS") {
                    getPosition(value, watson_init_pos);
                } else if (key == "WATSON_INIT_HP") {
                    watson_init_hp = stoi(value);
                } else if (key == "WATSON_INIT_EXP") {
                    watson_init_exp = stoi(value);
                } else if (key == "CRIMINAL_INIT_POS") {
                    getPosition(value, criminal_init_pos);
                } else if (key == "NUM_STEPS") {
                    num_steps = stoi(value);
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file: " << filepath << endl;
        }
    }

    ~Configuration() {
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

private:
    int map_num_rows, map_num_cols, max_num_moving_objects, sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp, num_steps;
    int num_walls, num_fake_walls;
    Position* arr_walls;
    Position* arr_fake_walls;
    string sherlock_moving_rule, watson_moving_rule;
    Position sherlock_init_pos, watson_init_pos, criminal_init_pos;

    void getArray(const string& str, Position*& arr, int& size) {
        size = 1;
        int count = 1;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == ';') {
                size++;
            }
        }    
        arr = new Position[size];
        int start = 0;
        int r,c;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == '(') {
                int count = 0;
                int j = i;
                while(str[j] != ',') {
                count++;
                j++;
                }
                r = stoi(str.substr(i + 1,  count - 1));
            }    
            if(str[i] == ',') {
                int count = 0;
                int j = i;
                while(str[j] != ')') {
                count++;
                j++;
                }
                c = stoi(str.substr(i + 1,  count - 1));
            }
        arr[start++] = {r, c};
        }
    }
    void getPosition(const string& value, Position& pos) {
        int comma_pos = value.find(",");
        pos.setRow(stoi(value.substr(1, comma_pos - 1)));
        pos.setCol(stoi(value.substr(comma_pos + 1, value.length() - comma_pos - 2)));
    }
};




Position :: Position(int r, int c ){
    this->r = r;
    this->c = c;
}

Position :: Position(const string & str_pos){
    int comma_pos = str_pos.find(",");
    this->r = stoi(str_pos.substr(1, comma_pos - 1));
    this->c = stoi(str_pos.substr(comma_pos + 1, (str_pos.size() - comma_pos - 2)));
}

bool Position :: isEqual(int in_r, int in_c) const {
    if(this->r == in_r && this->c == in_c){
        return true;
    }else{
        return false;
    }
}

const Position Position::npos = {-1, -1};


void getArray(const string& str, Position*& arr, int& size) {
        size = 1;
        int count = 1;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == ';') {
                size++;
            }
        }    
        arr = new Position[size];
        int start = 0;
        int r,c;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == '(') {
                int count = 0;
                int j = i;
                while(str[j] != ',') {
                count++;
                j++;
                }
                r = stoi(str.substr(i + 1,  count - 1));
            }    
            if(str[i] == ',') {
                int count = 0;
                int j = i;
                while(str[j] != ')') {
                count++;
                j++;
                }
                c = stoi(str.substr(i + 1,  count - 1));
                arr[start++] = {r, c};

            }
        }
}



int main() {
    Position *arr_walls;
    int num_walls;
    string ans;
    string line = "ARRAY_WALLS=[(1,2);(2,3);(3,4)]";
    int pos = line.find('=');
    string key = line.substr(0, pos);
    string value = line.substr(pos + 1);
    getArray(value, arr_walls, num_walls);
    for(int i = 0; i < num_walls - 1; i++){
        ans += arr_walls[i].str() + ";";
    }
    cout << num_walls << endl << ans;

    return 0;
}