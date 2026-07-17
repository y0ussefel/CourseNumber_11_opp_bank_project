#pragma once
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"


#include<iostream>
#include <iomanip>
class clsAddNewClientScreen:protected clsScreen
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
    static void AddNewClient()
    {
        
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {

            return;
        }

        _DrawScreenHeader("Add New Client Screen\n");
        string AccNumber = "";
        cout << "\nPlease Enter Account number : ";
        AccNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccNumber))
        {
            cout << "\nAccount number is already exist, choose another one";
            AccNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::GetAddNewClietObject(AccNumber);
        _ReadClientInfo(Client);

        clsBankClient::enSaveResult SaveResult = Client.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svFialedEmptyObject:
            cout << "\nError Account was not saved because its empty."; \
                break;
        case clsBankClient::enSaveResult::svSucceeded:
            cout << "\nAccount Added Successfully.";
            _Print(Client);
            break;
        case clsBankClient::enSaveResult::svFialedAccountNumberExist:
            cout << "\nAccount Number is already exist .";

            break;
        }

    }
};

