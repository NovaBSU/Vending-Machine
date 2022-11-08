#include<iostream>
#include<string>

using namespace std;

bool backBool = 0;
bool success = 0;

string hotDrink[7] = {"1", "hot drink", "Hot Drink", "hot Drink", "Hot drink", "hot", "Hot"};
string coldDrink[7] = {"2", "cold drink", "Cold Drink", "cold Drink", "Cold drink", "cold", "Cold"};
string savourySnack[7] = {"3", "savoury snack", "Savoury Snack", "savoury Snack", "Savoury snack", "savoury", "Savoury"};
string sweetSnack[7] = {"4", "sweet snack", "Sweet Snack", "sweet Snack", "Sweet snack", "Savoury", "Sweet"};
string utilityItem[7] = {"5", "utility", "Utility", "UTILITY", "utility item", "Utility Item", "Utility item"};
string back[5] = {"b", "B", "back", "Back", "BACK"};

string userInput = "NULL";

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
			cout << "success";
		}
		else if (userInput == coldDrink[i]) {
			cout << "success";
		}
		else if (userInput == savourySnack[i]) {
			cout << "success";
		}
		else if (userInput == sweetSnack[i]) {
			cout << "success";
		}
		else if (userInput == utilityItem[i]) {
			cout << "success";
		}
		else if (userInput == back[i]) {
			backBool = true;
			break;
		}
		else if (i == 6 and success == 0) {
			cout << "You input an invalid input" << endl << endl;
			backBool = true;
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