 /*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any
// other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MapElement;
class Path;
class Wall;
class FakeWall;

class Map;
class ArrayMovingObject;
class Position;

class MagicBook;
class EnergyDrink;
class FirstAid;
class ExcemptionCard;
class PassingCard;

class Configuration;

class MovingObject;
class Character;
class Sherlock;
class Watson;
class Criminal;
class Robot;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class BaseItem;
class MagicBook;
class EnergyDrink;
class FirstAid;
class ExcemptionCard;
class PassingCard;

class BaseBag;
class SherlockBag;
class WatsonBag;

class StudyPinkProgram;


class TestStudyInPink;

enum ItemType {
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C = 0, S, W, SW };
enum MovingObjectType { SHERLOCK, WATSON, CRIMINAL, ROBOT };
class MapElement {
    friend class TestStudyInPink;

protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ~MapElement(){};
    virtual ElementType getType() const { return type; };
};

class Path : public MapElement {
    friend class TestStudyInPink;

public:
    Path() : MapElement(PATH){};
    ~Path(){};
};
class Wall : public MapElement {
    friend class TestStudyInPink;

public:
    Wall() : MapElement(WALL){};
    ~Wall(){};
};
class FakeWall : public MapElement {
    friend class TestStudyInPink;

private:
    int r, c;
    int req_exp;

public:
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL) {
        this->req_exp = in_req_exp;
    };
    int getReqExp() const { return req_exp; }
    ~FakeWall(){};
};

class Position {
    friend class TestStudyInPink;

private:
    int r;
    int c;

public:
    static const Position npos;
    Position(int r = 0, int c = 0);
    Position(const string& str_pos);
    bool operator!=(const Position& pos) const {
        return r != pos.r || c != pos.c;
    }
    bool operator==(const Position& pos) const {
        return r == pos.r && c == pos.c;
    }
    int getRow() const { return r; }
    int getCol() const { return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }

    string str() const { return "(" + to_string(r) + "," + to_string(c) + ")"; }

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position& pos) const;
    ~Position(){};
};

class MovingObject {
    friend class TestStudyInPink;

protected:
    int index;
    Position pos;
    Map* map;
    string name;

public:
    MovingObject(int index, const Position pos, Map* map, const string& name = "") : index(index), pos(pos), map(map), name(name){};
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const { return pos; }
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() = 0;
};

class Map {
    friend class TestStudyInPink;

public:
    int num_rows, num_cols;
    Position* array_walls;
    Position* array_fake_walls;
    MapElement*** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position* array_walls,
        int num_fake_walls, Position* array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols) {
        map = new MapElement**[num_rows];
        for (int i = 0; i < num_rows; ++i) {
            map[i] = new MapElement*[num_cols];
            for (int j = 0; j < num_cols; ++j) {
                map[i][j] = new Path();
            }
        }
        for (int i = 0; i < num_fake_walls; ++i) {
            int r = array_fake_walls[i].getRow();
            int c = array_fake_walls[i].getCol();
            int in_req_exp = ((r * 257 + c * 139 + 89) % 900) + 1;
            delete map[r][c];
            map[r][c] = new FakeWall(in_req_exp);
        }
        for (int i = 0; i < num_walls; ++i) {
            int r = array_walls[i].getRow();
            int c = array_walls[i].getCol();
            delete map[r][c];
            map[r][c] = new Wall();
        }
    }
    ~Map() {
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }
    ElementType getElementType(int i, int j) { return map[i][j]->getType(); }
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
    bool isValid(const Position& pos, MovingObject* mv_obj) const;
    bool hople(int r, int c);
};

class Character : public MovingObject {
    friend class TestStudyInPink;

protected:
    int index;
    Position pos;
    Map* map;
    string name;
    int hp, exp;

public:
    Character(int index, const Position pos, Map* map, const string& name = "");
    virtual Position getNextPosition() = 0;
    virtual Position getCurrentPosition() const = 0;
    virtual void setHp(int hp) { this->hp = hp; };

    virtual void setExp(int exp) { this->exp = exp; }
    virtual int GetExp() { return exp; }
    virtual int GetHp() { return hp; }
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual string GetName() { return name; }
    ~Character(){};
};

class Sherlock : public Character {
    friend class TestStudyInPink;

private:
    Position init_pos;
    string moving_rule;
    int current_move_index = 0;
    int hp;
    int exp;
    int index;
    SherlockBag* bag;
public:
    Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int hp, int exp);
    Position getNextPosition() override;
    void setPosition(Position pos);
    MovingObjectType getObjectType() { return SHERLOCK; }
    void setHp(int hp) { this->hp = hp; }
    void setExp(int exp) { this->exp = exp; }
    int GetExp() { return exp; }
    int GetHp() { return hp; }
    Position getInitPosition() { return init_pos; }
    Position getCurrentPosition() const override { return init_pos; }
    void move();
    SherlockBag* getBag() {
        return bag;
    }
    void setBag(SherlockBag* bag) {
        this->bag = bag;
    }
    string str() const override;
    ~Sherlock() {}
};

class Watson : public Character {
    friend class TestStudyInPink;

private:
    Position init_pos;
    string moving_rule;
    int current_move_index = 0;
    int hp;
    int exp;
    int index;
    WatsonBag* bag;

public:
    Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int hp, int exp);
    Position getNextPosition() override;
    void move();
    void setHp(int hp) { this->hp = hp; }
    void setExp(int exp) { this->exp = exp; }
    int GetExp() { return exp; }
    int GetHp() { return hp; }
    Position getInitPosition() { return init_pos; }
    MovingObjectType getObjectType() { return WATSON; }
    Position getCurrentPosition() const override{ return init_pos; }
    string str() const override;
    string getmoving_rule() { return moving_rule; }
    WatsonBag* getBag() {
        return bag;
    }
    void setBag(WatsonBag* bag) {
        this->bag = bag;
    }
    int getcurrent_move_index() { return current_move_index; }
    ~Watson(){};
};

class Criminal : public Character {
    friend class TestStudyInPink;

private:
    int count_move = 0;
    Position init_pos;
    int index;
    int sherlock_r, sherlock_c;
    int watson_r, watson_c;
    Position PrevNextPosition = Position :: npos;
    Sherlock * sherlock;
    Watson * watson;

public:
    Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson);
    Position getNextPosition() override;
    int findmax(char temp);
    MovingObjectType getObjectType() { return CRIMINAL; }
    Position getCurrentPosition() const { return init_pos; }
    int getCount_move() { return count_move; }
    Position getPrevNextPosition() { return PrevNextPosition; }
    void move();
    string str() const override;
    ~Criminal(){};
    // ...
};

class ArrayMovingObject {
    friend class TestStudyInPink;

private:
    MovingObject** arr_mv_objs;
    int count = 0;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject* mv_obj);
    MovingObject* get(int index) const { return arr_mv_objs[index]; };
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class TestStudyInPink;
    friend class StudyPinkProgram;


public:
   int 
        map_num_rows, map_num_cols, 
        max_num_moving_objects,
        num_walls, num_fake_walls, 
        sherlock_init_hp, sherlock_init_exp,
        watson_init_hp, watson_init_exp,
        num_steps;
    Position sherlock_init_pos, watson_init_pos, criminal_init_pos;
    Position *arr_walls, *arr_fake_walls;
    string sherlock_moving_rule, watson_moving_rule;

public:
    Configuration(const string& filepath);
    ~Configuration();
    string str() const;
    void getPosition(const string& value, Position& pos);
    void getArray(const string value, Position*& positions, int& numPositions);
};


class Robot : public MovingObject {
    friend class TestStudyInPink;

private:
    Position init_pos;
    RobotType robot_type;
    Position pos;
    bool first;
protected:
    Criminal* criminal;
    BaseItem* item;
    string name;

public:
    Robot(int index, const Position init_pos, Map* map, RobotType robot_type, Criminal* criminal, const string& name) : MovingObject(index, init_pos, map, name), robot_type(robot_type), criminal(criminal) {    
    this->init_pos = init_pos;
    this->pos = init_pos;
    this->name = "Robot";

}
    MovingObjectType getObjectType() { return ROBOT; }
    static Robot* createRobot(int index, Map* map, Criminal* criminal,Sherlock* Sherlock, Watson* watson, bool& first);
    string GetName() { return name; }
    virtual BaseItem* getItem() { return item; }
    virtual Position getInit_pos() = 0;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual Position getCurrentPosition() const = 0;
    virtual string str() const = 0;
    virtual RobotType getRobotType() const = 0;
    virtual int getDistance() const = 0;

    bool getFirst(){
        return first;
    }
    void setFirst(bool flag){
        this->first = flag;
    }
    ~Robot(){};
};

class RobotC : public Robot {
    friend class TestStudyInPink;

private:
    int r, c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int sherlock_r, sherlock_c;
    int watson_r, watson_c;
    int index;

public:
    RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal);
    Position getNextPosition() override;
    Position getInit_pos() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    Position getCurrentPosition() const override { return init_pos; }
    int getDistance() const override { return 0; }
    int getDistance(Sherlock* sherlock) const;
    int getDistance(Watson* watson) const;
    ~RobotC(){};
};

class RobotS : public Robot {
    friend class TestStudyInPink;

private:
    int r, c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    Sherlock* sherlock;
    int sherlock_r, sherlock_c;
    int index;

public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal,Sherlock* sherlock);
    int findmin(char temp);
    Position getInit_pos() override;
    Position getCurrentPosition() const override { return init_pos; }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    int getDistance() const override;
    ~RobotS(){};
};

class RobotW : public Robot {
    friend class TestStudyInPink;

private:
    int r, c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int watson_r, watson_c;
    int index;
    Watson * watson;

public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal,Watson* watson);
    int findmin(char temp);
    Position getInit_pos() override;
    Position getCurrentPosition() const override { return init_pos; }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    RobotType getRobotType() const override;
    int getDistance() const override;
    ~RobotW(){};
};

class RobotSW : public Robot {
    friend class TestStudyInPink;

private:
    int r, c;
    Position pos;
    Position init_pos;
    RobotType robot_type;
    int sherlock_r, sherlock_c;
    int watson_r, watson_c;
    BaseItem* item;
    Sherlock * sherlock;
    Watson * watson;
    int index;  

public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson);
    int findmin(char temp);
    Position getInit_pos() override;
    Position getCurrentPosition() const override { return init_pos; }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    ~RobotSW(){};
    RobotType getRobotType() const override;
    int getDistance() const override;
};

class BaseItem {
    friend class TestStudyInPink;
private: 
    ItemType type;
public:
    BaseItem(ItemType type);
    virtual ~BaseItem();
    virtual bool canUse(Character* obj, Robot* robot) = 0;
    virtual void use(Character* obj, Robot* robot) = 0;
    virtual ItemType getType() {
        return type;
    };
};

class MagicBook : public BaseItem {
    friend class TestStudyInPink;

public:
    MagicBook () ;
    ~MagicBook(){} ;
    bool canUse(Character* obj, Robot* robot) ;
    void use(Character* obj, Robot* robot) ;
};

class EnergyDrink : public BaseItem {
    friend class TestStudyInPink;

public:
    EnergyDrink();
    ~EnergyDrink();
    bool canUse(Character* obj, Robot* robot) ;
    void use(Character* obj, Robot* robot) ;
};

class FirstAid : public BaseItem {
    friend class TestStudyInPink;

public:
    FirstAid();
    ~FirstAid();
    bool canUse(Character* obj, Robot* robot) ;
    void use(Character* obj, Robot* robot) ;
};

class ExcemptionCard : public BaseItem {
    friend class TestStudyInPink;

public:
    ExcemptionCard();
    ~ExcemptionCard();
    bool canUse(Character* obj, Robot* robot) ;
    void use(Character* obj, Robot* robot) ;
};

class PassingCard : public BaseItem {
    friend class TestStudyInPink;

public:
    string challenge;

public:
    ~PassingCard();
    PassingCard(const string& challenge);
    bool canUse(Character* obj, Robot* robot) ;
    void use(Character* obj, Robot* robot) ;
    string getChallenge() const;
};

class Node {
public:
    BaseItem* item;
    Node* next;

public:
    Node(BaseItem* item = nullptr, Node* next = nullptr)
        : item(item), next(next) {}
};

class BaseBag {
    friend class TestStudyInPink;

protected:
    int size;
    int capacity;
    Node* head;

public:
    BaseBag(int capacity);
    virtual ~BaseBag();
    virtual bool insert(BaseItem* item);
    virtual BaseItem* get() = 0;
    virtual BaseItem* get(ItemType itemType) = 0;
    virtual string str();
};

class SherlockBag : public BaseBag {
    friend class TestStudyInPink;

private:
    Sherlock* sherlock;

public:
    SherlockBag(Sherlock* Character);
    ~SherlockBag(){};
    BaseItem* get() override;
    BaseItem* get(ItemType itemType) override;
    BaseItem* get(Robot* robot);
    int getsize();
};

class WatsonBag : public BaseBag {
    friend class TestStudyInPink;

private:
    Watson* watson;

public:
    WatsonBag(Watson* Character);
    ~WatsonBag(){};
    BaseItem* get() override;
    BaseItem* get(ItemType itemType) override;
    int getsize();
};
// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
    friend class TestStudyInPink;

private:
    // Sample attributes
    int index = 2;
    Configuration* config;

    Sherlock* sherlock;
    Watson* watson;
    Criminal* criminal;

    SherlockBag* sherlock_bag;
    WatsonBag* watson_bag;

    Map* map;
    ArrayMovingObject* arr_mv_objs;

public:
    StudyPinkProgram(const string& config_file_path);

    bool isStop() const;
    void test(){};
    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        } else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        } else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--"
             << criminal->str() << endl;
    }
    void run(bool verbose);
    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
