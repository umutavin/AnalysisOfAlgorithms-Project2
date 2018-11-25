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


void MaxHeapify(Employee arr[], int n, int i, char type){
    if(type == 'c'){
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
           
           MaxHeapify(arr, n, largest, 'c');
       }
       return;
    }
    if(type == 'p'){
        Employee temp;
        int l = (2*i);
        int r = (2*i)+1;
        int largest = i;
        
        if (l <= n && arr[l].getPerf() > arr[i].getPerf()){
            largest = l;
        }
        if(r <= n && arr[r].getPerf() > arr[largest].getPerf()){
            largest = r;
        }
        if(largest != i){
            Employee temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            
            MaxHeapify(arr, n, largest, 'p');
        }
        return;
    }
    
}

void Build_MaxHeap(Employee arr[], int n, char type){
    if(type == 'c'){
        int i;
        for(i = n/2; i >= 1; i--){
            MaxHeapify(arr, n, i, 'c');
        }
    }
    
    else if(type == 'p'){
        int i;
        for(i = n/2; i >= 1; i--){
            MaxHeapify(arr, n, i, 'p');
        }
    }
}

void HeapSort(Employee arr[], int n, char type){
    if(type == 'c'){
        Build_MaxHeap(arr, n, 'c');
        for(int i = n; i >= 1; i--){
            Employee temp = arr[i];
            arr[i] = arr[1];
            arr[1] = temp;
            n = n-1;
            MaxHeapify(arr, n, 1, 'c');
        }
    }
    if(type == 'p'){
        Build_MaxHeap(arr, n, 'p');
        for(int i = n; i >= 1; i--){
            Employee temp = arr[i];
            arr[i] = arr[1];
            arr[1] = temp;
            n = n-1;
            MaxHeapify(arr, n, 1, 'p');
        }
    }
    
}
Employee extract(Employee arr[], int size){
    if (size < 1)
        cout << "Error: Heap underflow" << endl;
    Employee max = arr[size];
    arr[size] = arr[1];
    size = size - 1;
    MaxHeapify(arr, size, 1, 'p');
    return max;
}

void increaseKey(Employee arr[], int i, Employee key){
    int parent = (i)/2;
    arr[i] = key;
    while(i>1 && arr[parent].callNum < arr[i].callNum){
        arr[i] = arr[parent];
        i = parent;
    }
}

void insert(Employee arr[], int size, Employee key){
    size = size + 1;
    increaseKey(arr, size, key);
}


void PrintDay(Employee arr[], int day, int size){
    Employee p1 = extract(arr, size);
    insert(arr, size, p1);
    Employee p2 = extract(arr, size-1);
    insert(arr, size, p2);
    Employee p3 = extract(arr, size-2);
    insert(arr, size, p3);
    cout << endl << "AFTER DAY-" << day << endl;
    cout << "BEST PERFORMANCE: " << p1.getPerf() << ", " << p2.getPerf() << ", " << p3.getPerf() << endl;
    //cout << "MAXIMUM CALLS: " << arr[size].getPerf() << ", " << arr[size-1].getPerf() << ", " << arr[size-2].getPerf() << endl;
    HeapSort(arr, size, 'c');
    cout << "MAXIMUM CALLS: " << arr[size].ID << " " << arr[size].callNum << ", " << arr[size-1].callNum << ", " << arr[size-2].callNum << endl;
    
    if(day==10){
        cout << "MINIMUM CALLS: " << arr[13].ID << " " << arr[13].callNum << ", " << arr[14].callNum << ", " << arr[15].callNum << endl;
        HeapSort(arr, size, 'p');
        cout << "WORST PERFORMANCE: " << arr[8].getPerf() << ", " << arr[9].getPerf() << ", " << arr[10].getPerf() << endl;
        

    }
}

void ReadRecords(Employee arr[], int size, int i, ifstream& input ){
    string line, id, call_num, pos_fb, neg_fb;
    while(!input.eof()){
        getline(input, id, ',');
        getline(input, call_num, ',');
        getline(input, pos_fb, ',');
        getline(input, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > i+97){
            Employee employee(ID, callNum, posFB, negFB);
            insert(arr, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == arr[k].ID){
                    arr[k].callNum += employee.callNum;
                    arr[k].posFB += employee.posFB;
                    arr[k].negFB += employee.negFB;
                }
            }
        }
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
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 1, size);
    
    inputFile.open("Data/day2.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();

    HeapSort(array, size, 'p');
    PrintDay(array, 2, size);
    
    inputFile.open("Data/day3.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 3, size);
    
    inputFile.open("Data/day4.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 4, size);
    
    inputFile.open("Data/day5.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 5, size);
    
    inputFile.open("Data/day6.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 6, size);
    
    inputFile.open("Data/day7.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 7, size);
    
    inputFile.open("Data/day8.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 8, size);
    
    inputFile.open("Data/day9.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 9, size);
    
    inputFile.open("Data/day10.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    ReadRecords(array, size, i, inputFile);
    i=i+10;
    size = i-2;
    inputFile.close();
    inputFile.clear();
    
    HeapSort(array, size, 'p');
    PrintDay(array, 10, size);
    
    return 0;
}
