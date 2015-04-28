//Justin Liang
//CS165A
//MP-1
//SPRING 2013

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>
using namespace std;

struct queen
{	
	int row;
	int column;
	int numConflicts;
};
struct bestPossibleMoves
{
	int xpos;
	int ypos;
	int conflictsAtPos;
};

int numQueens = 0;
int maxMoves = 0;
queen *array;
int **board = {0};

void printBoard()
{
	for(int i = 0; i < numQueens; i++)
	{
		for(int j = 0; j < numQueens; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int** convertToBoard (queen x[])
{
	//Initialize chessboard to all 0's
	int** chessBoard = 0;
	chessBoard = new int *[numQueens];	
	for(int h = 0; h < numQueens; h++)
	{
		chessBoard[h] = new int[numQueens];
		for(int w = 0; w < numQueens; w++)
		{
			chessBoard[h][w] = 0;
		}
	}
	
	//Puts a 1 on the chessboard when there is a queen on that square
	for(int i = 0; i < numQueens; i++)
	{
		int r = array[i].row;
		int c = array[i].column;
		chessBoard[r][c] = 1;
	}
	return chessBoard;
}

int computeConflicts(int** x)
{	
	int** chessBoard = x;
	int conflicts = 0;
	for(int i = 0; i < numQueens; i++)
	{
		for(int j = 0; j < numQueens; j++)
		{
			if(chessBoard[i][j] == 1)
			{				
				//Check for row conflicts by traversing east on the board
				for(int column = j+1; column < numQueens; column++)
				{
					if(chessBoard[i][column] == 1)
					{
						conflicts++;
					}
				}
				
				//Check for diagonal conflicts by traversing south-east on the board
				int row = i+1;
				int column = j+1;
				while((row < numQueens) && (column < numQueens))
				{
					if(chessBoard[row][column] == 1)
					{
						conflicts++;
						break;
					}
					row++;
					column++;
				}
				
				//Check for diagonal conflicts by traversing south-west on the board
				row = i+1;
				column = j-1;
				while((row < numQueens) && (column >= 0))
				{
					if(chessBoard[row][column] == 1)
					{
						conflicts++;
						break;
					}
					row++;
					column--;
				}
			}
		}
	}
	return conflicts;
}

void updateQueenConflicts()
{
	int i = 0;
	while(i < numQueens)
	{
		int x = array[i].row;
		int y = array[i].column;
		array[i].numConflicts = 0;
		
		//Check for row conflicts by traversing east on the board
		for(int column = y+1; column < numQueens; column++)
		{
			if(board[x][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
		}
		//Check for row conflicts by traversing west on the board
		for(int column = y-1; column >= 0; column--)
		{
			if(board[x][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
		}
		//Check for diagonal conflicts by traversing south-east on the board
		int row = x+1;
		int column = y+1;
		while((row < numQueens) && (column < numQueens))
		{
			if(board[row][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
			row++;
			column++;
		}
		
		//Check for diagonal conflicts by traversing south-west on the board
		row = x+1;
		column = y-1;
		while((row < numQueens) && (column >= 0))
		{
			if(board[row][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
			row++;
			column--;
		}
		
		//Check for diagonal conflicts by traversing north-west on the board
		row = x-1;
		column = y-1;
		while((row >= 0) && (column >= 0))
		{
			if(board[row][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
			row--;
			column--;
		}
		
		//Check for diagonal conflicts by traversing north-east on the board
		row = x-1;
		column = y+1;
		while((row >= 0) && (column < numQueens))
		{
			if(board[row][column] == 1)
			{
				array[i].numConflicts++;
				break;
			}
			row--;
			column++;
		}
		i++;
	}
}

//Moves the queen from position x,y to a new position a,b
void moveQueen(int x, int y, int a, int b)
{
	board[x][y] = 0;
	board[a][b] = 1;
	
	for(int i = 0; i < numQueens; i++)
	{
		if(array[i].row == x && array[i].column == y)
		{
			array[i].row = a;
			array[i].column = b;
		}
	}
	updateQueenConflicts();
}

//Finds the queen with the maximum number 
//of conflicts and returns its index in the 1-d array
int findQueenWithMaxConflicts()
{
	int maxConflicts = 0;
	int indexOfQueenWithMax = 0;
	queue <int> temp;
	for(int i = 0; i < numQueens; i++)
	{		
		if(array[i].numConflicts >= array[indexOfQueenWithMax].numConflicts)
		{
			indexOfQueenWithMax = i;
			maxConflicts = array[i].numConflicts;
		}
	}
	
	// for(int i = 0; i < numQueens; i++)
	// {
		// if(array[i].numConflicts == maxConflicts)
		// {
			// temp.push(i);
		// }
	// }
	
	// int temparray[temp.size()];
	// int tempsize = temp.size();
	// for(int i = 0; i < tempsize; i++)
	// {
		// temparray[i] = temp.front();
		// temp.pop();
	// }
	
	// int random = (rand()%(tempsize-1)+1);
	return indexOfQueenWithMax;
}

void findSolution()
{
	int maxAllowed = 1;
	int k = 0;
	
	while (k < maxMoves)
	{
		int index = findQueenWithMaxConflicts();
		queue<bestPossibleMoves> q;
		for(int i = 1; i <= maxMoves; i++)
		{
			if(i >= 7)
				break;
			// int **tempBoard = board;
			// queen *tempArray = array;
			int x = array[index].row;
			int y = array[index].column;
			bestPossibleMoves b;
			
			if(x - i >= 0)
			{
				moveQueen(x,y,x-i,y);
				b.xpos = x-i;
				b.ypos = y;
				b.conflictsAtPos = array[index].numConflicts;
				q.push(b);
				moveQueen(x-i,y,x,y);
			}
			
			updateQueenConflicts();
			
			if(x + i < numQueens)
			{
				moveQueen(x,y,x+i,y);
				b.xpos = x+i;
				b.ypos = y;
				b.conflictsAtPos = array[index].numConflicts;
				q.push(b);
				moveQueen(x+i,y,x,y);
			}
			updateQueenConflicts();			
		}
		int qsize = q.size();
		bestPossibleMoves best[q.size()];
		for(int i = 0; i < qsize; i++)
		{
			best[i] = q.front();
			q.pop();
			
		}
		
		int tempConflicts = array[index].numConflicts;
		int bestX;
		int bestY;
		int x = array[index].row;
		int y = array[index].column;
		for(int i = 0; i < qsize; i++)
		{			
			if(best[i].conflictsAtPos < tempConflicts)
			{
				bestX = best[i].xpos;
				bestY = best[i].ypos;
				tempConflicts = best[i].conflictsAtPos;
			}
		}
		moveQueen(x,y,bestX,bestY);
		k = k + (abs(bestX-x));
	}
}

int main()
{
	cin >> numQueens;
	cin >> maxMoves;
	array = new queen[numQueens];
	// clock_t start, end;
	// start = clock();
	
	while(!cin.eof())
	{
		for(int i = 0; i < numQueens; i++)
		{
			cin >> array[i].row;
			array[i].row = array[i].row-1;
			cin >> array[i].column;
			array[i].column = array[i].column-1;
		}
	}
	
	board = convertToBoard(array);
	cout << "INITIAL BOARD:" << endl;
	printBoard();
	updateQueenConflicts();
	findSolution();	
	cout << endl << "FINAL BOARD:" << endl;
	printBoard();
	cout << endl;
	updateQueenConflicts();
	cout << computeConflicts(board) << endl;
	for(int i = 0; i < numQueens; i++)
	{
		cout << array[i].row << " " << array[i].column << endl;
		
	}
	// end = clock();
	// cout << "time took: " << (float(end-start)/(CLOCKS_PER_SEC/1000)) << endl;
	return 0;
}