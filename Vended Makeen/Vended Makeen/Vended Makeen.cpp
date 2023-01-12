#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

// The following variables are global because they are used in multiple functions
// and within the scope of this program it is very unlikely external files will be used.
// Therefore, using these as global variables is quite safe.

bool backBool = 0;

int xhash = 0;
int yhash = 0;

vector<string> cMenu{};
vector<float> pMenu{};

char filein[5000] = "NULL";
string filestring = "NULL";

string menuType = "NULL";
string userInput = "NULL";


void btru() { // The function btru has one function, it makes the DisplayMenu loop. This function helps me avoid code duplication as this is used regularly.
	backBool = true; 
} 

// This function checks if a yes/no answer has an error.
void errorCheck() {
	while (userInput != "yes" and userInput != "y" and userInput != "Yes" and userInput != "Y" and userInput != "no" and userInput != "n" and userInput != "No" and userInput != "N") {
		cout << "Input Error! Please input y/n" << '\n' << endl;
		cin >> userInput;
	}
}

void dev() { 
	// This is my developer function, from which new items can be added to any menu, 
	// and saved directly into the filesystem by the program automagically.
	string password = "NULL";
	double addRemove = 0;
	float menuType = 0;
	float cPrice = 0;
	float fileFloat = 0;
	int menuTypeInt = 0;
	int menuHash = 0;
	int success = 0;

	system("cls"); // Clear console, write out some cool sounding start jargon.
	cout << "Developer Mode Inititated..." << endl;
	cout << "\n" << "Please Input Developer Password" << endl;
	cin >> password;

	while (password == "dev123") {
		cout << "\n" << "Welcome, Adminstrator." << endl;
		success = 1;

		// This following block is used to pick which menu you would like to access and add to.
		// This is a simplified version of what I used in Display Menu that is a little less user friend,
		// I find this to be acceptable as it is within a developer/admin panel. 
		// It is still fully functional.
		cout << "\n" << "Which menu would you like to add to?" << endl << "Please enter 1 for Hot Drinks, 2 for Cold Drinks, 3 for Savoury Snacks or 4 for Sweet Snacks." << "\n" << endl;
		cin >> menuType;
		cout << "\n";

		while (cin.fail()) {
			// A pretty standard Cin.Fail block, however this can't be its own function 
			// as the error message and cin target must change each time. I will make these blocks with [CNF]
			cin.clear();
			cin.ignore(256000, '\n');
			cout << "Input Error. Please a menu number between 1 and 4." << endl;
			cin >> menuType;
		}

		menuTypeInt = menuType;

		ifstream vMenu;
		if (menuTypeInt == 1) {
			vMenu.open("hDrkMenu.txt");
		}
		else if (menuTypeInt == 2) {
			vMenu.open("cDrkMenu.txt");
		}
		else if (menuTypeInt == 3) {
			vMenu.open("svSnkMenu.txt");
		}
		else if (menuTypeInt == 4) {
			vMenu.open("swSnkMenu.txt");
		}
		else {
			cout << "Error 666- How TF did we end up here??";
		}

		// This block of code calls the items from the menu,
		// then pushes them onto the cMenu vector.
		// This uses a variable called the xhash to determine
		// how many items are in the list. The xhash is printed at the top of the file.
		vMenu.seekg(0); 
		vMenu.getline(filein, 3, '\n'); 
		filestring = filein; 
		xhash = stoi(filestring.substr(0, 3)); 
		for (int i = 0; i < xhash; i++) { 
			vMenu.getline(filein, 2000, '\n');
			filestring = filein; 
			cMenu.push_back(filestring); 
		} 

		vMenu.close();

		// This is where it becomes a little different from anything displayMenu does,
		// as it calls the price file in the same function. This is normally done in
		// the priceFn
		ifstream pricefile;
		if (menuTypeInt == 1) {
			pricefile.open("hDrkPrices.txt");
		}
		else if (menuTypeInt == 2) {
			pricefile.open("cDrkPrices.txt");
		}
		else if (menuTypeInt == 3) {
			pricefile.open("svSnkPrices.txt");
		}
		else if (menuTypeInt == 4) {
			pricefile.open("swSnkPrices.txt");
		}
		else {
			cout << "Error 666- How TF did we end up here??";
		}

		// Same as above, pulling in the menu items and pushing it to the back of the
		// vector, this time using the pMenu vector.
		// I would have functioned this, however I could not reuse the filestream name successfully.
		pricefile.seekg(0);
		pricefile.getline(filein, 3, '\n');
		filestring = filein;
		yhash = stoi(filestring.substr(0, 3));
		for (int i = 0; i < yhash; i++) {
			pricefile.getline(filein, 2000, '\n');
			filestring = filein;
			cPrice = stof(filestring.substr(0, 100));
			pMenu.push_back(cPrice);
		}

		pricefile.close();

		cin.clear(); // clear the cache
		cin.ignore(256000, '\n'); // clear it again

		// This is where we begin to take the new item into memory.
		// I use a getline here to allow for multi-word names without any input errors.
		cout << "What is the name of the item you would like to add to the menu?" << endl;
		getline(cin, filestring);
		cMenu.push_back(filestring);
		cout << "\n";

		// I have to clear the CIN here, otherwise the code breaks.
		cin.clear(); // clear the cache

		// Now we take a price from the user, check it against cin.fail
		// then push it to the back of the vector.
		cout << "How much would you like to charge for this item? (pounds.pence)" << endl;
		cin >> fileFloat;
		int fileFloatInt = fileFloat * 100;
		fileFloat = fileFloatInt;
		fileFloat = fileFloat / 100;
		while (cin.fail()) { 
			cin.clear(); 
			cin.ignore(256000, '\n'); 
			cout << "Input Error. Please input currency in numbers. (pounds.pence)" << endl;
			cin >> fileFloat;
		}

		pMenu.push_back(fileFloat);
		cout << "\n";

		// Once everything is pushed back, we use the menuType from earlier to write it all
		// to the correct files, overwriting the previous file.
		ofstream voMenu;
		if (menuTypeInt == 1) {
			voMenu.open("hDrkMenu.txt");
		}
		else if (menuTypeInt == 2) {
			voMenu.open("cDrkMenu.txt");
		}
		else if (menuTypeInt == 3) {
			voMenu.open("svSnkMenu.txt");
		}
		else if (menuTypeInt == 4) {
			voMenu.open("swSnkMenu.txt");
		}
		else {
			cout << "Error 666- How TF did we end up here??";
		}

		// This updated the xhash, the number used to tell the code how many items are in the list,
		// then writes the xhash to the file. After writing the xhash to file, it uses a for loop,
		// to write the rest of the items to the file.
		xhash++;
		voMenu << xhash << "\n";
		for (int i = 0; i < xhash; i++) {
			voMenu << cMenu[i] << "\n";
		}

		voMenu.close();

		// We then repeat the last two blocks of code, but for the price menu.
		// Again, I struggled with having to dupe code here as I couldn't use the
		// same filestream twice.
		ofstream poMenu;
		if (menuTypeInt == 1) {
			poMenu.open("hDrkPrices.txt");
		}
		else if (menuTypeInt == 2) {
			poMenu.open("cDrkPrices.txt");
		}
		else if (menuTypeInt == 3) {
			poMenu.open("svSnkPrices.txt");
		}
		else if (menuTypeInt == 4) {
			poMenu.open("swSnkPrices.txt");
		}
		else {
			cout << "Error 666- How TF did we end up here??";
		}

		poMenu << xhash << "\n";
		for (int i = 0; i < xhash; i++) {
			poMenu << pMenu[i] << "\n";
		}

		poMenu.close();

		cout << "Do you wish to add another item? (y/n)" << endl;
		cin >> userInput;
		errorCheck();
		if (userInput != "Y" and userInput != "yes" and userInput != "Yes" and userInput != "y") {
			password = "0";
		}
		else {
			system("cls");
		}
	}

	// A fun message if the user inputs the wrong password on the dev screen. This also kills the program.
	if (password !="dev123" and success == 0) {
		cout << "Tampering with private property is against the law." << endl;
		cout << "The police have been called to this location." << endl;
		cout << "Please do not resist." << endl;
	}
	
}

void priceFn() {

	float price = 0;
	float cPrice = 0;
	float credit = 0;
	float userPayment = 0;

	int uPay = 0;
	int pound = 0;
	int fifty = 0;
	int twenty = 0;
	int ten = 0;
	int five = 0;
	int two = 0;
	int one = 0;
	int userInputInt = 0;

	// This takes the user's input on what item they want after printing out the menu.
	cin >> userInputInt;

	while (cin.fail() or userInputInt > xhash or userInputInt < 1) { // [CNF]
		cin.clear(); 
		cin.ignore(256000, '\n'); 
		cout << "Input Error. Please input the number of the item you would like." << endl;
		cin >> userInputInt;
	}
#
	// We have to remove one from the user input intager because
	// the program starts from zero while the user interface starts from one.
	userInputInt--;

	// This then pulls the correct prices list using the menutype provided
	// by the displayMenu function.
	ifstream pricefile; 
	if (menuType == "hD") {
		pricefile.open("hDrkPrices.txt");
	}
	else if (menuType == "cD") {
		pricefile.open("cDrkPrices.txt");
	}
	else if (menuType == "svSnk") {
		pricefile.open("svSnkPrices.txt");
	}
	else if (menuType == "swSnk") {
		pricefile.open("swSnkPrices.txt");
	}
	else {
		// Any error 666 SHOULD be impossible. Covering all bases.
		cout << "Error 666- How TF did we end up here??";
	}

	// It then pulls it into memory.
	pricefile.seekg(0);
	pricefile.getline(filein, 3, '\n');
	filestring = filein; 
	yhash = stoi(filestring.substr(0, 3)); 
	for (int i = 0; i < yhash; i++) { 
		pricefile.getline(filein, 2000, '\n');
		filestring = filein;
		cPrice = stof(filestring.substr(0, 100));
		pMenu.push_back(cPrice); 
	} 

	pricefile.close();

	// Check the user selected the item they want.
	cout << '\n' << "The item you selected is " << cMenu[userInputInt] << endl;
	cout << "Is this correct? [y/n]" << endl;

	// This cin clear is here to fix a specific error with inputting decimal numbers into the
	// userInputInt, where it would return you to the menu.
	cin.clear();
	cin.ignore(256000, '\n');

	cin >> userInput;
	
	errorCheck();

	// If they did, then tell them the price.
	if (userInput == "yes" or userInput == "y" or userInput == "Yes" or userInput == "Y") {
		cin.clear();
		cout << '\n' << "The Price of " << cMenu[userInputInt] << " is " << char(156) << pMenu[userInputInt] << endl;

		// Draw the user's credit from the credit.txt file.
		ifstream fcredit;
		fcredit.open("credit.txt");
		fcredit.getline(filein, 10, '\n');
		filestring = filein;
		credit = stof(filestring.substr(0, 1));
		fcredit.close();

		// Declare a short term intager used to break the loop, then open a while loop to add money.
		int brk = 0;
		while (credit < pMenu[userInputInt] and brk == 0) {

			// Tell the user their credit, tell them to add more, then take money. Option to cancel.
			cout << "You have " << char(156) << credit << " in credit." << endl;
			cout << "Please input money in the Pounds.Pence format now or press 0 to cancel" << '\n' << endl;
			cin >> userPayment;
			cout << '\n';

			// [CNF]
			while (cin.fail() or userPayment < 0) {
				cin.clear();
				cin.ignore(256000, '\n');
				cout << "Input Error. Please input your money in the Pounds.Pence format or 0 to go back." << endl;
				cin >> userPayment;
			}
			
			// This is to shorten any input number to 2 decimal places.
			// By shortening the input to 2dp you avoid unrealistically small numbers.
			uPay = userPayment * 100;
			userPayment = uPay;
			userPayment = userPayment / 100;

			// Add the money the user paid in to their credit.
			credit += userPayment;

			if (userPayment == 0) {
				// Update the break variable, it doesn't like the break command being used in an if because if isn't a loop.
				brk = 1; 
			}

		}

		// When the user is done inputting money, if the credit is greater than or equal to the cost
		// dispense their item, then tell them their remaining credit.
		if (credit > pMenu[userInputInt] or credit == pMenu[userInputInt]) {
			credit -= pMenu[userInputInt];
			
			// This block corrects for an error where the math fails and produces a float
			// with more than 2dp. I am not sure how this happens, but this fix is sufficient.
			int credInt = credit * 100;
			credit = credInt;
			credit = credit / 100;

			cout << '\n' << "Purchase Successful!" << '\n' << "You have a total of " << char(156) << credit << " available." << endl;

			// Now write the remaining credit to the credit file.
			ofstream fcredit;
			fcredit.open("credit.txt");
			fcredit << credit;
			fcredit.close();
		}

		// Ask if the user wants to purchase another item.
		cout << "Would you like to purchase another item? (y/n)" << '\n' << endl;
		cin >> userInput;
		if (userInput == "yes" or userInput == "y" or userInput == "Yes" or userInput == "Y") {
			btru();
			cout << '\n' << endl;
		}

		// If the user does not want another item, ask if they would like their change.
		else {
			cout << "Would you like your change? (y/n)" << '\n' << endl;
			cin >> userInput;
			errorCheck();
			// If the user wants their change, dispense it. This is a greedy system,
			// but it works. It simply uses a while loop checking you have enough to
			// make each coin, biggest to smallest, then if you do, it dispenses that coin
			// and checks that coin again.
			if (userInput == "yes" or userInput == "y" or userInput == "Yes" or userInput == "Y") {
				while (credit > 1 or credit == 1) {
					credit--;
					pound++;
				}
				while (credit > 0.5 or credit == 0.5) {
					credit -= 0.5;
					fifty++;
				}
				while (credit > 0.2 or credit == 0.2) {
					credit -= 0.2;
					twenty++;
				}
				while (credit > 0.1 or credit == 0.1) {
					credit -= 0.1;
					ten++;
				}
				while (credit > 0.05 or credit == 0.05) {
					credit -= 0.05;
					five++;
				}
				while (credit > 0.02 or credit == 0.02) {
					credit -= 0.05;
					two++;
				}
				while (credit > 0.01 or credit == 0.01) {
					credit -= 0.01;
					one++;
				}

				// Display the change.
				cout << "Your Change is " << pound << " pound coins " << fifty << " fifty pence pieces " << twenty << endl << " twenty pence pieces " << ten << " ten pence pieces " << five << " five pence pieces " << two << " two pence pieces and " << one << " pennies." << endl;

				// Now write the 0 remaining credit to the credit file.
				// Stops infinite gredit exploit.
				ofstream fcredit;
				fcredit.open("credit.txt");
				fcredit << credit;
				fcredit.close();
			}
		}

	}

	else {
	// Return to menu/
		btru();
		cout << "Returning to Menu" << '\n' << endl;
	}
}

void menu() { 
	int menuHash = 0;

	// Pull in the menu from the file.
	// This is separated from the displayMenu as it would otherwise require a lot of duplicate code.
	ifstream vMenu; 

	// This checks the menuType given by the displayMenu and opens the designated file.
	if (menuType == "hD") {
		cout << '\n' << "Hot Drinks Menu" << endl; 
		vMenu.open("hDrkMenu.txt");
	}
	else if (menuType == "cD") {
		cout << '\n' << "Cold Drinks Menu" << endl; 
		vMenu.open("cDrkMenu.txt");
	}
	else if (menuType == "svSnk") {
		cout << '\n' << "Savoury Snacks Menu" << endl;
		vMenu.open("svSnkMenu.txt");
	}
	else if (menuType == "swSnk") {
		cout << '\n' << "Sweet Snacks Menu" << endl; 
		vMenu.open("swSnkMenu.txt");
	}
	else {
		cout << "Error 666- How TF did we end up here??";
	}

	// Pull in the menu from the file for the user.
	vMenu.seekg(0); 
	vMenu.getline(filein, 3, '\n'); 
	filestring = filein; 
	xhash = stoi(filestring.substr(0,3)); 
	for (int i = 0; i < xhash; i++) { 
		vMenu.getline(filein, 2000, '\n'); 
		filestring = filein; 
		cMenu.push_back(filestring); 
	} 
	
	// Now write the menu to the console.
	for (int i = 0; i < xhash; i++) { 
		menuHash++;
		cout << menuHash << ". " << cMenu[i] << " " << endl; 
	} 

	vMenu.close();

	// Now ask for the item number the user would like, this is continued into the priceFn.
	cout << '\n' << "Please enter the number of the item you would like" << endl;

	priceFn();

}

void displayMenu() { 

	// Define all the possible inputs for each menu type.
	string hotDrink[7] = { "1", "hot drink", "Hot Drink", "hot Drink", "Hot drink", "hot", "Hot" };
	string coldDrink[7] = { "2", "cold drink", "Cold Drink", "cold Drink", "Cold drink", "cold", "Cold" };
	string savourySnack[7] = { "3", "savoury snack", "Savoury Snack", "savoury Snack", "Savoury snack", "savoury", "Savoury" };
	string sweetSnack[7] = { "4", "sweet snack", "Sweet Snack", "sweet Snack", "Sweet snack", "Savoury", "Sweet" };
	string back[5] = { "b", "B", "back", "Back", "BACK" };

	bool success = 0;

	// Tell the user what is available
	cout << "What type of product are you looking for?" << endl; 
	cout << "1. Hot Drinks" << endl << "2. Cold Drinks" << endl << "3. Savoury Snacks" << endl << "4. Sweet Snacks" << "\n" << endl; 

	// Take their input
	getline(cin, userInput); 

	while (cin.fail()) { // [CNF]
		cin.clear();
		cin.ignore(256000, '\n'); 
		cout << "Input Error. Please re-input which type of product you are looking for." << endl; 
		cout << "1. Hot Drinks" << endl << "2. Cold Drinks" << endl << "3. Savoury Snacks" << endl << "4. Sweet Snacks" << endl << "5. Utility Items" << endl;
		getline(cin, userInput); 
	}

	// Now check against the possible menu types, using a for loop to check through the arrays
	// in a much more efficient way. This works as it uses the for loop's internal variable
	// as the array position.
	for (int i = 0; i < 7; i++) {
		if (userInput == hotDrink[i]) { 
			menuType = "hD";
			menu(); 
			break; 
		}
		else if (userInput == coldDrink[i]) {
			menuType = "cD";
			menu();
			break;
		}
		else if (userInput == savourySnack[i]) {
			menuType = "svSnk";
			menu();
			break;
		}
		else if (userInput == sweetSnack[i]) {
			menuType = "swSnk";
			menu();
			break;
		}
		else if (userInput == back[i]) {
			btru();
			break;
		}
		// if the user inputs the dev command, take them to the dev function
		else if (userInput == "dev1"){
			dev();
			break;
		}
		else if (userInput == "boo") {
			cout << "AAA!";
			break;
		}

		// If the user inputs an invalid input, then alert them of this and run it from the top
		else if (i == 6 and success == 0) { 
			btru();
			system("cls");
			cout << "You input an invalid input" << endl;
			cout << "Please press Enter to continue" << endl;
			break; 
		}
	}
}

int main() {
	// Some initializing text.
	cout << "Vending machine initializing..." << '\n' << endl; // tell the user the program starts
	cout << "Vending machine 1.0.0 initialized. Welcome user" << '\n' << endl; // flava flav text

	// Run display menu to start the function cascade. Then check if backBool is true
	// and if it is, clear cache and run displayMenu again.
	displayMenu();
	while (backBool == true) { 
		backBool = false; 
		cin.clear();
		cin.ignore(256000, '\n');
		displayMenu(); 
	}
	return 0;
	
}