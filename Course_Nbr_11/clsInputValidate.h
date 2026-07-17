#pragma once
#include <iostream>
#include "clsDate.h"
class clsInputValidate
{

public:
	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
			
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
			
	}

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
			
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
			
	}

	static bool IsDateBetween(clsDate Date, clsDate Date1, clsDate Date2)
	{
		if (!(clsDate::IsDate1BeforeDate2(Date1, Date2)))
		{
			clsDate::SwapDates(Date1, Date2);
		}	
		return ((Date.IsDateBeforeDate2(Date2) || Date.IsDateEqualDate2(Date2)) 
			&& (Date.IsDateAfterDate2(Date1)   || Date.IsDateEqualDate2(Date1)));
	}

	static int ReadIntNumber(string Message = "Invalid input! Please enter a valid integer: \n")
	{
		int Number ;
		
		while (!(cin >> Number))
		{
			cin.clear();

			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << Message;
		}

		return Number;
	}

	static double ReadDblNumber(string Message = "Invalid input! Please enter a valid integer: \n")
	{
		double Number ;
		
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << Message;
		}

		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string Message)
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << Message<<endl;
			Number = ReadIntNumber();
		}

		return Number;

	}

	static double ReadDblNumberBetween(double From, double To, string Message)
	{
		double Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << Message<<endl;
			Number = ReadIntNumber();
		}

		return Number;

	}

	static double IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	} 
};



