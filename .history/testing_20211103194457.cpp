
// ----------------------------------------start of the program---------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
#include <sstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;


void readfileformat(int &count,int &totalcolumn, int &totalrow){

    int temp;
    count = 0;

//open file
    string strtemp,strtitles;
    ifstream data;
    data.open("StudentDataBase.dat");

//get column
    data >> strtemp;
    stringstream ssstrcolumn(strtemp);
    ssstrcolumn >> totalcolumn;
    count++;

//get title
    data >> strtitles;
    count++;

//get compute
    int compute[totalcolumn];
    for (int i=0;i<totalcolumn;i++){
        data >> strtemp;
        stringstream ssstrcompute(strtemp);
        ssstrcompute >> temp;
        compute[i] = temp;
        count++;
    }

//get row
    data >> strtemp;
    stringstream ssstrrow(strtemp);
    ssstrrow >> totalrow;
    count++;

    data.close();
}


void askrowcolumn(const int totalcolumn, const int totalrow, int &roworcol, int &inputvalue){

    string strtemp;
    int temp;

    cout << "Enter 1 for row or 2 for column" << endl;
    cin >> roworcol;

    if (roworcol == 1){
        cout << "Enter row from 5 to " << totalrow << endl;
        cin >> inputvalue;
    } else if (roworcol == 2){
        cout << "Enter column from 1 to " << totalcolumn << endl;
        cin >> inputvalue;
    }
}


int readdata(int &count, int col, const int totalcolumn, const int totalrow){
    int num,numtemp;
    int localcount = 0;
    int rowarr[totalcolumn];
    string strtemp,str2;
    ifstream data;
    data.open("StudentDataBase.dat");

    for (int i = 0; i < count;i++){
        data >>strtemp;
    }

    data >> strtemp;
    cout << strtemp << endl;
    stringstream ssstrtemp(strtemp);

    while(ssstrtemp.good()){
        getline(ssstrtemp, str2, ',' );
        stringstream string_stream2(str2);
        string_stream2 >> numtemp;
        rowarr[localcount]= numtemp;
        localcount++;
    }

    count++;
    num = rowarr[col];
    //cout << rowarr[col] << endl;


    return num;
}

void findmean(){
    int c,tcolumn,trow,rc,input;
... (40 lines left)
Collapse
testing.cpp
3 KB
u can refer to my line 1 to 47
and the database
the database should be like that
Ayaan — Today at 7:34 PM
okay I'll see to into it in a bit
what am I supposed to be looking at? 
@Jv
Jv — Today at 7:36 PM
how to read first 5 line properly for the database
after reading the row and column and computable
then only declare array[row][col]
Ayaan — Today at 7:39 PM
okyyy
﻿
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;


void readfileformat(int &count,int &totalcolumn, int &totalrow){

    int temp;
    count = 0;

//open file
    string strtemp,strtitles;
    ifstream data;
    data.open("StudentDataBase.dat");

//get column
    data >> strtemp;
    stringstream ssstrcolumn(strtemp);
    ssstrcolumn >> totalcolumn;
    count++;

//get title
    data >> strtitles;
    count++;

//get compute
    int compute[totalcolumn];
    for (int i=0;i<totalcolumn;i++){
        data >> strtemp;
        stringstream ssstrcompute(strtemp);
        ssstrcompute >> temp;
        compute[i] = temp;
        count++;
    }

//get row
    data >> strtemp;
    stringstream ssstrrow(strtemp);
    ssstrrow >> totalrow;
    count++;

    data.close();
}


void askrowcolumn(const int totalcolumn, const int totalrow, int &roworcol, int &inputvalue){

    string strtemp;
    int temp;

    cout << "Enter 1 for row or 2 for column" << endl;
    cin >> roworcol;

    if (roworcol == 1){
        cout << "Enter row from 5 to " << totalrow << endl;
        cin >> inputvalue;
    } else if (roworcol == 2){
        cout << "Enter column from 1 to " << totalcolumn << endl;
        cin >> inputvalue;
    }
}


int readdata(int &count, int col, const int totalcolumn, const int totalrow){
    int num,numtemp;
    int localcount = 0;
    int rowarr[totalcolumn];
    string strtemp,str2;
    ifstream data;
    data.open("StudentDataBase.dat");

    for (int i = 0; i < count;i++){
        data >>strtemp;
    }

    data >> strtemp;
    cout << strtemp << endl;
    stringstream ssstrtemp(strtemp);

    while(ssstrtemp.good()){
        getline(ssstrtemp, str2, ',' );
        stringstream string_stream2(str2);
        string_stream2 >> numtemp;
        rowarr[localcount]= numtemp;
        localcount++;
    }

    count++;
    num = rowarr[col];
    //cout << rowarr[col] << endl;


    return num;
}

void findmean(){
    int c,tcolumn,trow,rc,input;
    readfileformat(c,tcolumn,trow);
    askrowcolumn(tcolumn,trow,rc,input);

    int temprow = 1;//=========
    int tempcol = 2;//======
    
    int tempdata[trow];
    int columndata[trow];
    int rowdata[tcolumn];
    for (int j = 0; j < tcolumn; j++){
        int tempc = c;
        for (int i = 0; i < trow; i++){
            tempdata[i] = readdata(tempc,j,tcolumn,trow);
            if (tempcol == j){ //===========
                columndata[i] = tempdata[i];
            }
        }
        rowdata[j] = tempdata[temprow]; //=========
    }


    for (int j = 0; j < tcolumn; j++){
        cout << rowdata[j] <<endl;
    }

    for (int i = 0; i < trow; i++){
        cout << columndata[i] <<endl;
    }


    cout << trow << endl;
}


int main(){

    findmean();

    return 0;
}
testing.cpp
3 KB