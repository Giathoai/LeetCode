/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 01.03.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"

using namespace std;

void g_satc_02() { // global
    cout << "----- Sample Testcase 02 -----" << endl;
    Configuration * config = new Configuration("sa_tc_02_config");
    cout << config->str() << endl;
    delete config;
}

class TestStudyInPink {
public:
    TestStudyInPink() = default;
    static void satc_1146() {
    cout << "----- Testcase 146 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "LU", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "LU", Position(6, 0), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    criminal->move();
    cout << criminal->str();

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
    static void satc_01() {
        cout << "----- Sample Testcase 01 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        cout << sherlock->str() << endl;

        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        cout << watson->str() << endl;

        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        cout << criminal->str() << endl;

        cout << "* Sherlock makes a move" << endl;
        sherlock->move();
        cout << sherlock->str() << endl;

        cout << "* Watson makes a move" << endl;
        watson->move();
        cout << watson->str() << endl;

        cout << "* Criminal makes a move" << endl;
        criminal->move();
        cout << criminal->str() << endl;

        ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(10);
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(watson);
        cout << arr_mv_objs->str() << endl;
        
        delete arr_mv_objs;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }

    static void satc_02() {
        g_satc_02();
    }

    static void satc_03() {
        // Sample test for RobotC
        cout << "----- Sample Testcase 03 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        criminal->move();

        RobotC * robotC = new RobotC(3, Position(7,9), map, criminal);
        cout << "Current position of Criminal: " << criminal->str() << endl;
        cout << "Criminal makes a move" << endl;
        criminal->move();
        cout << "New position of Criminal: " << criminal->str() << endl;

        cout << "Current position of robotC: " << robotC->str() << endl;
        cout << "RobotC makes a move" << endl;
        robotC->move();
        cout << "New position of robotC: " << robotC->str() << endl;

        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
    }
    static void tc_1161() {
    cout << "----- Testcase 161 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "LU", Position(3, 0), map, 100, 250);
    Watson * watson = new Watson(2, "LU", Position(3, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    cout << criminal->str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}

static void tc_1298() {
    cout << "----- Testcase 298 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseItem * firstAid1 = new FirstAid();
    BaseItem * firstAid2 = new FirstAid();

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->insert(firstAid1);
    sherlockBag->insert(firstAid2);

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete firstAid1;
    delete firstAid2;
    delete sherlockBag;
}
    static void tc_1180() {
        cout << "----- Testcase 180 -----" << endl;  
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        Sherlock * sherlock_2 = new Sherlock(3, "UUR", Position(1, 3), map, 250, 450);
        Sherlock * sherlock_3 = new Sherlock(4, "RRU", Position(1, 3), map, 250, 450);

        ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(1);
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(sherlock_2);
        arr_mv_objs->add(sherlock_3);
        arr_mv_objs->add(watson);

        cout << "Count: " << arr_mv_objs->count << endl;

        delete arr_mv_objs;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        }
        static void tc_1242() {
        cout << "----- Testcase 242 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 4), map, 250, 450);
        Watson * watson = new Watson(2, "LU", Position(1, 3), map, 300, 350);

        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        RobotC * robotC = new RobotC(3, Position(7,1), map, criminal);
        cout << robotC->getNextPosition().str();
        Position new_position = robotC->getNextPosition();
        RobotC * robotC_new = new RobotC(4, new_position, map, criminal);
        cout << "Current: " << robotC->pos.getRow() << " " << robotC->pos.getCol() << endl;
        cout << "Next position: " << robotC_new->pos.getRow() << " " << robotC_new->pos.getCol() << endl;

        delete robotC;
        delete robotC_new;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }

};






int main(int argc, const char * argv[]) {
    //TestStudyInPink::satc_01();
    //TestStudyInPink::satc_02();
    // TestStudyInPink::satc_03();
     TestStudyInPink::tc_1242();
    //StudyPinkProgram* huhu = new StudyPinkProgram("sa_tc_02_config");
    //huhu->run(true);
    //huhu->test();
    return 0;
}