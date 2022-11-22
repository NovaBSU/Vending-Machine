#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

bool backBool = 0;
bool success = 0;
int xhash = 0;

vector<string> cMenu{};

char filein[5000] = "NULL";
string filestring = "NULL";

string hotDrink[7] = {"1", "hot drink", "Hot Drink", "hot Drink", "Hot drink", "hot", "Hot"};
string coldDrink[7] = {"2", "cold drink", "Cold Drink", "cold Drink", "Cold drink", "cold", "Cold"};
string savourySnack[7] = {"3", "savoury snack", "Savoury Snack", "savoury Snack", "Savoury snack", "savoury", "Savoury"};
string sweetSnack[7] = {"4", "sweet snack", "Sweet Snack", "sweet Snack", "Sweet snack", "Savoury", "Sweet"};
string utilityItem[7] = {"5", "utility", "Utility", "UTILITY", "utility item", "Utility Item", "Utility item"};
string back[5] = {"b", "B", "back", "Back", "BACK"};

string userInput = "NULL";

void btru() {
	backBool = true;
}

void hDrink() {
	cout << "Hot Drinks Menu" << endl;
	ifstream hDrkMenu;
	hDrkMenu.open("hDrkMenu.txt");
	hDrkMenu.seekg(0);
	hDrkMenu.getline(filein, 2, '\n');
	filestring = filein;
	xhash = stoi(filestring.substr(0,1)); // this works..?? why
	for (xhash == 0; xhash--;) {
		hDrkMenu.getline(filein, 2, '\n'); // USE A GOT DANG STRING
		filestring = filein; // WHY DO I HAVE TO DO WEIRD CONVERSIONS LIKE THIS
		cMenu.push_back(filestring);
	}

	for (xhash == 0; xhash--;) {
		cout << cMenu[xhash] << endl;
	}
}

void cDrink() {
	cout << "Cold Drinks Menu" << endl;
	cout << "1. Coke" << endl << "2. Pepsi" << endl << "3. Fanta" << endl << "4. Oasis" << endl << "5. Iced Tea" << endl << endl;
	cin >> userInput;
}

void svSnk() {
	cout << "Savoury Snacks Menu" << endl;
	cout << "1. Cornish Pastry" << endl << "2. Crossiant" << endl << "3. Breakfast Bar" << endl << "4. Pepperami" << endl << "5. Fridge Raiders" << endl << endl;
	cin >> userInput;
}

void swSnk() {
	cout << "Sweets Menu" << endl;
	cout << "1. Dairy Milk" << endl << "2. Aero" << endl << "3. Bounty" << endl << "4. Freddo" << endl << "5. Wine Gums" << endl << endl;
	cin >> userInput;
}

void uItm() {
	cout << "Misc Menu" << endl;
	cout << "1. Powerbank" << endl << "2. Charger (USB C)" << endl << "3. Charger (Micro USB)" << endl << "4. Charger (Lightning)" << endl << "5. US to UK plug" << endl << endl;
	cin >> userInput;
}

void displayMenu() {
	cout << "What type of product are you looking for?" << endl;
	cout << "1. Hot Drinks" << endl << "2. Cold Drinks" << endl << "3. Savoury Snacks" << endl << "4. Sweet Snacks" << endl << "5. Utility Items" << endl << endl;

	getline(cin, userInput);

	while (cin.fail()) {
		cin.clear();
		cin.ignore(256000, '\n');
		cout << "Input Error. Please re-input which type of product you are looking for." << endl;
		cout << "1. Hot Drinks" << endl << "2. Cold Drinks" << endl << "3. Savoury Snacks" << endl << "4. Sweet Snacks" << endl << "5. Utility Items" << endl;
		getline(cin, userInput);
	}

	for (int i = 0; i < 7; i++) {
		if (userInput == hotDrink[i]) {
			hDrink();
			break;
		}
		else if (userInput == coldDrink[i]) {
			cDrink();
			break;
		}
		else if (userInput == savourySnack[i]) {
			svSnk();
			break;
		}
		else if (userInput == sweetSnack[i]) {
			swSnk();
			break;
		}
		else if (userInput == utilityItem[i]) {
			uItm();
			break;
		}
		else if (userInput == back[i]) {
			btru();
			break;
		}
		else if (i == 6 and success == 0) {
			cout << "You input an invalid input" << endl << endl;
			btru();
			break;
		}
	}
}

int main() {

	cout << "Vending machine initializing..." << endl << endl;
	cout << "Vending machine 1.0.0 initialized. Welcome user" << endl << endl;

	displayMenu();
	while (backBool == true) {
		backBool = false;
		displayMenu();
	}
	return 0;
}