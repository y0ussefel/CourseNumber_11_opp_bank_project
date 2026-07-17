#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsWithdrawScreen:protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc Number  : " << Client.getAccNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccNumber = "";
        cout << "\nPlease enter account number : ";
        cin >> AccNumber;
        return AccNumber;
    }

public:
    static void ShowWithdrawScreen()
    {

        _DrawScreenHeader("\t  Withdraw Screen");
        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease enter an amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (Client.Withdaraw(Amount))
            {
            cout << "\nSuccessfully done.";
            cout << "\nNew Balance Is: " << Client.AccBalance;
            }
            else {
                cout << "\nCannot withdraw, Insufficient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccBalance;
            }

        }
        else {
            cout << "\nOperation was cancelled.\n";
        }


    }
};

