#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

// Building a Dynamic Array system.

string intmain = "NULL";
char filein[5000] = "NULL";
string str = "NULL";
int x = 0;

int main() {

	ofstream myfile;
	myfile.open("DynamicArray.txt");
	myfile << 4567 << endl << 5678 << endl << 6789 << endl << 7890 << endl;
	myfile.close();

	ifstream mfile;
	mfile.open("DynamicArray.txt");
	mfile.seekg(x);
	for (int fuforloop = 0; fuforloop < 4; fuforloop++) {
		mfile.getline(filein, 20000000000000000, '\n');
		str = filein;
		cout << str << endl;
	}
	mfile.close();
	// if so, append to end of string
	// repeat
	// then stoi into intager when

	return 0;
}