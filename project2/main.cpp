//
//  main.cpp
//  project2
//
//  Created by Umut Avin on 19.11.2018.
//  Copyright © 2018 avin. All rights reserved.
//

#include <iostream>
#include "Employee.cpp"

using namespace std;


void MaxHeapify(Employee arr[], int n, int i){
    Employee temp;
    int l = (2*i);
    int r = (2*i)+1;
    int largest = i;
    
    if (l <= n && arr[l].callNum > arr[i].callNum){
        largest = l;
    }
    if(r <= n && arr[r].callNum > arr[largest].callNum){
        largest = r;
    }
    if(largest != i){
        Employee temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        MaxHeapify(arr, n, largest);
    }
    return;
}

void Build_MaxHeap(Employee arr[], int n)
{
    int i;
    for(i = n/2; i >= 1; i--){
        MaxHeapify(arr, n, i);
    }
}

void HeapSort(Employee arr[], int n)
{
    Build_MaxHeap(arr, n);
    for(int i = n; i >= 1; i--){
        Employee temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;
        n = n-1;
        MaxHeapify(arr, n, 1);
    }
}

int main() {
    Employee employee;
    string line, id, call_num, pos_fb, neg_fb;
    Employee* array = new Employee[1000];

    ifstream inputFile("Data/day1.csv", ifstream::in);
    
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    int i = 1;

    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        Employee employee(ID, callNum, posFB, negFB);
        array[i] = employee;
        i++;
    }
    int size = i-2;
    inputFile.close();
    
    HeapSort(array, size);
    
    for(int k=1;k<801;k++){
        cout << array[k].callNum << " ";
    }
    
    return 0;
}
