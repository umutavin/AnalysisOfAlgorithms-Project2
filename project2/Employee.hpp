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
public:
    int ID;
    int callNum;
    int posFB;
    int negFB;
    int performance;
    Employee(){
        performance = 0;
        callNum = 0;
        posFB = 0;
        negFB = 0;
    };
    Employee(int id, int call_num, int pos_fb, int neg_fb);
    int getPerf();
    Employee operator=(Employee& other);
    Employee extract(Employee arr[], int size);
    void MaxHeapify(Employee arr[], int n, int i, char type);
    void Build_MaxHeap(Employee arr[], int n, char type);
    void HeapSort(Employee arr[], int n, char type);

    //void increaseKey(Employee &employee);
};

#endif /* Employee_hpp */
