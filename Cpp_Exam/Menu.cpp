#include <iostream>
using namespace std;



int MenuAddResidents()
{
	int choice = 0;
	cout << endl;
	cout << "1. Fixation of residents by apartment\n0. Back to main Menu" << endl;
	cin >> choice;
	return choice;
}
int MenuDeleteResidents()
{
	int choice = 0;
	cout << endl;
	cout << "1. Detachment of residents from the apartment\n0. Back to main Menu" << endl;
	cin >> choice;
	return choice;
}
int MenuAddApartment()
{
	int choice = 0;
	cout << endl;
	cout << "1. Add a one-room apartment\n2. Add a two-room apartment\n3. Add a three-room apartment\n0. Back to main Menu" << endl;
	cin >> choice;
	return choice;
}
int MenuDeleteApartment()
{
	int choice = 0;
	cout << endl;
	cout << "1. Delete  one-room apartment\n2. Delete  two-room apartment\n3. Delete  three-room apartment\n0. Back to main Menu" << endl;
	cin >> choice;
	return choice;
}
int MenuCreateReport()
{
	int choice = 0;
	cout << endl;
	cout << "1. Displaying a complete list of residents\n2. Displaying a complete list of apartments\n3. Displaying information about a certain apartment\n0. Back to main Menu" << endl;
	cin >> choice;
	return choice;
}



void Mainmenu()
{
	int choise;
	bool exitMainMenu = false;
	bool exitMenu = false;
	while (!exitMainMenu)
	{
		cout << "1.Add residents of the house\n2.Remove residents of the house\n3.Add an apartment\n4.Delete the apartment\n5.Create a report" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			exitMenu = false;
			while (!exitMenu)
			{
				choise = MenuAddResidents();
				switch (choise)
				{
				case 1: cout << "Add +++";
					break;
				case 0:
					exitMenu = true;
					break;
				}
			}
			break;
		case 2:
			exitMenu = false;
			while (!exitMenu)
			{
				choise = MenuDeleteResidents();
				switch (choise)
				{
				case 1: cout << "Delete ---";
					break;
				case 0:
					exitMenu = true;
					break;
				}
			}
			break;
		case 3:
			exitMenu = false;
			while (!exitMenu)
			{
				choise = MenuAddApartment();
				switch (choise)
				{
				case 1: cout << "Add 1 apartaments";
					break;
				case 2: cout << "Add 2 apartaments";
					break;
				case 3: cout << "Add 3 apartaments";
					break;
				case 0:
					exitMenu = true;
					break;
				}
			}
			break;

		case 4:
			exitMenu = false;
			while (!exitMenu)
			{
				choise = MenuDeleteApartment();
				switch (choise)
				{
				case 1: cout << "Delete 1 apartaments";
					break;
				case 2:cout << "Delete 1 apartaments";
					break;
				case 3: cout << "Delete 1 apartaments";
					break;
				case 0:
					exitMenu = true;
					break;
				}
			}
			break;
		case 5:
			exitMenu = false;
			while (!exitMenu)
			{
				choise = MenuCreateReport();
				switch (choise)
				{
				case 1: cout << "info resident ++++++";
					break;
				case 2: cout << "info apartmants ++++++";
					break;
				case 3: cout << "info ONLY apartments ++++++";
					break;
				case 0:
					exitMenu = true;
					break;
				}
			}
			break;
		case 0:
			exitMainMenu = true;
			break;
		}





	}
}