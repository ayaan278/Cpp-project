// ----------------------------------------start of the program---------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <set>
using namespace std;


// -------------------------type definiations used in the function-------------------------------------------
typedef vector<tuple<string,int,string,int>> vec;
typedef vector<int> vec1;
typedef vector<vector<int>> vec2;


//----------------------------------------Global variables-----------------------------------------------------
int status=0;
string username,password;

struct datavalues
{
    int totalcol;
    int totalrow;
    string titles;
    vec1 computablecols;
    vec2 fulldata;
};

// ----------------------------------Start of functions defination-------------------------------------------
void login();
int checkadmin(string,string);
void getchoice();
void adminmenu();
void usermenu();
void createuser(vec);
void logout();
void changepass(vec);
void deleteuser(vec);
vec loadfile();
void clearfile();
void database(struct datavalues d,string);//changed
void savefile();
void savereport(int,string,double,double);
void saveHTMLreport(string,double,double);
void clearActivity();
void logrecord(string);
void pressenter(int);
void viewfunc(struct datavalues d);//changed
void loadmin();//changed
void minrow(int,int**,int,int);//changed
void mincolumn(int,double&,int);
void loadmax();
void maxrow(int);
void maxcolumn(int,double&,int);
void loadmed();
void findrowmed();
void findcolmed();
//changed
void askrowcolumn(struct datavalues d, int&, int&,int&);
void loadmean(struct datavalues d);
void findmean(struct datavalues d,const int,const int, const int,double&,double&,double&, int&);
void loadvar(struct datavalues d);
void findvar(const double,const double,const int, double&);
void loadfindstdv(struct datavalues d);
void asktwocolumn(struct datavalues d, int&, int&);
void loadfindcorr(struct datavalues d);
//till here
void finddistinct();
void findhistogram();
void findMP();
void reportsmenu();


//------------------------------------------main function------------------------------------------------------
int main()
{   
    clearActivity();
    login();
    return 0;
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------------This functions login the user into the system-------------------------------------
void login()
{   
    int s;
    char n;
    cout<<"|-------------------------------------------------|\n"
        <<"|      Hello and Welcome to Our System            |\n"
        <<"|-------------------------------------------------|\n"
        <<"|ENTER 1 TO LOGIN                                 |\n"
        <<"|ENTER 0 TO EXIT                                  |\n"
        <<"|-------------------------------------------------|\n";
    cin>>n;
    cin.ignore(25,'\n');
    if(n=='1')
    { 
        cout<<"-----------------------------------------------------------\n"
            <<"Please enter the username-\n";
        cin>>username;
        cin.ignore(25,'\n');
        cout<<"Please enter the password-\n";
        cin>>password;
        cin.ignore(25,'\n');
        status=checkadmin(username,password);
        logrecord(" just logged in");
        getchoice();
    }
    else if(n=='0')
            exit(0);
    else
    {
        cout<<"Wrong choice\n"
            <<"Please enter from given choices only\n";
        login();
    }
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//---------------------------This functions checks if the user is admin or not----------------------------------
 int checkadmin(string name,string pass)
 {      
    vec users;
    users = loadfile();
     for (int i=0;i<users.size();i++)
    {   
        if(get<0>(users[i])==name && get<2>(users[i])==pass && get<1>(users[i])==1)
            return 1;
        else if(get<0>(users[i])==name && get<2>(users[i])==pass && get<1>(users[i])==0)   
            return 0;
    }
    return 2;
 }

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------This functions takes the input from the user and calls different functions---------------
void getchoice() 
{   
    if(status==1)
        adminmenu();
    else
    {   
        if(status==0)
        usermenu();
        else
        {
        cout<<"Either username or password was wrong\n";
        login();
        }
    }
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------------------This function shows the menu for the admin----------------------------------
void adminmenu()
{
    char ch;
    cout << "|--------------------------------------------------------|\n"
        << "       Hello admin "<<username<<"                         \n"
        << "|--------------------------------------------------------|\n"
        << "| Please Enter from the choice given below               |\n"
        << "| Enter 1 to Login as a User Account to view FUNCTION    |\n"
        << "| Enter 2 to Create a New User Account                   |\n"
        << "| Enter 3 to Logout from your User Account               |\n"
        << "| Enter 4 to Delete any User Account                     |\n"
        << "| Enter 5 To Change your Password                        |\n"
        << "| Enter O To Exit                                        |\n"
        << "|--------------------------------------------------------|\n";
    cin >> ch;
    cin.ignore(' ','\n');
    string str=" just choose menu option ";
    str.push_back(ch);
    logrecord(str);
    vec users;
    users=loadfile();
    switch(ch)
    {
        case('1') : clearfile();
                    break;
        case('2') : createuser(users);
                    break;
        case('3') : logout();
                    break;
        case('4') :  deleteuser(users);
                    break;
        case('5') :  changepass(users);
                    break;
        case('0') : exit(0);
                    break;
        default: cout<<"Wrong choice\n"
                     <<"Please try again\n";
                        adminmenu();
                        break;    
    }
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//--------------------------This function shows the menu for a regular user-------------------------------------
void usermenu()
{
    char ch;
    cout <<"|--------------------------------------------------------|\n"
        << "        Hello user "<< username<<"                        \n"
        << "|--------------------------------------------------------|\n"
        << "| Please Enter from the choice given below               |\n"
        << "| Enter 1 to view all the FUNCTION                       |\n"
        << "| Enter 2 to Logout from your User Account               |\n"
        << "| Enter 3 To Change your Password                        |\n"
        << "| Enter O To Exit                                        |\n"
        << "|--------------------------------------------------------|\n";
    cin >> ch;
    cin.ignore(' ','\n');
    string str=" just choose menu option "+ch;
    str.push_back(ch);
    logrecord(str);
    vec users;
    users=loadfile();
    switch(ch)
    {   case('1') : clearfile(); 
                    break;
        case('2') : logout();
                    break;
        case('3') : changepass(users);
                    break;
        case('0') : exit(0);
                    break;

        default: cout<<"Wrong choice\n"
                    <<"Please try again\n";
                    usermenu();
                    break;
    }
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------------This functions creates the new user-----------------------------------------------
void createuser(vec users) 
{   
    string user,pass;
    int s, flag=0,f;
    cout <<"Enter a unique user name -\n";
    cin >> user;
    cout << "Enter your password -\n";
    cin >> pass;
    cout <<"Enter 1 to create new admin, 0 for reguler user-\n";
    cin>>s;
    for(int i=0; i<users.size(); i++)
    {if(get<0>(users[i])==user)
    {
        flag = 1;
        break;
    }}
    if(flag!=1)
    {ofstream outfile;
    outfile.open("Users.dat",ios::ate|ios::app);
    int activity=1;
    outfile << user << " " << s << " " << pass << " " << activity <<endl;
    outfile.close();
    cout << "-----------------------------------------------------\n"
         << "Username and password created successfully.\n"<<endl;
    string str=" just created another user as "+user;
    logrecord(str);}
    else 
    cout<<"The username already exists\n";
    pressenter(f==1);
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------------This functions logout the user from the system---------------------------------
void logout()
{   
    string str=" logged out from the system ";
    logrecord(str);
    system("cls");
    cout<<"Logout was successful.\n";
}

//---------------------------------------------Salah Fayeq------------------------------------------------------
//----------------------------This functions changes the password-------------------------------------
void changepass(vec users) 
{
    string newpass1,newpass2,oldpass;           
    cout << "Enter your old password to continue..." << endl;
    cin >> oldpass;       
    for (int i=0;i<users.size();i++)
    {
        if (oldpass == get<2>(users[i]) && username==get<0>(users[i]))
       {    
            cout << "Please enter the new password"<< endl;
            cin >> newpass1;
            cout << "Please re-enter your new password"<< endl;
            cin >> newpass2;
            if(newpass1==newpass2)
            {
                get<2>(users[i])=newpass1;
                cout << "Password changed you may procced to login"<< endl;
            }
                else
                cout <<"passwords don't match try again"<<endl;
            string str=" just changed his password ";
            logrecord(str);       
       }
         else
            cout <<"password is wrong"<<endl;
                break;  
    }
    ofstream outfile;
    outfile.open("Users.dat" , ios::out);
    for (int i=0;i<users.size();i++)
    { 
        outfile << get<0>(users[i]) << " " 
                << get<1>(users[i]) << " " 
                << get<2>(users[i]) << " " 
                << get<3>(users[i]) <<endl;
    }
    outfile.close();
    pressenter(status);
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//----------------------------This functions deletes the user--------------------------------------
void deleteuser(vec users) 
{
    string name, pass;
                cout << "-----------------------------------------------------\n"
                    << "Enter the Username to delete-\n";
                cin >> name;
                cout << "-----------------------------------------------------\n"
                    << "Enter Password to confirm deletion-\n";
                cin >> pass;
     for (int i=0;i<users.size();i++)
    {   
        if (name==get<0>(users[i]) && pass==get<2>(users[i]) && get<3>(users[i])==1)
             { 
                cout << get<0>(users[i]) << ": "
                    << ((get<1>(users[i])==1)?"admin":"user")
                    << ": " <<get<2>(users[i]) << ": "
                    << ((get<3>(users[i])==1)?"Deleted":"Active")
                    << endl;
                get<3>(users[i])=0;
                    break;
             }       
    }
    ofstream outfile;
    outfile.open("Users.dat",ios::out);
    for (int i=0;i<users.size();i++)
    { 
        outfile << get<0>(users[i]) << " " 
                << get<1>(users[i]) << " " 
                << get<2>(users[i]) << " " 
                << get<3>(users[i]) <<endl;
    }
    outfile.close();
    cout << "---------------------------------------------------\n"
                    <<"Account deletion was successful.\n" << endl;
    string str=" deleted the user "+name;
    logrecord(str);
    pressenter(1);
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
// ---------------------------------This function loads Users.dat the file-----------------------------------------
vec loadfile() //needs debugging
{   
    vec users;
    tuple<string,int,string,int> userdata;
    ifstream file;
    file.open("Users.dat");
    while (file>>get<0>(userdata))
    {
        file >>get<1>(userdata);
        file >>get<2>(userdata);
        file >>get<3>(userdata);
        users.push_back(userdata);
    }
    file.close();
    return users;
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
// ---------------------This function loads the student database file and clears the comma----------------------
void clearfile() 
{    
    struct datavalues d;
    string filename;
    cout<<"Before proceeding enter the name of the data base file with proper extension\n";
    cin>>filename;
    ifstream data;
    data.open(filename);
    if(!data){
        cout<<"file doesn't exist\nTry again\n";
        clearfile();
    }
    data >> d.totalcol;
    data >> d.titles;

    string compute,temp;
    int temp2;
    for (int i = 0; i < d.totalcol; i++){
        data >> compute;
        stringstream sscompute(compute);
        getline(sscompute, temp, ',');
        stringstream sstemp(temp);
        sstemp >> temp2;
        d.computablecols.push_back(temp2); 
    }
    data >> d.totalrow;
    data.close();
    database(d,filename);
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
// -----------------------------This function stores the data base file in the vector------------------------------------
void database(struct datavalues d,string filename)
{   
    ifstream data;
    data.open(filename);
    if(!data){
        cout<<"file doesn't exist\nTry again\n";
        clearfile();
    }
    vec1 rowdata;
    string temp3, temp4;

    for (int i=0; i<d.totalcol+3; i++){
        data>>temp3;
    }
    int temp5;
    for (int i = 0; i < d.totalrow; i++){
        data >> temp3;
        stringstream sstemp3(temp3);
        for (int j = 0; j < d.totalcol; j++){
            getline (sstemp3, temp4,','); //splite comma
            stringstream sstemp4(temp4); //convert into int
            sstemp4 >> temp5;
            rowdata.push_back(temp5); //add into vector
        }
        d.fulldata.push_back(rowdata); //add into 2d vector
        rowdata.clear();
    }
    cout<<"File was loaded successfully\n";
    data.close();
    viewfunc(d);
}

//---------------------------------------------omar------------------------------------------------------
// -------------------------------This function saves the new file----------------------------------------
void savefile()
{       
    string newfilename;
    cout << "Enter the new file name "<< endl;
    cin >> newfilename; 
    ofstream file(newfilename+".dat",ios::app);
    for(int i=0;i<100;i++)
    {
        // file<<get<0>(student[i]) <<", "
        //     <<get<1>(student[i]) <<", "
        //     <<get<2>(student[i]) <<", "
        //     <<get<3>(student[i]) <<", "
        //     <<get<4>(student[i]) << endl;
    }
    string str=" Created and saved a newfile as "+newfilename+"\n";
    logrecord(str);
}

//---------------------------------------------Ahmad Ayaan/Salah Fayeq------------------------------------------------------
// -----------------This function clears the user activity in a file before function starts--------------------------
void clearActivity()
{
    ofstream file;
    file.open("Report.dat",ios::out|ios::trunc);
    file.close();
    ofstream outfile;
    outfile.open("Activity.dat",ios::out|ios::trunc);
    outfile.close();
    ofstream hfile;
    hfile.open("Report.html" ,ios::out|ios::trunc);
}

//---------------------------------------------Salah Fayeq------------------------------------------------------
// --------------------This function saves the report of the user choices in a file-------------------------
void savereport(int flag,string str, double col,double results)
{
    ofstream outFile;
    outFile.open("Report.dat",ios::out|ios::app);
    outFile << "you just"<<" " << str << " "<< col <<" and the result is: " << results<< endl;
    outFile.close();
    if(flag==1)
    {
    logrecord(" saved the report");
    cout<<"Created the report successfully\n";
    }
    pressenter(3);
}

//---------------------------------------------Salah Fayeq------------------------------------------------------
// -----------------This function saves the report in HTML of the user choices in a file---------------------
void saveHTMLreport(int flag,string str, double col,double results)
{      
    ofstream file;
    file.open("a.html");

    file << "<html>" << endl;
    file << "<body>" << endl;
    file << "<h1>" << "Testing HTML " << "</h1>" << endl;
    file << "<table style=\"width:50%\"> " << endl;

    for (int i=1; i<11; i++)
    {
        file << "<tr>";
        file << "<td style=\"background-color:#F100FF\"> " << i << " </td> "
             << "<td style=\"background-color:#FFFF00\"> " << 'x' << " </td>"
             << "<td> " << 8 << " </td> "
             << "<td> " << '=' << " </td>"
             << "<td style=\"font-size:20px\"> " << 8*i << " </td>" << endl;          
        file << "</tr>" << endl;
    }

    file << "</table>" << endl;
    file << "</body>" << endl;
    file << "</html>" << endl;
    file.close();

    system("chrome a.html");
    if(flag==1) {
        logrecord(" saved the HTML report");
        cout<<"Created the HTML report successfully\n";
    }
    
    pressenter(3);
}

//---------------------------------------------Ahmad Ayaan------------------------------------------------------
// -------------------------This function saves the user activity in a file-------------------------------------
void logrecord(string str)
{
    ofstream outfile;
    outfile.open("Activity.dat",ios::out|ios::app);
    outfile << "--> " << username << " " << str << endl;
    outfile.close();
}
//---------------------------------------------Liew ------------------------------------------------------
//----------------------This functions asks the user to press enter to continue---------------------------------
void pressenter(int flag)
{
    char temp = 'x';
    cout << "Press enter to continue...." << endl;
    cin.get(temp);
    cin.ignore(20,'\n');
    if(temp=='\n')
    {
        if(flag==0)
        usermenu();
        else if(flag==1)
        adminmenu();
        else if(flag==2)
        reportsmenu();
    }
    else
    {
        cout<<"Wrong selection\n";
        pressenter(flag);
    }
}

//---------------------------------------------Salah Fayeq------------------------------------------------------
// --------------------This function shows different functions for user to perform------------------------------
void viewfunc(struct datavalues d)
{   
    char temp = 'x',ch;
    cout << "Press enter to continue...." << endl;
    cin.get(temp);
    cin.ignore(20,'\n');
    cout <<"|------------------------------------------------------------|\n"
        <<"              "<<username<<" ,Please enter a number to procced:\n"
        <<"|-------------------------------------------------------------|\n"
        <<"|  Enter 1 to find the minmum value:                          |\n"
        <<"|  Enter 2 to find the maximum value:                         |\n"
        <<"|  Enter 3 to find the median of the value:                   |\n"
        <<"|  Enter 4 to find the mean of the value:                     |\n"
        <<"|  Enter 5 to find the variance of the value:                 |\n"
        <<"|  Enter 6 to find the standard deviation of the value        |\n"   
        <<"|  Enter 7 to find the correlation between the values         |\n"   
        <<"|  Enter 8 to find the distinct data members                  |\n"
        <<"|  Enter 9 to plot a histogram                                |\n"
        <<"|  Enter R to proceed to the Reports menu                     |\n" 
        <<"|  Enter B to go back to User's menu                          |\n"
        <<"|  Enter S to save the file with a newname                    |\n"  
        <<"|  Enter 0 to exit                                            |\n"     
        <<"|-------------------------------------------------------------|\n"
        <<endl;
    cin>>ch;
    cin.ignore(' ','\n');
    string word= " Just choose a Statystical menu option ";
    word.push_back(ch);
    logrecord(word);
    switch(ch)
    {
         case('1')    : loadmin(d);
                         break;
         case('2')    : loadmax(d);
                         break;
         case('3')    : loadmed(d);               
                         break;
         case('4')    : loadmean(d);
                         break;
         case('5')    : loadvar(d);
                         break;
         case('6')    : loadfindstdv(d);
                         break;                
         case('7')    : loadfindcorr(d);
                         break;     
         case('8')    : finddistinct(d);
                         break;
         case('9')    : findhistogram(d);
                         break;
         case('R')    : reportsmenu();
                         break;
         case('B')    : getchoice();
                         break;
         case('S')    : savefile();
                         break;
         case('0')    : exit(0);
                         break;               
         default: cout<<"Wrong choice\n"
                        <<"Please Enter from the choice given below\n";
                // viewfunc();
                break;         
    }
}
//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This functions loads the minimum function-------------------------------------
void loadmin(struct datavalues d)
{
    int row,col,roworcol;
    double min;
    askrowcolumn(d, row, col, roworcol);
    findmin(d, col, row, roworcol, min);

    cout<<"\nThe minimum of";
    if (roworcol == 1)
        cout << "column " << col;
    else if (roworcol == 2)
        cout << "row " << row;
    cout << " is " << min << ".";
}

//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This function prints minimum from a row-------------------------------------
void findmin(struct datavalues d,const int col,const int row, const int roworcol,double &min)
{   
    cout<<""
    if(rowcol==1)
    {
        for (int i=0;i<d.totalrow;i++){

        }
    }
    else if(rowcol==2)
    {

    }
    // for(int i=0;i<row;i++)
    // {   
    //     if(i==choice)
    //     {   
    //     for(int j;j<column;j++)
    //     {
    //         min=ar[i][j];
    //         if (flag==4){
    //             cout<<"The minimum value of the row "<<choice<<" is "<<min<<endl;
    //             logrecord(" calculated the minimum");
    //         }
    //         break;
    //     }
    //     }
    // }
}


//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This function print the minimum from a column-------------------------------------
void mincolumn(int choice,double &min,int flag)
{   
//     if(flag ==4){
//         cout<<"Enter the column number from 1 to 4"<<endl;
//         cin>>choice;    
//     }
//     if(choice==1)
//     for(int i=0;i<student.size();i++)
//     {  min=get<1>(student[0]);
//        { 
//         if(get<1>(student[i])<min)
//             min=get<1>(student[i]);
//         }
//     }
//     else if(choice==2)
//     for(int i=0;i<student.size();i++)
//     {  min=get<2>(student[0]);
//        { 
//         if(get<2>(student[i])<min)
//             min=get<2>(student[i]);
//         }
//     }
//     else if(choice==3)
//     {min=get<3>(student[0]);
//     for(int i=0;i<student.size();i++)
//         { 
//         if(get<3>(student[i])<min)
//             min=get<3>(student[i]);
//         }
//     }
//     else if(choice==4)
//    { min=get<4>(student[0]);
//     for(int i=0;i<student.size();i++)
//         { 
//         if(get<4>(student[i])<min)
//             min=get<4>(student[i]);
//         }
//     }
//     if (flag==4){
//         cout<<"The minimum value of the column "<<choice<<" is "<<min<<endl;
//         logrecord(" calculated the minimum");
//     }
}

//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This functions loads the maximum function-------------------------------------
void loadmax()
 {   
     //double value=0.0;
//     int flag = 5,c=0;
//     logrecord(" calculated the maximum");
//     char ch;
//     cout <<"Please enter the 1 to find maximum for the specific row and 2 for the column"<<endl;
//     cin>>ch;
//     if(ch=='1')
//         maxrow(flag);
//     else if(ch=='2')
//         maxcolumn(c,value,flag);
//     pressenter(2);

}
//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This function print the maximum from a row-------------------------------------
void maxrow(int flag)
{
    // double max=0.0;
    // int choice;
    // cout<<"Enter the row number from 0 to 99 to find the maximum from 3 subjects"<<endl;
    // cin>>choice;
    // for(int i=0;i<student.size();i++)
    // {   
    //     if(i==choice)
    //     {   max=get<1>(student[i]);
    //         if(get<2>(student[i])>get<1>(student[i]) && get<2>(student[i])>get<3>(student[i]) && get<2>(student[i])>get<4>(student[i]))
    //         max=get<2>(student[i]);
    //         else if(get<3>(student[i])>get<1>(student[i]) && get<3>(student[i])>get<2>(student[i]) && get<3>(student[i])>get<4>(student[i]))
    //             max=get<3>(student[i]);
    //         else if(get<4>(student[i])>get<1>(student[i]) && get<4>(student[i])>get<2>(student[i]) && get<4>(student[i])>get<3>(student[i]))
    //             max=get<4>(student[i]);
    //         if (flag==5){
    //             cout<<"The maximum value of the row "<<choice<<" is "<<max<<endl;
    //             logrecord(" calculated the maximum");
    //         }
    //         break;
    //     }
    // }
}

//---------------------------------------------Omar ------------------------------------------------------
//------------------------------This function prints maximum from a column-------------------------------------
void maxcolumn(int choice,double &max,int flag)
{
//     max=0.0;
//     if(flag ==5){
//         cout<<"Enter the column number from 1 to 4"<<endl;
//         cin>>choice;    
//     }
//     if(choice==1)
//     for(int i=0;i<student.size();i++)
//     {  max=get<1>(student[0]);
//        { 
//         if(get<1>(student[i])>max)
//             max=get<1>(student[i]);
//         }
//     }
//     if(choice==2)
//     for(int i=0;i<student.size();i++)
//     {  max=get<2>(student[0]);
//        { 
//         if(get<2>(student[i])>max)
//             max=get<2>(student[i]);
//         }
//     }
//     else if(choice==3)
//     {max=get<3>(student[0]);
//     for(int i=0;i<student.size();i++)
//         { 
//         if(get<3>(student[i])>max)
//             max=get<3>(student[i]);
//         }
//     }
//     else if(choice==4)
//    { max=get<4>(student[0]);
//     for(int i=0;i<student.size();i++)
//         { 
//         if(get<4>(student[i])>max)
//             max=get<4>(student[i]);
//         }
//     }
//     if (flag==5){
//         cout<<"The maximum value of the row "<<choice<<" is "<<max<<endl;
//         logrecord(" calculated the maximum");
//     }
}
//---------------------------------------------Salah Fayeq---------------------------------------------------
//------------------------------This functions loads the median function-------------------------------------
void loadmed()
{   
    // int flag =0;
    // int row = -1;
    // int col = -1;
    // int choice;
    // float rowmedian,colmedian;
    // float rowsum,colsum,rowlen,collen;

    // cout <<"\n"<<"Enter 1 to find the median of a row, or 2 to find the median of column: "<<endl;
    // cin >> choice;
    // cin.ignore(' ','\n');
    
    // if (choice==1)
    // {
    //    findrowmed(flag,row,rowmedian,rowsum,rowlen);
    // }
    // else if (choice==2)
    // {
    //     findcolmed(flag,col,colmedian,colsum,collen);
    // }
    // else
    // {
    //     cout<<"Wrong choice\n"
    //          <<"Enter again\n";
    //     loadmed();
    // }
    // logrecord(" calculated the median");
    // pressenter(2);
}

void findrowmed(int flag,int &row,float &rowmedian,float &rowsum,float &rowlen)
{
    // rowmedian=0;
    // rowsum=0;
    // rowlen=0;
    // if(row==-1){
    //     do{
    //         cout<<endl<<"Enter the row you want to calculate"<<endl;
    //     }
    // }
}

void findcolmed()
{
    
}

//---------------------------------------------Liew ------------------------------------------------------
//------------------------------This functions loads the mean function-----------------------------------------
void askrowcolumn(struct datavalues d, int &row, int &col,int &roworcol){

    do{
        cout << endl << "Enter 1 for column or 2 for row" << endl;
        cin >> roworcol;
        if (!(roworcol ==1 || roworcol ==2))
            cout << "Invalid input. Please enter again." << endl;
    }while(!(roworcol ==1 || roworcol ==2));

    if (roworcol == 1){
        do{
            cout << endl << "Enter a column from 0 to " << d.totalcol - 1 << "." << endl;
            cin >> col;
            if (!(col >= 0 && col < d.totalcol && d.computablecols[col] == 1))
                cout << "Invalid input. Please enter a valid and computable column." << endl;
        }while (!(col >= 0 && col < d.totalcol && d.computablecols[col] == 1));
    } else{
        do{
            cout << endl << "Enter a row from 0 to " << d.totalrow - 1 << "." << endl;
            cin >> row;
            if (!(row >= 0 && row < d.totalrow))
                cout << "Invalid input. Please enter a valid row." << endl;
        }while(!(row >= 0 && row < d.totalrow));
    }
}

//---------------------------------------------Liew ------------------------------------------------------
//------------------------------This functions loads the mean function-----------------------------------------
void loadmean(struct datavalues d)
{
    int row,col,roworcol,count;
    double sum,sumofsq,mean;

    askrowcolumn(d,row,col,roworcol);
    findmean(d,col,row,roworcol,sum,sumofsq,mean,count);

    cout << endl << "The mean of ";
    if (roworcol == 1)
        cout << "column " << col;
    else if (roworcol == 2)
        cout << "row " << row;
    cout << " is " << mean << ".";

}

//---------------------------------------------Liew ------------------------------------------------------
//------------------------------This functions finds the mean -----------------------------------------
void findmean(struct datavalues d,const int col,const int row, const int roworcol,double &sum,double &sumofsq,double &mean,int &count)
{
    sum = 0;
    sumofsq = 0;
    count = 0;
    if (roworcol==1){
        for (int i=0;i<d.totalrow;i++){
            sum = sum + d.fulldata[i][col];
            sumofsq = sumofsq + ((d.fulldata[i][col])*(d.fulldata[i][col]));
            count++;
        }
    } else if (roworcol==2){
        for (int i=0;i<d.totalcol;i++){
            if (d.computablecols[i]==1){
                sum = sum + d.fulldata[row][i];
                sumofsq = sumofsq + ((d.fulldata[row][i])*(d.fulldata[row][i]));
                count++;
            }
        }
    }
    mean = sum/count;
}

//---------------------------------------------Liew ------------------------------------------------------
//------------------------------This function loads the variance function------------------------------------
void loadvar(struct datavalues d){
    int row,col,roworcol,count;
    double sum,sumofsq,mean,var;

    askrowcolumn(d,row,col,roworcol);
    findmean(d,col,row,roworcol,sum,sumofsq,mean,count);
    findvar(sum,sumofsq,count,var);

    cout << endl << "The variance of ";
    if (roworcol == 1)
        cout << "column " << col;
    else if (roworcol == 2)
        cout << "row " << row;
    cout << " is " << var << ".";
}

// //---------------------------------------------Liew ------------------------------------------------------
// //--------------------------This functions finds the variance-----------------------------------
void findvar(const double sum,const double sumofsq,const int count, double &var){
    var = (sumofsq - ((sum*sum)/count)) / (count - 1);
}


//---------------------------------------------Liew ------------------------------------------------------
//------------------------This functions loads and finds the standard deviation function----------------------------------
void loadfindstdv(struct datavalues d){
    int row,col,roworcol,count;
    double sum,sumofsq,mean,var,stdv;

    askrowcolumn(d,row,col,roworcol);
    findmean(d,col,row,roworcol,sum,sumofsq,mean,count);
    findvar(sum,sumofsq,count,var);
    stdv = sqrt(var);

    cout << endl << "The standard deviation of ";
    if (roworcol == 1)
        cout << "column " << col;
    else if (roworcol == 2)
        cout << "row " << row;
    cout << " is " << stdv << ".";
}

//---------------------------------------------Liew ------------------------------------------------------
//------------------------This functions asks user to input two column----------------------------------
void asktwocolumn(struct datavalues d, int &col1, int &col2){
    
    do{
        cout << endl << "Enter a column from 0 to " << d.totalcol - 1 << " for the first column." << endl;
        cin >> col1;
        if (!(col1 >= 0 && col1 < d.totalcol && d.computablecols[col1] == 1))
            cout << "Invalid input. Please enter a valid and computable column." << endl;
    }while (!(col1 >= 0 && col1 < d.totalcol && d.computablecols[col1] == 1));

    do{
        cout << endl << "Enter a column from 0 to " << d.totalcol - 1 << " for the second column." << endl;
        cin >> col2;
        if (!(col2 >= 0 && col2 < d.totalcol && d.computablecols[col2] == 1))
            cout << "Invalid input. Please enter a valid and computable column." << endl;
    }while (!(col2 >= 0 && col2 < d.totalcol && d.computablecols[col2] == 1));

}

//---------------------------------------------Liew ------------------------------------------------------
//-------------------------This function loads and finds the correlation--------------------------------
void loadfindcorr(struct datavalues d){
    int roworcol,count,row,col1,col2;
    double sum1,sum2,sumofsq1,sumofsq2,mean1,mean2,sumofcol1x2,corr;
    roworcol = 1;
    sumofcol1x2 = 0;
    asktwocolumn(d,col1,col2);
    findmean(d,col1,row,roworcol,sum1,sumofsq1,mean1,count);
    findmean(d,col2,row,roworcol,sum2,sumofsq2,mean2,count);
    for (int i = 0; i < d.totalrow;i++){
        sumofcol1x2 = sumofcol1x2 + (d.fulldata[i][col1]*d.fulldata[i][col2]);
    }
    double doublerow = (double)d.totalrow;
    corr = (sumofcol1x2-(doublerow*mean1*mean2))/(sqrt(sumofsq1-(doublerow*mean1*mean1))*sqrt(sumofsq2-(doublerow*mean2*mean2)));    
    cout << "The correlation between column " << col1 << " and " << col2 << " is " << corr << endl;
}


//---------------------------------------------Liew ------------------------------------------------------
//------------------------------This functions finds distinct member-----------------------------------------
void finddistinct()
{   
//     int flag=0;
//    double mindata,maxdata,tempmax,tempmin;
//     for (int i=2;i<=5;i++){
//         maxcolumn(i,tempmax,flag);
//         mincolumn(i,tempmin,flag);
//         maxdata = (maxdata<tempmax) ? tempmax : maxdata;
//         mindata = (mindata>tempmin) ? tempmin : mindata;
//     }
//     cout << "     Distinct Numbers Table    " << endl;
//     cout << "---------------+---------------" << endl;//15-+15-
//     cout << "|    Number    |   Frequency  |" << endl;
//     cout << "---------------+---------------" << endl;
//     for (int k=mindata;k<=maxdata;k++){
//         int f = 0;
//         for (int i=0;i<100;i++){
//             if (k == get<1>(student[i]))
//                 f++;
//             if (k == get<2>(student[i]))
//                 f++;
//             if (k == get<3>(student[i]))
//                 f++;
//             if (k == get<4>(student[i]))
//                 f++;
//         }
//         if (f!=0){
//             cout << "|" << setw(7) << right << k;
//             cout << setw(8) << right <<"|";
//             cout << setw(8) <<right << f;
//             cout << setw(7) << right <<"|" << endl;
//             cout << "---------------+---------------" << endl;
//         }
//     }
//     logrecord(" found out the distinct member ");
//     pressenter(2);
}

//------------------------------------------Salah Fayeq---------------------------------------------------
//------------------------------This function finds the histogram-----------------------------------------
void findhistogram()
{
//     srand(time(NULL));
//     set<int> s;

//     findUnique(student, s);
//     vector<int> v2(s.begin(),s.end());
//     vector<int> hist (v2.size(),0);

//     for (int j=0; j<student.size(); j++){
//         for (int i=0;i<v2.size(); i++){
//             if(student[j] == v2[i])
//                 hist[i]++;
//         }
//     }

//     for (int i=0; i<student.size(); i++){
//         cout << v2[i] << "-->";
//         for(int k=0;k<hist[i];k++)
//             cout << "=";
//         cout <<endl;       
//     }
}


//---------------------------------------------Ahmad Ayaan------------------------------------------------------
//------------------------------This functions shows the report menu-----------------------------------------
void reportsmenu()
{   
    // string str1;
    // double db=0;
    // double ds=0;
    // char ch;
    // cout <<"--------------------------------------------------------\n"
    //     <<"          "<<username<<" ,Please enter a number to procced:\n"
    //     <<"--------------------------------------------------------\n"
    //     <<"|  Enter 1 to create a report as a text file           |\n"
    //     <<"|  Enter 2 to create a HTML report                     |\n"
    //     <<"|  Enter B to go back to perform more functions        |\n"
    //     <<"|  Enter U to go back to User's settings menu          |\n"
    //     <<"|  Enter 0 to exit                                     |\n"
    //     <<"--------------------------------------------------------\n";
    // cin>>ch;
    // cin.ignore(' ','\n');
    // string str=" choose the report's menu option ";
    // str.push_back(ch);
    // logrecord(str);
    // switch(ch)
    // {
    //      case('1')    : savereport(1,str1,db,ds);
    //                      break;
    //      case('2')    : saveHTMLreport(1,str1,db,ds);
    //                      break;
    //      case('B')    : //viewfunc();
    //                      break;
    //      case('U')    : getchoice();
    //                      break;
    //      case('0')    : exit(0);
    //                      break;               
    //      default: cout<<"Wrong choice------------->\n"
    //                     <<"Please Enter from the choice given below\n";
    //             reportsmenu();
    //             break;         
    // }
}