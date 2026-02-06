#include <iostream>

using namespace std;

void ShowMainMenuScreen();

enum enMainMenuOptions {enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5};

struct strClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string PhoneNumber = "";
	double Balance = 0;
};

strClient CurrentClient = {"A10", "1234", "Mekdad Salloum", "098765", 3000};

string Tabs(short NumberOfTabs)
{
	string T = "";

	for (short i = 1; i <= NumberOfTabs; i++)
	{
		T += "\t";
	}

	return T;
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

void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Quick Withdraw Screen\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "1) 20\t  2) 50\n";
	cout << Tabs(6) << "3) 100\t  4) 200\n";
	cout << Tabs(6) << "5) 400\t  6) 600\n";
	cout << Tabs(6) << "7) 800\t  8) 1000\n";
	cout << Tabs(6) << "9) Exit.\n";
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(4) << "Your Balance Is: " << CurrentClient.Balance << endl;
	cout << Tabs(4) << "Choose What To Withdraw From (1) To (8): ";

}

void ShowNormalWithdrawScreen()
{

}

void ShowDepositScreen()
{

}

void ShowCheckBalanceScreen()
{
	cout << Tabs(4) << "=======================================================\n";
	cout << Tabs(6) << "Check Balance Screen\n";
	cout << Tabs(4) << "=======================================================\n\n";
	cout << Tabs(4) << "Your Balance Is: " << CurrentClient.Balance << endl;
}

void Login()
{

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
	ShowMainMenuScreen();

	system("pause>0");
	return 0;
}