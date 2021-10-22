#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

// start 
void createuser();
void loginuser();
void deleteuser();


void getchoice()
{   //try
    int ch;
    cout << "-----------------------------------------------------\n"
        << "|         Hello and Welcome to Our System           |\n"
        << "-----------------------------------------------------\n"
        << "| Please Enter from the choice given below          |\n"
        << "| Enter 1 to Create a New User Account              |\n"
        << "| Enter 2 to Login using existing User Account      |\n"
        << "| Enter 3 to Logout from your User Account          |\n"
        << "| Enter 4 to Delete any User Account                |\n"
        << "| Enter 5 TO Change your Password                   |\n"
        << "-----------------------------------------------------\n";

    cin >> ch;
    switch(ch)
    {
        case(1) : createuser();
                    break;
        case(2) : loginuser();
                    break;
        case(3) :
                    break;
        case(4) :  deleteuser();
                     break;
        case(5) : break;

        // default:
    }
    
}
 checkadmin(string name,string pass,int status) {
        string adminu,adminp;
    cout<<"-----------------------------------------------------------\n"
        <<"ALERT: *Only Admin have the authority to create a username*\n"
        <<"Please enter the username-\n";
    cin>>adminu;
    cout<<"Please enter the password-\n";
    cin>>adminp;
    if(adminu==name && adminp==pass && status==1)
    return true;
    else 
    return false;
}
void createuser()
{
    ifstream file;
    file.open("Users.dat");
    vector<tuple<string,int,string,int>> users;
    tuple<string,int,string,int> userdata;
     while (file>>get<0>(userdata)){
        file >>get<1>(userdata);
        file >>get<2>(userdata);
        file >>get<3>(userdata);
        users.push_back(userdata);
    }

     for (auto elem: users)
    {   
        if(checkadmin(get<0>(elem),get<2>(elem),get<1>(elem))==true)
        {   
            string user,pass;
            int status,power;
            if (!file.is_open())
            {
                cout << " File not found\n";
                exit(-1);
            }
            else
            {   int pos;
                cout << "-----------------------------------------------------\n"
                    <<"Enter a unique user name -\n";
                cin >> user;
                cout << "-----------------------------------------------------\n"
                    <<"Enter your password -\n";
                cin >> pass;
                ofstream outfile;
                outfile.open("Users.dat",ios::out|ios::ate|ios::app);
                status=1;
                power=0;
                outfile << user << " " << power << " " << pass << " " << status<<endl;
                outfile.close();
                file.close();
                cout<<"Username and password created successfully."<<endl;
                break;
            }
        }
        else
        {
            cout << "-----------------------------------------------------\n"
                <<"Please enter the correct admin username or password\n";
                createuser();
        }
    }
}
void loginuser()
{
    vector<tuple<string,int,string,int>> users;
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

    string name, pass;
    cout << "-----------------------------------------------------\n"
        << "Enter Username-\n";
    cin >> name;
    cout << "-----------------------------------------------------\n"
        << "Enter Password-\n ";
    cin >> pass;

    for (auto elem: users)
    {
         if (name == get<0>(elem) &&
             pass == get<2>(elem) &&
             get<3>(elem)==1)
        {
            cout << get<0>(elem) << ": "
                 << ((get<1>(elem)==1)?"admin":"user")
                 << ": " <<get<2>(elem) << ": "
                 << ((get<3>(elem)==1)?"Active":"Deleted")
                 << endl;
                 break;
        }
        else{
            cout << "-----------------------------------------------------\n"
                <<"Wrong username or password\n"
                <<"Please try again\n";
                loginuser();
        }
}
}
void deleteuser()
{
    vector<tuple<string,int,string,int>> users;
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
    string name, pass;
    cout << "-----------------------------------------------------\n"
        << "Enter the Username to delete-\n";
    cin >> name;
    cout << "-----------------------------------------------------\n"
        << "Enter Password to confirm deletion-\n";
    cin >> pass;

     for (auto elem: users)
    {   
        if (name == get<0>(elem) &&
             pass == get<2>(elem) &&
             get<3>(elem)==1)
             {  
                cout << get<0>(elem) << ": "
                 << ((get<1>(elem)==1)?"admin":"user")
                 << ": " <<get<2>(elem) << ": "
                 << ((get<3>(elem)==1)?"Deleted":"Active")
                 << endl;
                ofstream outfile;
                outfile.open("Users.dat",ios::out);
                
                get<3>(elem)=0;
                outfile << get<0>(elem) << " " 
                        << get<1>(elem) << " " 
                        << get<2>(elem) << " " 
                        << get<3>(elem) <<endl;
                users.push_back(elem);
                outfile.close();

                cout << "---------------------------------------------------\n"
                    <<"Account deletion was successful." << endl;
                    break;
             }
        else {
              cout << "-----------------------------------------------------\n"
                <<"Wrong username or password\n"
                <<"Please try again\n";
                deleteuser();
        }
    }
}

int main()
{
    getchoice();
    return 0;
}