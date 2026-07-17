#pragma once
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iostream>
#include <iomanip>


class clsUpdateClientScreen:protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter First name : ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter Last name : ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Pin Code : ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter Phone : ";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\nEnter Account balance: ";
        Client.AccBalance = clsInputValidate::ReadDblNumber();
    }
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
    static void UpdateClientScreeen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
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
        _Print(Client);
        

        cout << "\nUpdate Client Info: ";
        cout << "\n________________\n";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResult SaveResult;
        SaveResult = Client.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svFialedEmptyObject:
            cout << "\nError Account was not saved because its empty."; \
                break;
        case clsBankClient::enSaveResult::svSucceeded:
            cout << "\nAccount updated Successfully.";
            _Print(Client);
            break;
        }
    }

};
 
