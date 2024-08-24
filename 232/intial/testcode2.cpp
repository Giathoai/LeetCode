#include<iostream>
#include<cstring>
#include <sstream>
#include <string.h>
#include <fstream>
enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL }; 
enum RobotType { C=0, S, W, SW };
enum MovingObjectType {SHERLOCK, WATSON, CRIMINAL, ROBOT};
using namespace  std;

void reverse(char str[]) {
    char temp[strlen(str)];
    for(int i = strlen(str) - 1,  j = 0; i >= 0, j < strlen(str); i--, j++) {
        temp[j] = str[i];
    }
    for(int i = 0; i < strlen(str); i++) {
        str[i] = temp[i];
    }
}

void recover(char signal[]) {
    for(int i = 0; i < strlen(signal); i++) {
    if(signal[i] <= 'Z' && signal[i] >= 'A') {
        signal[i] += 32;
    }
    else if(signal[i] <= 'z' && signal[i] >= 'a'){
        signal[i] -= 32;
    }
}
}

void calSum(string fileName)   {
    int sum = 0;
    int temp = 0;
    for(int i = 0; i < fileName.length(); i++) {
        if(i == fileName.length() - 1) {
            temp = temp * 10 + fileName[i] - '0';
            sum += temp;
        }
        if(fileName[i] >= '0' && fileName[i] <= '9') {
            temp = temp * 10 + fileName[i] - '0';
        }else{
            sum += temp;
            temp = 0;
        }
    }    
    cout << sum;
}    

void cutString(string s, int index){
    if(index > s.length()){
        cout << "";

    }else{
        cout << s.substr(index, s.length() - index);
    }
}

void findAllIndex(string s1, string s2){
    bool flag = false;
    for(int i = 0; i < s1.length(); i++){
        if(s1[i] == s2[0]){
            flag = true;
            cout << i << " ";
        }
    }
    if(flag == false) cout << -1;
}
int findMaxColumn(int arr[][1000], int row, int col){
    int max = 0;
    int ans = 0;
    for(int i = 0; i < col; i++){
        int sum= 0;
        for(int j = 0; j < row; j++){
            sum += arr[j][i];
        }
        if(sum >= max){
            max = sum;
            ans = i;
        }
    }
    return ans;
}

int diagonalProduct(int arr[][1000], int row, int col) {
    int multi = 1;
    for(int i = 0; i < row; i++){
       multi *= arr[i][i];
    }
    return multi;
}

bool isSymmetric(int arr[][1000], int row, int col) {
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(arr[i][j] != arr[j][i]) return false;
        }
    }
    return true;
}       
int diagonalDiff(int arr[][1000], int row, int col, int x, int y) {
    int d1 = 0, d2 = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i - x == j - y) {
                d1 += arr[i][j];
            }
            if(i - x == y - j){
                d2 += arr[i][j];
            }
        }        
    }
    return abs(d1 - d2);
}

int giaithua(int n){
    if(n == 0 || n == 1) return 1;
    return n * giaithua(n - 1);
}

void sum2(int * array, int numEls, int &result)
{
    result = 0;
    for(int i = 0; i < numEls; i++){
        result += array[i];

    }
}

bool completeNum(int N)
{
    int sum = 0;
    for(int i = 1; i < N; i++){
        if(N % i == 0){
            sum += i;
        }
    }
    cout << sum;
    if(sum == N){
        return true;
    }else{
        return false;
    }
}

int calculateSumFromLine(const string& line) {
    int sum = 0;
    istringstream iss(line); 
    string numStr;
    while (iss >> numStr) { 
        int num = stoi(numStr);
        if (num >= 0) {
            sum += num;
        }
    }
    return sum;
}

//
int find(char str[], char substr[]) {
    for(int i = 0; i < strlen(str); i++){
        bool flag = true;
        for(int j = 0; j < strlen(substr); j++){
            if(str[i + j] != substr[j]) flag = false;
        }
        if(flag == true) return i;
    }
}
//"car taxi bike bike car taxi"
//    i
//    i    j
//         z     
void printFirstRepeatedWord(char str[]) {
    char **sub = new char*[100];
    char *token = strtok(str, " ");
    
    int dem = 0;
    while(token != NULL){
        sub[dem] = token;
        token = strtok(NULL, " ");
        dem++;
    }
    int index;
    for (int i = 1; i < dem; i++) {
        for (int j = 0; j < i; j++) {
            if (strcmp(sub[i],sub[j]) == 0) {
                cout << sub[i];
                return;
            }
            
        }

        
    }
    cout << "No Repetition";
}

void process(string fileName){
    ifstream inputFile(fileName);
    int n, m;
    
    float max, maxmax;

    inputFile >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            float x;
            inputFile >> x;
            if(j == 0) max = x;
            else if(x > max) max = x;
        }
        if(i == 0) maxmax = max;
        else if( max > maxmax) maxmax = max;
        cout << max << " ";
    }
    cout << maxmax;
}

      
void process(char str[], char outstr[]) {
    int i, j = 0;
    int flag = 0;
    
    for (i = 0; str[i] == ' '; i++);
    for (; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            outstr[j++] = str[i];
            flag = 0;
        } else if (!flag) {
            outstr[j++] = ' ';
            flag = 1;
        }
    }
    if (j > 0 && outstr[j - 1] == ' ') j--;
    outstr[j] = '\0';
}

void replaceString(string s, string s1, string s2){
    for(int i = s.length(); i >= 0;i--){
        if(s.substr(i, s1.length()) == s1){
            s.replace(i, s1.length(), s2);
            break;
        }
    }
    cout << s;
}

void deleteWord(string s, string s1){
    for(int i = s.length(); i >= 0;i--){
        if(s.substr(i, s1.length()) == s1){
            s.replace(i, s1.length(), "");
            break;
        }
    }
    cout << s;
}


void uppercase(string output)   {
    string input;
    getline(cin, input);
    for(int i = 0; i < input.length(); i++){
        if(input[i] <= 'z' && input[i] >= 'a'){
        input[i] -= 32;
        }
    }
    ofstream outFile(output);
    outFile << input;
    outFile.close();
}

bool isPalindrome(const char* str) {
    for(int i = strlen(str) - 1,  j = 0; i >= 0, j < strlen(str); i--, j++) {
        if(str[j] != str[i]) return false;
    }
    return true;
}



class BaseItem  {
    friend class TestStudyInPink;
public:
    virtual bool CanUse(Character* obj, Robot* robot) = 0;
    virtual void use(Character* obj, Robot* robot) = 0;
    virtual ItemType getType() const = 0;
};

class MagicBook : public BaseItem {
    friend class TestStudyInPink;
public:
    bool CanUse(Character* obj, Robot* robot) override;
    void use(Character* obj, Robot* robot) override;
    ItemType getType() const override;
};

class EnergyDrink : public BaseItem {
    friend class TestStudyInPink;
public:
    bool CanUse(Character* obj, Robot* robot) override;
    void use(Character* obj, Robot* robot) override;
    ItemType getType() const override;
};

class FirstAid : public BaseItem{
    friend class TestStudyInPink;
public:
    bool CanUse(Character* obj, Robot* robot) override;
    void use(Character* obj, Robot* robot) override;
    ItemType getType() const override;
};

class ExcemptionCard : public BaseItem{
    friend class TestStudyInPink;
public:
    bool CanUse(Character* obj, Robot* robot) override;
    void use(Character* obj, Robot* robot) override;
    ItemType getType() const override;

};

class PassingCard : public BaseItem{
    friend class TestStudyInPink;
private:
    string challenge;
public:
    PassingCard(int i, int j);
    bool CanUse(Character* obj, Robot* robot) override;
    void use(Character* obj, Robot* robot) override;
    string getChallenge() const;
    ItemType getType() const override;
};

class BaseBag{
    friend class TestStudyInPink;
protected:
    class Node{
        public:
        BaseItem* item;
        Node* next;
        public:
        Node(BaseItem* item, Node* next = nullptr):item(item), next(next){}
    };
protected:
    int size = 0;
    int capacity;
    Node* head; 
public:
    BaseBag(int capacity);
    virtual ~BaseBag();
    virtual bool insert(BaseItem* item);
    virtual BaseItem* get() = 0;
    virtual BaseItem* get(ItemType itemType);
    virtual string str() const;
};

class SherlockBag : public BaseBag{
    friend class TestStudyInPink;
private:
    Sherlock * sherlock;
    BaseBag* Bag;
public:
    SherlockBag(Sherlock * Character);
    BaseItem* get();
    BaseItem* get(ItemType itemType);
    int getsize();

};

class WatsonBag : public BaseBag{
    friend class TestStudyInPink;
private:
    Watson * watson;
    BaseBag* Bag;
public:
    WatsonBag(Watson * Character);
    BaseItem* get();
    BaseItem* get(ItemType itemType);
    int getsize();
};
// Robot, BaseItem, BaseB


bool MagicBook :: CanUse(Character* obj, Robot* robot){
    int exp = obj->GetExp();
    return (robot == nullptr && exp <= 350);
} 

void MagicBook :: use(Character* obj, Robot* robot){
    if(CanUse(obj, robot) == true){
        obj->setExp(ceil((float)(obj->GetExp()) * 1.25));
    }    
}

ItemType MagicBook :: getType() const{
    return MAGIC_BOOK;
}

bool EnergyDrink :: CanUse(Character* obj, Robot* robot){
    int hp = obj->GetHp();
    return (robot == nullptr && hp <= 100);
}

void EnergyDrink :: use(Character* obj, Robot* robot){
    if(CanUse(obj, robot) == true){
        obj->setHp(ceil((float)obj->GetHp() * 1.2));
    }    
}

ItemType EnergyDrink :: getType() const{
    return ENERGY_DRINK;
}

bool FirstAid :: CanUse(Character* obj, Robot* robot){
    int hp = obj->GetHp();
    int exp = obj->GetExp();
    return((hp <= 100 || exp <= 350) && robot == nullptr);
}

void FirstAid :: use(Character* obj, Robot* robot){
    if(CanUse(obj, robot) == true){
        obj->setHp(ceil((float)obj->GetHp() * 1.5));
    }
}

ItemType FirstAid :: getType() const{
    return FIRST_AID;
}

bool ExcemptionCard :: CanUse(Character* obj, Robot* robot){
    int hp = obj->GetHp();
    string name = obj->GetName();
    return((hp % 2 == 1 && name == "Sherlock") && robot != nullptr); 
}

void ExcemptionCard :: use(Character* obj, Robot* robot){
        if(CanUse(obj, robot) == true){
            // khong mat hp hoac exp
        }
       
}

ItemType ExcemptionCard :: getType() const{
    return EXCEMPTION_CARD;
}

PassingCard :: PassingCard(int i, int j) {
    int t = (i * 11 +j) % 4;
    switch (t){
    case 0 :
        challenge = "RobotS";
        break;
    case 1 :
        challenge = "RobotC";
        break;
    case 2 :
        challenge = "RobotSW";
        break;
    case 3 :
        challenge = "all";  
        break;  
    } 
}

bool PassingCard :: CanUse(Character* obj, Robot* robot){
    if(obj->GetName() == "Watson" && obj->GetHp() % 2 == 0 && robot != nullptr){
        return true;
    }   
}

void PassingCard :: use(Character* obj, Robot* robot){
    if(CanUse(obj, robot) == true ){
        if(challenge == "all"){
            // su dung 
        }else if(robot->GetName() == challenge){
            // su dung
        }else{
            // van su dung
        }
    }
}

ItemType PassingCard :: getType() const{
    return PASSING_CARD;
}

string PassingCard :: getChallenge() const{
    return challenge;
}

BaseBag :: BaseBag(int capacity){
    this->capacity = capacity;
    this->size = 0;
    this->head = nullptr;
}

bool BaseBag :: insert(BaseItem* item){
    if(this->size == this->capacity) return false;
    Node* newNode = new Node(item, head);
    head = newNode;
    size++;
    return true;
}

BaseItem* BaseBag :: get(ItemType itemType){
    if(size == 0){
        return nullptr;
    }
    Node* curr = head;
    Node* prev = nullptr;
    while(curr && curr->item->getType() != itemType){
        prev = curr;
        curr = curr->next;
        
    }
    if(!curr){
        return nullptr;
    }
    if(curr != head){
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    
    return item;

}

BaseBag :: ~BaseBag(){
    Node* curr = head;
    while(curr){
        Node* temp = curr;
        curr = curr->next;
        delete curr->item;
        delete temp;
    }
    head = nullptr;

}

string BaseBag :: str() const{
    string ans = "Bag[count=" + to_string(size) + ";";
    Node* curr = head;
    while(curr){
        curr = curr->next;
        ans += to_string(curr->item->getType()) + ";]";
    }
    return ans;
}
SherlockBag :: SherlockBag(Sherlock * Character) : BaseBag(13), sherlock(Character){
    this->Bag = this;
}

BaseItem* SherlockBag :: get(){
    if(size == 0){
        return nullptr;
    }
    Node* curr = head;
    Node* prev = nullptr;
    while (curr && !curr->item->CanUse((this->sherlock), nullptr)) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        return nullptr;
    }
    if (prev) {
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    
    return item;
}

BaseItem* SherlockBag :: get(ItemType itemType){
    if(size == 0){
        return nullptr;
    }
    Node* curr = head;
    Node* prev = nullptr;
    while(curr && curr->item->getType() != itemType){
        prev = curr;
        curr = curr->next;
        
    }
    if(!curr){
        return nullptr;
    }
    if(curr != head){
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    
    return item;

}

int SherlockBag :: getsize() {
    return size;
}
WatsonBag :: WatsonBag(Watson * Character) : BaseBag(13), watson(Character){
    this->Bag = this;
}

BaseItem* WatsonBag :: get(){
    if(size == 0){
        return nullptr;
    }
    Node* curr = head;
    Node* prev = nullptr;
    while (curr && !curr->item->CanUse((this->watson), nullptr)) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        return nullptr;
    }
    if (prev) {
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    
    return item;
}


BaseItem* WatsonBag :: get(ItemType itemType){
    if(size == 0){
        return nullptr;
    }
    Node* curr = head;
    Node* prev = nullptr;
    while(curr && curr->item->getType() != itemType){
        prev = curr;
        curr = curr->next;
        
    }
    if(!curr){
        return nullptr;
    }
    if(curr != head){
        prev->next = curr->next;
        curr->next = head;
        head = curr;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    
    return item;

}

int WatsonBag :: getsize(){
    return size;
}


int main(){
    
   
    return 0;
}