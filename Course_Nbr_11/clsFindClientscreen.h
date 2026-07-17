#pragma once
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iostream>
#include <iomanip>
#include"clsUser.h"

class clsFindClientscreen:protected clsScreen
{
private:
    
    static void _Print(clsBankClient C)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << C.FirstName;
        cout << "\nLastName    : " << C.LastName;
        cout << "\nFull Name   : " << C.FullName();
        cout << "\nEmail       : " << C.Email;
        cout << "\nPhone       : " << C.Phone;
        cout << "\nAcc Number  : " << C.getAccNumber();
        cout << "\nPassword    : " << C.PinCode;
        cout << "\nBalance     : " << C.AccBalance;
        cout << "\n___________________\n";

    }

public:
    static void FindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
            return;

        string AccountNumber = "";
        cout << "\nEnter account client number : ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number not found , try Again. ";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (!Client.isEmpty())
            cout << "\nClient Found :-)\n";
        else
            cout << "\nClient Not Found :-(\n";

        _Print(Client);
    }
};

