//
//  Employee.cpp
//  project2
//
//  Created by Umut Avin on 19.11.2018.
//  Copyright © 2018 avin. All rights reserved.
//

#include "Employee.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

Employee::Employee(int id, int call_num, int pos_fb, int neg_fb){

    ID = id;
    callNum = call_num;
    posFB = pos_fb;
    negFB = neg_fb;

};

int Employee::getPerf(){
    performance = 2*callNum + posFB - negFB;
    return performance;
}

Employee Employee::operator=(Employee &other){
    ID = other.ID;
    callNum = other.callNum;
    posFB = other.posFB;
    negFB = other.negFB;
    return* this;
};





