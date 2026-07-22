#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iostream>
#include <iomanip>

using namespace std;

class clsCurreencyMenu:protected clsScreen
{
private:
	enum enCurrencyMenu{eListCurrency=1,eFindCurrency = 2,eUpdateRate=3
		,eCurrencyCalculator =4,eExit =5};

	static short _ReadCurrencyMenuOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "\nInvalid Number try again : ");
		return Choice;
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrenciesScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrenciesCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorSceen();
	}
	static void _GoBackToCurrencyMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowCurrencyMenue();

	}
	
	static void _PerformCurrencyMenueOption(enCurrencyMenu CmenuOption)
	{

		switch (CmenuOption)
		{
		case enCurrencyMenu::eListCurrency:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyMenue();
			break;
		case enCurrencyMenu::eFindCurrency:
			system("cls");
			_ShowFindCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;
		case enCurrencyMenu::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyMenue();
			break;
		case enCurrencyMenu::eCurrencyCalculator:
			system("cls");
			_ShowCurrenciesCalculatorScreen();
			_GoBackToCurrencyMenue();
			break;
		case enCurrencyMenu::eExit:
		{

		//do nothing here the main screen will handle it :-) ;
		}

		}
	}
		
public:
	static void ShowCurrencyMenue()
	{
		system("cls");

		_DrawScreenHeader("   Currency Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Currency List.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Culculator .\n";
		
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrencyMenueOption(enCurrencyMenu(_ReadCurrencyMenuOptions()));
	}

};

