#include <iostream>

using namespace std;

struct AutoTellerMachine
// to represent each customer who uses the ATM program
{
    int     loggedInAccountLocation;
    int     accountNumber;
    double  accountBalance;
    double  beginningBalance;
    double  lastMoneyMovement;
    char    lastOperation;
    string  username;
    string  password;
    
    //menu when you're in your account
    void    AccountMenu();
    //user log in
    void    AccountLogin(int loginUserAccountNumber, string loginUsername, string loginPassword);
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
    
    void    SetAccountNumber(int accountNum);

    int     GetAccountLogin() const;
    double  GetLastMoneyMovement(int accountID) const;
    double  GetAccountBalance(int accountID) const;
    double  GetBeginningBalance(int accountID) const;
    char    GetLastOperation(int accountID) const;
    string  GetUsername(int accountID) const;
    
    
}ATM;