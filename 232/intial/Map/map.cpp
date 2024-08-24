#include "main.h"

enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum MovingObject
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROTBOT
};

class Position {
private:
    int r;
    int c; //pos
public:

    static const Position npos; 
    
    Position(int r=0, int c=0){
        this->r = r;
        this->c = c;
    };

    Position(const string & str_pos){
        int a;
        for(int i = 0; i < str_pos.size(); i++){
            if(str_pos[i] == ','){
            a = i;
            break;
             }
        }
    this->r = stoi(str_pos.substr(1, a - 1));
    this->c = stoi(str_pos.substr(a + 1, (str_pos.size() - a - 2)));
    };

    int getRow() const{
        return r;
    };
    int getCol() const{
        return c;
    };
    void setRow(int r){
        this->r = r; 
    };
    void setCol(int c){
        this->c = c;
    };

    string str() const{
        return "(" + to_string(r) + "," + to_string(c) + ")";
    };

    bool isEqual(int in_r, int in_c) const{
        if(this->r == in_r && this->c == in_c){
            return true;
        }else{
            return false;
        }
    };
};


class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type){
        this->type = in_type;
    };
    virtual ~MapElement(){};
    virtual ElementType getType() const{};
};

class Path : public MapElement {
public: 
    Path() : MapElement(type) {
        
    }
};  

class Wall : public MapElement {
public: 
    Wall() : MapElement(type){}

};
class FakeWall : public MapElement {
private:
    int req_exp;  
    int r,c; 
public:
    FakeWall(int in_req_exp) : MapElement(type) {
        in_req_exp = ((r * 257 + c * 139 + 89) % 900) + 1;
        this->req_exp = in_req_exp;
    }
    int getReqExp() const{
        return req_exp;
    }

};
class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
     Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
    {

        this->num_rows = num_rows;
        this->num_cols = num_cols;
        
    };
    ~Map(){};
    int getNumRows() const{
        return num_rows;
    };
    int getNumCols() const{
        return num_cols;
    };
    ElementType getElementType(int i, int j) const{};

    bool isValid(int i, int j, MovingObject object, int exp) const{};
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
};
void configuration(string fileName){};