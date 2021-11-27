#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "autotellermachine.hpp"

using std::cout;
using std::cin; 
using std::string;
using std::vector;
using std::right;
using std::left;
using std::system; 
using std::setfill;


/*DECLERATIONS*/

struct Table
{
    // Redovisar antalet kunder genom att hämta högsta angedda siffer-ID
    int     get_max_account_number();
    //Skapar tabellen som visar uttag och intag
    void    print_table(int accountNum);//
    //Skapar en ny rad på tabellen
    void  insert_row();//
}table;
struct Interface
{
    //Visualiserar vår interface
    void show_header();
    //Visar användarens olika interaktions alternativ
    void show_options();
    //Adderar en ny kund till listan
    void handle_add_cust();
    //Uppdaterar data om valfri kund baserat på id
    void handle_update_cust();
    //Raderar data om valfri kund baserat på id
    void handle_delete_cust();
}intface;

vector <AutoTellerMachine> ATM_list;

bool quit = false;

void createAccount();
bool logIn();
void userIn(int userAccount);
void getUsersFromFile();
void saveUsersToFile();
void clearScreen();

/*DECLERATIONS END*/

/*INIT*/
int main()
{
    ATM.loggedInAccountLocation = -1;
    char userChoice;
    bool start = true;
    getUsersFromFile();

    while(start)
    {
        intface.show_header();
        intface.show_options();
        cin >> userChoice;
        switch (toupper(userChoice))
        {
            case 'L':
            {
                bool wrongUserAccount = logIn();
                if(!wrongUserAccount)
                {
                    userIn(ATM.loggedInAccountLocation);
                }
                if(quit)
                {
                    saveUsersToFile();
                    start = false;
                }
                break;
            }
                
            case 'C':
            {
                createAccount();
                break;
            }
                
            case 'Q':
            {
                cout << "You will now exit\n";
                saveUsersToFile();
                start = false;
                break;
            }

            default:
                cout << "You must choose a valid option\n\n";
                break;
        }
    }
    return 0;
}
/*INIT END*/


/*FUNKTIONS*/

void getUsersFromFile()
{
    ifstream fin;
    fin.open("user_list.csv");

    string readAccountNumber, readUsername, readPassword, readAccountBalance, readLastMoneyMovement, 
           readLastOperation, readBeginningBalance;
    bool wrong = false;

	while (!fin.eof())
	{
        wrong = false;
        getline(fin, readAccountNumber, ',');
		getline(fin, readUsername, ',');
		getline(fin, readPassword, ',');
        getline(fin, readAccountBalance, ',');
        getline(fin, readLastMoneyMovement, ',');
        getline(fin, readLastOperation, ',');
        getline(fin, readBeginningBalance, '\n');

        if(readAccountNumber == "")
        {
            wrong = true;
        }
        if(!wrong)
        {
            AutoTellerMachine user;
            // try{cust.accountNumber = stoi(readAccountNumber);}
            // catch(const std::exception& e)
            // {
            //     printf("\nDBG_LOG :: Try-Catch :: stoi Error: %s\n", e.what());
            // }
            
            user.accountNumber = stoi(readAccountNumber);
            user.username = readUsername;
            user.password = readPassword; 
            user.accountBalance = stoi(readAccountBalance);
            user.lastMoneyMovement = stoi(readLastMoneyMovement); 
            if(readLastOperation == "a")
            {
                user.lastOperation = 'a';
            }
            else if(readLastOperation == "W")
            {
                user.lastOperation = 'W';
            }
            else if(readLastOperation == "D")
            {
                user.lastOperation = 'D';
            }
            user.beginningBalance = stoi(readBeginningBalance);
            ATM_list.push_back(user);
        }

    }

	fin.close();
}

bool logIn()
{
    string loginName, loginPassword;
    int userAccountNumber;
    bool notCorrect = true, noAccount = true;

    table.insert_row();
    cout << "|" << left << setw(20) << setfill(' ') << "Log in " 
         << right << setw(20) << setfill(' ') << "|" << endl;
    table.insert_row();

    //cout << "Log in\n\n";
    //cout << "Account number: ";

    cout << " " << left << setw(16) << setfill(' ') << "Account number: ";
    cout << endl << "->";

    if( ! (cin >> userAccountNumber)) 
    {
        cin.clear();
        cout << "You have yo write the correct account number ex. 1000\n";
        //error
    }
    else
    {
        notCorrect = false;
    }

    
    // if( ! (cin >> userAccountNumber)) 
    // {
    //     cin.clear();
    //     cout << "You have yo write the correct account number ex. 1000\n";
    //     //error
    // }
    // else
    // {
    //     notCorrect = false;
    // }
    if(!notCorrect)
    {
        // cout << "Username: ";
        // cin >> loginName;
        // cout << "Passwordd: ";
        // cin >> loginPassword;
        // clearScreen();
        // noAccount = ATM.AccountLogin(userAccountNumber, loginName, loginPassword);

        cout << " " << left << setw(16) << setfill(' ') << "Username: ";
        cout << "\n->";
        cin >> loginName;
        cout << " " << left << setw(16) << setfill(' ') << "Password: ";
        cout << "\n->";
        cin >> loginPassword;

        clearScreen();
        noAccount = ATM.AccountLogin(userAccountNumber, loginName, loginPassword);
    }
        
    return noAccount;
}

void userIn(int userAccount)
{
    bool inAccount = true;
    if (userAccount >= 0)
    {
        while (inAccount)
        {
            int i = userAccount;
            char loginChoice;
            table.print_table(i);
            ATM_list[i].AccountMenu();
            cin >> loginChoice;
            system("cls");
            switch (toupper(loginChoice))
            {
                case 'D':
                {
                    bool positiveNumber = true;
                    ATM_list[i].SetBeginningBalance(i);
                    double depositMoney;
                    while(positiveNumber)
                    {
                        depositMoney = 0;
                        cout <<"How much do you want to deposit: ";
                        cin >> depositMoney;
                        system("cls");
                        if(depositMoney > 0)
                        {
                            ATM_list[i].DepositMoney(depositMoney);
                            ATM_list[i].SetLastOperation(i, toupper(loginChoice));
                            ATM_list[i].SetLastMoneyMovement(i, depositMoney);
                            positiveNumber = false;
                        }
                        else
                        {
                            cout <<"You can't deposit a negative amount\n";
                        }
                    }
                    break;
                }
                    
                case 'W':
                {
                    bool wAmount = true;
                    ATM_list[i].SetBeginningBalance(i);
                    double withdrawalAmount;
                    while(wAmount)
                    {
                        withdrawalAmount = 0;
                        cout <<"How much do you want to withdraw from your account: ";
                        cin >> withdrawalAmount;
                        system("cls");
                        if(withdrawalAmount < ATM_list[i].accountBalance)
                        {
                            ATM_list[i].WithdrawMoney(withdrawalAmount);
                            ATM_list[i].SetLastOperation(i, toupper(loginChoice));
                            ATM_list[i].SetLastMoneyMovement(i, withdrawalAmount);
                            wAmount = false;
                        }
                        else
                        {
                            cout << "You can't withdraw more than you have on your account.\n";
                        }
                    }
                    break;
                }
                    
                case 'R':
                {
                    //Your beginning balance before your last operation
                    table.print_table(i);
                    // cout << "Beginning balance: SEK" << ATM_list[i].GetBeginningBalance(ATM.loggedInAccountLocation)
                    //         << ".00\n";

                    cout << "|" <<  left << setw(20) << setfill(' ') << "Beginning balance: "
                             << "SEK" << left << setw(16) << setfill(' ') << ATM_list[i].GetBeginningBalance(ATM.loggedInAccountLocation)
                             << "|" << endl;
                    table.insert_row();

                    //If you deposit money last time
                    if (ATM_list[i].GetLastOperation(i) == 'D') 
                    {
                        // cout << "Deposit amount: SEK" << ATM_list[i].lastMoneyMovement << ".00" << endl;
                        
                        cout << "|" <<  left << setw(20) << setfill(' ') << "Deposit amount: " 
                             << "SEK" << left << setw(16) << setfill(' ') << ATM_list[i].lastMoneyMovement
                             << "|" << endl;
                        table.insert_row();
                    }
                    //If you withdraw money the last time
                    else if (ATM_list[i].GetLastOperation(i) == 'W')
                    {
                        cout << "|" << left << setw(20) << setfill(' ') << "Withdrawl amount: " 
                             << "SEK" << left << setw(16) << setfill(' ') << ATM_list[i].lastMoneyMovement 
                             << "|" << endl;
                        table.insert_row();
                    }

                    cout << "|" <<  left << setw(20) << setfill(' ') << "Your balance: " << "SEK" << left 
                         << setw(16) << setfill(' ') << ATM_list[i].GetAccountBalance(ATM.loggedInAccountLocation)
                         << "|" << endl;

                    table.insert_row();
                    system("pause");
                    system("cls");
                    break;
                }
                    
                case 'Z':
                {
                    cout << "You logout\n";
                    inAccount = false;
                    break;
                }
                    
                case 'Q':
                {
                    quit = true;
                    inAccount = false;
                    break;
                }
                    
                default:
                    cout << "You must choose a valid option\n\n";
                    break;
            }
        }
        ATM.loggedInAccountLocation = -1;
    }
}

void createAccount()
{
    string _username, _password;

    cout << "Create an account\n\nUsername: ";
    cin >> _username;
    cout << "Password: ";
    cin >> _password;
    clearScreen();
    ATM.CreateNewAccount(_username, _password);
        
}

void saveUsersToFile()
{
    ofstream fout;
    int firsttime = 0;
    for (int i = 0; i < ATM_list.size(); i++)
    {
        if(firsttime > 0)
        {
            fout << endl;
        }
        if(firsttime == 0)
        {
            fout.open("user_list.csv", ios::trunc);
            firsttime = 1;
        }
        else if(firsttime == 1)
        {
            fout.close();
            fout.open("user_list.csv", ios::app);
            firsttime == 2;
        }
        
        cout << ATM_list[i].accountNumber << "," << ATM_list[i].username << "," << ATM_list[i].password 
             << "," << ATM_list[i].accountBalance << "," << ATM_list[i].lastMoneyMovement << "," 
             << ATM_list[i].lastOperation << "," << ATM_list[i].beginningBalance << "\n";
        fout << ATM_list[i].accountNumber << "," << ATM_list[i].username << "," << ATM_list[i].password 
             << "," << ATM_list[i].accountBalance << "," << ATM_list[i].lastMoneyMovement << "," 
             << ATM_list[i].lastOperation << "," << ATM_list[i].beginningBalance;
        
        
        _sleep(1000);
    }
    fout.close();

}

void clearScreen()
{
    system("cls");
}



/*Funktions in struct Autotellermachine*/
bool AutoTellerMachine::AccountLogin(int loginUserAccountNumber, string loginUsername, string loginPassword)
{
    bool noAccount = true;
    //Check if user exist and log in
    for (int i = 0; i < ATM_list.size(); i++)
    {
        if ( (ATM_list[i].username == loginUsername) && 
             (ATM_list[i].password == loginPassword) &&
             (ATM_list[i].accountNumber == loginUserAccountNumber) )
        {
            ATM.SetAccountLogin(i);
            noAccount = false;
            cout << "Access Granted\n";
            break;
        }
    }

    if(noAccount)
    {
        cout << right << setw(38) << setfill('*') << "LOGIN FAILED" << setw(26) << setfill('*') << " "
             << "\n- try another username, password or check you account number -\n\n";
    }
    return noAccount;
}

void AutoTellerMachine::CreateNewAccount(string newUsername, string newPassword)
{
    bool createUser = true;
    for (int i = 0; i < ATM_list.size(); i++)
    {
        if (newUsername == ATM_list[i].username)
        {
            cout << "That username already exist\n";
            createUser = false;
            break;
        }
    }
    if (createUser)
    {
        int nextAccount = table.get_max_account_number();
        if(nextAccount == 0)
        {
            nextAccount = 1000;
        }
        else
        {
            ++nextAccount;
        }
        
        AutoTellerMachine newUser;
        newUser.accountNumber = nextAccount;
        newUser.username = newUsername;
        newUser.password = newPassword;
        newUser.beginningBalance = 0;
        newUser.accountBalance = 0;
        newUser.lastMoneyMovement = 0;
        newUser.lastOperation = 'a';
        ATM_list.push_back(newUser);
        cout << "Thank you, your account has been created!\nAccount number: " <<
                nextAccount << endl << "Username: " << newUsername << endl << 
                "Password: ********\n";
        system("pause");
        system("cls");
    }
}

void AutoTellerMachine::AccountMenu()
{
    cout << "\n"
            "[d] Deposit Money\n[w] Withdraw Money\n[r] Request Balance\n"
            "[z] Logout\n[q] Quit\n";
    
}

void AutoTellerMachine::DepositMoney(double depositAmount)
{
    ATM_list[ATM.loggedInAccountLocation].accountBalance += depositAmount;
}

void AutoTellerMachine::WithdrawMoney(double withdrawalAmount)
{
    ATM_list[ATM.loggedInAccountLocation].accountBalance -= withdrawalAmount;
}

/*Set funktions*/
void AutoTellerMachine::SetAccountLogin(int setAccountLocation)
{
    ATM.loggedInAccountLocation = setAccountLocation;
}

void AutoTellerMachine::SetLastMoneyMovement(int accountID, double amount)
{
    ATM_list[accountID].lastMoneyMovement = amount;
}

void AutoTellerMachine::SetLastOperation(int accountID, char userInput)
{
    ATM_list[accountID].lastOperation = userInput;
}

void AutoTellerMachine::SetBeginningBalance(int accountID)
{
    ATM_list[accountID].beginningBalance = ATM_list[accountID].accountBalance;
}

void AutoTellerMachine::SetAccountNumber(int accountNum)
{
    ATM_list[accountNum].accountNumber = accountNum;
}

/*GET*/
double AutoTellerMachine::GetBeginningBalance(int accountID) const
{
    return ATM_list[accountID].beginningBalance;
}

int AutoTellerMachine::GetAccountLogin() const
{
    return loggedInAccountLocation;
}

double AutoTellerMachine::GetLastMoneyMovement(int accountID) const
{
    return ATM_list[accountID].lastMoneyMovement;
}

double AutoTellerMachine::GetAccountBalance(int accountID) const
{
    return ATM_list[accountID].accountBalance;
}

char AutoTellerMachine::GetLastOperation(int accountID) const
{
    return ATM_list[accountID].lastOperation;
}

string AutoTellerMachine::GetUsername(int accountID) const
{
    return ATM_list[accountID].username;
}

/*END Funktions in struct Autotellermachine*/

//Funktions for Table

void Table::print_table(int accountNum)
{
    cout << "|" << right << setfill('=') << setw(40) << "|" << endl
         << "| " << left << setfill(' ') << setw(10) << "Account: " << left << setw(28) << ATM_list[accountNum].accountNumber << "|" << endl 
         << "| " << left << setw(10) << "User: " << left << setw(28) << ATM_list[accountNum].username << "|" << endl
        //  << "| " << left << setfill(' ') << setw(28) << ATM_list[accountNum].accountNumber << "|" << endl
        //  << "| " << left << setfill(' ') << setw(28) << ATM_list[accountNum].username << "|" << endl
         << "| " << left << setw(10) << "Balance: " << left << setw(28) << ATM_list[accountNum].accountBalance << "|" << endl
         << "|" << right << setfill('=') << setw(40) << "|" << endl;
}

int Table::get_max_account_number()
{
    int max = 0;
    for(int cust = 0; cust < ATM_list.size(); cust++)
    {
        if(ATM_list[cust].accountNumber > max)
        {
            max = ATM_list[cust].accountNumber;
        }
    }
    return max;
}

void Table::insert_row()
{
    cout << "|" << right << setfill('-') << setw(40) << "|" << endl;
}

//END Funktions for Table

//Funktions for Interface

void Interface::show_options()
{
    cout << "Please select an option below\n[l] Log in\n[c] Create new acount\n[q] Quit\n";
}


void Interface::show_header()
{
    cout << "|" << right << setfill('=') << setw(50) << "|" << endl
         << "|" << right << setfill(' ') << setw(50) << "|" << endl
         << "|" << left << setfill(' ') << setw(9) << " " << right 
         << setw(20) << "Welcome to Melina's ATM machine" << right << setw(10) << "|" << endl
         << "|" << right << setfill(' ') << setw(50) << "|" << endl
         << "|" << right << setfill('=') << setw(50) << "|" << endl;
}

//END Funktions for Interface

/*FUNKTIONS END*/