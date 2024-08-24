#include "study_in_pink2.h"

using namespace std;

MapElement ::MapElement(ElementType in_type) { this->type = in_type; }

bool Map ::isValid(const Position& pos, MovingObject* mv_obj) const {
    int NumRow = getNumRows(); //(1,2)
    int NumCol = getNumCols();
    int r = pos.getRow();
    int c = pos.getCol();
    if (r < 0 || r >= NumRow || c < 0 || c >= NumCol) {
        return false;
    }
    if (map[r][c]->getType() == WALL)
        return false;
    FakeWall* fakeWall = dynamic_cast<FakeWall*>(map[r][c]);
    Watson* watson = dynamic_cast<Watson*>(mv_obj);

    if (watson != nullptr && fakeWall != nullptr) {
        if (watson->GetExp() > fakeWall->getReqExp()) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}
Position ::Position(int r, int c) {
    this->r = r;
    this->c = c;
}

Position ::Position(const string& str_pos) {
    int comma_pos = str_pos.find(",");
    this->r = stoi(str_pos.substr(1, comma_pos - 1));
    this->c =
        stoi(str_pos.substr(comma_pos + 1, (str_pos.size() - comma_pos - 2)));
}

bool Position ::isEqual(int in_r, int in_c) const {
    if (this->r == in_r && this->c == in_c) {
        return true;
    } else {
        return false;
    }
}

bool Position ::isEqual(const Position& pos) const {
    if (this->r == pos.getRow() && this->c == pos.getCol()) {
        return true;
    } else {
        return false;
    }
}

const Position Position::npos = Position(-1, -1);

MovingObject ::~MovingObject() {}

Character ::Character(int index, const Position pos, Map* map,
                      const string& name)
    : MovingObject(index, pos, map, "") {}

Sherlock ::Sherlock(int index, const string& moving_rule,
                    const Position& init_pos, Map* map, int init_hp,
                    int init_exp)
    : Character(index, pos, map, "Sherlock") {
    this->name = "Sherlock";
    this->index = index;
    this->moving_rule = moving_rule;
    this->init_pos = init_pos;
    this->pos = pos;
    this->hp = init_hp;
    this->map = map;
    if (init_hp > 500)
        this->hp = 500;
    if (init_hp == 0) {
    }
    this->moving_rule = moving_rule;
    this->exp = init_hp;
    if (init_exp > 900)
        this->exp = 900;
    if (init_exp == 0) {
    }
}

Position Sherlock ::getNextPosition() {
    int r = this->init_pos.getRow();
    int c = this->init_pos.getCol();
    if (moving_rule.empty()) {
        return Position ::npos;
    }
    char move = moving_rule[current_move_index];
    current_move_index++;
    current_move_index = (current_move_index) % moving_rule.size();
    switch (move) {
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
    bool isValid = this->map->isValid(Position(r, c), this);
    if (!isValid) {
        return Position ::npos;
    }
    return Position(r, c);
}

void Sherlock ::move() {
    Position nextpos = getNextPosition();
    //cout << "nextpos=" << nextpos.str() << endl;
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid && this->GetHp() > 1 && this->GetExp() > 1) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

void Sherlock ::setPosition(Position pos) { this->init_pos = pos; }
string Sherlock ::str() const {
    return "Sherlock[index=" + to_string(this->index) +
           ";pos=" + init_pos.str() + ";moving_rule=" + moving_rule + "]";
}
Watson ::Watson(int index, const string& moving_rule, const Position& init_pos,
                Map* map, int init_hp, int init_exp)
    : Character(index, pos, map, "Watson") {
    this->name = "Watson";
    this->index = index;
    this->moving_rule = moving_rule;
    this->init_pos = init_pos;
    this->pos = pos;
    this->hp = init_hp;
    this->map = map;

    if (init_hp > 500)
        this->hp = 500;
    if (init_hp == 0) {
        // nín
    }
    this->moving_rule = moving_rule;
    this->exp = init_exp;
    if (init_exp > 900)
        this->exp = 900;
    if (init_exp == 0) {
        // nín
    }
}

Position Watson ::getNextPosition() {
    int r = this->init_pos.getRow();
    int c = this->init_pos.getCol();
    if (moving_rule.empty()) {
        return Position ::npos;
    }
    char move = moving_rule[current_move_index];
    current_move_index++;
    current_move_index = (current_move_index) % moving_rule.size();
    switch (move) {
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
    bool isValid = this->map->isValid(Position(r, c), this);
    if (!isValid) {
        return Position ::npos;
    }
    return Position(r, c);
}

void Watson ::move() {
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid && this->GetHp() > 1 && this->GetExp() > 1) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

string Watson ::str() const {
    return "Watson[index=" + to_string(this->index) + ";pos=" + init_pos.str() +
           ";moving_rule=" + moving_rule + "]";
}

Criminal ::Criminal(int index, const Position& init_pos, Map* map,
                    Sherlock* sherlock, Watson* watson)
    : Character(index, pos, map, "Criminal") {
    this->name = "Criminal";
    this->init_pos = init_pos;
    this->index = index;
    this->map = map;
    this->sherlock = sherlock;
    this->watson = watson;
    sherlock_c = sherlock->getCurrentPosition().getCol();
    sherlock_r = sherlock->getCurrentPosition().getRow();
    watson_c = watson->getCurrentPosition().getCol();
    watson_r = watson->getCurrentPosition().getRow();
}

int Criminal ::findmax(char temp) {
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp) {
    case 'U':
        if(r <= 0) return 0;
        else return abs(r - 1 - sherlock_r) + abs(c - sherlock_c) + abs(r - 1 - watson_r) + abs(c - watson_c);
        break;  
    case 'D':
        if(r >= map->getNumRows() - 1) return 0;
        else return abs(r + 1 - sherlock_r) + abs(c - sherlock_c) + abs(r + 1 - watson_r) + abs(c - watson_c);
        break;
    case 'L':
        if(c <= 0) return 0;
        else return abs(r - sherlock_r) + abs(c - 1 - sherlock_c) + abs(r - watson_r) + abs(c - 1 - watson_c);
        break;
    case 'R':
        if(c >= map->getNumCols() - 1) return 0;
        else return abs(r - sherlock_r) + abs(c + 1 - sherlock_c) + abs(r - watson_r) + abs(c + 1 - watson_c);
        break;
    default:
        break;
    }
    return 0;
}

Position Criminal ::getNextPosition() {
    sherlock_c = sherlock->getCurrentPosition().getCol();
    sherlock_r = sherlock->getCurrentPosition().getRow();
    watson_c = watson->getCurrentPosition().getCol();
    watson_r = watson->getCurrentPosition().getRow();
    int max_R = findmax('R');
    int max_D = findmax('D');
    int max_L = findmax('L');
    int max_U = findmax('U');
    int r = init_pos.getRow();
    int c = init_pos.getCol();
   
    //static int a = 0;
    int max = -123456789;
    char max_char;
    //cout << "hientai" << sherlock_r << " " << sherlock_c << " " << watson_r << " " << watson_c << endl;
    //cout << a++ << "R: " << max_R << " " << "D: " << max_D << " "<< "L: " << max_L << " " << "U: " << max_U << endl;
    if(this->map->hople(r, c + 1)){
        max = max_R;
        max_char = 'R';
    }else if(this->map->hople(r + 1, c)){
        max = max_D;
        max_char = 'D';
    }else if(this->map->hople(r, c - 1)){
        max = max_L;
        max_char = 'L';
    }else if(this->map->hople(r - 1, c)){
        max = max_U;
        max_char = 'U';
    }

    if ((max_D >= max) && this->map->hople(r + 1, c)) {
        max = max_D;
        max_char = 'D';
    }
    if (max_L >= max && this->map->hople(r, c - 1)) {
        max = max_L;
        max_char = 'L';
    }
    if (max_U >= max && this->map->hople(r - 1, c)) {
        max = max_U;
        max_char = 'U';
    }

    if (max_char == 'R')
        c++;
    else if (max_char == 'D')
        r++;
    else if (max_char == 'L')
        c--;
    else if (max_char == 'U')
        r--;
    if(init_pos == Position(r, c)){
        return Position :: npos;
    }
    return Position(r, c);
}

void Criminal ::move() {
    Position nextpos = getNextPosition();
    if(nextpos == init_pos) PrevNextPosition = Position :: npos;
    else this->PrevNextPosition = init_pos;
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position :: npos && isValid ) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
        this->count_move++;
    }
}

string Criminal ::str() const {
    return "Criminal[index=" + to_string(this->index) +
           ";pos=" + init_pos.str() + "]";
}

ArrayMovingObject ::ArrayMovingObject(int capacity) {
    this->capacity = capacity;
    arr_mv_objs = new MovingObject*[capacity];

    for (int i = 0; i < capacity; i++) {
        arr_mv_objs[i] = nullptr;
    }
}

ArrayMovingObject ::~ArrayMovingObject() { delete[] arr_mv_objs; }

bool ArrayMovingObject ::isFull() const { return (count == capacity); }

bool ArrayMovingObject ::add(MovingObject* mv_obj) {
    if (this->isFull())
        return false;
    arr_mv_objs[this->count] = mv_obj;
    count++;
    return true;
}

int ArrayMovingObject ::size() const { return count; }
string ArrayMovingObject ::str() const {
    string ans = "ArrayMovingObject[count=" + to_string(count) +
                 ";capacity=" + to_string(capacity) + ";";
    for (int i = 0; i < count - 1; i++) {
        if (arr_mv_objs[i] != nullptr) {
            ans += arr_mv_objs[i]->str() + ";";
        }
    }
    ans += arr_mv_objs[count - 1]->str() + "]";
    return ans;
}

Configuration ::Configuration(const string& filepath) {
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
Configuration ::~Configuration() {
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

string Configuration ::str() const {
    string ans =
        "Configuration[ \nMAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
    ans += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
    ans += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
    ans += "NUM_WALLS=" + to_string(num_walls) + "\n";
    ans += "ARRAY_WALLS=[";
    if(num_walls > 0){
        for (int i = 0; i < num_walls - 1; i++) {
            ans += arr_walls[i].str() + ";";
        }
        ans += arr_walls[num_walls - 1].str() + "]\n";
    }else{
        ans += "]\n";
    }
    ans += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
    ans += "ARRAY_FAKE_WALLS=[";
    if(num_fake_walls > 0){
        for (int i = 0; i < num_fake_walls - 1; i++) {
            ans += arr_fake_walls[i].str() + ";";
        }
        ans += arr_fake_walls[num_fake_walls - 1].str() + "]\n";
    }else{
        ans += "]\n";
    }
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

void Configuration ::getPosition(const string& value, Position& pos) {
    int comma_pos = value.find(",");
    pos.setRow(stoi(value.substr(1, comma_pos - 1)));
    pos.setCol(
        stoi(value.substr(comma_pos + 1, (value.size() - comma_pos - 2))));
}

void Configuration ::getArray(const string value, Position*& arr, int& num) {
    num = 0;
    int count = 1;
    for (int i = 0; i < value.length(); i++) {
        if (value[i] == ',') {
            num++;
        }
    }
    arr = new Position[num];
    int start = 0;
    int r, c;
    for (int i = 0; i < value.length(); i++) {

        if (value[i] == '(') {
            int count = 0;
            int j = i;
            while (value[j] != ',') {
                count++;
                j++;
            }
            r = stoi(value.substr(i + 1, count - 1));
        }
        if (value[i] == ',') {
            int count = 0;
            int j = i;
            while (value[j] != ')') {
                count++;
                j++;
            }
            c = stoi(value.substr(i + 1, count - 1));
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

Robot* Robot ::createRobot(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson, bool& first) {
    Robot* robot;
    int distance_sherlock = abs(sherlock->getCurrentPosition().getRow() - criminal->getPrevNextPosition().getRow()) + abs(sherlock->getCurrentPosition().getCol() - criminal->getPrevNextPosition().getCol());
    int distance_watson = abs(watson->getCurrentPosition().getRow() - criminal->getPrevNextPosition().getRow()) + abs(watson->getCurrentPosition().getCol() - criminal->getPrevNextPosition().getCol());

    Position pos_cri = criminal->getPrevNextPosition();

    if (first == 1) {
        robot = new RobotC(index, pos_cri, map, criminal);
        first = 0;
    } else {
        if (distance_sherlock < distance_watson) {
            robot = new RobotS(index, pos_cri, map, criminal, sherlock);
        } else if (distance_sherlock > distance_watson) {
            robot = new RobotW(index, pos_cri, map, criminal, watson);
        } else {
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
        robot->item = new FirstAid();
    } else if (s >= 6 && s <= 7) {
        robot->item = new ExcemptionCard();
    } else if (s >= 8 && s <= 9) {
        int i = pos_cri.getRow();
        int j = pos_cri.getCol();
        int t = (i * 11 + j) % 4;
        string challenge;
    switch (t) {
    case 0:
        challenge = "RobotS";
        break;
    case 1:
        challenge = "RobotC";
        break;
    case 2:
        challenge = "RobotSW";
        break;
    case 3:
        challenge = "all";
        break;
    }
        robot->item = new PassingCard(challenge);
    }
    return robot;
}
RobotC ::RobotC(int index, const Position& init_pos, Map* map,
                Criminal* criminal)
    : Robot(index, pos, map, robot_type, criminal, "RobotC") {
    this->index = index;
    this->robot_type = C;
    this->init_pos = init_pos;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
}

Position RobotC ::getInit_pos() { return this->pos; }
Position RobotC ::getNextPosition() {
    int r = criminal->getPrevNextPosition().getRow();
    int c = criminal->getPrevNextPosition().getCol();
    if(r == init_pos.getRow() && c == init_pos.getCol()) {
        return Position(-1, -1);
    }
    return Position(r, c);
}

void RobotC ::move() {
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotC ::getRobotType() const { return C; }

int RobotC ::getDistance(Sherlock* sherlock) const {
    int r = sherlock->getCurrentPosition().getRow();
    int c = sherlock->getCurrentPosition().getCol();
    return abs(r - init_pos.getRow()) + abs(c - init_pos.getCol());
}

int RobotC ::getDistance(Watson* watson) const {
    int r = watson->getCurrentPosition().getRow();
    int c = watson->getCurrentPosition().getCol();
    return abs(r - init_pos.getRow()) + abs(c - init_pos.getCol());
}

string RobotC ::str() const {
    return ("Robot[pos=" + init_pos.str() + ";type=" + "C" + ";dist=]");
}

RobotS ::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
    : Robot(index, pos, map, robot_type, criminal, "RobotS") {
    this->init_pos = init_pos;
    this->index = index;
    this->pos = init_pos;
    this->robot_type = S;
    this->map = map;
    this->sherlock = sherlock;
    this->sherlock_r = sherlock->getCurrentPosition().getRow();
    this->sherlock_c = sherlock->getCurrentPosition().getCol();

}

int RobotS ::findmin(char temp) {
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp) {
    case 'U':
        if(r <= 0) return 2000000000;
        else return abs(r - 1 - sherlock_r) + abs(c - sherlock_c);
        break;
    case 'D':
        if(r >= map->getNumRows() - 1) return 2000000000;
        else return abs(r + 1 - sherlock_r) + abs(c - sherlock_c);
        break;
    case 'L':
        if(c <= 0) return 2000000000;
        else return abs(r - sherlock_r) + abs(c - 1 - sherlock_c);
        break;
    case 'R':
        if(c >= map->getNumCols() - 1) return 2000000000;
        else return abs(r - sherlock_r) + abs(c + 1 - sherlock_c);
        break;
    default:
        break;
    }
    return 0;
}

bool Map :: hople(int r, int c) {
    if(r >= 0 && r < num_rows && c >= 0 && c < num_cols){
        if(map[r][c]->getType() != WALL){
            return true;
        }
    }
    return false;
}

Position RobotS ::getInit_pos() { return this->pos; }
Position RobotS ::getNextPosition() {
    this->sherlock_r = sherlock->getCurrentPosition().getRow();
    this->sherlock_c = sherlock->getCurrentPosition().getCol();
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');
    // U R D L
    int r = init_pos.getRow();
    int c = init_pos.getCol();

     int min ;
    char min_char;
    if(this->map->hople(r, c + 1)){
        min = min_R;
        min_char = 'R';
    }else if(this->map->hople(r + 1, c)){
        min = min_D;
        min_char = 'D';
    }else if(this->map->hople(r, c - 1)){
        min = min_L;
        min_char = 'L';
    }else if(this->map->hople(r - 1, c)){
        min = min_U;
        min_char = 'U';
    }

    if(min_L <= min && this->map->hople(r, c - 1)){
        min_char = 'L';
        min = min_L;
    }
    if (min_D <= min && this->map->hople(r + 1, c)){
        min_char = 'D';
        min = min_D;
    }    
    if (min_R <= min && this->map->hople(r, c + 1)){
        min_char = 'R';
        min = min_R;
    }    
    if (min_U <= min && this->map->hople(r - 1, c)){
        min_char = 'U';
        min = min_U;
    }

    if (min_char == 'R')
        c++;
    else if (min_char == 'D')
        r++;
    else if (min_char == 'L')
        c--;
    else if (min_char == 'U')
        r--;
    return Position(r, c);
}
void RobotS ::move() {
    Position nextpos = getNextPosition();
    //cout << nextpos.str() << endl;
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotS ::getRobotType() const { return S; }

int RobotS ::getDistance() const {
    return abs(sherlock_r - init_pos.getRow()) +
           abs(sherlock_c - init_pos.getCol());
}
string RobotS ::str() const {
    return ("Robot[pos=" + init_pos.str() + ";type=" + "S" +
            ";dist=" + to_string(getDistance()) + "]");
}
RobotW ::RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
    : Robot(index, pos, map, robot_type, criminal, "RobotW") {
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->init_pos = init_pos;
    this->robot_type = W;
    this->watson = watson;
    this->watson_r = watson->getCurrentPosition().getRow();
    this->watson_c = watson->getCurrentPosition().getCol();
}

int RobotW ::findmin(char temp) {
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp) {
    case 'U':
        if(r <= 0) return 2000000000;
        else return abs(r - 1 - watson_r) + abs(c - watson_c);
        break;
    case 'D':
        if(r >= map->getNumRows() - 1) return 2000000000;
        else return abs(r + 1 - watson_r) + abs(c - watson_c);
        break;
    case 'L':
        if(c <= 0) return 2000000000;
        else return abs(r - watson_r) + abs(c - 1 - watson_c);
        break;
    case 'R':
        if(c >= map->getNumCols() - 1) return 2000000000;
        else return abs(r - watson_r) + abs(c + 1 - watson_c);
        break;
    default:
        break;
    }
    return 0;
}
Position RobotW ::getNextPosition() {
    watson_r = watson->getCurrentPosition().getRow();
    watson_c = watson->getCurrentPosition().getCol();
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');

    int r = init_pos.getRow();
    int c = init_pos.getCol();
    // U R D L
    //cout << a++ << " " << r << " " << c << " " << min_L << " " << min_D << " " << min_R << " " << min_U << ";" <<  watson_r << " " << watson_c;

    int min ;
    char min_char;
    if(this->map->hople(r, c + 1)){
        min = min_R;
        min_char = 'R';
    }else if(this->map->hople(r + 1, c)){
        min = min_D;
        min_char = 'D';
    }else if(this->map->hople(r, c - 1)){
        min = min_L;
        min_char = 'L';
    }else if(this->map->hople(r - 1, c)){
        min = min_U;
        min_char = 'U';
    }

    if(min_L <= min && this->map->hople(r, c - 1)){
        min_char = 'L';
        min = min_L;
    }    
    if (min_D <= min && this->map->hople(r + 1, c)){
        min_char = 'D';
        min = min_D;
    }    
    if (min_R <= min && this->map->hople(r, c + 1)){
        min_char = 'R';
        min = min_R;
    }    
    if (min_U <= min && this->map->hople(r - 1, c)){
        min_char = 'U';
        min = min_U;
    }
    
    if (min_char == 'R')
        c++;
    else if (min_char == 'D')
        r++;
    else if (min_char == 'L')
        c--;
    else if (min_char == 'U')
        r--;

    return Position(r, c);
}
Position RobotW ::getInit_pos() { return this->pos; }

void RobotW ::move() {
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotW ::getRobotType() const { return W; }

int RobotW ::getDistance() const {
    int row = watson->getCurrentPosition().getRow();
    int col = watson->getCurrentPosition().getCol();
    return abs(row - init_pos.getRow()) +
           abs(col - init_pos.getCol());
}
string RobotW ::str() const {
    return ("Robot[pos=" + init_pos.str() + ";type=" + "W" +
            ";dist=" + to_string(getDistance()) + "]");
}

RobotSW ::RobotSW(int index, const Position& init_pos, Map* map,
                  Criminal* criminal, Sherlock* sherlock, Watson* watson)
    : Robot(index, pos, map, robot_type, criminal, "RobotSW") {
    this->index = index;
    this->pos = init_pos;
    this->init_pos = init_pos;
    this->map = map;
    this->robot_type = SW;
    this->sherlock = sherlock;
    this->watson = watson;
    this->sherlock_c = sherlock->getCurrentPosition().getCol();
    this->sherlock_r = sherlock->getCurrentPosition().getRow();
    this->watson_c = watson->getCurrentPosition().getCol();
    this->watson_r = watson->getCurrentPosition().getRow();
}

int RobotSW ::findmin(char temp) {
    int r = init_pos.getRow();
    int c = init_pos.getCol();
    switch (temp) {
    case '1':
        if(r - 1 < 0 || c + 1 > map->getNumCols() - 1) return 2000000000;
        else return abs((r - 1) - sherlock_r) + abs((c + 1) - sherlock_c) +
               abs((r - 1) - watson_r) + abs((c + 1) - watson_c);
    case '2':
        if(r + 1 > map->getNumRows() - 1 || c + 1 > map->getNumCols() - 1) return 2000000000;
        else return abs((r + 1) - sherlock_r) + abs((c + 1) - sherlock_c) +
               abs((r + 1) - watson_r) + abs((c + 1) - watson_c);
    case '3':
        if(r + 1 > map->getNumRows() - 1 || c - 1 < 0) return 2000000000;
        else return abs((r + 1) - sherlock_r) + abs((c - 1) - sherlock_c) +
               abs((r + 1) - watson_r) + abs((c - 1) - watson_c);
    case '4':
        if(r - 1 < 0 || c - 1 < 0) return 2000000000;
        else return abs((r - 1) - sherlock_r) + abs((c - 1) - sherlock_c) +
               abs((r - 1) - watson_r) + abs((c - 1) - watson_c);
    case 'U':
        if(r - 2 < 0) return 2000000000;
        else return abs((r - 2) - sherlock_r) + abs(c - sherlock_c) +
               abs((r - 2) - watson_r) + abs(c - watson_c);
    case 'D':
        if(r + 2 > map->getNumRows() - 1) return 2000000000;
        else return abs((r + 2) - sherlock_r) + abs(c - sherlock_c) +
               abs((r + 2) - watson_r) + abs(c - watson_c);
    case 'L':
        if(c - 2 < 0) return 2000000000;
        else return abs(r - sherlock_r) + abs((c - 2) - sherlock_c) +
               abs(r - watson_r) + abs((c - 2) - watson_c);
    case 'R':
        if(c + 2 > map->getNumCols() - 1) return 2000000000;
        else return abs(r - sherlock_r) + abs((c + 2) - sherlock_c) +
               abs(r - watson_r) + abs((c + 2) - watson_c);
    default:
        break;
    }
    return 0;
}

Position RobotSW ::getNextPosition() {
    sherlock_c = sherlock->getInitPosition().getCol();
    sherlock_r = sherlock->getInitPosition().getRow();
    watson_c = watson->getInitPosition().getCol();
    watson_r = watson->getInitPosition().getRow();
    int min_RU = findmin('1');
    int min_RD = findmin('2');
    int min_LD = findmin('3');
    int min_LU = findmin('4');
    int min_R = findmin('R');
    int min_D = findmin('D');
    int min_L = findmin('L');
    int min_U = findmin('U');

    int r = init_pos.getRow();
    int c = init_pos.getCol();  
    // U 1 R 2 D 3 L 4
    int min;
    int min_char;
    if(this->map->hople(r - 1, c - 1)){
        min_char = '4';
        min = min_LU;
    }else if(this->map->hople(r, c - 2)){
        min_char = 'L';
        min = min_L;
    }else if(this->map->hople(r + 1, c - 1)){
        min_char = '3';
        min = min_LD;
    }else if(this->map->hople(r + 2, c)){
        min_char = 'D';
        min = min_D;
    }else if(this->map->hople(r + 1, c + 1)){
        min_char = '2';
        min = min_RD;
    }else if(this->map->hople(r, c + 2)){
        min_char = 'R';
        min = min_R;
    }else if(this->map->hople(r - 1, c + 1)){
        min_char = '1';
        min = min_RU;
    }else if(this->map->hople(r - 2, c)){
        min_char = 'U';
        min = min_U;
    }

    if(min_LU < min && this->map->hople(r - 1, c - 1)){
        min_char = '4';
        min = min_LU;
    }
        if (min_L <= min && this->map->hople(r, c - 2)){
        min_char = 'L';
        min = min_L;
    }    
    if (min_LD <= min && this->map->hople(r + 1, c - 1)){
        min_char = '3';
        min = min_LD;
    }    
    if (min_D <= min && this->map->hople(r + 2, c)){
        min_char = 'D';
        min = min_D;
    }    
    if (min_RD <= min && this->map->hople(r + 1, c + 1)){
        min_char = '2';
        min = min_RD;
    }    
    if (min_R <= min && this->map->hople(r, c + 2)){
        min_char = 'R';
        min = min_R;
    }    
    if (min_RU <= min && this->map->hople(r - 1, c + 1)){
        min_char = '1';
        min = min_RU;
    }    
    if (min_U <= min && this->map->hople(r - 2, c)){
        min_char = 'U';
        min = min_U;
    }

    if (min_char == 'R')
        c += 2;
    else if (min_char == 'D')
        r += 2;
    else if (min_char == 'L')
        c -= 2;
    else if (min_char == 'U')
        r -= 2;
    else if (min_char == '1') {
        r -= 1;
        c += 1;
    } else if (min_char == '2') {
        r += 1;
        c += 1;
    } else if (min_char == '3') {
        r += 1;
        c -= 1;
    } else if (min_char == '4') {
        r -= 1;
        c -= 1;
    }
    return Position(r, c);
}

Position RobotSW ::getInit_pos() { return this->pos; }

void RobotSW ::move() {
    Position nextpos = getNextPosition();
    bool isValid = this->map->isValid(nextpos, this);
    if (nextpos != Position ::npos && isValid) {
        this->init_pos.setRow(nextpos.getRow());
        this->init_pos.setCol(nextpos.getCol());
    }
}

RobotType RobotSW ::getRobotType() const { return SW; }

int RobotSW ::getDistance() const {
    return abs(watson_r - init_pos.getRow()) +
           abs(watson_c - init_pos.getCol()) +
           abs(sherlock_r - init_pos.getRow()) +
           abs(sherlock_c - init_pos.getCol());
}
string RobotSW ::str() const {
   return ("Robot[pos=" + init_pos.str() + ";type=" + "SW" +
            ";dist=" + to_string(getDistance()) + "]");
}

bool MagicBook ::canUse(Character* obj, Robot* robot) {
    int exp = obj->GetExp();
    return (robot == nullptr && exp <= 350);
}

void MagicBook ::use(Character* obj, Robot* robot) {
    if (canUse(obj, robot) == true) {
        obj->setExp(ceil((float)(obj->GetExp()) * 1.25));
    }
}

ItemType MagicBook ::getType() const { return MAGIC_BOOK; }

bool EnergyDrink ::canUse(Character* obj, Robot* robot) {
    int hp = obj->GetHp();
    return (robot == nullptr && hp <= 100);
}

void EnergyDrink ::use(Character* obj, Robot* robot) {
    if (canUse(obj, robot) == true) {
        obj->setHp(ceil((float)obj->GetHp() * 1.2));
    }
}

ItemType EnergyDrink ::getType() const { return ENERGY_DRINK; }

bool FirstAid ::canUse(Character* obj, Robot* robot) {
    int hp = obj->GetHp();
    int exp = obj->GetExp();
    return ((hp <= 100 || exp <= 350) && robot == nullptr);
}

void FirstAid ::use(Character* obj, Robot* robot) {
    if (canUse(obj, robot) == true) {
        obj->setHp(ceil((float)obj->GetHp() * 1.5));
    }
}

ItemType FirstAid ::getType() const { return FIRST_AID; }

bool ExcemptionCard ::canUse(Character* obj, Robot* robot) {
    int hp = obj->GetHp();
    string name = obj->GetName();
    return ((hp % 2 == 1 && name == "Sherlock") && robot != nullptr);
}

void ExcemptionCard ::use(Character* obj, Robot* robot) {
if (!canUse(obj, robot)) return;
    Sherlock* sherlock = dynamic_cast<Sherlock*>(obj);
    switch (robot->getType()) {
        case C:
            if (sherlock->getHp() > 500) sherlock->setPos(robot->getNextPosition());
            else sherlock->getBag()->insert(robot->getItem());
            break;
        case S:
            if (sherlock->getExp() > 400) sherlock->getBag()->insert(robot->getItem());
            break;
        case W:
            sherlock->getBag()->insert(robot->getItem());
            break;
        case SW:
            if (sherlock->getExp() > 300 && sherlock->getHp() > 335) 
                sherlock->getBag()->insert(robot->getItem());
            break;
    }
}

ItemType ExcemptionCard ::getType() const { return EXCEMPTION_CARD; }

PassingCard ::PassingCard(string challenge) {
    this->challenge = challenge;
}

bool PassingCard ::canUse(Character* obj, Robot* robot) {
    if (obj->GetName() == "Watson" && obj->GetHp() % 2 == 0 && robot != nullptr ) {
        if(challenge == "all" || challenge == robot->GetName())
        return true;
    }
    return false;
}

void PassingCard ::use(Character* obj, Robot* robot) {
      if (!canUse(obj, robot)) return;
    Watson* watson = dynamic_cast<Watson*>(obj);
    int exp = watson->getExp();
    if (challenge == "all") exp += 50;
    if (challenge == "RobotS" && robot->getType() == S) exp += 50;
    if (challenge == "RobotC" && robot->getType() == C) exp += 50;
    if (challenge == "RobotSW" && robot->getType() == SW) exp += 50;
    exp -= 50;
    if (exp < 0) exp = 0;
    watson->setExp(exp); 
    switch (robot->getType()) {
        case W: 
            if (exp > 350) watson->getBag()->insert(robot->getItem());
            break;
        case SW:
            if (exp > 165 && watson->getHp() > 600) watson->getBag()->insert(robot->getItem());
            break;
        case C:
            watson->getBag()->insert(robot->getItem());
            break;
        default: 
            break;
    }
}

ItemType PassingCard ::getType() const { return PASSING_CARD; }

string PassingCard ::getChallenge() const { return challenge; }

BaseBag ::BaseBag(int capacity) {
    this->capacity = capacity;
    size = 0;
    head = nullptr;
}

bool BaseBag ::insert(BaseItem* item) {
    if (this->size == this->capacity)
        return false;
    if(head == NULL){
        head = new Node(item);
        size++;
        return true;
    }else{   
        Node* newNode = new Node(item, head);
        head = newNode;
        size++;
        return true;
    }
    return false;
}

string BaseBag :: str(){
    string ans = "Bag[count=" + to_string(size) + ";";
    Node* curr = this->head;
    string nameItem[5] = {"MagicBook", "EnergyDrink", "FirstAid", "ExcemptionCard", "PassingCard"};
    while (curr != NULL) {
        int i = curr->item->getType();
        ans += nameItem[i] + ";";
        curr = curr->next;
    }
    return ans + "]";
}

BaseBag ::~BaseBag() {
    Node* curr = head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        delete curr->item;
        delete temp;
    }
    head = nullptr;
}

SherlockBag ::SherlockBag(Sherlock* Character)
    : BaseBag(13), sherlock(Character) {
        this->sherlock = Character;
    }

BaseItem* SherlockBag ::get() {
    if (size == 0) {
        return nullptr;
    }

    Node* curr = head;
    while (curr != NULL && !curr->item->canUse((this->sherlock), nullptr)) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        return nullptr;
    }

    if (curr != head) {
        BaseItem* swap;
        swap = curr->item;
        curr->item = head->item;
        head->item = swap;
    }

    BaseItem* item = head->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return item;
}

BaseItem* SherlockBag ::get(ItemType itemType) {
    if (size == 0) {
        return nullptr;
    }
    Node* curr = head;
    while (curr != NULL && curr->item->getType() != itemType) {
        curr = curr->next;
    }

    if (!curr) {
        return nullptr;
    }
    if (curr != head) {
        BaseItem* swap;
        swap = curr->item;
        curr->item = head->item;
        head->item = swap;
    }
    BaseItem* item = curr->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;

    return item;
}

BaseItem* SherlockBag ::get(Robot* robot) {
    if (size == 0) {
        return nullptr;
    }

    Node* curr = head;
    while (curr != NULL && !curr->item->canUse((this->sherlock), robot)) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        return nullptr;
    }

    if (curr != head) {
        BaseItem* swap;
        swap = curr->item;
        curr->item = head->item;
        head->item = swap;
    }

    BaseItem* item = head->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return item;
}

int SherlockBag ::getsize() { return size; }
WatsonBag ::WatsonBag(Watson* Character) : BaseBag(13), watson(Character) {
    this->watson = Character;
}

BaseItem* WatsonBag ::get() {
    if (size == 0) {
        return nullptr;
    }
    Node* curr = head;
    while (curr != NULL && !curr->item->canUse((this->watson), nullptr)) {
        curr = curr->next;
    }

    cout << endl;
    if (curr == nullptr) {
        return nullptr;
    }

    if (curr != head) {
        BaseItem* swap;
        swap = curr->item;
        curr->item = head->item;
        head->item = swap;
    }

    BaseItem* item = head->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return item;
}

BaseItem* WatsonBag ::get(ItemType itemType) {
    if (size == 0) {
        return nullptr;
    }

    Node* curr = head;
    while (curr != NULL && !curr->item->canUse((this->watson), nullptr)) {
        curr = curr->next;
    }

    cout << endl;
    if (curr == nullptr) {
        return nullptr;
    }

    if (curr != head) {
        BaseItem* swap;
        swap = curr->item;
        curr->item = head->item;
        head->item = swap;
    }

    BaseItem* item = head->item;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return item;
}

int WatsonBag ::getsize() { return size; }
StudyPinkProgram ::StudyPinkProgram(const string& config_file_path) {
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls,
                  config->arr_walls, config->num_fake_walls,
                  config->arr_fake_walls);

    sherlock =
        new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos,
                     map, config->sherlock_init_hp, config->sherlock_init_exp);
    // cout << sherlock->str() << endl;
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos,
                        map, config->watson_init_hp, config->watson_init_exp);
    // cout << watson->str() << endl;
    criminal =
        new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    // cout << criminal->str() << endl;
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    // cout << arr_mv_objs->str();
    arr_mv_objs->add(criminal);
    // cout << arr_mv_objs->str();
    arr_mv_objs->add(sherlock);
    // cout << arr_mv_objs->str();
    arr_mv_objs->add(watson);
    // cout << arr_mv_objs->str();
    sherlock_bag = new SherlockBag(sherlock);
    // cout << sherlock_bag->str() << endl;
    watson_bag = new WatsonBag(watson);
    // cout << sherlock_bag->str() << endl;
}

bool StudyPinkProgram ::isStop() const {
    if (sherlock->GetHp() <= 0 || watson->GetHp() <= 0 ||
        criminal->getCurrentPosition() == watson->getCurrentPosition() ||
        criminal->getCurrentPosition() == sherlock->getCurrentPosition()) {

        return 1;
    } else {
        return 0;
    }
}

void StudyPinkProgram ::run(bool verbose) {
    bool first = 1;
    for (int istep = 0; istep < config->num_steps; ++istep) {
        for (int i = 0; i < arr_mv_objs->size(); ++i) {
            if (arr_mv_objs->get(i) == nullptr)
                continue;
            arr_mv_objs->get(i)->move();
            if (arr_mv_objs->get(i)->getObjectType() == ROBOT) {
                Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(i));
                if (sherlock->getCurrentPosition() == robot->getCurrentPosition()) {
                    if (robot->getRobotType() == S) {
                        if (sherlock->GetExp() > 400) {
                            sherlock_bag->insert(robot->getItem());
                        } else {
                            if (sherlock->GetHp() % 2 == 1) {
                                BaseItem* card =
                                    sherlock_bag->get(EXCEMPTION_CARD);
                                if (card == nullptr) {
                                    sherlock->setExp(
                                        ceil((float)sherlock->GetExp() * 0.9));
                                }
                            }
                        }
                        //cout << sherlock_bag->str() << endl;
                        BaseItem* vatpham = sherlock_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(sherlock, nullptr);
                        }
                    } else if (robot->getRobotType() == W) {
                        sherlock_bag->insert(robot->getItem());
                        BaseItem* vatpham = sherlock_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(sherlock, nullptr);
                        }
                    } else if (robot->getRobotType() == SW) {
                        if (sherlock->GetExp() > 300 ||
                            sherlock->GetHp() > 335) {
                            sherlock_bag->insert(robot->getItem());
                        } else {
                            BaseItem* card = sherlock_bag->get(EXCEMPTION_CARD);
                            if (card == nullptr) {
                                sherlock->setExp(
                                    ceil((float)sherlock->GetExp() * 0.85));
                                sherlock->setHp(
                                    ceil((float)sherlock->GetHp() * 0.85));
                            }
                        }
                        BaseItem* vatpham = sherlock_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(sherlock, nullptr);
                        }
                    } else if (robot->getRobotType() == C) {
                        if (sherlock->GetHp() > 500) {
                            sherlock->setPosition(
                                criminal->getCurrentPosition());
                        }
                        BaseItem* vatpham = sherlock_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(sherlock, nullptr);
                        }
                    }
                }
                if (watson->getCurrentPosition() == robot->getCurrentPosition()) {
                    if (robot->getRobotType() == S) {
                        BaseItem* vatpham = watson_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(watson, nullptr);
                        }
                    } else if (robot->getRobotType() == W) {
                        if (watson->GetHp() % 2 == 0) {
                            PassingCard* card = dynamic_cast<PassingCard*>(
                                watson_bag->get(PASSING_CARD));
                            if (card != nullptr) {
                                if (card->getChallenge() == "all" ||
                                    card->getChallenge() == "RobotW") {
                                    watson_bag->insert(robot->getItem());
                                } else {
                                    watson->setExp(
                                        ceil((float)watson->GetExp() - 50));
                                    watson_bag->insert(robot->getItem());
                                }
                            }
                        }
                        if (watson->GetHp() > 350) {
                            watson_bag->insert(robot->getItem());

                        } else {
                            watson->setHp(ceil((float)watson->GetHp() * 0.95));
                        }
                        BaseItem* vatpham = watson_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(watson, nullptr);
                        }
                    } else if (robot->getRobotType() == SW) {
                        if (watson->GetHp() % 2 == 0) {
                            PassingCard* card = dynamic_cast<PassingCard*>(
                                watson_bag->get(PASSING_CARD));
                            if (card != nullptr) {
                                if (card->getChallenge() == "all" ||
                                    card->getChallenge() == "RobotSW") {
                                    watson_bag->insert(robot->getItem());
                                } else {
                                    watson->setExp(
                                        ceil((float)watson->GetExp() - 50));
                                    watson_bag->insert(robot->getItem());
                                }
                            }
                        }
                        if (watson->GetExp() > 600 && watson->GetHp() > 165) {
                            watson_bag->insert(robot->getItem());
                        } else {
                            watson->setExp(
                                ceil((float)watson->GetExp() * 0.85));
                            watson->setHp(ceil((float)watson->GetHp() * 0.85));
                        }
                        BaseItem* vatpham = watson_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(watson, nullptr);
                        }
                    } else if (robot->getRobotType() == C) {
                        watson_bag->insert(robot->getItem());
                        BaseItem* vatpham = watson_bag->get();
                        if (vatpham != nullptr) {
                            vatpham->use(watson, nullptr);
                        }
                    }
                }
            }
            // if (verbose) {
            // printStep(istep);
            // //cout << istep << endl;
            // cout << watson_bag->str() << endl;
            // cout << sherlock_bag->str() << endl;
            // }   
        }
        if (criminal->getCount_move() % 3 == 0) {
            if (!(arr_mv_objs->isFull())) {
                index++;
                Robot* robot = Robot ::createRobot(index, map, criminal, sherlock, watson, first);
                arr_mv_objs->add(robot);
            }
        }
        if (watson->getCurrentPosition() == sherlock->getCurrentPosition()) {
            for (int i = 0; i < 15; i++) {
                if (watson_bag->getsize() >= 14) {
                    break;
                } else {
                    BaseItem* item = sherlock_bag->get(PASSING_CARD);
                    if (item != nullptr) {
                        watson_bag->insert(item);
                    }
                }
            }
            for (int i = 0; i < 13; i++) {
                if (sherlock_bag->getsize() >= 12) {
                    break;
                } else {
                    BaseItem* item = watson_bag->get(EXCEMPTION_CARD);
                    if (item != nullptr) {
                        sherlock_bag->insert(item);
                    }
                }
            } 
        }
        if (isStop()) {
            printStep(istep);   
            break;
        }
        // if (verbose) {
        //     printStep(istep);
        //     cout << watson_bag->str() << endl;
        //     cout << sherlock_bag->str() << endl;
        // }
        //cout << arr_mv_objs->str() << endl;
    }
    // cout << sherlock->GetHp() << endl;
    // cout << watson->GetHp() << endl;
    // cout << isStop() << endl;
    // cout << sherlock->getCurrentPosition().str() << endl;
    // cout << watson->getCurrentPosition().str() << endl;
    // cout << criminal->getCurrentPosition().str() << endl;
    printResult();
}

void StudyPinkProgram ::test() {
    bool first = 1;
    for (int istep = 0; istep < config->num_steps; ++istep) {
        for (int i = 0; i < arr_mv_objs->size(); ++i) {
            if (arr_mv_objs->get(i) == nullptr)
                continue;
            arr_mv_objs->get(i)->move();
        }
        // if (isStop()) {
        //         printStep(istep);
        //         break;
        //    }
        //     if (true) {
        //         printStep(istep);
        //     }

        if (criminal->getCount_move() % 3 == 0) {
            if (!(arr_mv_objs->isFull())) {
                index++;
                Robot* robot =
                    Robot ::createRobot(index, map, criminal, sherlock, watson, first);
                arr_mv_objs->add(robot);
            }
        }
        cout << arr_mv_objs->str() << endl;
        // cout << criminal->getCount_move() << endl;
    }

    //         printResult();
    // Robot *robot = new RobotC(0, Position(0, 0), map, criminal);
    // cout << robot->getRobotType();
    // cout << arr_mv_objs->get(2)->str();
    // arr_mv_objs->get(2)->move();
    // cout << arr_mv_objs->get(2)->str();

    //     for (int i = -1; i < config->map_num_cols; i++)
    //     {
    //         if (i == -1)
    //             cout << setw(5) << "";
    //         else
    //             cout << setw(5) << i;
    //     }
    //     cout << endl;
    //     for (int i = 0; i < map->getNumRows(); i++)
    //     {
    //         cout << setw(5) << i;
    //         for (int j = 0; j < map->getNumCols(); j++)
    //         {
    //             int idx = (int)map->getElementType(i, j);
    //             string nameElement[3] = {".", "W", "F"};
    //             cout << setw(5) << nameElement[idx];
    //         }
    //         cout << endl;
    //     }
}
StudyPinkProgram ::~StudyPinkProgram() {
    delete config;
    delete map;
    delete arr_mv_objs;
    delete sherlock;
    delete watson;
    delete criminal;
    delete sherlock_bag;
    delete watson_bag;
}
