#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <array>
using namespace std;

typedef vector<tuple<int,int,int,int,int>> vec1;

vec1 array1()
{
    string arr1[100];
    int arr2[100][5];
    int k=0;
    int i=0;
    ifstream data;
    data.open("StudentDataBase.dat");

    vec1 users;
    tuple<string,int,string,int> userdata;
    ifstream file;
    file.open("S.dat");
    while (file>>get<0>(userdata))
    {
        file >>get<1>(userdata);
        file >>get<2>(userdata);
        file >>get<3>(userdata);
        users.push_back(userdata);
    }
    file.close();
   

    for (int i=0; i<100; i++){
        string s = arr1[i];
        stringstream string_stream(s);
        int i2 = 0;

        while(string_stream.good()){
            string y;
            getline( string_stream, y, ',' );
            stringstream string_stream2(y);
            string_stream2 >> k;

            arr2[i][i2]=k;
            i2++;
        }
    }

	// for(i=0;i<100;i++)
	// {
    //    for (int i3=0;i3<5;i3++){
    //        cout << arr2[i][i3] << endl;
    //    }
	// }
    
    int asd = arr2[99][1]+arr2[99][4];
    //cout << asd << endl;

    return asd;
}

int main()
{
    array ar;
    ar=array1();
    for(int i=0;i<100;i++)
	{
       for (int i3=0;i3<5;i3++){
           cout << ar[i][i3] << endl;
       }
	}
}