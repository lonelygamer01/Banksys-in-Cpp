#include <iostream>
#include <string>
#include <time.h>
#include <thread>
#include <regex>
#include <fstream>
#include <cwchar>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//COPYING SOME RANDOM SHIT FROM STACKOVERFLOW TO MAKE THINGS WORK ALREADY
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif
//the function declaration ends


//storing the username and password of the logged in user for future use
string current_username, current_password, current_id;

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
//CHECKING THE VALID EMAIL ADDRESS WITH REGEX
bool isEmailValid(string email) {
    
    regex emailregex(R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})");

    return regex_match(email, emailregex);
}

//AUTHORIZING THE USER TO CHANGE ANY DATA IN PROFILE
bool auth()
{
    string passw;
    cout << "You are about to change some information, in order to do that we need to make sure its You!" << endl;
    cout << "Please enter you password: ";
    getline(cin, passw);

    if (passw == current_password)
    {
        cout << "Password correct!" << endl;
        Sleep(1000);
        return true;
    }
    else
    {
        cout << "Invalid password!" << endl;
        Sleep(1000);
       return false;
    }   
}

// CHECKING IF THE FILES NEEDED FOR THE APP EXIST OR NOT IF THERE IS AN ERROR CREATE THEM
void checkforfiles()
{
    cout << "Checking for files..." << endl;
    Sleep(2000);
    ifstream logintxt("login.txt");
    if (!logintxt)
    {
        ofstream createLoginFile("login.txt");
        createLoginFile << "example;example"<< endl;
        createLoginFile.close();
    }
    else
    {
        logintxt.close();
    }

    ifstream userdatatxt("user_data.txt");
    if (!userdatatxt)
    {
        ofstream createUserdataFile("user_data.txt");
        createUserdataFile << "0;example;example;example;example@example.com;example;example;2023-05-30.21:53:51"<< endl;
        createUserdataFile.close();
    }
    else
    {
        userdatatxt.close();
    }

    ifstream transactiontxt("transactions.txt");
    if (!transactiontxt)
    {
        ofstream createTransactionFile("transactions.txt");
        createTransactionFile << "0;2023-05-30.21:53:51;0000000;examplecomment;exampletypecode;1500";
        createTransactionFile.close();
    }
    else
    {
        transactiontxt.close();
    }  
    ifstream accounttxt("account.txt");
    if (!accounttxt)
    {
        ofstream createAccountFile("account.txt");
        createAccountFile << "0000000;2023-05-30.21:53:51;exampletypecode;0;1500;examplecardnumber"<< endl;
        createAccountFile.close();
    }
    else
    {
        accounttxt.close();
    }
    cout << "File1 ready..." << endl;
    Sleep(1000);
    cout << "File2 ready..." << endl;
    Sleep(1000);
    cout << "File3 ready..." << endl;
    Sleep(1000);
    cout << "File4 ready..." << endl;
    Sleep(1000);
}
        
class App{
    //REGISTRATION PAGE
    public:
    void regpage()
    {
        system("cls");
        bool notvalid;
        string firstname, lastname, phone, email, login_name, password, regdate;
        string submit;

        cout << "============== Registration ==============" << endl;

        cout << "Firstname: ";
        getline(cin, firstname);
        
        cout << "Lastname: ";
        getline(cin, lastname);
        
        cout << "Phone number: ";
        getline(cin, phone);
        
        cout << "Email address: ";
        getline(cin, email);
        if (isEmailValid(email)) {notvalid = false;}
        else {notvalid = true;  cout << "Not valid email address!"; Sleep(1000);}
        if (notvalid == true){regpage();}
        
        cout << "A username (don't forget it!): ";
        getline(cin, login_name);
        
        cout << "Strong password: ";
        getline(cin, password);
        

        regdate = currentDateTime();

        cout << "Are you sure you want to submit it?" << endl;
        cout << "[1.] Yes" << endl;
        cout << "[0.] No, bring me back to main page" << endl;
        getline(cin, submit);
        system("cls");
        // IF HE SAY YES
        if (submit == "1")
        {
            // GETTING THE LAST REGISTERED CUSTOMER'S ID: READING IT THEN LOADING IT TO STORED_ID THEN CASTING IT TO INTEGER THEN +1 THEN CASTING IT BACK TO STRING
            string rest1, rest2, rest3, rest4, rest5, rest6, rest7;
            string id, stored_id;
            ifstream file_read("user_data.txt");
            while (getline(file_read, id, ';') && getline(file_read, rest1, ';') && getline(file_read, rest2, ';') && getline(file_read, rest3, ';') && getline(file_read, rest4, ';') && getline(file_read, rest5, ';') && getline(file_read, rest6, ';') && getline(file_read, rest7))
            {
                //getting the last id
                stored_id = id;
            }
            file_read.close();
            int stored_id_int = stoi(stored_id);
            stored_id_int += 1;
            stored_id = to_string(stored_id_int);
            
            cout << "Registration was successful!" << endl;
            Sleep(2000);

            ofstream file;
            ofstream file2;
            file.open("user_data.txt", ios_base::app);
            file << stored_id << ";" << firstname << ";" << lastname << ";" << phone << ";" << email << ";" << login_name << ";" << password << ";" << regdate << endl;
            file.close();
            file2.open("login.txt", ios_base::app);
            file2 << login_name << ";" << password << endl;
            file2.close();
            welcomepage();
        }
        else if (submit == "0")
        {   
            welcomepage();
        }

    }

    //LOG-IN PAGE
    public:
    void loginpage()
    {
        system("cls");
        //the input strings
        string user, passw;
        //the file
        //string text;

        //the file parts
        string username, password;
        //rest
        bool match;
        int attempts = 3;
        do
        {
            cout << "Username: ";
            getline(cin, user);
            
            cout << "Password: ";
            getline(cin, passw);

            ifstream file("login.txt");
            while (getline(file, username, ';') && getline(file, password))
            {
                if (user == username && passw == password)
                {
                    match = true;
                    current_username = user;
                    current_password = passw;
                    break;
                }
                else {match = false;}  
            }
            file.close();
            ifstream file_user("user_data.txt");
            string id, fname, lname, pnum, email, uname, passw, regdate;
            while (getline(file_user, id, ';') && getline(file_user, fname, ';') && getline(file_user, lname, ';') && getline(file_user, pnum, ';') && getline(file_user, email, ';') && getline(file_user, uname, ';') && getline(file_user, passw, ';') && getline(file_user, regdate))
            {
                if (uname == current_username && passw == current_password)
                {
                    current_id = id;
                    break;            
                }   
            }
            file_user.close();            

            if (match)
            {
                cout << "Login was successful..." << endl;
                Sleep(2000);
                userpage();
                break;
            }
            else
            {
                attempts -= 1;
                cout << "Incorrect username or password..." << endl;
                cout << "You have " << attempts << " attempts left" << endl;
                Sleep(2000);
                system("cls");
            }
        } while (attempts > 0);
        if (attempts == 0)
        {
            welcomepage();
        }   
    }

    //WHEN THE USER LOGGED IN
    public:
    void userpage()
    {
        string choice;
        system("cls");
        cout << "============== Main menu ==============" << endl;
        cout << "[0.] Log-out" << endl;
        cout << "[1.] View / Create Your accounts" << endl;
        cout << "[2.] View / Edit profile information" << endl;
        cout << "[3.] Make a transaction" << endl;
        
        cout << "Menu index [0-3]: ";
        getline(cin, choice);

        if (choice == "0")
        {           
            welcomepage();
        }
        if (choice == "1")
        {
           accounts();
        }
        if (choice == "2")
        {
            editprofile();
        }
        if (choice == "3")
        {
            transaction();
        }
        else
        {
            cout << "Invalid input!" << endl;
            Sleep(1000);
            userpage();
        }
    }
    public:
    void accounts()
    {
        system("cls");
        cout << "============== Your Accounts ==============" << endl;
        cout << "Account number:" << "    Date of create:" << "        Balance:" << endl;
        //bool match;
        int noofacc = 0;
        string choice;
        string accnum, dateofcreate, typecode, customerid, balance, cardnum;
        ifstream account("account.txt");
        while (getline(account, accnum, ';') && getline(account, dateofcreate, ';') && getline(account, typecode, ';') && getline(account, customerid, ';') && getline(account, balance, ';') && getline(account, cardnum))
        {
            if (customerid == current_id)
            {
                cout << accnum << "             " << dateofcreate << "       " << balance << "$" << endl;
                noofacc++;
            }  
        }
        account.close();
        cout << "[0.] Back" << endl;
        cout << "[1.] Create new account" << endl;
        cout << "Menu index: ";
        getline(cin, choice);
        if (choice == "0")
        {
            userpage();
        }
        if (choice == "1")
        {
            //MAKING SURE YOU CANT OPEN MORE THAN 4 ACCOUNT
            if (noofacc == 4)
            {
                cout << "Maximum number of accounts reached!" << endl;
                Sleep(1000);
                accounts();
            }
            else
            {
                string acc, cardnum, needcard, confirm;
                cout << "Choose Your account type:" << endl;
                cout << "[1.] Current account  [2.] Saving account" << endl;
                getline(cin, acc);
                cout << "Do You need a card to Your account?" << endl;
                cout << "[1.] Yes  [2.] No" << endl;  
                getline(cin, needcard);
                cout << "Please confirm the action!" << endl;           
                cout << "[0.] Cancel  [1.] Confirm" << endl;
                getline(cin, confirm);
                if (confirm == "0")
                {
                    accounts();
                }
                if (confirm == "1")
                {
                    if (acc == "1" || acc == "2" && needcard == "1" || needcard == "2" )
                    {
                        cout << "Creating your account..." << endl;
                        Sleep(3000);

                        srand(static_cast<unsigned int>(time(nullptr)));
                        int randomNumber = rand() % 900000 + 100000;
                        string randomnumber = to_string(randomNumber);
                        string time = currentDateTime();

                        ofstream file;
                        file.open("account.txt", ios_base::app);
                        file << randomnumber<< ";" << time << ";" << acc << ";" << current_id << ";" << "5000" << ";" << "0" << endl;
                        file.close();     
                        cout << "Success..." << endl;
                        accounts();                
                    }
                    else
                    {
                        cout << "One of your given options was not valid!" << endl;
                        Sleep(1000);
                        accounts();                    
                    }                             
                }
                else
                {
                    cout << "Invalid input!" << endl;
                    Sleep(1000);
                    accounts();
                }
            }  
        }
        else
        {
            cout << "Invalid input!" << endl;
            Sleep(1000);
            accounts();
        }      
    }

    //A FUNCTION TO CALL WHEN THE USER WANT TO CHANGE A PROFILE DATA AND ENTER THE DATA
    public:
    void enternewdata(/*int choice,*/ string new_data)
    {
        if (auth() == true)
        {
            cout << "Enter the new data: ";
            getline(cin, new_data);
            cout << "Saving..." << endl;
            Sleep(1500);
            /*
            string id, fname, lname, pnum, email, uname, passw, regdate;
            ifstream file("user_data.txt");
            //GOING THROUGH THE FILE
            while (getline(file, id, ';') && getline(file, fname, ';') && getline(file, lname, ';') && getline(file, pnum, ';') && getline(file, email, ';') && getline(file, uname, ';') && getline(file, passw, ';') && getline(file, regdate))
            {
                //FINDING THE CURRENTLY LOGGED IN USER IN THE FILE
                if (uname == current_username && passw == current_password)
                {
                    if (choice == 1)
                    {
                        
                    }
                    
                    
                    break;            
                } 
            }
            file.close();
            */
            cout << "Saved" << endl;
            Sleep(1000);
            editprofile(); 
        }
        else
        {
            editprofile();
        } 
    }

    public:
    void editprofile()
    {
        string choice;
        string id, fname, lname, pnum, email, uname, passw, regdate;
        int numberofaccounts = 0;
        //COUNTING THE NUMBER OF ACCOUNTS
        string accnum, dateofcreate, typecode, customerid, balance, cardnum;
        ifstream account("account.txt");
        while (getline(account, accnum, ';') && getline(account, dateofcreate, ';') && getline(account, typecode, ';') && getline(account, customerid, ';') && getline(account, balance, ';') && getline(account, cardnum))
        {
            if (customerid == current_id)
            {
                numberofaccounts++;
            }  
        }
        account.close();        
        system("cls");
        cout << "============== Your Profile ==============" << endl << endl;

        ifstream file("user_data.txt");
        while (getline(file, id, ';') && getline(file, fname, ';') && getline(file, lname, ';') && getline(file, pnum, ';') && getline(file, email, ';') && getline(file, uname, ';') && getline(file, passw, ';') && getline(file, regdate))
        {
            if (uname == current_username && passw == current_password)
            {
                cout << "CustomerID: "<< current_id << endl;
                cout << "Firstname: "<< fname << endl;
                cout << "Lastname: "<< lname << endl;
                cout << "Phone number: "<< pnum << endl;
                cout << "Email address: "<< email << endl;
                cout << "Username: "<< uname << endl;
                cout << "Date of registration: "<< regdate << endl;
                cout << "Number of accounts: "<< numberofaccounts << endl << endl;    
                break;            
            }   
        }
        file.close();
        cout << "============== Editing Your Profile ==============" << endl << endl;
        cout << "Please choose which information You would like to modify" << endl;
        cout << "Warning! This service currently unavailable!" << endl;
        cout << "[0.] Back" << endl;
        cout << "[1.] Firstname" << endl;
        cout << "[2.] Lastname" << endl;
        cout << "[3.] Phone number" << endl;
        cout << "[4.] Email address" << endl;
        cout << "[5.] Username" << endl;
        cout << "[6.] Password" << endl;

        cout << "Menu index [0-6]: ";
        getline(cin, choice);

        if (choice == "0")
        {           
            userpage();
        }
        if (choice == "1")
        {
            string fname_edit;
            enternewdata(fname_edit);
        }
        if (choice == "2")
        {
            string lname_edit;
            enternewdata(lname_edit);
        }
        if (choice == "3")
        {
            string phone_edit;
            enternewdata(phone_edit);
        }
        if (choice == "4")
        {
            string email;
            auth();
            cout << "Enter the new data: ";
            getline(cin, email);

            if (isEmailValid(email)) {
                cout << "The email is valid!" << endl;
                cout << "Saving..." << endl;
                Sleep(1500);
                cout << "Saved" << endl;
                Sleep(1000);
                editprofile();
            } 
            else {
                cout << "The email is not valid!" << endl;
                Sleep(1000);
                editprofile();
            }
        }
        if (choice == "5")
        {
            string uname_edit;
            enternewdata(uname_edit);
        }
        if (choice == "6")
        {
            string passw_edit;
            enternewdata(passw_edit);
        }
        else
        {
            cout << "Invalid input!" << endl;
            Sleep(1000);
            editprofile();
        }
    }
    public:
    void transaction()
    {
        system("cls");
        char choice;
        int index = 1;
        cout << "============== Transfer money to other account(s) ==============" << endl;
        cout << "Warning! This service currently unavailable!" << endl;
        cout << "Select Your account" << endl;
        cout << "[0.] Exit" << endl;
        
        //OPEINT THE ACCOUNTS.TXT
        string accnum, dateofcreate, typecode, customerid, balance, cardnum;
        ifstream account("account.txt");
        while (getline(account, accnum, ';') && getline(account, dateofcreate, ';') && getline(account, typecode, ';') && getline(account, customerid, ';') && getline(account, balance, ';') && getline(account, cardnum))
        {
            //GETTING THE MATCHING LINES
            if (customerid == current_id)
            {
                cout << "[" << index << ".]"<< " " << accnum << " " << dateofcreate << endl;
                index++;

            }  
        }
        account.close();  

        cout << "Menu index: ";
        cin >> choice;

        switch (choice)
        {
        case '0':
            userpage();
        default:
            transaction();
        }


    }


    //WELCOME PAGE
    public:
    void welcomepage()
    {
        string choice;
        system("cls");
        cout << "============== MAZE BANK ==============" << endl;
        cout << "Welcome!" << endl;

        cout << "[0.] Exit" << endl;
        cout << "[1.] Register as a new customer" << endl;
        cout << "[2.] Log-in to your profile" << endl;
        cout << "Menu index: ";
        getline(cin, choice);
        if (choice == "0")
        {
            exit(0);
        }
        else if (choice == "1")
        {
            regpage();
        }
        else if (choice == "2")
        {
            loginpage();
        }
        else
        {
            cout << "Invalid input!";
            Sleep(1500);
            welcomepage();
        } 
    }
};


//WHERE THE PROGRAM STARTS ITSELF
int main()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 24;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    system("color 2");
    checkforfiles();
    App app;
    app.welcomepage();

    cout << "Program finished running..." << endl;
    system("pause");

    return 0;
}