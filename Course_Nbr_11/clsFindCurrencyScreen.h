#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen:protected clsScreen
{
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }
    static short _ReadFindCurrencyOption()
    {
        cout << "Find By Country [1] By Currency Code [2]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 2, "\n\t\t\t\t     Please Enter 1 or 2");
        return Choice;
    }

    static void _CountryCurrencyFound(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCountry Found !";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCountry is not Found !";
        }
    }
public:

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t Find Currency Screen");

        short Ansewer = _ReadFindCurrencyOption();
        string CountryOrCurrency;

        if (Ansewer == 1)
        {
            cout << "\nEnter Country : ";
            CountryOrCurrency = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(CountryOrCurrency);

            _CountryCurrencyFound(Currency);
        }
        else {
            cout << "\nEnter Currency Code : ";
            CountryOrCurrency = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCurrencyCode(CountryOrCurrency);
             _CountryCurrencyFound(Currency);

             

        }

    }
};

