#include<iostream>
#include<cstring>

using namespace std;

class Position {
    friend class TestStudyInPink;
private:
    int r;
    int c; 
public:
    static const Position npos; 
    Position(int r=0, int c=0);
    Position(const string & str_pos);
    bool operator!=(const Position & pos) const{
        return r != pos.r || c != pos.c;
    }
    bool operator==(const Position & pos) const{
        return r == pos.r || c == pos.c;
    }
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
    bool isEqual(const Position & pos) const;
};

Position :: Position(int r, int c){
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

bool Position :: isEqual(const Position & pos) const {
    if(this->r == pos.getRow() && this->c == pos.getCol()){
        return true;
    }else{
        return false;
    }
}

const Position Position::npos = Position(-1, -1) ;


void removeChar(char* str, int index) {
    int length = strlen(str);
    for (int i = index; i < length - 1; ++i) {
        str[i] = str[i + 1];
    }

    str[length - 1] = '\0';  
}
/*
string hople(char* name){
    int n = strlen(name);
    for(int i = 0; i < n; i++){
        if(name[i] >= 'A' && name[i] <= 'Z'){
            name[i] += 32;
        }
    }

    int j = 0;

    for (int i = 0; i < n; ++i) {
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) {
            name[j++] = name[i];
        }
    }
    name[j] = '\0';
    if((name[0] >= 'a' && name[0] <= 'z')) name[0] -= 32;
    return name;    
}
void process(const char *name, char *outstr)
{   
    string ans = "";
    char* nameStr = (char*)name;
    char* token = strtok(nameStr, " ");
    while (token != NULL) { 
        ans += hople(token);
        ans += " ";
        token = strtok(NULL, " ");
    }
    for(int i = 0; i < ans.length()-1; i++){
        outstr[i] = ans[i];
    }
}
*/
void hople(char* name) {
    int n = strlen(name);

    // Chuyển tất cả ký tự sang chữ thường
    for (int i = 0; i < n; ++i) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            name[i] += 32;
        }
    }

    // Loại bỏ các ký tự không phải chữ cái Latin
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) {
            name[j++] = name[i];
        }
    }
    name[j] = '\0';

    // Chuyển ký tự đầu tiên sang chữ hoa nếu nó là chữ cái thường
    if (name[0] >= 'a' && name[0] <= 'z') {
        name[0] -= 32;
    }
}


void process(const char* name, char* outstr) {
    // Tạo một bản sao của chuỗi đầu vào để làm việc với strtok
    char temp[strlen(name) + 1];
    strcpy(temp, name);

    char result[256] = "";
    char* token = strtok(temp, " ");
    while (token != NULL) {
        hople(token);
        strcat(result, token);
       if(token[0] == '\0'){}
        else strcat(result, " ");
       
        token = strtok(NULL, " ");
    }

    // Xóa khoảng trắng cuối cùng nếu có
    int len = strlen(result);
    if (len > 0 && result[len - 1] == ' ') {
        result[len - 1] = '\0';
    }
    
    // Sao chép kết quả vào outstr
    strcpy(outstr, result);
}


int main() {
    const int MAX_SIZE = 100;
    char name[] = "doAn VAN *(()hau @!#$ 3wjrgih3iy4934%^&*%";
    
    char outstr[MAX_SIZE];
    char outstr2[MAX_SIZE];
    process(name, outstr);
    cout << outstr << endl;

    return 0;
}