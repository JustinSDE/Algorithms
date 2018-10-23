/*this "word search.cpp" file implements the methods used for seach words in cubes*/
#include "word search.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

// global variables
extern vector<map<char, int>> wordCharCounts;
extern vector<vector<vector<int>>> cubeCharCounts;
extern vector<string> words;
extern vector<string> cubes;
extern vector<int> cubeWordCount;
extern vector<vector<bool>> isNeighbors;

// the getIndex function converts an index input into the <i,j,k> tuple
// the return value indicates whether the index is valid or not
bool getIndex(int index, int & i, int & j, int & k)
{
	if (index < 0 || index>63)
		return false;
	i = index / 16;
	index = index - i * 16;
	j = index / 4;
	k = index % 4;
	return true;
}

// this isNeighbor function tests if two indices are neighbors in a 4X4X4 cube
bool isNeighbor(int index1, int index2)
{
	int a, b, c, d, e, f;
	bool b1 = getIndex(index1, a, b, c);
	bool b2 = getIndex(index2, d, e, f);
	if (b1&&b2) {
		int i_diff = abs(a - d), j_diff = abs(b - e), k_diff = abs(c - f);
		// the two indices are neighbors if the i j k diff are <= 1 and they are not all zero
		if (i_diff <= 1 && j_diff <= 1 && k_diff <= 1 && (i_diff || j_diff || k_diff))
			return true;
	}
	return false;
}

// the initializeNeighbors function initializes the 2D array for fast check of neighbor indices
// because there are thousands X thousands lookups, during which we need to determine neighborhoodship 
// during each DFS step, we can create a lookup matrix and therefore remove repetitive unnecessary calculations 
void initializeNeighbors(std::vector<std::vector<bool>>& isNeighbors)
{
	if (!isNeighbors.empty())
		isNeighbors.clear();
	vector<bool> temp(64);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			temp[j] = isNeighbor(i, j);
		}
		isNeighbors.push_back(temp);
	}
	return;
}

// the resetChecked function resets the array checked which records if an index has been visited or not
void resetChecked(std::vector<bool>& checked)
{
	for (int i = 0; i < 64; i++) {
		checked[i] = false;
	}
}

// this coverable function tests if a word can be composed with (covered by) the letters from a cube
bool coverable(std::vector<std::vector<int>>& cubeStat, std::map<char, int>& wordStat)
{
	for (auto it = wordStat.begin(); it != wordStat.end(); it++) {
		char c = it->first;
		// if the cube doesn't contain a letter from the word, or the number of a specfic letter is less than the appearance 
		// from the word, then it is guaranteed that the word doesn't exist in the cubic, so we can skip
		if (it->second > int(cubeStat[c-'a'].size())) {
			return false;
		}
	}
	return true;
}

// the dfsWordSearch function is the key function which searches for the word in the cube through DFS
bool dfsWordSearch(std::vector<std::vector<int>>& cubeStat, /*a dictionary (RBtree) storing the indices of each character in the cube*/
					std::string & word, std::vector<bool>& checked, /*an array keep track of whether a specific index has been visited*/
					int offset /*the current letter to look for in the word*/, 
					int prevCubePos /*the previous letter index in the cube*/)
{
	// return true if no more letter to look up
	if (offset >= int(word.length()))
		return true;
	char currentChar = word[offset];
	// use a reference to avoid copying the whole array of indices of current letter
	auto& validPositions = cubeStat[currentChar-'a'];
	int sz = validPositions.size();
	// look up for the first character in word (indicated by invalid prevCubePos value), no need to care about checked and previous index
	if (prevCubePos < 0 || prevCubePos>63) {
		// look up through all the valid positions in the cube which hold the look up character
		for (int i = 0; i < sz; i++) {
			int temp_index = validPositions[i];
			// set checked to true after visiting this indice
			checked[temp_index] = true;
			// look up for the next character in the word
			bool res = dfsWordSearch(cubeStat, word, checked, offset + 1, temp_index);
			if (res)
				return true;				// return true if the word exists in the cube
			else							// the word does not exist starting from current position, backtrack
				checked[temp_index] = false; // set the checked to false upon backtracking
		}
	}
	// not the first look up, need to consider if checked and if neighbor
	else {
		for (int i = 0; i < sz; i++) {
			int temp_index = validPositions[i];
			// if the current index has been visited or if it is not neighbor of previous index, skip this index
			if (checked[temp_index] || !isNeighbors[prevCubePos][temp_index])
				continue;
			checked[temp_index] = true;
			bool res = dfsWordSearch(cubeStat, word, checked, offset + 1, temp_index);
			if (res)
				return true;
			else
				checked[temp_index] = false;
		}
	}
	return false;
}

// the searchOneWord function provides the method to check if a word exist in a cube
bool searchOneWord(std::vector<std::vector<int>>& cubeStat, std::string & word, vector<bool>& checked)
{
	// reset the checked array before the search
	resetChecked(checked);
	// start the search from word position 0 with a previous cube index -1;
	return dfsWordSearch(cubeStat, word, checked, 0, -1);
}

// the searchAllWords function calcuates the number of words appearing in a cube
int searchAllWords(std::vector<std::vector<int>>& cubeStat, std::vector<bool>& checked)
{
	int resultCount = 0, numberOfWords = words.size();
	for (int wordNumber = 0; wordNumber < numberOfWords; wordNumber++) {
		// only make a search is the word is coverable by the cube
		if (coverable(cubeStat, wordCharCounts[wordNumber])) {
			resetChecked(checked);
			if (searchOneWord(cubeStat, words[wordNumber], checked))
				resultCount++;       // increment the result count if the word exists in the cube
		}
	}
	return resultCount;            // return the number of words existing in the cube.
}

// the searchForCubes function calculates the number of words for a group of cubes
void searchForCubes(int startIndex, int endIndex)
{
	// create the checked array which stores if an index has been visited
	vector<bool> checked(64);
	// search for each cube and update the number of existing words
	for (int i = startIndex; i < endIndex; i++) {
		cubeWordCount[i] = searchAllWords(cubeCharCounts[i], checked);
	}
	return;
}