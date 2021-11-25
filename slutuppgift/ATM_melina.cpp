#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

/*DECLERATIONS*/

struct AutoTellerMachine
// to represent each customer who uses the ATM program
{
    int     loggedInAccountLocation;
    double  accountBalance;
    double  beginningBalance;
    double  lastMoneyMovement;
    char    lastOperation;
    string  username;
    string  password;
    vector <AutoTellerMachine> ATM_list;
    
    //menu when you're in your account
    void    AccountMenu();
    //user log in
    void    AccountLogin(string loginUsername, string loginPassword);
    //user create an account
    void    CreateNewAccount(string newUsername, string newPassword);
    
    void    DepositMoney(double depositAmount);
    void    WithdrawMoney(double withdrawalAmount);

    //loggedInAccountLocation
    void    SetAccountLogin(int setAccountLocation);
    //The amount of money you withdrew or deposit
    void    SetLastMoneyMovement(int accountID, double amount);
    //money you have in the beginning of a withdraw or deposit
    void    SetBeginningBalance(int accountID);
    //The last input of the user, withdraw of deposit monew
    void    SetLastOperation(int accountID, char userInput);

    int     GetAccountLogin() const;
    double  GetLastMoneyMovement(int accountID) const;
    double  GetAccountBalance(int accountID) const;
    double  GetBeginningBalance(int accountID) const;
    char    GetLastOperation(int accountID) const;
    string  GetUsername(int accountID) const;
    
    
}ATM;

bool quit = false;

void menu_1();
void createAccount();
void logIn();
void userIn(int userAccount);

/*DECLERATIONS END*/

/*INIT*/
int main()
{
    ATM.loggedInAccountLocation = -1;
    char userChoice;
    bool start = true;

    while(start)
    {
        menu_1();
        cin >> userChoice;
        switch (toupper(userChoice))
        {
            case 'L':
                logIn();
                userIn(ATM.loggedInAccountLocation);

                if(quit)
                {
                    start = false;
                }
                break;
                
            case 'C':
                createAccount();
                break;
                
            case 'Q':
                cout << "You will now exit\n";
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

void menu_1()
{
    cout << "Welcome to the ATM Machine\n\n"
         "Please select an option below\n[l] Log in\n[c] Create new acount\n[q] Quit\n";
}
void logIn()
{
    string loginName, loginPassword;
    cout << "Log in\n\n";
    cout << "Username: ";
    cin >> loginName;
    cout << "Passwordd: ";
    cin >> loginPassword;
    system("cls");
    ATM.AccountLogin(loginName, loginPassword);
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
            cout << "|" << right << setfill('=') << setw(20) << "|" << endl;
            cout << "| " << left << setw(18) << setfill(' ') << ATM.ATM_list[i].username <<
                    "|" << endl << "| " << left << setw(10) << "Balance: " << left << setw(8)
                 << ATM.ATM_list[i].accountBalance << "|" << endl;
            cout << "|" << right << setfill('=') << setw(20) << "|" << endl;
            ATM.ATM_list[i].AccountMenu();
            cin >> loginChoice;
            system("cls");
            switch (toupper(loginChoice))
            {
                case 'D':
                {
                    bool positiveNumber = true;
                    ATM.ATM_list[i].SetBeginningBalance(i);
                    double depositMoney;
                    while(positiveNumber)
                    {
                        depositMoney = 0;
                        cout <<"How much do you want to deposit: ";
                        cin >> depositMoney;
                        system("cls");
                        if(depositMoney > 0)
                        {
                            ATM.ATM_list[i].DepositMoney(depositMoney);
                            ATM.ATM_list[i].SetLastOperation(i, toupper(loginChoice));
                            ATM.ATM_list[i].SetLastMoneyMovement(i, depositMoney);
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
                    ATM.ATM_list[i].SetBeginningBalance(i);
                    double withdrawalAmount;
                    while(wAmount)
                    {
                        withdrawalAmount = 0;
                        cout <<"How much do you want to withdraw from your account: ";
                        cin >> withdrawalAmount;
                        system("cls");
                        if(withdrawalAmount < ATM.ATM_list[i].accountBalance)
                        {
                            ATM.ATM_list[i].WithdrawMoney(withdrawalAmount);
                            ATM.ATM_list[i].SetLastOperation(i, toupper(loginChoice));
                            ATM.ATM_list[i].SetLastMoneyMovement(i, withdrawalAmount);
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
                    cout << "Beginning balance: SEK" << ATM.ATM_list[i].GetBeginningBalance(ATM.loggedInAccountLocation)
                            << ".00\n";

                    //If you deposit money last time
                    if (ATM.ATM_list[i].GetLastOperation(i) == 'D') 
                    {
                        cout << "Deposit amount: SEK" << ATM.ATM_list[i].lastMoneyMovement << ".00" << endl;
                    }
                    //If you withdraw money the last time
                    else if (ATM.ATM_list[i].GetLastOperation(i) == 'W')
                    {
                        cout << "Withdrawl amount: SEK" << ATM.ATM_list[i].lastMoneyMovement << ".00" << endl;
                    }

                    cout << "Your balance: SEK" << ATM.ATM_list[i].GetAccountBalance(ATM.loggedInAccountLocation)
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


/*Funktions in struct*/
void AutoTellerMachine::AccountLogin(string loginUsername, string loginPassword)
{
    bool noAccount = true;
    //Check if user exist and log in
    for (int i = 0; i < ATM.ATM_list.size(); i++)
    {
        if ( (ATM.ATM_list[i].username == loginUsername) && 
             (ATM.ATM_list[i].password == loginPassword) )
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
        cout << "Thank you, your account has been created!\n\n";
        AutoTellerMachine newUser;
        newUser.username = newUsername;
        newUser.password = newPassword;
        newUser.beginningBalance = 0;
        newUser.accountBalance = 0;
        ATM.ATM_list.push_back(newUser);
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
    ATM.ATM_list[ATM.loggedInAccountLocation].accountBalance += depositAmount;
}

void AutoTellerMachine::WithdrawMoney(double withdrawalAmount)
{
    ATM.ATM_list[ATM.loggedInAccountLocation].accountBalance -= withdrawalAmount;
}

/*Set funktions*/
void AutoTellerMachine::SetAccountLogin(int setAccountLocation)
{
    ATM.loggedInAccountLocation = setAccountLocation;
}

void AutoTellerMachine::SetLastMoneyMovement(int accountID, double amount)
{
    ATM.ATM_list[accountID].lastMoneyMovement = amount;
}

void AutoTellerMachine::SetLastOperation(int accountID, char userInput)
{
    ATM.ATM_list[accountID].lastOperation = userInput;
}

void AutoTellerMachine::SetBeginningBalance(int accountID)
{
    ATM.ATM_list[accountID].beginningBalance = ATM.ATM_list[accountID].accountBalance;
}

/*GET*/
double AutoTellerMachine::GetBeginningBalance(int accountID) const
{
    return ATM.ATM_list[accountID].beginningBalance;
}

int AutoTellerMachine::GetAccountLogin() const
{
    return loggedInAccountLocation;
}

double AutoTellerMachine::GetLastMoneyMovement(int accountID) const
{
    return ATM.ATM_list[accountID].lastMoneyMovement;
}

double AutoTellerMachine::GetAccountBalance(int accountID) const
{
    return ATM.ATM_list[accountID].accountBalance;
}

char AutoTellerMachine::GetLastOperation(int accountID) const
{
    return ATM.ATM_list[accountID].lastOperation;
}

string AutoTellerMachine::GetUsername(int accountID) const
{
    return ATM.ATM_list[accountID].username;
}


/*FUNKTIONS END*/