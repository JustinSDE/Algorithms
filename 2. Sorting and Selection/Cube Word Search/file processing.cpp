/*the "file processing.cpp" file defines the functions that processes the cubes and words file*/

#include "file processing.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

// access to global variables defined in "main.cpp"
extern vector<map<char, int>> wordCharCounts;
extern vector<vector<vector<int>>> cubeCharCounts;
extern vector<string> words;
extern vector<int> cubeWordCount;

// the processCubes function takes the cubes.txt file name,
// processes the file and outputs the result into the global variables
void processCubes(char* filename) {
	ifstream cubesTxt(filename);						// open file
	if (cubesTxt.is_open()) {
		string line;
		while (getline(cubesTxt, line)) {				// read line
			cubeWordCount.push_back(0);					// set the result array indicator to 0

			// create a map of <char, array> pair to record the positions of each character
			// the original string representation of the cube is no longer needed
			// refer to the design doc for more information...
			vector<vector<int>> charCnt(26);
			int sz = line.length();
			for (int i = 0; i < sz; i++) {
				charCnt[line[i]-'a'].push_back(i);
			}
			cubeCharCounts.push_back(charCnt);
		}
	}
	else {
		// inform the user there is an error while opening the file
		cerr << "cannot open " << filename << endl;
		exit(1);
	}

}
// the processWords function takes the words.txt file name,
// processes the file and outputs the result into the global variables
void processWords(char* filename) {
	ifstream wordsTxt(filename);						// open file
	if (wordsTxt.is_open()) {
		set<string> rawWords;							// use a set (RB-tree) to avoid duplicate words
		string line;
		int sz;
		bool validWord;									// a flag to check if the word is valid
		while (getline(wordsTxt, line)) {
			sz = line.length();
			validWord = true;
			for (int i = 0; i < sz; i++) {
				if (line[i] >= 'a' && line[i] <= 'z')
					continue;
				else if (line[i] >= 'A' && line[i] <= 'Z')	// convert upper case to lower case
					line[i] = line[i] - 'A' + 'a';
				else {
					validWord = false;					// if not letter character, set the flag and break the loop
					break;
				}
			}
			// only take words if it is valid
			if (validWord) {
				rawWords.insert(line);
			}
		}
		// insert all valid words into the global string array
		for (auto word : rawWords) {
			words.push_back(word);
			// use a map to record the appearance count of each character in a word
			map<char, int> charCnt;
			for (auto x : word) {
				charCnt[x]++;
			}
			wordCharCounts.push_back(charCnt);
		}
	}
	else {
		// inform the user that the file cannot be opened...
		cout << "cannot open " << filename << endl;
		exit(1);
	}
}