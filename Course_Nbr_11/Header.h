#pragma once

#include <iostream>
#include "clsInputValidate.h";
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include <iomanip>
using namespace std;


void ReadClientInfo(clsBankClient& Client)
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

void UpdateClient()
{
    string AccountNumber = "";
    cout << "\nEnter account client number : ";
    AccountNumber = clsInputValidate::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number not found , try Again. ";
        AccountNumber = clsInputValidate::ReadString();

    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    cout << "\nUpdate Client Info: ";
    cout << "\n________________\n";
    ReadClientInfo(Client);

    clsBankClient::enSaveResult SaveResult;
    SaveResult = Client.Save();
    switch (SaveResult)
    {
    case clsBankClient::enSaveResult::svFialedEmptyObject:
        cout << "\nError Account was not saved because its empty."; \
            break;
    case clsBankClient::enSaveResult::svSucceeded:
        cout << "\nAccount updated Successfully.";
        Client.Print();
        break;
    }
}

void AddNewClient()
{
    string AccNumber = "";
    cout << "\nPlease Enter Account number : ";
    AccNumber = clsInputValidate::ReadString();
    while (clsBankClient::IsClientExist(AccNumber))
    {
        cout << "\nAccount number is already exist, choose another one";
        AccNumber = clsInputValidate::ReadString();

    }

    clsBankClient Client = clsBankClient::GetAddNewClietObject(AccNumber);
    ReadClientInfo(Client);

    clsBankClient::enSaveResult SaveResult = Client.Save();
    switch (SaveResult)
    {
    case clsBankClient::enSaveResult::svFialedEmptyObject:
        cout << "\nError Account was not saved because its empty."; \
            break;
    case clsBankClient::enSaveResult::svSucceeded:
        cout << "\nAccount updated Successfully.";
        Client.Print();
        break;
    case clsBankClient::enSaveResult::svFialedAccountNumberExist:
        cout << "\nAccount Number is already exist .";

        break;
    }

}

void DeleteClient()
{
    string AccountNumber = "";
    cout << "\nEnter account client number : ";
    AccountNumber = clsInputValidate::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number not found , try Again. ";
        AccountNumber = clsInputValidate::ReadString();

    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();
    cout << "\nAre you sure you want to delete this Client Y/n : ";
    char Answer = 'n';
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        if (Client.Delete())
        {
            cout << "\nClient Deleted successfully (-:";
            Client.Print();
        }
        else
        {
            cout << "\nError ,Client Not Deleted  )-:";

        }
    }
}

void PrintClientRecordLine(clsBankClient Client)
{
    cout << "| " << setw(15) << left << Client.getAccNumber();
    cout << "| " << setw(20) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(20) << left << Client.Email;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(12) << left << Client.AccBalance;
}

void ShowClientsList()
{

    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(20) << "Email";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (clsBankClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void PrintClientRecordBalanceLine(clsBankClient Client)
{

    cout << "| " << setw(15) << left << Client.getAccNumber();
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.AccBalance;

}

void ShowTotalBalances()
{

    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = clsBankClient::GetTotalBalances(vClients);

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (clsBankClient Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
    cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(int(TotalBalances)) << ")";
}



int main()
{
    //UpdateClient();
    //AddNewClient();
    //DeleteClient();
    ShowTotalBalances();
    // ShowClientsList();
    system("pause>0");
    return 0;

}

