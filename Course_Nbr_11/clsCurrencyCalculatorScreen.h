#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen:protected clsScreen
{
private:

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";
    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode = "";
        cout << Message;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);

        return Currency;
        
    }

    static void _PrintCalculationsResults(clsCurrency Currency1, clsCurrency Currency2, float Amount)
    {
        _PrintCurrencyCard(Currency1, "Convert From :");

        float ConvertToUSD = Currency1.ConvertToUSD(Amount);
        cout << to_string(Amount) + " " + Currency1.CurrencyCode() + " = " + to_string(ConvertToUSD) + " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "Converting From USD to : \n";

        _PrintCurrencyCard(Currency2, "To :");
        cout << to_string(Amount) + " " + Currency1.CurrencyCode() + " = " + to_string(Currency1.ConvertToOtherCurrency(Amount,Currency2)) + " " + Currency2.CurrencyCode();

    }


public:
    static void ShowCurrencyCalculatorSceen()
    {
        _DrawScreenHeader("\t Calculate Currency Screen");
            char Answer = 'n';
          
        do {
            clsCurrency CurrencyCode1 = _GetCurrency("\nEnter Currency 1 Code : ");

            clsCurrency CurrencyCode2 = _GetCurrency("\nEnter Currency 2 Code : ");
            
            float Amount = _ReadAmount();

            _PrintCalculationsResults(CurrencyCode1, CurrencyCode2, Amount);
            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Answer;
        } while (tolower(Answer == 'y'));
    }


};

