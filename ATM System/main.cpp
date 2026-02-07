#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void ShowMainMenuScreen();

enum enMainMenuOptions { enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enChangePinCode = 5, enShowClientDetails = 6, enShowClientHistory = 7, enLogout = 8 };

enum enActions {aWithdraw = 1, aDeposit = 2, aChangePinCode = 3, aLogin = 4, aLogout = 5};

enum  enColor {
	Black = 0,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White,

	BrightBlack,
	BrightRed,
	BrightGreen,
	BrightYellow,
	BrightBlue,
	BrightMagenta,
	BrightCyan,
	BrightWhite
};

struct strClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string PhoneNumber = "";
	double Balance = 0;
};

strClient CurrentClient;

const string ClientsFileName = "Clients.txt";
string ClientHistoryFileName = "";

int ToAnsi(enColor color, bool isBackground = false)
{
	int c = static_cast<int>(color);

	if (c < 8) {
		return (isBackground ? 40 : 30) + c;
	}
	else {
		return (isBackground ? 100 : 90) + (c - 8);
	}
}

string ColorCode(enColor text, bool IsBold = false)
{
	return "\x1B[" +
		string(IsBold ? "1;" : "") +
		to_string(ToAnsi(text)) +
		"m";
}

string Reset()
{
	return "\x1B[0m";
}

string Tabs(short NumberOfTabs)
{
	string T = "";

	for (short i = 1; i <= NumberOfTabs; i++)
	{
		T += "\t";
	}

	return T;
}

string GetDateAndTimeNow()
{
	time_t Now = time(0);
	tm LocalTime;

	localtime_s(&LocalTime, &Now); 

	int Day = LocalTime.tm_mday;
	int Month = LocalTime.tm_mon + 1;
	int Year = LocalTime.tm_year + 1900;

	int Hour = LocalTime.tm_hour;
	int Min = LocalTime.tm_min;

	string Period = "am";

	if (Hour >= 12)
	{
		Period = "pm";
		if (Hour > 12)
			Hour -= 12;
	}

	if (Hour == 0)
		Hour = 12;

	string DateTimeString =
		"[" + to_string(Day) + "/" +
		to_string(Month) + "/" +
		to_string(Year) + " - " +
		to_string(Hour) + ":" +
		(Min < 10 ? "0" : "") + to_string(Min) + " " +
		Period + "]";

	return DateTimeString;
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

string GetActionString(enActions Action)
{
	switch (Action)
	{
	case aWithdraw:
	{
		return "Withdraw";
		break;
	}

	case aDeposit:
	{
		return "Deposit";
		break;
	}

	case aChangePinCode:
	{
		return "Change PinCode";
		break;
	}

	case aLogin:
	{
		return "Login";
		break;
	}

	case aLogout:
	{
		return "Logout";
		break;
	}
	}

}

string ConvertActionToLine(enActions Action)
{
	return GetDateAndTimeNow() + " | " + GetActionString(Action);
}

bool LogAction(enActions Action)
{
	fstream File;
	File.open(ClientHistoryFileName, ios::out | ios::app);

	if (File.is_open())
	{
		string Line = ConvertActionToLine(Action);
		File << Line << endl;

		File.close();
		return true;
	}

	return false;
}

enMainMenuOptions ReadMainMenuOption()
{
	short Option = 0;
	cin >> Option;

	cout << "\n";
	while (cin.fail() || Option < 1 || Option > 8)
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
			cout << ColorCode(enColor::BrightGreen) << Tabs(4) << "Done Successfully, New Balance Is : " << CurrentClient.Balance << endl;
			cout << ColorCode(enColor::BrightWhite);
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
		cout << ColorCode(enColor::BrightRed) << Tabs(4) << "The Amount Exceeds Your Balance, Make Another Choice.\n";
		cout << ColorCode(enColor::BrightWhite);
		cout << Tabs(4) << "Press Any Key To Continue...\n";
		system("pause>0");
		return false;
	}
	return Deposit(Amount * -1);
}

short GetQuickWithdrawAmount(short QuickWithdrawOption)
{
	switch (QuickWithdrawOption)
	{
	case 1:
	{
		return 20;
		break;
	}

	case 2:
	{
		return 50;
		break;
	}

	case 3:
	{
		return 100;
		break;
	}

	case 4:
	{
		return 200;
		break;
	}

	case 5:
	{
		return 400;
		break;
	}

	case 6:
	{
		return 600;
		break;
	}

	case 7:
	{
		return 800;
		break;
	}

	case 8:
	{
		return 1000;
		break;
	}

	}
}

void PerformQuickWithdrawOption(short Option)
{
	if (Option == 9)
		return;

	short WithdrawAmount = GetQuickWithdrawAmount(Option);

	if (Withdraw(WithdrawAmount))
	{
		LogAction(enActions::aWithdraw);
	}
}

void ShowQuickWithdrawScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Quick Withdraw Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightMagenta);
	cout << Tabs(6) << "1) 20\t  2) 50\n";
	cout << Tabs(6) << "3) 100\t  4) 200\n";
	cout << Tabs(6) << "5) 400\t  6) 600\n";
	cout << Tabs(6) << "7) 800\t  8) 1000\n";
	cout << Tabs(6) << "9) Exit.\n";
	cout << ColorCode(enColor::Yellow) << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite);
	cout << Tabs(4) << "Your Balance Is: " << ColorCode(enColor::BrightGreen) << CurrentClient.Balance << "\n\n";
	cout << ColorCode(enColor::BrightWhite);
	cout << Tabs(4) << "Choose What To Withdraw From (1) To (8): ";

	PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Normal Withdraw Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite);

	if (!Withdraw(ReadWithdrawAmount()))
	{
		//ShowNormalWithdrawScreen();
	}

	else
	{
		LogAction(enActions::aWithdraw);
	}
}

void ShowDepositScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Deposit Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite);

	if (Deposit(ReadDepositAmount()))
	{
		LogAction(enActions::aDeposit);
	}
}

void ShowCheckBalanceScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Check Balance Screen\n";
	cout << Tabs(4) << "=======================================================\n\n";
	cout << ColorCode(enColor::BrightWhite);
	cout << Tabs(4) << "Your Balance Is: " << ColorCode(enColor::BrightGreen) << CurrentClient.Balance << endl;
	cout << ColorCode(enColor::BrightWhite);
}

bool CheckOldPinCode()
{
	string OldPinCode;

	cout << Tabs(4) << "Enter Current PinCode: ";
	cin >> OldPinCode;

	if (OldPinCode != CurrentClient.PinCode)
		return false;

	return true;
}

string ReadNewPinCode()
{
	bool IsValid = true;
	string NewPinCode = "";
	string ConfirmPinCode = "";

	do
	{
		if (!IsValid)
		{
			cout << ColorCode(enColor::BrightRed);
			cout << "\n";
			cout << Tabs(4) << "No Match!, Try Again...\n";
			cout << ColorCode(enColor::BrightWhite);
		}

		cout << "\n";
		cout << Tabs(4) << "Enter New PinCode: ";
		cin >> NewPinCode;

		cout << Tabs(4) << "Confirm PinCode: ";
		cin >> ConfirmPinCode;

		IsValid = (NewPinCode == ConfirmPinCode);

	} while (!IsValid);

	return NewPinCode;
}

bool ChangePinCode(string NewPinCode)
{
	char Answer = 'N';

	cout << "\n";
	cout << Tabs(4) << "Are You Sure You Want To Change PinCode? (Y/N)? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		vector <strClient> Clients = LoadClientsFromFile(ClientsFileName);

		for (strClient& C : Clients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.PinCode = NewPinCode;
				CurrentClient.PinCode = NewPinCode;
				break;
			}
		}

		if (SaveClientsToFile(Clients, ClientsFileName))
		{
			cout << ColorCode(enColor::BrightGreen);
			cout << "\n";
			cout << Tabs(4) << "Done Successfully, New PinCode Is : " << CurrentClient.PinCode << endl;
			cout << ColorCode(enColor::BrightWhite);
			return true;
		}
	}

	return false;
}

void ShowChangePinCodeScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Change PinCode Screen\n";
	cout << Tabs(4) << "=======================================================\n\n";
	cout << ColorCode(enColor::BrightWhite);

	if (CheckOldPinCode())
	{
		string NewPinCode = ReadNewPinCode();
		
		if (ChangePinCode(NewPinCode))
		{
			LogAction(enActions::aChangePinCode);
		}
	}

	else
	{
		cout << ColorCode(enColor::BrightRed);
		cout << "\n";
		cout << Tabs(4) << "Incorrect PinCode, Try Again Later...\n";
		cout << ColorCode(enColor::BrightWhite);
	}
}

void PrintClientCard(strClient Client)
{
	cout << "\n";
	cout << Tabs(4) << "The Following Are The Client Details: \n";
	cout << ColorCode(enColor::BrightCyan) << Tabs(4) << "-------------------------------------------------------\n" << ColorCode(enColor::BrightWhite);
	cout << Tabs(4) << "Account Number: " << Client.AccountNumber << "\n";
	cout << Tabs(4) << "Pin Code      : " << Client.PinCode << "\n";
	cout << Tabs(4) << "Name          : " << Client.Name << "\n";
	cout << Tabs(4) << "Phone Number  : " << Client.PhoneNumber << "\n";
	cout << Tabs(4) << "Balance       : " << ColorCode(enColor::BrightGreen) << Client.Balance << "\n";
	cout << ColorCode(enColor::BrightCyan) << Tabs(4) << "-------------------------------------------------------\n" << ColorCode(enColor::BrightWhite);

}

void ShowClientDetailsScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Show Client Details Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite);
	PrintClientCard(CurrentClient);
}

void ShowClientHistory()
{
	fstream File;
	File.open(ClientHistoryFileName, ios::in);

	if (File.is_open())
	{
		string Line = "";

		while (getline(File, Line))
		{
			cout << Line << endl;
		}

		File.close();
	}
}

void ShowClientHistoryScreen()
{
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Show Client History Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite);
	ShowClientHistory();
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

void InitializeHistoryFile()
{
	ClientHistoryFileName = CurrentClient.AccountNumber + "_Histroy.txt";
}

void Login()
{
	bool IsValid = true;
	string AccountNumber = "", PinCode = "";

	do
	{
		system("cls");
		cout << ColorCode(enColor::BrightGreen);
		cout << Tabs(4) << "=======================================================\n";
		cout << Tabs(6) << "Login Screen\n";
		cout << Tabs(4) << "=======================================================\n";
		cout << ColorCode(enColor::BrightWhite);

		if (!IsValid)
		{

			cout << ColorCode(enColor::Red) << Tabs(4) << "Invalid Account Number/ PinCode!\n" << ColorCode(enColor::White);
		}

		cout << Tabs(4) << "Enter Account Number: ";
		cin >> AccountNumber;

		cout << Tabs(4) << "Enter PinCode: ";
		cin >> PinCode;

		IsValid = CheckAccountNumberAndPinCode(AccountNumber, PinCode);

	} while (!IsValid);

	InitializeHistoryFile();
	LogAction(enActions::aLogin);
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

	case enMainMenuOptions::enChangePinCode:
	{
		system("cls");
		ShowChangePinCodeScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enShowClientDetails:
	{
		system("cls");
		ShowClientDetailsScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enShowClientHistory:
	{
		system("cls");
		ShowClientHistoryScreen();
		GoBackToMainMenuScreen();
		break;
	}

	case enMainMenuOptions::enLogout:
	{
		LogAction(enActions::aLogout);
		system("cls");
		Login();
	}
	}
}

void ShowMainMenuScreen()
{
	system("cls");
	cout << ColorCode(enColor::Yellow);
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "ATM Main Menu Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::Blue);
	cout << Tabs(6) << "1) Quick Withdra.\n";
	cout << Tabs(6) << "2) Normal Withdra.\n";
	cout << Tabs(6) << "3) Deposit.\n";
	cout << Tabs(6) << "4) Check Balance.\n";
	cout << Tabs(6) << "5) Change PinCode.\n";
	cout << Tabs(6) << "6) Show Client Details.\n";
	cout << Tabs(6) << "7) Show Client History.\n";
	cout << ColorCode(enColor::Red) << Tabs(6) << "8) Logout.\n";
	cout << ColorCode(enColor::Yellow) << Tabs(4) << "=======================================================\n";
	cout << ColorCode(enColor::BrightWhite) << Tabs(4) << "Choose What Do You Want To Do? (1 To 8)? ";

	PerformMainMenuOption(ReadMainMenuOption());
}

int main()
{
	Login();

	system("pause>0");
	return 0;
}