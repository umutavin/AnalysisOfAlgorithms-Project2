//
//  Employee.hpp
//  project2
//
//  Created by Umut Avin on 19.11.2018.
//  Copyright © 2018 avin. All rights reserved.
//

#ifndef Employee_hpp
#define Employee_hpp

#include <iostream>

class Employee{
private:
    int getPerf();
public:
    int ID;
    int callNum;
    int posFB;
    int negFB;
    int performance;
    Employee(){};
    Employee(int id, int call_num, int pos_fb, int neg_fb);
    Employee operator=(Employee& other){
        ID = other.ID;
        callNum = other.callNum;
        posFB = other.posFB;
        negFB = other.negFB;
        return* this;
    };
    
    //void increaseKey(Employee &employee);
};

#endif /* Employee_hpp */
