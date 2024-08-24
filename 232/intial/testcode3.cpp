/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "main.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//Forward declaration
class TestStudyInPink;
 class MovingObject;
 class Position;
 class Configuration;
 class Map;

 class Criminal;
 class RobotS;
 class RobotW;
 class RobotSW;
 class RobotC;

class ArrayMovingObject;
 class StudyPinkProgram;

 class BaseItem;
 class BaseBag;
 class SherlockBag;
 class WatsonBag;



enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL }; 
enum RobotType { C=0, S, W, SW };
enum MovingObjectType {SHERLOCK, WATSON, CRIMINAL, ROBOT};
class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement(){};
    virtual ElementType getType() const{
        return type;
    };
};

class Path : public MapElement {
    friend class TestStudyInPink;
public: 
    Path() : MapElement(PATH){};  
};  
class Wall : public MapElement {
    friend class TestStudyInPink;
public: 
    Wall() : MapElement(WALL){};
};
class FakeWall : public MapElement {
    friend class TestStudyInPink;
private:
    int r,c;
    int req_exp;  
public:
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL) {
        this->req_exp = in_req_exp;
    };
    int getReqExp() const{
        return req_exp;
    }
    
};

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

class MovingObject {
    friend class TestStudyInPink;
protected:
    int index;
    Position pos; 
    Map * map;
    string name;
public:
    MovingObject(int index, const Position pos, Map* map, const string& name = "") : index(index), pos(pos), map(map), name(name){

    };
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const{
        return pos;
    }
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() = 0;
    
};

class Map {
    friend class TestStudyInPink;
private:
    int num_rows, num_cols;
    Position * array_walls;
    Position * array_fake_walls;
    MapElement *** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols){
    map = new MapElement ** [num_rows];
    for (int i = 0; i < num_rows; ++i) {
        map[i] = new MapElement * [num_cols];
        for (int j = 0; j < num_cols; ++j) {
            map[i][j] = new Path(); 
        }
    }
    for (int i = 0; i < num_fake_walls; ++i) {
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        int in_req_exp = ((r * 257 + c * 139 + 89) % 900) + 1;
        delete map[r][c];
        map[r][c] =  new FakeWall(in_req_exp);
    }
    for (int i = 0; i < num_walls; ++i) {
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        delete map[r][c];
        map[r][c] =  new Wall();
    }
    }
    ~Map(){
        for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            delete[] map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
    }
    int getNumRows() const{
        return num_rows;
    }
    int getNumCols() const{
        return num_cols;
    }
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const;
};

class Character : public MovingObject{
    friend class TestStudyInPink;
protected:
    int index;
    Position pos; 
    Map * map;
    string name;
    int init_hp, init_exp;
public:
    Character(int index, const Position pos, Map *map, const string & name="");
    virtual Position getNextPosition() = 0;
    virtual Position getCurrentPosition() const{
        return pos;
    }
    virtual void setHp(int hp){
        this->init_hp = hp;
    };
    
    void setExp(int exp){
        this->init_exp = exp;
    }
    int GetExp(){
        return init_exp;
    }
    int GetHp(){
        return init_hp;
    }
    virtual void move() = 0;
    virtual string str() const = 0;
    string GetName(){
        return name;
    }
};

class Sherlock : public Character {
    friend class TestStudyInPink;
private:
    Position init_pos;
    string moving_rule;
    int current_move_index = 0;
    int init_hp;
    int init_exp;
    int index;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition() override;
    Position setPosition(Position pos);
    MovingObjectType getObjectType(){
        return SHERLOCK;
    }
    void setHp(int hp){
        this->init_hp = hp;
    }
    void setExp(int exp){
        this->init_exp = exp;
    }
    int GetExp(){
        return init_exp;
    }
    int GetHp(){
        return init_hp;
    }
    Position getCurrentPosition() const{
        return init_pos;
    }
    void move();
    string str() const override;
};

class Watson : public Character {
    friend class TestStudyInPink;
private:
    Position init_pos;
    string moving_rule;
    int current_move_index = 0;
    int init_hp;
    int init_exp;
    int index;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition() override;
    void move();
    void setHp(int hp){
        this->init_hp = hp;
    }
    void setExp(int exp){
        this->init_exp = exp;
    }
    int GetExp(){
        return init_exp;
    }
    int GetHp(){
        return init_hp;
    }
    MovingObjectType getObjectType(){
        return WATSON;
    }
    Position getCurrentPosition() const{
        return init_pos;
    }
    string str() const override;
};

class Criminal : public Character {
    friend class TestStudyInPink;
private:
    int count_move = 0;
    Position init_pos;
    int index;
    int sherlock_r, sherlock_c;
    int watson_r, watson_c;
    Position PrevNextPosition;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getNextPosition() override;
    int findmax(char temp);
    MovingObjectType getObjectType(){
        return CRIMINAL;
    }
    Position getCurrentPosition() const{
        return init_pos;
    }
    int getCount_move(){
        return count_move;
    }
    Position getPrevNextPosition(){
        return PrevNextPosition;
    }
    void move();
    string str() const override;
    // ...
};

class ArrayMovingObject {
    friend class TestStudyInPink;
private:
    MovingObject ** arr_mv_objs;
    int count = 0;
    int capacity;
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const{
        return arr_mv_objs[index];
    };
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class TestStudyInPink;
    friend class StudyPinkProgram;

private:
    private:
    int map_num_rows, map_num_cols, max_num_moving_objects, sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp, num_steps;
    int num_walls, num_fake_walls;
    Position* arr_walls;
    Position* arr_fake_walls;
    string sherlock_moving_rule, watson_moving_rule;
    Position sherlock_init_pos, watson_init_pos, criminal_init_pos;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    void getPosition(const string& value, Position& pos);
    void getArray(const string value, Position* &arr, int& num);
};

class Robot : public MovingObject {
    friend class TestStudyInPink;
private:
    Position init_pos;
    RobotType robot_type;
    Position pos;
protected:
    Criminal* criminal;
    BaseItem* item;
    string name;
public:
    Robot(int index, const Position init_pos, Map* map, RobotType robot_type, Criminal* criminal, const string& name) : MovingObject(index, init_pos, map, name), robot_type(robot_type), criminal(criminal) {}    
    MovingObjectType getObjectType(){
        return ROBOT;
    }
    static Robot* createRobot(int index, Map* map, Criminal* criminal, Sherlock* Sherlock, Watson* watson); 
    string GetName(){
        return name;
    }
    BaseItem* getItem(){
        return item;
    }
    virtual Position getInit_pos() = 0;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual RobotType getRobotType() const = 0;
    virtual int getDistance() const = 0;  
};

class RobotC : public Robot {
    friend class TestStudyInPink;
private:
    int r,c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int sherlock_r,sherlock_c;
    int watson_r,watson_c;
    int index;
public:
    RobotC ( int index , const Position & init_pos , Map * map , Criminal * criminal);
    Position getNextPosition() override;
    Position getInit_pos() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    int getDistance() const override{};
    int getDistance(Sherlock* sherlock) const ;
    int getDistance(Watson* watson) const ;
};

class RobotS : public Robot {
    friend class TestStudyInPink;
private:
    int r,c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int sherlock_r,sherlock_c;
    int index;
public:
    RobotS ( int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock);
    int findmin(char temp);
    Position getInit_pos() override;
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    int getDistance() const override;

};

class RobotW : public Robot {
    friend class TestStudyInPink;
private:
    int r,c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int watson_r,watson_c;
    int index;
public:
    RobotW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson);
    int findmin(char temp);
    Position getInit_pos() override;
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getRobotType()const override;
    int getDistance() const override;
};

class RobotSW : public Robot {
    friend class TestStudyInPink;
private:
    int r,c;    
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int sherlock_r,sherlock_c;
    int watson_r,watson_c;
    BaseItem* item;
    int index;
public:
    RobotSW ( int index , const Position & init_pos , Map * map , Criminal * criminal, Sherlock * sherlock , Watson * watson );
    int findmin(char temp);
    Position getInit_pos() override;
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    int getDistance() const override;
};

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

class Node{
public:
    BaseItem* item;
    Node* next;
public:
    Node(BaseItem* item, Node* next = nullptr):item(item), next(next){
            
    }
};
class BaseBag{
    friend class TestStudyInPink;
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
// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    // Sample attributes
    int index = 2;
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    SherlockBag * sherlock_bag;
    WatsonBag * watson_bag;

    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if(watson->getCurrentPosition().isEqual(sherlock->getCurrentPosition())){
                    for(int i = 0; i < 15; i++){
                        if(watson_bag->getsize() >= 14){
                            break;
                        }else{
                            BaseItem* item = sherlock_bag->get(PASSING_CARD);
                            if(item != nullptr){
                            watson_bag->insert(item);
                            }
                        }
                    }
                    for(int i = 0; i < 13; i++){
                        if(sherlock_bag->getsize() >= 12){
                            break;
                        }else{
                            BaseItem* item = watson_bag->get(EXCEMPTION_CARD);
                            if(item != nullptr){
                            sherlock_bag->insert(item);
                            }
                        }
                    }
                }    
                if(criminal->getCount_move() % 3 == 0){
                    if(arr_mv_objs->isFull()){
                    index++;
                    Robot* robot = Robot :: createRobot(index, map, criminal, sherlock, watson);
                    arr_mv_objs->add(robot);
                    }
                }
                if(arr_mv_objs->get(i)->getObjectType() == ROBOT){
                    Robot * robot = dynamic_cast<Robot*>(arr_mv_objs->get(i));
                    if(sherlock->getCurrentPosition().isEqual(robot->getCurrentPosition())){
                        if(robot->getRobotType() == S){
                            if(sherlock->GetExp() > 400){
                                sherlock_bag->insert(robot->getItem());
                            }else{
                                if(sherlock->GetHp() % 2 == 1){
                                    BaseItem * card = sherlock_bag->get(EXCEMPTION_CARD);
                                    if(card == nullptr){
                                        sherlock->setExp(ceil((float)sherlock->GetExp() * 0.9));
                                    } 
                                }   
                            }
                            BaseItem* vatpham = sherlock_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(sherlock, nullptr);
                            }
                        }else if(robot->getRobotType() == W){
                            sherlock_bag->insert(robot->getItem());
                            BaseItem* vatpham = sherlock_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(sherlock, nullptr);
                            }
                        }else if(robot->getRobotType() == SW){
                           if(sherlock->GetExp() > 300 || sherlock->GetHp() > 335){
                                sherlock_bag->insert(robot->getItem());
                            }else{
                                BaseItem * card = sherlock_bag->get(EXCEMPTION_CARD);
                                if(card == nullptr){
                                    sherlock->setExp(ceil((float)sherlock->GetExp() * 0.85));
                                    sherlock->setHp(ceil((float)sherlock->GetHp() * 0.85));
                                }    
                            }
                            BaseItem* vatpham = sherlock_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(sherlock, nullptr);
                            }
                        }else if(robot->getRobotType() == C){ 
                            if(sherlock->GetHp() > 500){
                                sherlock->setPosition(criminal->getCurrentPosition());
                            }
                            BaseItem* vatpham = sherlock_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(sherlock, nullptr);
                            }
                        }        
                    }
                    if(watson->getCurrentPosition().isEqual(robot->getCurrentPosition())){
                        if(robot->getRobotType() == S){
                            BaseItem* vatpham = watson_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(watson, nullptr);
                            }
                        }else if(robot->getRobotType() == W){
                            if(watson->GetHp() % 2 == 0){
                                PassingCard* card = dynamic_cast<PassingCard*>(watson_bag->get(PASSING_CARD));
                                if(card != nullptr){
                                    if(card->getChallenge() == "all" || card->getChallenge() == "RobotW"){
                                        watson_bag->insert(robot->getItem());
                                    }else{
                                        watson->setExp(ceil((float)watson->GetExp() - 50));
                                        watson_bag->insert(robot->getItem());
                                    }    
                                }
                                
                            }
                            if(watson->GetHp() > 350){
                                watson_bag->insert(robot->getItem());

                            }else{
                                watson->setHp(ceil((float)watson->GetHp() * 0.95));
                            }
                            BaseItem* vatpham = watson_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(watson, nullptr);
                            }
                        }else if(robot->getRobotType() == SW){
                            if(watson->GetHp() % 2 == 0){
                                PassingCard* card = dynamic_cast<PassingCard*>(watson_bag->get(PASSING_CARD));
                                if(card != nullptr){
                                    if(card->getChallenge() == "all" || card->getChallenge() == "RobotSW"){
                                        watson_bag->insert(robot->getItem());
                                    }else{
                                        watson->setExp(ceil((float)watson->GetExp() - 50));
                                        watson_bag->insert(robot->getItem());
                                    }    
                                }
                            }
                            if(watson->GetExp() > 600 && watson->GetHp() > 165){
                                watson_bag->insert(robot->getItem());
                            }else{
                                watson->setExp(ceil((float)watson->GetExp() * 0.85));
                                watson->setHp(ceil((float)watson->GetHp() * 0.85));
                            }
                            BaseItem* vatpham = watson_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(watson, nullptr);
                            }
                        }else if(robot->getRobotType() == C){
                            watson_bag->insert(robot->getItem());
                            BaseItem* vatpham = watson_bag->get();
                            if(vatpham != nullptr){
                                vatpham->use(watson, nullptr);
                            }
                        }       
                    }
                }
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};



MapElement :: MapElement(ElementType in_type){
    this->type = in_type;
}

bool Map :: isValid(const Position & pos , MovingObject * mv_obj) const {
    int NumRow = getNumRows(); //(1,2)
    int NumCol = getNumCols();
    int r = pos.getRow();
    int c = pos.getCol();
    if(r < 0 || r >= NumRow || c < 0 || c >= NumCol){
            return false;
    }
    if(map[r][c]->getType() == WALL) return false;
    FakeWall* fakeWall = dynamic_cast<FakeWall*>(map[r][c]);
    Watson* watson = dynamic_cast<Watson*>(mv_obj);
    if(watson != nullptr){
        if(watson->GetExp() >= fakeWall->getReqExp()){
            return true;
        }else{
            return false;
        }
    }
    return true;
}
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

MovingObject :: ~MovingObject(){

}

Character :: Character(int index, const Position pos, Map * map, const string & name) : MovingObject(index, pos, map, ""){

}
    


Sherlock :: Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : Character(index, pos, map, "Sherlock"){
    this->name = "Sherlock";
    this->index = index;
    this->moving_rule = moving_rule;
    this->init_pos = init_pos;
    this->pos = pos;
    this->init_hp = init_hp;
    this->map = map;
    if(init_hp > 500) this->init_hp = 500;
    if(init_hp == 0){
    }
    this->moving_rule = moving_rule;
    this->init_exp = init_exp;
    if(init_exp > 900) this->init_exp = 900;
    if(init_exp == 0){
    }
}

Position Sherlock :: getNextPosition(){
        int r = this->init_pos.getRow();
        int c = this->init_pos.getCol();
        if (moving_rule.empty()) {
            return Position :: npos;
        }
        char move = moving_rule[current_move_index];
        current_move_index = (current_move_index++) % moving_rule.size();
        switch (move)
        {
        case 'U':
            r--;
            break;
        case 'D':
            r++;
            break;
        case 'R':
            c++;
            break;
        case 'L':
            c--;
            break;        
        default:
            break;
        }
    return Position(r,c);

}

void Sherlock :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

Position Sherlock :: setPosition(Position pos){
    this->init_pos = pos;
}
string Sherlock :: str() const{
    return "Sherlock[index=" + to_string(this->index) + ";pos=" + init_pos.str() + ";movingrule=" + moving_rule + "]";

}
Watson :: Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : Character(index, pos, map, "Watson"){
    this->name = "Watson";
    this->index = index;
    this->moving_rule = moving_rule;
    this->init_pos = init_pos;
    this->pos = pos;
    this->init_hp = init_hp;
    this->map = map;
    
    if(init_hp > 500) this->init_hp = 500;
    if(init_hp == 0){
        // nín
    }
    this->moving_rule = moving_rule;
    this->init_exp = init_exp;
    if(init_exp > 900) this->init_exp = 900;
    if(init_exp == 0){
        // nín
    }
}

Position Watson :: getNextPosition(){
    int r = this->init_pos.getRow();
    int c = this->init_pos.getCol();
    if (moving_rule.empty()) {
        return Position :: npos;
    }
    char move = moving_rule[current_move_index];
    current_move_index = (current_move_index + 1) % moving_rule.size();
    switch (move)
    {
    case ('U'):
        r--;
        break;
    case ('D'):
        r++;
        break;
    case ('R'):
        c++;
        break;
    case ('L'):
        c--; 
        break;       
    default:
        break;
    }
    return Position(r,c);
}

void Watson :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }

}

string Watson :: str() const {
    return "Watson[index=" + to_string(this->index) + ";pos=" + init_pos.str() + ";movingrule=" + moving_rule + "]";
}

Criminal :: Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson)  : Character(index, pos, map, "Criminal"){
    this->name = "Criminal";
    this->init_pos = init_pos;
    this->index = index;
    this->map = map;
    sherlock_c = sherlock->getCurrentPosition().getCol();
    sherlock_r = sherlock->getCurrentPosition().getRow();
    watson_c = watson->getCurrentPosition().getCol();
    watson_r = watson->getCurrentPosition().getRow();
}

int Criminal :: findmax(char temp){
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp)
    {
    case 'U':
        return abs(--r - sherlock_r) + abs(c - sherlock_c) + abs(--r - watson_r) + abs(c - watson_c);
        break;
    case 'D':
        return abs(++r - sherlock_r) + abs(c - sherlock_c) + abs(++r - watson_r) + abs(c - watson_c);
        break;
    case 'L':
        return abs(r - sherlock_r) + abs(--c - sherlock_c) + abs(r - watson_r) + abs(--c - watson_c);
        break;
    case 'R':
        return abs(r - sherlock_r) + abs(++c - sherlock_c) + abs(r - watson_r) + abs(++c - watson_c);
        break;
    default:
        break;
    }
}

Position Criminal :: getNextPosition() {
    int max_R = findmax('R');
    int max_D = findmax('D');
    int max_L = findmax('L');
    int max_U = findmax('U');
   
    int max = max_R;
    char max_char = 'R';
    if (max_D >= max) {
        max = max_D;
        max_char = 'D';
    }
    if (max_L >= max){
        max = max_L;
        max_char = 'L';
    }    
    if (max_U >= max){
        max = max_U;
        max_char = 'U';
    }
    int r = init_pos.getRow();
    int c = init_pos.getCol();

    if (max_char =='R') c++;
    else if (max_char == 'D') r++;
    else if (max_char == 'L') c--;
    else if (max_char == 'U') r--;
    return Position(r,c);
}

void Criminal :: move(){
    this->PrevNextPosition = init_pos;
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos.getCol() != Position :: npos.getCol() && nextpos.getRow() != Position :: npos.getCol() && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
        this->count_move++;
    }
}

string Criminal :: str() const{
    return "Criminal[index=" + to_string(this->index) + ";pos=" + init_pos.str() + "]";
}

ArrayMovingObject :: ArrayMovingObject(int capacity){
    this->capacity = capacity;
    MovingObject ** arr_mv_objs = new MovingObject*[capacity];

    for(int i = 0; i < capacity; i++){
        arr_mv_objs[i] = nullptr;
    }    
}

ArrayMovingObject :: ~ArrayMovingObject(){
    for (int i = 0; i < capacity; ++i) {
    delete arr_mv_objs[i];
    }
}

bool ArrayMovingObject :: isFull() const{
    return(count == capacity);
}

bool ArrayMovingObject :: add(MovingObject * mv_obj){
    if(this->isFull()) return false;
    arr_mv_objs[this->count++] = mv_obj;
    return true;
}

int ArrayMovingObject :: size() const{
    for(int i = 0; i < capacity; i++){

    }
}
string ArrayMovingObject :: str() const{
    string ans = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
    for(int i = 0; i < capacity; i++){
        if(arr_mv_objs[i] != nullptr){
            ans += arr_mv_objs[i]->str() + ";";
        }    
    }
    return ans;
}

Configuration :: Configuration(const string & filepath){
    ifstream file(filepath);
        if (file.is_open()) {
            string line;
            while (!file.eof()) {
                getline(file, line);
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
            cout << "Unable to open file: " << filepath << endl;
        }
}        
Configuration :: ~Configuration() {
        delete[] arr_walls;
        delete[] arr_fake_walls;
}

string Configuration :: str() const {
    string ans = "Configuration[ \nMAP_NUM_ROWS=" + to_string(map_num_rows) + "\n"; 
    ans += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n"; 
    ans += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n"; 
    ans += "NUM_WALLS=" + to_string(num_walls) + "\n";
    ans += "ARRAY_WALLS=[";
    for(int i = 0; i < num_walls - 1; i++){
        ans += arr_walls[i].str() + ";";
    }
    ans += arr_walls[num_walls - 1].str() + "]\n";
    ans += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
    ans += "ARRAY_FAKE_WALLS=[";
    for(int i = 0; i < num_fake_walls - 1; i++){
        ans += arr_fake_walls[i].str() + ";";
    }
    ans += arr_fake_walls[num_fake_walls - 1].str() + "]\n";
    ans += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
    ans += "SHERLOCK_INIT_POS=" + sherlock_init_pos.str() + "\n";
    ans += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
    ans += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
    ans += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
    ans += "WATSON_INIT_POS=" + watson_init_pos.str() + "\n";
    ans += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
    ans += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
    ans += "CRIMINAL_INIT_POS=" + criminal_init_pos.str() + "\n";
    ans += "NUM_STEPS=" + to_string(num_steps) + "\n";
    ans += "]";
    
    return ans;
}

void Configuration :: getPosition(const string& value, Position& pos) {
    int comma_pos = value.find(",");
    pos.setRow(stoi(value.substr(1, comma_pos - 1)));
    pos.setCol(stoi(value.substr(comma_pos + 1, (value.size() - comma_pos - 2))));
}


void Configuration :: getArray(const string value, Position*& arr, int& num) {
        num = 0;
        int count = 1;
        for(int i = 0; i < value.length(); i++) {
            if(value[i] == ',') {
                num++;
            }
        }    
        arr = new Position[num];
        int start = 0;
        int r,c;
        for(int i = 0; i < value.length(); i++) {
            
            if(value[i] == '(') {
                int count = 0;
                int j = i;
                while(value[j] != ',') {
                count++;
                j++;
                }
                r = stoi(value.substr(i + 1,  count - 1));
            }    
            if(value[i] == ',') {
                int count = 0;
                int j = i;
                while(value[j] != ')') {
                count++;
                j++;
                
                }
                c = stoi(value.substr(i + 1,  count - 1));
                arr[start++] = {r, c};
            }

        
        
        }
       
    }

int digitalRoot(int n) {
    if (n < 10)
        return n;
    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return digitalRoot(sum);
}

Robot * Robot :: createRobot(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson){
    Robot* robot;
    bool first = 1;
    int distance_sherlock = abs(sherlock->getCurrentPosition().getRow() - criminal->getCurrentPosition().getRow()) + abs(sherlock->getCurrentPosition().getCol() - criminal->getCurrentPosition().getCol());
    int distance_watson = abs(watson->getCurrentPosition().getRow() - criminal->getCurrentPosition().getRow()) + abs(watson->getCurrentPosition().getCol() - criminal->getCurrentPosition().getCol());

    Position pos_cri = criminal->getCurrentPosition();
    
        if(first == 1){
            robot = new RobotC(index, pos_cri, map, criminal);
        }else if(first == 0){
            if(distance_sherlock < distance_watson){
            robot = new RobotS(index, pos_cri, map, criminal, sherlock);
            }else if(distance_sherlock > distance_watson){    
            robot = new RobotW(index, pos_cri, map, criminal, watson);
            }else{
            robot = new RobotSW(index, pos_cri, map, criminal, sherlock, watson);
            }
        }
    int p = pos_cri.getRow() * pos_cri.getCol();
    int s = digitalRoot(p);  
    if (s >= 0 && s <= 1) {
        robot->item = new MagicBook();
    } else if (s >= 2 && s <= 3) {
        robot->item = new EnergyDrink();
    } else if (s >= 4 && s <= 5) {
        robot->item =new FirstAid();
    } else if (s >= 6 && s <= 7) {
        robot->item = new ExcemptionCard();
    } else if (s >= 8 && s <= 9) {
        robot->item = new PassingCard(pos_cri.getRow(), pos_cri.getCol());
    } 
    return robot;
}
RobotC :: RobotC (int index , const Position & init_pos , Map * map , Criminal * criminal ) : Robot(index, pos, map, robot_type, criminal, "RobotC"){
    this->index = index;
    this->robot_type = C;
    this->init_pos = init_pos;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
}

Position RobotC :: getInit_pos(){
    return this->pos;
}
Position RobotC :: getNextPosition(){
    int r = criminal->getPrevNextPosition().getRow();
    int c = criminal->getPrevNextPosition().getCol();
    return Position(r,c);
}

void RobotC :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotC :: getRobotType() const{
    return C;
}

int RobotC :: getDistance(Sherlock* sherlock) const{
    int r = sherlock->getCurrentPosition().getRow();
    int c = sherlock->getCurrentPosition().getCol();
    return abs(r - init_pos.getRow()) + abs(c - init_pos.getCol());
}

int RobotC :: getDistance(Watson* watson) const{
    int r = watson->getCurrentPosition().getRow();
    int c = watson->getCurrentPosition().getCol();
    return abs(r - init_pos.getRow()) + abs(c - init_pos.getCol());
}

string RobotC :: str() const{
    return ("[pos=" + init_pos.str() + ";type=" + to_string(robot_type) + ";dist=]");
}

RobotS :: RobotS (int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock) : Robot(index, pos, map, robot_type, criminal, "RobotS"){
    this->init_pos = init_pos;    
    this->index = index;
    this->pos = init_pos;
    this->robot_type = S;
    this->map = map;
    this->sherlock_r = sherlock->getCurrentPosition().getRow();
    this->sherlock_c = sherlock->getCurrentPosition().getCol();
}

int RobotS :: findmin(char temp){
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp)
    {
    case 'U':
        return abs(--r - sherlock_r) + abs(c - sherlock_c);
    case 'D':
        return abs(++r - sherlock_r) + abs(c - sherlock_c);
    case 'L':
        return abs(r - sherlock_r) + abs(--c - sherlock_c);
    case 'R':
        return abs(r - sherlock_r) + abs(++c - sherlock_c);
    default:
    break;
    }
}

Position RobotS :: getInit_pos(){
    return this->pos;
}
Position RobotS :: getNextPosition(){
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');
    // U R D L
    int min = min_L;
    if(min_D <= min) min = min_D;
    if(min_R <= min) min = min_R;
    if(min_U <= min) min = min_U;

    int r = init_pos.getRow();
    int c = init_pos.getCol();

    if(min == min_R) c++;
    else if(min == min_D) r++;
    else if(min == min_L) c--;
    else if(min == min_U) r--;

    return Position(r,c);
}

void RobotS :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotS :: getRobotType() const{
    return S;
}

int RobotS :: getDistance() const{
    return abs(sherlock_r - init_pos.getRow()) + abs(sherlock_c - init_pos.getCol());
}
string RobotS :: str() const{
    return ("[pos=]" + init_pos.str() + ";type=" + to_string(robot_type) + "dist=" + to_string(getDistance()));
}
RobotW :: RobotW (int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson) : Robot(index, pos, map, robot_type, criminal, "RobotW"){
    this->index = index;    
    this->pos = init_pos;
    this->map = map;
    this->init_pos = init_pos;
    this->robot_type = W;
    this->watson_r = watson->getCurrentPosition().getRow();
    this->watson_c = watson->getCurrentPosition().getCol();
}

int RobotW :: findmin(char temp){
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp)
    {
    case 'U':
        return abs(--r - watson_r) + abs(c - watson_c);
    case 'D':
        return abs(++r - watson_r) + abs(c - watson_c);
    case 'L':
        return abs(r - watson_r) + abs(--c - watson_c);
    case 'R':
        return abs(r - watson_r) + abs(++c - watson_c);
    default:
    break;
    }  
}


Position RobotW :: getNextPosition(){
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');
    // U R D L
    int min = min_L;
    if(min_D <= min) min = min_D;
    if(min_R <= min) min = min_R;
    if(min_U <= min) min = min_U;

    int r = init_pos.getRow();
    int c = init_pos.getCol();

    if(min == min_R) c++;
    else if(min == min_D) r++;
    else if(min == min_L) c--;
    else if(min == min_U) r--;

    return Position(r,c);
}
Position RobotW :: getInit_pos() {
    return this->pos;
}

void RobotW :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotW :: getRobotType() const{
    return W;
}

int RobotW :: getDistance() const{
    return abs(watson_r - init_pos.getRow()) + abs(watson_c - init_pos.getCol());
}
string RobotW :: str() const{
    return ("[pos=]" + init_pos.str() + ";type=" + to_string(robot_type) + "dist=" + to_string(getDistance()));
}

RobotSW :: RobotSW (int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock , Watson * watson) : Robot(index, pos, map, robot_type, criminal, "RobotSW"){
    this->index = index;
    this->pos = init_pos;
    this->init_pos = init_pos;
    this->map = map;
    this->sherlock_c = sherlock->getCurrentPosition().getCol();
    this->sherlock_r = sherlock->getCurrentPosition().getRow();
    this->watson_c = watson->getCurrentPosition().getCol();
    this->watson_r = watson->getCurrentPosition().getRow();
    this->robot_type = SW;
}

int RobotSW :: findmin(char temp){
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp)
    {
    case '1':
        return abs((r - 1) - sherlock_r) + abs((c + 1) - sherlock_c) + abs((r - 1) - watson_r) + abs((c + 1) - watson_c);
    case '2':
        return abs((r + 1) - sherlock_r) + abs((c + 1) - sherlock_c) + abs((r + 1) - watson_r) + abs((c + 1) - watson_c);
    case '3':
        return abs((r + 1) - sherlock_r) + abs((c - 1) - sherlock_c) + abs((r + 1) - watson_r) + abs((c - 1) - watson_c);
    case '4':
        return abs((r - 1) - sherlock_r) + abs((c - 1) - sherlock_c) + abs((r - 1) - watson_r) + abs((c - 1) - watson_c);
    case 'U':
        return abs((r - 2) - sherlock_r) + abs(c - sherlock_c) + abs((r - 2) - watson_r) + abs(c - watson_c);
    case 'D':
        return abs((r + 2) - sherlock_r) + abs(c - sherlock_c) + abs((r + 2) - watson_r) + abs(c - watson_c);
    case 'L':
        return abs(r - sherlock_r) + abs((c - 2) - sherlock_c) + abs(r - watson_r) + abs((c - 2) - watson_c);
    case 'R':
        return abs(r - sherlock_r) + abs((c + 2) - sherlock_c) + abs(r - watson_r) + abs((c + 2) - watson_c);
    default:
        break;
    }
}

Position RobotSW :: getNextPosition(){
    int min_RU = findmin('1');
    int min_RD = findmin('2');
    int min_LD = findmin('3');
    int min_LU = findmin('4');
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');
    // U RU R RD D LD L LU
    int min = min_LU;
    if(min_L <= min) min = min_L;
    if(min_LD <= min) min = min_LD;
    if(min_D <= min) min = min_D;
    if(min_RD <= min) min = min_RD;
    if(min_R <= min) min = min_R;
    if(min_RU <= min) min = min_RU;
    if(min_U <= min) min = min_U;

    int r = init_pos.getRow();
    int c = init_pos.getCol();

    if(min == min_R) c += 2;
    else if(min == min_D) r += 2;
    else if(min == min_L) c -= 2;
    else if(min == min_U) r -= 2;
    else if(min == min_RU) {
        r -= 1;
        c += 1;
    }
    else if(min == min_RD) {
        r += 1;
        c += 1;
    }
    else if(min == min_LD) {
        r += 1;
        c -= 1;
    }
    else if(min == min_LU) {
        r -= 1;
        c -= 1;
    }

    return Position(r,c);
}

Position RobotSW :: getInit_pos(){
    return this->pos;
}

void RobotSW :: move(){
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if(nextpos != Position :: npos && isValid){
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotSW :: getRobotType() const{
    return SW;
}

int RobotSW :: getDistance() const{
    return abs(watson_r - init_pos.getRow()) + abs(watson_c - init_pos.getCol()) + abs(sherlock_r - init_pos.getRow()) + abs(sherlock_c - init_pos.getCol());
}
string RobotSW :: str() const{
    return ("[pos=]" + init_pos.str() + ";type=" + to_string(robot_type) + "dist=" + to_string(getDistance()));
}

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
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    SherlockBag * sherlock_bag;
    WatsonBag * watson_bag;

    Map * map;
    ArrayMovingObject * arr_mv_objs;

    // map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    // sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    // watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    // criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    // arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    // arr_mv_objs->add(criminal);
    // arr_mv_objs->add(sherlock);
    // arr_mv_objs->add(watson);
    
    sherlock_bag = new SherlockBag(sherlock);
    watson_bag = new WatsonBag(watson);
    sherlock_bag->insert();
    cout << sherlock_bag->getsize() << endl;
    return 0;
}