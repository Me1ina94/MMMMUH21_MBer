#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "autotellermachine.hpp"

using namespace std;

/*DECLERATIONS*/

struct Table
{
    // Redovisar antalet kunder genom att hämta högsta angedda siffer-ID
    void get_max_id();
    // Anger Dagens datum
    void write_date();
    // Avläser dagens datum
    void read_date();
    //Skapar tabellen som uppvisar datan
    void print_table(int accountNum);//
    //Skapar en ny rad på tabellen
    string insert_row();//
}table;
struct Interface
{
    //Visualiserar vår interface
    void show_interface();
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
void logIn();
void userIn(int userAccount);
int maxAccountNumber();
void getUsers();
void saveCustomerData();

/*DECLERATIONS END*/

/*INIT*/
int main()
{
    ATM.loggedInAccountLocation = -1;
    char userChoice;
    bool start = true;

    while(start)
    {
        void getUsers();
        intface.show_options();
        cin >> userChoice;
        switch (toupper(userChoice))
        {
            case 'L':
                logIn();
                userIn(ATM.loggedInAccountLocation);

                if(quit)
                {
                    void saveCustomerData();
                    start = false;
                }
                break;
                
            case 'C':
                createAccount();
                break;
                
            case 'Q':
                cout << "You will now exit\n";
                void saveCustomerData();
                start = false;
                break;

            default:
                cout << "You must choose a valid option\n\n";
                break;
        }
    }
    return 0;
}
/*INIT END*/


/*FUNKTIONS*/

void getUsers()
{

}

void saveCustomerData()
{
    ofstream fout;
    int firsttime = 0;
    for (int i = 0; i < ATM_list.size(); i++)
    {
        if(firsttime == 0)
        {
            fout.open("user_list.cvs", ios::trunc);
            firsttime = 1;
        }
        else if(firsttime == 1)
        {
            fout.close();
            fout.open("user_list.cvs", ios::app);
            firsttime == 2;
        }
        if(firsttime > 0)
        {
            fout << endl;
        }
        cout << ATM_list[i].accountNumber << "," << ATM_list[i].username << "," << ATM_list[i].password 
             << "," << ATM_list[i].accountBalance << "," << ATM_list[i].lastMoneyMovement << "," 
             << ATM_list[i].lastOperation << ATM_list[i].beginningBalance << "\n";
        fout << ATM_list[i].accountNumber << "," << ATM_list[i].username << "," << ATM_list[i].password 
             << "," << ATM_list[i].accountBalance << "," << ATM_list[i].lastMoneyMovement << "," 
             << ATM_list[i].lastOperation << ATM_list[i].beginningBalance << "\n";
        
        _sleep(500);
    }
    fout.close();

}

void Interface::show_options()
{
    cout << "Welcome to the ATM Machine\n\n"
         "Please select an option below\n[l] Log in\n[c] Create new acount\n[q] Quit\n";
}

void logIn()
{
    string loginName, loginPassword;
    int userAccountNumber;
    cout << "Log in\n\n";
    cout << "Account number: ";
    cin >> userAccountNumber;
    cout << "Username: ";
    cin >> loginName;
    cout << "Passwordd: ";
    cin >> loginPassword;
    system("cls");
    ATM.AccountLogin(userAccountNumber, loginName, loginPassword);
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
                    cout << "Beginning balance: SEK" << ATM_list[i].GetBeginningBalance(ATM.loggedInAccountLocation)
                            << ".00\n";

                    //If you deposit money last time
                    if (ATM_list[i].GetLastOperation(i) == 'D') 
                    {
                        cout << "Deposit amount: SEK" << ATM_list[i].lastMoneyMovement << ".00" << endl;
                    }
                    //If you withdraw money the last time
                    else if (ATM_list[i].GetLastOperation(i) == 'W')
                    {
                        cout << "Withdrawl amount: SEK" << ATM_list[i].lastMoneyMovement << ".00" << endl;
                    }

                    cout << "Your balance: SEK" << ATM_list[i].GetAccountBalance(ATM.loggedInAccountLocation)
                            << ".00\n";
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
    system("cls");
    ATM.CreateNewAccount(_username, _password);
        
}

int maxAccountNumber()
{
    int max = 0;
    for(int cust = 0; cust = ATM_list.size(); cust++)
    {
        if(ATM_list[cust].accountNumber > max)
        {
            max = cust;
        }
    }
    return max;
}

/*Funktions in struct Autotellermachine*/
void AutoTellerMachine::AccountLogin(int loginUserAccountNumber, string loginUsername, string loginPassword)
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
        cout << "******* LOGIN FAILED *******\n- try another username or password -\n\n";
    }
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
        int nextAccount = maxAccountNumber();
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


//Funktions for Table

void Table::print_table(int accountNum)
{
    cout << "|" << right << setfill('=') << setw(30) << "|" << endl
         << "|" << right << setfill(' ') << setw(30) << ATM_list[accountNum].accountNumber 
         << endl << "| " << left << setw(28) << setfill(' ') << ATM_list[accountNum].username 
         << "|" << endl << "| " << left << setw(20) << "Balance: " << left << setw(8)
         << ATM_list[accountNum].accountBalance << "|" << endl
         << "|" << right << setfill('=') << setw(30) << "|" << endl;
}

//Funktions for Interface


/*FUNKTIONS END*/