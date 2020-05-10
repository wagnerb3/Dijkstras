/*
 * Graph.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: Brett Wagner
 */

#include "Graph.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
Graph::Graph(int n, int first, string vertexnames[]) {
	numOfVerts = n;
	start = first;
	dataArr = new string[n];
	for (int i = 0; i < n; i++) {
		dataArr[i] = vertexnames[i];
	}
	distances = new int[n];
	adjMatrix = new int*[n];
	visited = new bool[n];
	prev = new int[n];
	for (int i = 0; i < n; i++) {
		adjMatrix[i] = new int[n];
	}
	genGraph();
	for (int i = 0; i < n; i++) {
		distances[i] = 1000000;
		visited[i] = false;
	}
	printAdjMat();
	dijkstra();
	printPath(1);
}
void Graph::dijkstra() {
	distances[start] = 0;
	visited[start] = true;
//Step 1:
//set the distance to the starting vertex to 0 and set
//the visited array to true for the start index;
	for (int i = 0; i < numOfVerts; i++) {
		distances[i] = adjMatrix[start][i];
		if (i == start) {
			prev[i] = -1;
		} else {
			prev[i] = start;
		}
	}
//Step 2:
// Initialize the distances to the cost of going to each node from the
//start index (this is done using the adjacency matrix)
	bool nComplete = true;
	while (nComplete) {
		for (int i = 0; i < numOfVerts; i++) {
			if (visited[i] == false) {
				break;
			}
			if (i == numOfVerts && visited[i] == true) {
				nComplete = false;
			}
		}
		int min = minDistance();
		if (min == -1) {
			break;
		}
		setDistances(min);
		printInfoSoFar();
	}
//Step 3:
//loop until every vertex has been visited, calling the methods
//minDistance to find the next unvisited vertex with the minimum
//distance, and then calling setDistances method for every vertex
//to update distances for the unvisited vertices. (I called printInfoSoFar()
//in this loop to see the progress of the algorithm)
}
void Graph::setDistances(int latestVert) { //8 pts
	for (int i = 0; i < numOfVerts; i++) {
		if (distances[latestVert] + adjMatrix[latestVert][i] < distances[i]) {
			distances[i] = distances[latestVert] + adjMatrix[latestVert][i];
			prev[i] = latestVert;
		}
	}
	// This method updates the distances array with the costs being
	//updated to either their cost so far, or the cost of
	//traveling through the recently visited vertex + the cost of
	//traveling from that vertex to the new vertex (whichever is the
	//minimum). If the minimum is through the recently visited vertex,
	//then update the previous array so that it holds the latest visited
	//vertex's index number
}
int Graph::minDistance() { //8 pts
	int dex = -1;
	int min = 100000;
	for (int i = 0; i < numOfVerts; i++) {
		if (visited[i] == false) {
			if (distances[i] < min) {
				min = distances[i];
				dex = i;
			}
		}
	}
	visited[dex] = true;
	return dex;
	//This method finds the next unvisited vertex with the minimum
//distance.
//Once the minimum is found (along with its index in the distance
//array), the visited array at that index is set to True and that index is
//returned from this method.
}
//This method prints out the final path from the starting vertex to the end vertex,
//which is the index passed into this method
void Graph::printPath(int end) {
	int *temppath = new int[numOfVerts];
	int ct = 0;
	temppath[ct] = end;
	int dist = distances[end];
	int prevnode = prev[end];
	ct++;
	while (prevnode != start) {
		temppath[ct] = prevnode;
		prevnode = prev[prevnode];
		ct++;
	}
	temppath[ct] = start;
	cout << "Shortest Path: " << dist << endl;
	for (int i = ct; i >= 0; i--) {
		cout << dataArr[temppath[i]] << "(" << temppath[i] << ")->";
	}
	cout << endl;
}
//This method prints out the adjacency matrix with the distances
void Graph::printAdjMat() {
	cout << "********************************************" << endl
			<< "Adjacency Matrix (Graph):" << endl;
	for (int i = 0; i < numOfVerts; i++) {
		for (int j = 0; j < numOfVerts; j++) {
			cout << adjMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "********************************************" << endl;
}
//This method prints out the information in the distance array, the previous array, and the visited array
//It is called so you can watch the progress of the construction of the shortest path
void Graph::printInfoSoFar() {
	cout << "\t";
	for (int i = 0; i < numOfVerts; i++) {
		cout << "\t" << i;
	}
	cout << endl;
	cout << "Dist:\t";
	for (int i = 0; i < numOfVerts; i++) {
		cout << "\t" << distances[i];
	}
	cout << endl;
	cout << "Prev:\t";
	for (int i = 0; i < numOfVerts; i++) {
		cout << "\t" << prev[i];
	}
	cout << endl;
	cout << "Visited:";
	for (int i = 0; i < numOfVerts; i++) {
		cout << "\t" << visited[i];
	}
	cout << endl;
	cout << endl;
}
//This method generates the distances for the graph. My way of representing vertices that are
//not connected was to set those distances to 100 (it could just as easily been 1000000, but
//that didn’t look as nice when I printed out the adjacency matrix)
void Graph::genGraph() {
	srand(time(NULL));
	for (int i = 0; i < numOfVerts; i++) {
		for (int j = 0; j < numOfVerts; j++) {
			if (i == j) {
				adjMatrix[i][j] = 0;
			} else {
				adjMatrix[i][j] = rand() % 9 + 1;
				if (adjMatrix[i][j] == 9) {
					adjMatrix[i][j] = 100;
				}
			}
		}
	}
}

