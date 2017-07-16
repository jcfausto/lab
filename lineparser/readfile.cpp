
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>

// Optional: To measure running time
#include <chrono> 

using namespace std;

// Optional: To measure running time
using namespace std::chrono;

int main() {

	// Optional: To measure running time
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	std::map<char, char> openingSymbols = { {'(', ')'}, {'{', '}'} };

	std::vector<char> closingSymbols = { ')', '}' };

	std::stack<char> textSymbols;

	string line;
	int lineNumber = 0;
	ifstream file("text.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			lineNumber++;
			cout << "Line: " << lineNumber;
			istringstream iss(line);
			char currentChar;
			int charPos = 0;
			while ( iss.get(currentChar)) { //Using iss >> c will make the spaces to be ignored.
				charPos++;				
				
				bool isOpenSymbol = openingSymbols.find(currentChar) != openingSymbols.end();
				
				if (isOpenSymbol) {
					cout << endl << "    (" << lineNumber << ":" << charPos << "," << currentChar << ")";
					textSymbols.push(currentChar);
					continue;
				}
				
				bool isClosingSymbol = (std::find(std::begin(closingSymbols), std::end(closingSymbols), currentChar) != closingSymbols.end());

				if (isClosingSymbol) {
		
					if (textSymbols.empty()) {
						cout << endl << "Error: No openning symbol found for " << currentChar;
						break;
					}

					char openSymbol = textSymbols.top();
					char expectedCloseSymbol = openingSymbols[openSymbol];
					
					bool symbolsMatch = expectedCloseSymbol == currentChar;
					
					if (symbolsMatch) {
						textSymbols.pop();
					} else {
						cout << endl << "Error: Expected symbol `" << expectedCloseSymbol << "` not found. Found `" << currentChar << "` at line " << lineNumber << " char pos " << charPos;
						break;
					}

				}	

			}
			cout << endl;
		}
		file.close();
	}
	else cout << "Unable to open file";

	// Optional: To measure running time
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>( t2 - t1 ).count();
	cout << duration << endl;

	return 0;
}