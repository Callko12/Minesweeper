/*
 *
 * Minesweeper, Attempt 1
 * 5/7/14
 * Kendra Callwood
 * C++
 *
 * Should be implemented as an array for efficiency
 * This version completed: 
 *
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

#include "MSNode.h"

int row;
int col;

// build/show visual field
void show(MSNode ** A) {
	cout << "  ";
	for (int j=0; j<col; j++) {
			cout.width(5);
			cout << j;
		} cout << endl;
	for (int i = 0; i<row; i++) {
		cout << i << "  ";
		for (int j=0; j<col; j++) {
			cout.width(3);
			cout << "| " << A[i][j].symbol << " ";
		}
		cout << "|" << endl;
		cout << "   ";
		for (int j=0; j<col; j++) {
			cout.width(5);
			cout << "-----";
		}
		cout << endl;
	} cout << endl;
}

void update (MSNode ** A, int i, int j) {
// If any surrounding spots are bombs, up count

	if (A[i][j].seen == true) {
		return;
	}

	A[i][j].seen = true;

	if ((i+1)<row && (j>0) && A[i+1][j-1].xplode == true) { A[i][j].count++;
 } 
	if ((i+1)<row && A[i+1][j].xplode == true) { A[i][j].count++; }
	if ((i+1)<row && (j+1)<col && A[i+1][j+1].xplode == true) { A[i][j].count++; }
	if ((j+1)<col && A[i][j+1].xplode == true) A[i][j].count++;
	if ((i>0) && (j+1)<col && A[i-1][j+1].xplode == true) { A[i][j].count++;
 }
	if ((i>0) && A[i-1][j].xplode == true) A[i][j].count++;
	if ((i>0) && (j>0) && A[i-1][j-1].xplode == true) { A[i][j].count++; }
	if ((j>0) && A[i][j-1].xplode == true) { A[i][j].count++; }


	if (A[i][j].count == 0) {
		A[i][j].symbol = ' ';
		if ((i+1)<row && (j>0)) { update(A,i+1,j-1); }
		if ((i+1)<row) { update(A,i+1,j); }
		if ((i+1)<row && (j+1)<col) { update(A,i+1,j+1); }
		if ((j+1)<col) { update(A,i,j+1); }
		if ((i>0) && (j+1)<col) { update(A,i-1,j+1); }
		if ((i>0)) { update(A,i-1,j); }
		if ((i>0) && (j>0)) { update(A,i-1,j-1); }
		if ((j>0)) { update(A,i,j-1); }
	}
	else { 
		int a = A[i][j].count;
		stringstream b;
		b << a;
		A[i][j].symbol = b.str(); }
}

// For memory error
void error_and_exit() {
	cout << "Failure to allocate memory!"  << endl << endl;
}

bool completed (MSNode ** A) {
	bool comp;
	for (int i = 0; i<row; i++) {
		for (int j=0; j<col; j++) {
			 if (A[i][j].seen == false) {
				return false;
			}
		}
	}
	return true;
}


int main () {

	int bombNum;

	cout << "Number of rows: " << flush;
	cin >> row;
	cout << "Number of columns: " << flush;
	cin >> col;
	cout << "Number of bombs: " << flush;
	cin >> bombNum;

	if (bombNum >= (row*col)) {
		cout << "Illegal board" << endl;
		return 0;
	}

	int addyCount = 0;


	// build logical field
	MSNode ** A;

	A = new(nothrow) MSNode * [row];
	if (A == NULL) error_and_exit();
	for (int i=0; i<row; i++) {
		A[i] = new (nothrow) MSNode [col];
		if (A[i] == NULL) error_and_exit();
	}

	// initialize every block
	for (int i = 0; i<row; i++) {
		for (int j=0; j<col; j++) {
			A[i][j].count = 0;
			A[i][j].symbol = '*';
			A[i][j].xplode = false;
			A[i][j].seen = false;
			A[i][j].addy = addyCount;
			addyCount++;
		}
	}
	addyCount = 0;	

	// Places bombs in random spots
	srand (time(NULL));
	for (int x=0; x<bombNum; x++) {
		int bomb = rand() % (row*col);
		for (int i = 0; i<row; i++) {
			for (int j=0; j<col; j++) {
				if (A[i][j].addy == bomb) {
					if (A[i][j].xplode != true) {
						A[i][j].xplode = true;
						A[i][j].seen = true;
					}
					else {x=x-1;}

					j = col; i = row;
				}
			}
		}
	} cout << endl;


	// Here starts the actual game loop
	show(A);

	do {
	int a,b,x,y;
	string c;
		cout << "Choose a spot: " << flush;
		cin >> c;
		if (c == "quit") {		// Fix for illegal string  input
			cout << "Game Ended" << endl;
			return 0;
		}
		x = atoi(c.c_str());
		cout << x << " " << endl;
		cin >> c;
		y = atoi(c.c_str());
		cout << y<< endl;

		if (x == 54 && y == 60) {	// Gets new coodinates to flag
			cin >> c;
			x = atoi(c.c_str());
			cin >> c;
			y = atoi(c.c_str());
			cout << x << " " << y << endl;
			A[y][x].symbol = '?';
		}

		else if (x<0 || y<0 || x>=col || y>=row) {	
		cin.ignore(1000, '\n');
			cout << "Illegal Input. To keep playing, enter legal coordinates.  " << endl;
		
		}

		else if (A[y][x].xplode == true) {
			cout << "YOU LOSE!" << endl;

			for (int i = 0; i<row; i++) {
				for (int j=0; j<col; j++) {
					if (A[i][j].xplode) {
						A[i][j].symbol = 'X';
					}
				}
			}

			show(A);
					return 0;
			}
	
		else if (A[y][x].seen == true ){
			cout << "Already seen, choose again" << endl;
		}
		// If any surrounding spots are bombs, up count
		else update(A,y,x);

		if (!completed(A)) show(A);

	} while (!completed(A));

	for (int i = 0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if (A[i][j].xplode) {
				A[i][j].symbol = 'X';
			}
		}
	}

	show(A);
	cout << "Well Done!" << endl << endl;

}
