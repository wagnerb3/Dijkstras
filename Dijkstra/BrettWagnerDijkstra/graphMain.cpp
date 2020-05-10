/*
 * graphMain.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: Brett Wagner
 */

#include "Graph.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main() {
	srand(time(NULL));
	string names[12] = { "Albany", "Buffalo", "Chicago", "Detroit", "Encino",
			"Fargo", "Gotham", "Houston", "Indianapolis", "Jackson", "Kenosha",
			"Lewiston" };
	int size = 4;
	Graph g1(size, 3, names);
	cout << endl
			<< "**********************************************************************"
			<< endl;
	size = 7;
	Graph g2(size, 6, names);
	cout << endl
			<< "**********************************************************************"
			<< endl;
	size = 12;
	Graph g3(size, 11, names);
}

