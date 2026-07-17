#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"
#include <vector>
#include <fstream>
class clsBankClient:public clsPerson
{
private:
	enum enMode{EmptyMode = 0,UpdateMode =1,AddNewMode =3};

	enMode _Mode;
	string _AccNumber;
	string _PinCode;
	double _Balance;
	bool _MarkForDelete = false;
	struct stTransferLog;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separetor = "#//#")
	{
		vector<string> vClientsData;

		vClientsData = clsString::Split(Line, Separetor);

		return clsBankClient(enMode::UpdateMode, vClientsData[0], vClientsData[1], vClientsData[2], vClientsData[3]
			, vClientsData[4], vClientsData[5], stoi(vClientsData[6]));

	}

	static  string _ConvertObjectClientToLine(clsBankClient Client,string Separator ="#//#")
	{
		
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Separator;
		stClientRecord += Client.LastName + Separator;
		stClientRecord += Client.Email + Separator;
		stClientRecord += Client.Phone + Separator;
		stClientRecord += Client.getAccNumber() + Separator;
		stClientRecord += Client.PinCode + Separator;
		stClientRecord += to_string(Client.AccBalance);

		return stClientRecord;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	
	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}
		}MyFile.close();

		return vClients;
	}

	static void _SaveClinetsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C._MarkForDelete == false)
				{

				DataLine = _ConvertObjectClientToLine(C);
				MyFile << DataLine << endl;
				}
			}
		}MyFile.close();
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccNumber() == getAccNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClinetsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	void _AddNew()
	{
		_AddDataLineToFile(_ConvertObjectClientToLine(*this));
	}

	string _PrepareTransferFile(double Amount, clsBankClient RecieverBalance, string AccNumber, string Separator = "#//#")
	{
		string DataLine = "";
		DataLine += clsDate::GetSystemDateTime() + Separator;
		DataLine += getAccNumber() + Separator;
		DataLine += RecieverBalance.getAccNumber() + Separator;
		DataLine += to_string(Amount) + Separator;
		DataLine += to_string(AccBalance) + Separator;
		DataLine += to_string(RecieverBalance.AccBalance) + Separator;
		DataLine += AccNumber;

		return DataLine;
	}

	void _RegisterTransfer(double Amount, clsBankClient RecieverBalance, string AccNumber)
	{
		fstream File;
		string Data = _PrepareTransferFile(Amount, RecieverBalance, AccNumber);
		File.open("TransferLog.txt", ios::out | ios::app);

		if (File.is_open())
		{

			File << Data << endl;
			File.close();


		}
	}

	static stTransferLog _ConvertTransferLogLine(string Line, string Seperator = "#//#")
	{
		stTransferLog TransferLog;
			vector <string> vTransfer = clsString::Split(Line, Seperator);

			TransferLog.DateTime = vTransfer[0];
			TransferLog.SenderAccNumber = vTransfer[1];
			TransferLog.DistinationAccNumber = vTransfer[2];
			TransferLog.Amount = stod(vTransfer[3]);
			TransferLog.SenderBalance = stod(vTransfer[4]);
			TransferLog.DistinationBalance = stod(vTransfer[5]);
			TransferLog.UserName = vTransfer[6];

			return TransferLog;
	}
public:
	struct stTransferLog
	{
		string DateTime;
		string SenderAccNumber;
		string DistinationAccNumber;
		double Amount;
		double SenderBalance;
		double DistinationBalance;
		string UserName;

	};

	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float Balance):clsPerson(FirstName,LastName,Email,Phone)
	{
		_Mode = Mode;
		_AccNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}


	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//Properties

	string getAccNumber()
	{
		return _AccNumber;
	}

	void setPinCode(string pin)
	{
		_PinCode = pin;
	}

	string getPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode))string PinCode;

	void setBalance(double Balance)
	{
		_Balance = Balance;
	}

	double getBalance()
	{
		return _Balance;
	}

	__declspec(property(get = getBalance, put = setBalance))double AccBalance;

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc Number  : " << _AccNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _Balance;
		cout << "\n___________________\n";

	}

	static clsBankClient Find(string AccNumber)
	{
		vector < clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode

		string Line;
		if (MyFile.is_open())
		{

		while (getline(MyFile, Line))
		{
			clsBankClient Client = _ConvertLineToClientObject(Line);
			if (Client.getAccNumber() == AccNumber)
			{
				MyFile.close();
				return Client;
			}
			vClients.push_back(Client);
				
		}
		MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccNumber,string PinCode)
	{
		vector < clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode

		string Line;
		if (MyFile.is_open())
		{

		while (getline(MyFile, Line))
		{
			clsBankClient Client = _ConvertLineToClientObject(Line);
			if (Client.getAccNumber() == AccNumber && Client.PinCode == PinCode)
			{
				MyFile.close();
				return Client;
			}
			vClients.push_back(Client);
				
		}
		MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccNumber);
		return (!Client.isEmpty());
	}

	static  clsBankClient GetAddNewClietObject(string AccNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccNumber , "", 0);
	}

	enum enSaveResult { svFialedEmptyObject = 0, svSucceeded = 1, svFialedAccountNumberExist =3 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		return enSaveResult::svFialedEmptyObject;
		break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccNumber))
				return enSaveResult::svFialedAccountNumberExist;
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}

		default:
			return enSaveResult::svFialedEmptyObject;

		}
	}

	bool Delete()
	{
		if (_Mode == enMode::EmptyMode || _Mode == enMode::AddNewMode)
			return false;

		vector<clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccNumber() == _AccNumber)
			{
				C._MarkForDelete = true;
				break;
			}

		}
		_SaveClinetsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances( vector <clsBankClient> Clients)
	{
		double TotalBalaces = 0;
		for (clsBankClient& C : Clients)
		{
			TotalBalaces += C.AccBalance;
		}
		return TotalBalaces;
	}

	 void Deposit(double Amount)
	{
		_Balance += Amount;
		Save();
	}

	 bool Withdaraw(double Amount)
	{
		 if (Amount > _Balance)
			 return false;
		 else {

			_Balance -= Amount;
			Save();
		 }
		
	}

	 bool Transfer(double Amount,clsBankClient &Recever)
	 {
		 if (Amount > _Balance)
		 {
			 return false;
		 }
		 else {
			 Withdaraw(Amount);
			 Recever.Deposit(Amount) ;
			 _RegisterTransfer(Amount, Recever, CurrentUser.UserName);
			 return true;
		 }
	 }

	
	 static vector<stTransferLog> GetTransferLogList()
	 {
		 vector<stTransferLog> vTransfer;
		 stTransferLog Transfer;

		 fstream File;
		 File.open("TransferLog.txt", ios::in);
		 string DataLine = "";
		 if (File.is_open())
		 {
			 while (getline(File, DataLine))
			 {
				 Transfer = _ConvertTransferLogLine(DataLine);

				 vTransfer.push_back(Transfer);
			 }
			 File.close();
		 }
		 return vTransfer;
	 }
};

