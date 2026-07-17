#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTrasferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTotalBalancesScreen.h"
#include <iomanip>


class clsTransactionsScreen:protected clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4,eTransferLog = 5,eShowMainMenue = 6
    };

    static short _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1,6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void  _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void  _ShowTransferScreen()
    {
        clsTrasferScreen::ShowTransferScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalanceScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }
   

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        
        
            switch (TransactionsMenueOption)
            {
            case enTransactionsMenueOptions::eDeposit:
            {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eWithdraw:
            {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eShowTotalBalance:
            {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenue();
                break;
            }
            case enTransactionsMenueOptions::eTransfer:
            {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenue();
                break;
            }
            case enTransactionsMenueOptions::eTransferLog:
            {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenue();
                break;
            }


            case enTransactionsMenueOptions::eShowMainMenue:
            {
                //do nothing here the main screen will handle it :-) ;
            }
          }     
        
    }
public:
    static void ShowTransactionsMenue()
    {
        
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
            return;

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption(enTransactionsMenueOptions(_ReadTransactionsMenueOption()));
    }
};

