#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include <fstream>
#include "clsUser.h"
class clsTransferLogScreen:protected clsScreen
{
private:
    static void _PrintTransferRegisterRecordLine(clsBankClient::stTransferLog TransferRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferRegisterRecord.DateTime;
        cout << "| " << setw(8) << left << TransferRegisterRecord.SenderAccNumber;
        cout << "| " << setw(8) << left << TransferRegisterRecord.DistinationAccNumber;
        cout << "| " << setw(8) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TransferRegisterRecord.SenderBalance;
        cout << "| " << setw(10) << left << TransferRegisterRecord.DistinationBalance;
        cout << "| " << setw(8) << left << TransferRegisterRecord.UserName;
    }

public:
    static void ShowTransferLogScreen()
    {
        //if (!CheckAccessRights(clsUser::enPermissions::pShowLoginRegester)) {

        //    return;
        //}

        vector <clsBankClient::stTransferLog> vTransferRegisterRecord = clsBankClient::GetTransferLogList();

        string Title = "  Transfer Register List Screen\n";
        string SubTitle = "\t   (" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8)  << "S.Acc";
        cout << "| " << left << setw(8)  << "D.Acc";
        cout << "| " << left << setw(8)  << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(8)  << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferRegisterRecord)
            {

                _PrintTransferRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

