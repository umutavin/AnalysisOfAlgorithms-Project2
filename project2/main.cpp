//  Created by Umut Avin on 19.11.2018.
//  150140018
//  Copyright © 2018 avin. All rights reserved.


#include <iostream>
#include "Employee.cpp"
#include <time.h>

using namespace std;

void Heapify(int arr[], int n, int i){
    int temp;
    int l = (2*i);
    int r = (2*i)+1;
    int largest = i;
    
    if (l <= n && arr[l] > arr[i]){
        largest = l;
    }
    if(r <= n && arr[r]> arr[largest]){
        largest = r;
    }
    if(largest != i){
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        Heapify(arr, n, largest);
    }
}

void BuildHeap(int arr[], int n){
    int i;
    int counter=0;
    for(i = n/2; i >= 1; i--){
        Heapify(arr, n, i);
        counter++;
    }
}

void HeapSort(int arr[], int n){
    int temp;
    BuildHeap(arr, n);
    for(int i = n; i >= 1; i--){
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;
        n = n-1;
        Heapify(arr, n, 1);
    }
}
int extractNum(int arr[], int size){
    if (size < 1)
        cout << "Error: Heap underflow" << endl;
    int max = arr[1];
    arr[1] = arr[size];
    size = size - 1;
    Heapify(arr, size, 1);
    return max;
}

void SortNumbers(){
    string num;
    int arrayNum[2000000];
    int i=0;
    ifstream input("Data/numbers.csv", ifstream::in);
    if (!input.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
    }
    while(!input.eof()){
        getline(input, num, '\n');
        int number = atoi(num.c_str());
        arrayNum[i] = number;
        i++;
    }
    input.close();
    ofstream outputFile("output.csv", ofstream::out);
    
    BuildHeap(arrayNum, i-1);
    int temp;
    cout << endl << endl;
    for(int k=0; k<10; k++){
        clock_t begin = clock();
        for(int j=0; j<200000; j++){
            temp = extractNum(arrayNum, i-1);
            outputFile << temp << endl;
        }
        clock_t end = clock();
        double elapsed_sec = double(end-begin)/ CLOCKS_PER_SEC;
        cout << elapsed_sec << endl;
        
    }
    outputFile.close();
    
    
}



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
    Employee max = arr[1];
    arr[1] = arr[size];
    size = size - 1;
    MaxHeapify(arr, size, 1, 'p');
    return max;
}

void increaseKey(Employee arr[], int i, Employee key){
    int parent = (i)/2;
    arr[i] = key;
    while(i>1 && arr[parent].getPerf() < arr[i].getPerf()){
        arr[i] = arr[parent];
        i = parent;
    }
}

void insert(Employee arr[], int size, Employee key){
    size = size + 1;
    increaseKey(arr, size, key);
}


void PrintPerf(Employee arr[], int day, int size){
    Employee p1 = extract(arr, size);
    insert(arr, size-1, p1);
    Employee p2 = extract(arr, size);
    insert(arr, size-1, p2);
    Employee p3 = extract(arr, size);
    insert(arr, size-1, p3);
    cout << endl << "AFTER DAY-" << day << endl;
    cout << "BEST PERFORMANCE: " << p1.ID << ", " << p2.ID << ", " << p3.ID << endl;
    if(day==10){
        cout << "MINIMUM CALLS: " << arr[size].ID << ", " << arr[size-1].ID << ", " << arr[size-2].ID << endl;
        Build_MaxHeap(arr, size, 'p');
        cout << "WORST PERFORMANCE: " << arr[size-1].ID << ", " << arr[size-2].ID << ", " << arr[size-3].ID << endl;
        
     
    }
}

void PrintCalls(Employee arr[], int day, int size){
    Employee c1 = extract(arr, size);
    insert(arr, size-1, c1);
    Build_MaxHeap(arr, size, 'c');
    Employee c2 = extract(arr, size);
    insert(arr, size-1, c2);
    Build_MaxHeap(arr, size, 'c');
    Employee c3 = extract(arr, size);
    insert(arr, size-1, c3);
    cout << "MAXIMUM CALLS: " << c1.ID << ", " << c2.ID << ", " << c3.ID << endl;
}

void ReadRecords(Employee arr[], int size, int i, ifstream& input ){
    string line, id, call_num, pos_fb, neg_fb;
    
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
    int count = size;
    
    inputFile.close();
    inputFile.clear();
    
    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 1, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 1, size);
    
    inputFile.open("Data/day2.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    
    inputFile.close();
    inputFile.clear();
    
    count = size;
    
    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 2, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 2, size);
    
    inputFile.open("Data/day3.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
      
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 3, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 3, size);
    
    inputFile.open("Data/day4.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');


                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 4, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 4, size);
    
    inputFile.open("Data/day5.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 5, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 5, size);
    
    inputFile.open("Data/day6.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 6, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 6, size);
    
    inputFile.open("Data/day7.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    
    count = size;

    inputFile.close();
    inputFile.clear();
    
    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 7, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 7, size);
    
    inputFile.open("Data/day8.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 8, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 8, size);
    
    inputFile.open("Data/day9.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');

                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 9, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 9, size);
    
    inputFile.open("Data/day10.csv", ifstream::in);
    if (!inputFile.is_open()) {
        cout << endl << "File cannot be loaded!" << endl;
        return 0;
    }
    while(!inputFile.eof()){
        getline(inputFile, id, ',');
        getline(inputFile, call_num, ',');
        getline(inputFile, pos_fb, ',');
        getline(inputFile, neg_fb, '\n');
        int ID = atoi(id.c_str());
        int callNum = atoi(call_num.c_str());
        int posFB = atoi(pos_fb.c_str());
        int negFB = atoi(neg_fb.c_str());
        if(ID > count+99){
            Employee employee(ID, callNum, posFB, negFB);
            insert(array, size, employee);
            i++;
            size = size + 1;
        }
        else{
            Employee employee(ID, callNum, posFB, negFB);
            for(int k=1; k<size; k++){
                if(employee.ID == array[k].ID){
                    array[k].callNum += employee.callNum;
                    array[k].posFB += employee.posFB;
                    array[k].negFB += employee.negFB;
                    Build_MaxHeap(array, size, 'p');
                }
            }
        }
    }
    inputFile.close();
    inputFile.clear();
    count = size;

    Build_MaxHeap(array, size, 'p');
    PrintPerf(array, 10, size);
    Build_MaxHeap(array, size, 'c');
    PrintCalls(array, 10, size);
    
    SortNumbers();
    
    return 0;
}

