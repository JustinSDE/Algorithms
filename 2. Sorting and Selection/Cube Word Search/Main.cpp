#include "file processing.h"
#include "word search.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// global variables shared by different modules
vector<map<char, int>> wordCharCounts;
vector<vector<vector<int>>> cubeCharCounts;
vector<string> words;
vector<int> cubeWordCount;
vector<vector<bool>> isNeighbors;

int main(int argc, char* argv[]) {
	auto start = chrono::steady_clock::now();  // start timing

	// tell user what is going wrong in the input command
	if (argc < 3) {
		cerr << "Three input commands required:\n \t executable [cubes.txt] [words.txt]\n";
		exit(1);
	}

	// process the cube.txt file
	processCubes(argv[1]);
	// get the total number of cubes
	int numberOfCubes = int(cubeCharCounts.size());

	//process the words.txt file
	processWords(argv[2]);

	// initialize the isNeighbors[64][64] 2D array structure for fast checking of neighboring indices
	initializeNeighbors(isNeighbors);
	// resize the output array that stores the counts of words in each cube to make sure it fits
	cubeWordCount.resize(numberOfCubes);

	// the number of concurrent threads 
	const int numberOfThread = 1;
	// divide the cubes into bins, each bin is calculated by one concurrent thread
	vector<int> bins;
	for (int i = 0; i <= numberOfThread; i++) {
		bins.push_back(numberOfCubes*i / numberOfThread);
	}

	// create the threads to run the calculation
	thread threads[numberOfThread];
	for (int i = 0; i < numberOfThread; i++) {
		threads[i] = thread(searchForCubes, bins[i], bins[i + 1]);
	}

	// wait until all threads have finished calculation
	for (int i = 0; i < numberOfThread; i++) {
		threads[i].join();
	}

	// output the result
	for (int i = 0; i < numberOfCubes; i++)
		cout << cubeWordCount[i] << endl;

	// output the total time used in executation
	cout << "scored " << numberOfCubes << " cubes with dimension 4 in ";
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration<double, ratio<1, 1>>(diff).count() << " second with Shiliang's design" << endl;
}
