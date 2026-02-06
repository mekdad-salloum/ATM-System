#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void ShowMainMenuScreen();

enum enMainMenuOptions { enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5 };

const string ClientsFileName = "Clients.txt";

struct strClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string PhoneNumber = "";
	double Balance = 0;
};

strClient CurrentClient;

string Tabs(short NumberOfTabs)
{
	string T = "";

	for (short i = 1; i <= NumberOfTabs; i++)
	{
		T += "\t";
	}

	return T;
}

vector <string> SplitString(string S, string Seperator = "//")
{
	vector <string> vString;
	string Word = "";
	short Pos = 0;

	while ((Pos = S.find(Seperator)) != string::npos)
	{
		Word = S.substr(0, Pos);

		if (Word != "")
			vString.push_back(Word);

		S.erase(0, Pos + Seperator.length());
	}

	if (S != "")
		vString.push_back(S);

	return vString;
}

strClient ConvertLineToRecordClient(string Line, string Seperator = "//")
{
	strClient Client;
	vector <string> vClient = SplitString(Line, Seperator);

	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.PhoneNumber = vClient[3];
	Client.Balance = stod(vClient[4]);

	return Client;
}

string ConvertRecordToLineClient(strClient Client, string Seperator = "//")
{
	string sClient = "";

	sClient += Client.AccountNumber + Seperator;
	sClient += Client.PinCode + Seperator;
	sClient += Client.Name + Seperator;
	sClient += Client.PhoneNumber + Seperator;
	sClient += to_string(Client.Balance);

	return sClient;
}

vector <strClient> LoadClientsFromFile(string FileName)
{
	vector <strClient> Clients;

	fstream File;
	File.open(FileName, ios::in);

	if (File.is_open())
	{
		string Line = "";
		strClient Client;

		while (getline(File, Line))
		{
			Client = ConvertLineToRecordClient(Line);
			Clients.push_back(Client);
		}

		File.close();
	}

	return Clients;
}

bool SaveClientsToFile(vector <strClient> Clients, string FileName)
{
	bool IsSuccess = false;

	fstream File;
	File.open(FileName, ios::out);

	if (File.is_open())
	{
		string Line = "";

		for (strClient& C : Clients)
		{
			Line = ConvertRecordToLineClient(C);
			File << Line << endl;
		}

		File.close();
		IsSuccess = true;
	}

	return IsSuccess;
}

strClient FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode)
{
	strClient Client;
	vector <strClient> Clients = LoadClientsFromFile(ClientsFileName);

	for (strClient& C : Clients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			break;
		}
	}

	return Client;
}

enMainMenuOptions ReadMainMenuOption()
{
	short Option = 0;
	cin >> Option;

	cout << "\n";
	while (cin.fail() || Option < 1 || Option > 5)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << Tabs(4) << "Invalid Input, Enter A Number Between 1 And 5: ";
		cin >> Option;
	}

	return (enMainMenuOptions)Option;
}

void GoBackToMainMenuScreen()
{
	cout << "\nPress Any Key To Go Back To Main Menu Screen...";
	system("Pause>0");
	ShowMainMenuScreen();
}

short ReadQuickWithdrawOption()
{
	short Option = 0;
	cin >> Option;

	cout << "\n";
	while (cin.fail() || Option < 1 || Option > 9)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << Tabs(4) << "Invalid Input, Enter A Number Between 1 And 9: ";
		cin >> Option;
	}

	return Option;
}

short ReadWithdrawAmount()
{
	short Amount;

	cout << "\n";
	cout << Tabs(4) << "Enter An Amount Multiple Of 5's: ";
	cin >> Amount;

	cout << "\n";
	while (cin.fail() || Amount % 5 != 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << Tabs(4) << "Invalid Input, Enter An Amount Multiple Of 5's: ";
		cin >> Amount;
	}

	return Amount;
}

short ReadDepositAmount()
{
	short Amount;

	cout << "\n";
	cout << Tabs(4) << "Enter A Positve Deposit Amount: ";
	cin >> Amount;

	cout << "\n";
	while (cin.fail() || Amount < 1)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << Tabs(4) << "Invalid Input, Enter A Positve Deposit Amount: ";
		cin >> Amount;
	}

	return Amount;
}

bool Deposit(double Amount)
{
	char Answer = 'N';

	cout << "\n";
	cout << Tabs(4) << "Are You Sure You Want To Perform This Transaction? (Y/N)? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		vector <strClient> Clients = LoadClientsFromFile(ClientsFileName);

		for (strClient& C : Clients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.Balance += Amount;
				CurrentClient.Balance = C.Balance;
				break;
			}
		}

		if (SaveClientsToFile(Clients, ClientsFileName))
		{
			cout << "\n";
			cout << Tabs(4) << "Done Successfully, New Balance Is : " << CurrentClient.Balance << endl;
			return true;
		}
	}

	return false;
}

bool Withdraw(double Amount)
{
	if (CurrentClient.Balance < Amount)
	{
		cout << "\n";
		cout << Tabs(4) << "The Amount Exceeds Your Balance, Make Another Choice.\n";
		cout << Tabs(4) << "Press Any Key To Continue...\n";
		system("pause>0");
		return false;
	}
	return Deposit(Amount * -1);
}

void PerformQuickWithdrawOption(short Option)
{
	switch (Option)
	{
	case 1:
	{
		Withdraw(20);
		break;
	}

	case 2:
	{
		Withdraw(50);
		break;
	}

	case 3:
	{
		Withdraw(100);
		break;
	}

	case 4:
	{
		Withdraw(200);
		break;
	}

	case 5:
	{
		Withdraw(400);
		break;
	}

	case 6:
	{
		Withdraw(600);
		break;
	}

	case 7:
	{
		Withdraw(800);
		break;
	}

	case 8:
	{
		Withdraw(1000);
		break;
	}

	default:
		break;
	}
}

void ShowQuickWithdrawScreen()
{
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Quick Withdraw Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "1) 20\t  2) 50\n";
	cout << Tabs(6) << "3) 100\t  4) 200\n";
	cout << Tabs(6) << "5) 400\t  6) 600\n";
	cout << Tabs(6) << "7) 800\t  8) 1000\n";
	cout << Tabs(6) << "9) Exit.\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(4) << "Your Balance Is: " << CurrentClient.Balance << "\n\n";
	cout << Tabs(4) << "Choose What To Withdraw From (1) To (8): ";

	PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Normal Withdraw Screen\n";
	cout << Tabs(4) << "=======================================================\n";

	if (!Withdraw(ReadWithdrawAmount()))
	{
		ShowNormalWithdrawScreen();
	}
}

void ShowDepositScreen()
{
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Deposit Screen\n";
	cout << Tabs(4) << "=======================================================\n";

	Deposit(ReadDepositAmount());
}

void ShowCheckBalanceScreen()
{
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Check Balance Screen\n";
	cout << Tabs(4) << "=======================================================\n\n";
	cout << Tabs(4) << "Your Balance Is: " << CurrentClient.Balance << endl;
}

bool CheckAccountNumberAndPinCode(string AccountNumber, string PinCode)
{
	strClient Client = FindClientByAccountNumberAndPinCode(AccountNumber, PinCode);

	if (Client.AccountNumber != "")
	{
		CurrentClient = Client;
		return true;
	}

	return false;
}

void Login()
{
	bool IsValid = true;
	string AccountNumber = "", PinCode = "";

	do
	{
		system("cls");
		cout << Tabs(4) << "=======================================================\n";
		cout << Tabs(6) << "Login Screen\n";
		cout << Tabs(4) << "=======================================================\n";

		if (!IsValid)
		{
			cout << Tabs(4) << "Invalid Account Number/ PinCode!\n";
		}

		cout << Tabs(4) << "Enter Account Number: ";
		cin >> AccountNumber;

		cout << Tabs(4) << "Enter PinCode: ";
		cin >> PinCode;

		IsValid = CheckAccountNumberAndPinCode(AccountNumber, PinCode);

	} while (!IsValid);

	ShowMainMenuScreen();
}

void PerformMainMenuOption(enMainMenuOptions Option)
{
	switch (Option)
	{
	case enMainMenuOptions::enQuickWithdraw:
	{
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enNormalWithdraw:
	{
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enCheckBalance:
	{
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enLogout:
	{
		system("cls");
		Login();
	}
	}
}

void ShowMainMenuScreen()
{
	system("cls");
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "ATM Main Menu Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "1) Quick Withdra.\n";
	cout << Tabs(6) << "2) Normal Withdra.\n";
	cout << Tabs(6) << "3) Deposit.\n";
	cout << Tabs(6) << "4) Check Balance.\n";
	cout << Tabs(6) << "5) Logout.\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(4) << "Choose What Do You Want To Do? (1 To 5)? ";

	PerformMainMenuOption(ReadMainMenuOption());
}

int main()
{
	Login();

	system("pause>0");
	return 0;
}