#pragma once
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iostream>
#include <iomanip>


class clsDeleteClientScreen:protected clsScreen


{
 private:
     static void  _Print(clsBankClient C)
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
	static void ShowDeleteClientScreen()
    {
      
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;

        _DrawScreenHeader("\tDelete Client Screen");
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

        cout << "\nAre you sure you want to delete this Client Y/n : ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted successfully (-:";
                _Print(Client);
            }
            else
            {
                cout << "\nError ,Client Not Deleted  )-:";

            }
        }
    }
};

