#pragma once

#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLinetoCurrencyObject(string Line,string Separator ="#//#")
	{
		vector<string> vData = clsString::Split(Line, Separator);

		return clsCurrency (enMode::UpdateMode,vData[0],vData[1],vData[2],stod(vData[3]));

		 
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;

	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		 vector <clsCurrency> _vCurrencies;
		 fstream File;	

		 File.open("Currencies.txt", ios::in);
		 if (File.is_open())
		 {
			 string Line = "";
			 while (getline(File, Line))
			 {
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

				
				_vCurrencies.push_back(Currency);

			 }
			 File.close();

		 }
		 return _vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream File;

		File.open("Currencies.txt", ios::out);
		if (File.is_open())
		{
			for (clsCurrency& C : vCurrencies)
			{
				string DataLine = _ConverCurrencyObjectToLine(C);

				File << DataLine << endl;

			}File.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencies);

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode,string Country,string CurrencyCode,
		string CurrencyName,float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate=Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCurrencyCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string Line = "";
			while (getline(File, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
				{
					File.close();
					return Currency;
				}
				
				

			}
			File.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string Line = "";
			while (getline(File, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country() )== Country)
				{
					File.close();
					return Currency;
				}
				
				

			}
			File.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C = clsCurrency::FindByCurrencyCode( CurrencyCode);

		return (!C.IsEmpty());
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amout, clsCurrency Currency2)
	{
		float AmountUSD = ConvertToUSD(Amout);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountUSD;
		}

		return (float)(Currency2.Rate() * AmountUSD);
	}
};

