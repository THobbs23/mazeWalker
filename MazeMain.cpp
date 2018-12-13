//				Maze Program
//				CSC 412
//				Tyler Hobbs
//				30 September 2018

#include<cstdlib>
#include<fstream>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<cstring>

using namespace std;

struct node {

	char nodeState;
	int nodeCoord;
	int nodeNum;
	vector<string> path;

};

queue <node> BFSQueue;
stack <node> DFSStack;

bool loadMaze(char mazeAry[][10], map<int,char> &theMap) {
	ifstream inFile;
	string filePath;
	
	system("CLS");
	cout << endl << "\tSpecify the path to your maze file (or filename if in the directory): ";
	cin >> filePath;
	
	inFile.open(filePath.c_str());

	if (!inFile) {
		// file not found
		return false;
	}
	else {
		
		for (int y = 0; y < 10; y++) {
			
			for (int x = 0; x < 10; x++) {
				//mazeAry[x][y] cartesian style, also reads into the map for comparisons

				inFile >> mazeAry[x][y];

				theMap[(x * 10) + y] = mazeAry[x][y];

			}
		}

		inFile.close();
	}


	return true;

}

void displayMaze(char mazeAry[][10]) {

	// spits out a formatted maze from the array

	system("CLS");

	cout << "\tMaze read in from file";

	for (int y = 0; y < 10; y++) {

		cout << endl << endl << "\t";

		for (int x = 0; x < 10; x++) {

			cout << mazeAry[x][y] << "    ";

		}
	}

}

bool checkVisit(map<int, bool> visited, int coord) {

	// checks if the coordinate has been visited

	// coord is (x*10)+y
	
	auto it = visited.begin();

	it = visited.find(coord);

	if (it != visited.end()) {
		// doesn't get to the end, found in map
		return true;
	}
	else {
		// gets to the end, not found in map
		return false;
	}

}

int findEntry(char mazeAry[][10]) {

	// looks along the left wall for the 'E'ntrance, probably crashes if the entrance isn't on the left wall

	int entry = -1;

	for (int y = 0; y < 10;  y++) {
		if (mazeAry[0][y] == 'E') {
			entry = y;
		}
	}

	return entry;

}

void checkChildrenBFS(map<int,char> maze, map<int, bool> &visited, node current, int x, int y) {

	int newCoord, coord, newX, newY ;
	string pathString;


	// checks for children clockwise


		if (!checkVisit(visited, current.nodeCoord-1) && (maze[current.nodeCoord -1] == 'P' || maze[current.nodeCoord-1] == 'X')) { // check up (y-1) for a move
																	// if up hasn't been visited and is a path or exit
			//cout << "check up";


			node newNode;
			// creates new coordinates
			newX = x;
			newY = y - 1;
			newCoord = (newX * 10) + newY;

			// makes the string path to the node

			pathString = "";
			pathString += " ";
			pathString += to_string(newX);
			pathString += ",";
			pathString += to_string(newY);
			pathString += " ->";

			vector<string> temp;

			temp = current.path;

			temp.push_back(pathString);

			newNode.path = temp;

			newNode.nodeState = maze[newCoord];
			newNode.nodeCoord = newCoord;
			newNode.nodeNum = current.nodeNum++;

			BFSQueue.push(newNode);

			visited[newCoord] = true;

		}

		if (!checkVisit(visited, current.nodeCoord+10) && (maze[current.nodeCoord + 10] == 'P' || maze[current.nodeCoord +10] == 'X')) { // check right (x+1) for a move
																	// if right hasn't been visited and is a path or exit

			//cout << "check right";

			node newNode;

			// create new coordinates

			newX = x + 1;
			newY = y;
			newCoord = (newX * 10) + newY;

			// string for the node path

			pathString = "";
			pathString += " ";
			pathString += to_string(newX);
			pathString += ",";
			pathString += to_string(newY);
			pathString += " ->";

			// adds in state, coordinates, path string and node number of the new node

			vector<string> temp;

			temp = current.path;

			temp.push_back(pathString);

			newNode.path = temp;

			newNode.nodeState = maze[newCoord];
			newNode.nodeCoord = newCoord;
//			newNode.path.push_back(pathString);
			newNode.nodeNum = current.nodeNum++;

			// pushes the node on the queue and marks it as visited

			BFSQueue.push(newNode);

			visited[newCoord] = true;
		}

		if (!checkVisit(visited, current.nodeCoord+1) && (maze[current.nodeCoord + 1] == 'P' || maze[current.nodeCoord + 1] == 'X')) { // check down (y+1) for a move
																	// if down hasn't been visited and is a path or exit

			//cout << "check down";

			node newNode;

			// new coordinates

			newX = x;
			newY = y + 1;
			newCoord = (newX * 10) + newY;

			// string for the node path

			pathString = "";
			pathString += " ";
			pathString += to_string(newX);
			pathString += ",";
			pathString += to_string(newY);
			pathString += " ->";

			// adds state, coordinates, path string and node number to the new node

			vector<string> temp;

			temp = current.path;

			temp.push_back(pathString);

			newNode.path = temp;


			newNode.nodeState = maze[newCoord];
			newNode.nodeCoord = newCoord;
//			newNode.path.push_back(pathString);
			newNode.nodeNum = current.nodeNum++;

			// pushes new node to the queue and marks it as visited

			BFSQueue.push(newNode);

			visited[newCoord] = true;

		}

		if (!checkVisit(visited, current.nodeCoord-10) && (maze[current.nodeCoord - 10] == 'P' || maze[current.nodeCoord - 10] == 'X')) { // check left (x-1) for a move
																	// if left hasn't been visited and is a path or exit

			//cout << "check left";

			node newNode;

			// makes new coordinates

			newX = x - 1;
			newY = y;
			newCoord = (newX * 10) + newY;

			// string for the node path

			pathString = "";
			pathString += " ";
			pathString += to_string(newX);
			pathString += ",";
			pathString += to_string(newY);
			pathString += " ->";

			// adds state, coordinates, path string, node number to new node

			vector<string> temp;

			temp = current.path;

			temp.push_back(pathString);

			newNode.path = temp;

			newNode.nodeState = maze[newCoord];
			newNode.nodeCoord = newCoord;
//			newNode.path.push_back(pathString);
			newNode.nodeNum = current.nodeNum++;

			// pushes new node and marks it as visited

			BFSQueue.push(newNode);

			visited[newCoord] = true;

		}

}

void checkChildrenDFS(map<int, char> maze, map<int, bool> &visited, node current, int x, int y) {

	node newNode;
	int newCoord, coord, newX, newY;
	string pathString;

	// checks for children clockwise


	if (!checkVisit(visited, current.nodeCoord - 1) && (maze[current.nodeCoord - 1] == 'P' || maze[current.nodeCoord - 1] == 'X')) { // check up (y-1) for a move
																																	 // if up hasn't been visited and is a path or exit
																																	 //cout << "check up";


		node newNode;

		// new coordinates

		newX = x;
		newY = y - 1;

		newCoord = (newX * 10) + newY;

		// string for node path

		pathString = "";
		pathString += " ";
		pathString += to_string(newX);
		pathString += ",";
		pathString += to_string(newY);
		pathString += " ->";

		// adds state, coordinates, path string, node number to new node

		vector<string> temp;

		temp = current.path;

		temp.push_back(pathString);

		newNode.path = temp;
		
		newNode.nodeState = maze[newCoord];
		newNode.nodeCoord = newCoord;
//		newNode.path.push_back(pathString);
		newNode.nodeNum = current.nodeNum++;

		// pushes node to stack, marks it visited

		DFSStack.push(newNode);

		visited[newCoord] = true;

	}

	if (!checkVisit(visited, current.nodeCoord + 10) && (maze[current.nodeCoord + 10] == 'P' || maze[current.nodeCoord + 10] == 'X')) { // check right (x+1) for a move
																																		// if right hasn't been visited and is a path or exit

																																		//cout << "check right";

		node newNode;

		// makes new coordinates

		newX = x + 1;
		newY = y;
		newCoord = (newX * 10) + newY;

		// string for the node path

		pathString = "";
		pathString += " ";
		pathString += to_string(newX);
		pathString += ",";
		pathString += to_string(newY);
		pathString += " ->";

		// adds state, coordinates, path string, node number to new node

		vector<string> temp;

		temp = current.path;

		temp.push_back(pathString);

		newNode.path = temp;

		newNode.nodeState = maze[newCoord];
		newNode.nodeCoord = newCoord;
//		newNode.path.push_back(pathString);
		newNode.nodeNum = current.nodeNum++;

		// pushes node to stack, marks it visited

		DFSStack.push(newNode);

		visited[newCoord] = true;
	}

	if (!checkVisit(visited, current.nodeCoord + 1) && (maze[current.nodeCoord + 1] == 'P' || maze[current.nodeCoord + 1] == 'X')) { // check down (y+1) for a move
																																	 // if down hasn't been visited and is a path or exit

																																	 //cout << "check down";

		node newNode;

		// new coordinates

		newX = x;
		newY = y + 1;
		newCoord = (newX * 10) + newY;

		// string for node path

		pathString = "";
		pathString += " ";
		pathString += to_string(newX);
		pathString += ",";
		pathString += to_string(newY);
		pathString += " ->";

		// adds state, coordinates, path string, node number to new node

		vector<string> temp;

		temp = current.path;

		temp.push_back(pathString);

		newNode.path = temp;

		newNode.nodeState = maze[newCoord];
		newNode.nodeCoord = newCoord;
//		newNode.path.push_back(pathString);
		newNode.nodeNum = current.nodeNum++;

		// pushes new node to stack, marks it visited

		DFSStack.push(newNode);

		visited[newCoord] = true;

	}

	if (!checkVisit(visited, current.nodeCoord - 10) && (maze[current.nodeCoord - 10] == 'P' || maze[current.nodeCoord - 10] == 'X')) { // check left (x-1) for a move
																																		// if left hasn't been visited and is a path or exit

																																		//cout << "check left";

		node newNode;

		// new coordinates

		newX = x - 1;
		newY = y;
		newCoord = (newX * 10) + newY;

		// string for node path

		pathString = "";
		pathString += " ";
		pathString += to_string(newX);
		pathString += ",";
		pathString += to_string(newY);
		pathString += " ->";

		// adds state, coordinates, path string, node number to new node
		
		vector<string> temp;

		temp = current.path;

		temp.push_back(pathString);

		newNode.path = temp;

		newNode.nodeState = maze[newCoord];
		newNode.nodeCoord = newCoord;
//		newNode.path.push_back(pathString);
		newNode.nodeNum = current.nodeNum++;

		// adds new node to stack, marks it visited

		DFSStack.push(newNode);

		visited[newCoord] = true;

	}

}


void BFSMaze(char mazeAry[][10], map<int, char> maze, map<int, bool> &visited) {

	node current;
	int newCoord, coord, newX, x, newY, y;
	string pathString;

	int entrance = findEntry(mazeAry);

	newCoord = coord = newX = x = newY = 0;
	y = entrance;

	// initial string for node path

	pathString = "";
	pathString += "Entrance -> ";
	pathString += to_string(x);
	pathString += ",";
	pathString += to_string(y);
	pathString += " ->";

	// entry node initialization, marks entry visited and pushes to queue

	current.nodeNum = 1;
	current.nodeState = 'E';
	current.path.push_back(pathString);
	current.nodeCoord = (x*10)+y;

	visited[current.nodeCoord] = true;

	BFSQueue.push(current);

	while (!BFSQueue.empty()) {

		// working with the front of the queue, pop it off 

		current = BFSQueue.front();
		BFSQueue.pop();

		coord = current.nodeCoord;
		y = coord % 10;
		x = coord / 10;

	//	cout << " loop " << x << "," << y ;

		if (current.nodeState == 'X') { // check if current node is the exit
			
			// exit node string path 

			pathString = "";
			//pathString += " ";
			//pathString += to_string(x);
			//pathString += ",";
			//pathString += to_string(y);
			pathString += " Exit";

			current.path.push_back(pathString);

			// this is what i use to try to print the node path but it isn't working

			int i = 0;
			for (auto it = current.path.begin(); it != current.path.end(); it++) {
				if (i % 10 == 0)
					cout << endl << "\t";
				cout << *it ;
				i++;
			}



		}
		else {

			checkChildrenBFS(maze, visited, current, x, y);

		}

	}

}

void DFSMaze(char mazeAry[][10], map<int, char> maze, map<int, bool> &visited) {


	node current;
	int newCoord, coord, newX, x, newY, y;
	string pathString;

	int entrance = findEntry(mazeAry);

	newCoord = coord = newX = x = newY = 0;
	y = entrance;

	// initial string for node path

	pathString = "";
	pathString += "Entrance -> ";
	pathString += to_string(x);
	pathString += ",";
	pathString += to_string(y);
	pathString += " ->";

	// initialize entry node, marks visited, pushes to the stack

	current.nodeNum = 1;
	current.nodeState = 'E';
	current.path.push_back(pathString);
	current.nodeCoord = (x * 10) + y;

	visited[current.nodeCoord] = true;

	DFSStack.push(current);

	while (!DFSStack.empty()) {

		// working with the top of the stack, pop it off

		current = DFSStack.top();
		DFSStack.pop();

		coord = current.nodeCoord;
		y = coord % 10;
		x = coord / 10;

		//	cout << " loop " << x << "," << y ;

		if (current.nodeState == 'X') { // check if current node is the exit

			// exit node string path

			pathString = "";
			//pathString += " ";
			//pathString += to_string(x);
			//pathString += ",";
			//pathString += to_string(y);
			pathString += " Exit";

			current.path.push_back(pathString);

			// this doesn't work in BFS either


			int i = 0;
			for (auto it = current.path.begin(); it != current.path.end(); it++) {
				if (i % 10 == 0)
					cout << endl << "\t";
				cout << *it << " ";
				i++;
			}

			// it does print the final node though




		}
		else {

			checkChildrenDFS(maze, visited, current, x, y);

		}

	}

}

int main() {

	char Maze[10][10];
	map<int, bool> BFSVisitMap;
	map<int, bool> DFSVisitMap;
	map<int, char> mazeMap;
//	queue <node> BFSQueue;
//	stack <node> DFSStack;
	string choice = "";

	// main driver for menu choices

	do {

		cout << endl << endl << "\t1 -\t\tLoad a new Maze"; 
		cout << endl << "\t2 -\t\tDisplay the current Maze";
		cout << endl << "\t3 -\t\tBreadth First Search the current Maze";
		cout << endl << "\t4 -\t\tDepth First Search the current Maze";
		cout << endl << "\t-999 -\t\tExit the Application";

		cout << endl << endl << "\tEnter your desired selection: ";
		cin >> choice;

		if (choice == "1") {

			if (!loadMaze(Maze, mazeMap))
			{
				system("CLS");
				cout << endl << "\tFile not found!";
			}
			else {
				system("CLS");
				cout << endl << "\tMaze successfully read in!";
			}
		}
		else if (choice == "2") {
			displayMaze(Maze);
		}
		else if (choice == "3") {
			displayMaze(Maze);
			cout << endl << endl << "\tBreadth First Search of the Maze" << endl << endl;
			BFSMaze(Maze, mazeMap, BFSVisitMap);
		}
		else if (choice == "4") {
			displayMaze(Maze);
			cout << endl << endl << "\tDepth First Search of the Maze" << endl << endl;
			DFSMaze(Maze, mazeMap, DFSVisitMap);
		}
		else if (choice == "-999") {
			break;
		}
		else {
			system("CLS");
			cout << endl << "\tYou entered an invalid selection!";
			cout << endl << endl <<  "\tPlease choose a valid selection: ";
		}

	} while (choice != "-999");

	cin.get();

	return 0;
}