#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include <iomanip>
class clsTrasferScreen:protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)

    {
       
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc Number  : " << Client.getAccNumber();
        cout << "\nBalance     : " << Client.AccBalance;
        cout << "\n___________________\n";

    }
    

    static string _ReadAccoutNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        if (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";

            AccountNumber = clsInputValidate::ReadString();

        }
        return AccountNumber;
    }
    static double _ReadAmount()
    {

    }
public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Screen");
        
        clsBankClient SenderClient = clsBankClient::Find(_ReadAccoutNumber());
        _PrintClient(SenderClient);

        
        clsBankClient RecieverClient = clsBankClient::Find(_ReadAccoutNumber());
        _PrintClient(RecieverClient);


        double Amount ;

        cout << "\nEnter transfer Amount : ";
        
        Amount = clsInputValidate::ReadDblNumberBetween(0, SenderClient.AccBalance, "\nAmount Excused enter a valid amount : ");

        char Ansewer = 'n';

        cout << "\nAre you sure you want to perform this transaction? ";
        
        cin >> Ansewer;
        if (tolower(Ansewer) == 'y')
        {
            if (SenderClient.Transfer(Amount, RecieverClient))
            {
                cout << "\nTransfer done successfully\n";               
            }
            else {
                cout << "\nTransfer Failed \n";
            }
        }
        
        _PrintClient(SenderClient);
        _PrintClient(RecieverClient);

        

    }
};

