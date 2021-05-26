/*
Syed Muhammad Shehroz Ali
L17-6334 CS-D
Assignment 4
Minesweeper
*/


#include<iostream>
#include<ctime>
#include<Windows.h>
#include<cstdlib>
using namespace std;

const int Row = 10, Cols = 10;

// Place mine Function creates random number of mine and places them in random location
void Place_Mines(int Array[][Cols], int Rows, int Cols, int &Number_of_mines);
// To make game efficent Count_Neighboring_Mines fuction finds all the mines and increments the Neighboring 8 cells around it
void Count_Neighboring_Mines(int Array[][Cols], int Rows, int Cols);
// Display_board function Displays the board and the cell that user has revaled
void Display_board(int Array[][Cols], int Array2[][Cols],int Array3[][Cols]);
// play_game fuction implements the game logics and rule  
void play_game(int Array[][Cols], int Array2[][Cols], int Array3[][Cols], int &Number_of_mines, bool &game_Over, bool &game_won);
// I have Modified the PrintXY function given in the Assignment to fit my requirements
// PrintXY function  lets you print colours in background 
void PrintXY(bool check, int color);


// The game is lost when user open a cell containing a mine and game is won when all the cell containing mines are flaged
// A flaged cell can be Unflaged by selecting the flag option and selecting the already flaged cell 
int main() {

	int Setup_board[Row][Cols] = { 0 };
	int Revealed[Row][Cols] = { 0 };
	int Flaged[Row][Cols] = { 0 };
	bool game_over = false,game_won=false;
	int Number_of_mines;

	Place_Mines(Setup_board, Row, Cols, Number_of_mines);
	Count_Neighboring_Mines(Setup_board, Row, Cols);
	Display_board(Setup_board, Revealed,Flaged);

	while (game_over == false && game_won == false)
	{
		play_game(Setup_board, Revealed, Flaged, Number_of_mines, game_over, game_won);
		Display_board(Setup_board, Revealed, Flaged);
	}

	if (game_over == true)
	{
		cout << "KABOOM! You opened a mine and Died\n"<<"       Game over!\n";
	}
	else if (game_won == true)
	{
		cout << "You Correctly Flaged all the mines\n"<<"       Game won!\n";
	}
	system("pause");
}

void Place_Mines(int Array[][Cols], int Rows, int Cols, int &Number_of_mines) {


	int tempCol = 0, tempRow = 0;

	srand((int)time(0));

	// Generating random Number of mines
	Number_of_mines = rand() % (15 - 10 + 1) + 10;

	for (int i = 1; i <= Number_of_mines; i++)
	{

		tempRow = (rand() % 10);
		tempCol = (rand() % 10);

		// if a mine already exist at that location loop runs again to find a new location to place that mine
		if (Array[tempRow][tempCol] != -1)
		{
			Array[tempRow][tempCol] = -1;
		}
		else
		{
			i--;
		}
	}

}


void Count_Neighboring_Mines(int Array[][Cols], int Rows, int Cols) {
	// The following Ifs Validates and increments the cell around a mine given that the cell being incremented is not a mine
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			if (Array[i][j] == -1)
			{
				if (i - 1 >= 0 && j - 1 >= 0 && Array[i - 1][j - 1] != -1)
				{
					Array[i - 1][j - 1]++;
				}
				if (i - 1 >= 0 && j >= 0 && Array[i - 1][j] != -1)
				{
					Array[i - 1][j]++;
				}
				if (i - 1 >= 0 && j + 1 < Cols && Array[i - 1][j + 1] != -1)
				{
					Array[i - 1][j + 1]++;
				}
				if (j - 1 >= 0 && Array[i][j - 1] != -1)
				{
					Array[i][j - 1]++;
				}
				if (j + 1<Cols && Array[i][j + 1] != -1)
				{
					Array[i][j + 1]++;
				}
				if (i + 1<Rows && j - 1 >= 0 && Array[i + 1][j - 1] != -1)
				{
					Array[i + 1][j - 1]++;
				}
				if (i + 1<Rows && Array[i + 1][j] != -1)
				{
					Array[i + 1][j]++;
				}
				if (i + 1<Rows && j + 1<Cols && Array[i + 1][j + 1] != -1)
				{
					Array[i + 1][j + 1]++;
				}
			}
		}
	}

}


void Display_board(int Array[][Cols],int Array2[][Cols], int Array3[][Cols]) {
	system("CLS");
	
	cout << "  ---------------Mine Sweeper----------------" << endl;
	cout << endl;
	cout << "     a   b   c   d   e   f   g   h   i   j";
	cout << endl;
	cout << endl << "   ";
	// the following lines of code Displays and flags the Cells that user had opted to reveal and flag
	PrintXY(1, 112);
	for (int i = 0; i < 41; i++)
	{
		cout << "-";
	}
	cout << endl;
	PrintXY(0, 0);
	for (int i = 0; i < Row; i++)
	{
		cout << " " << i << " ";
		PrintXY(1, 112);
		cout << "|";
		for (int j = 0; j < Cols; j++)
		{
			if (Array[i][j] == -1 && Array2[i][j]==1)
			{
				cout << " " << "*" << " |";
			}
			else if (Array2[i][j] == 1 && Array3[i][j] == 0)
			{
				cout << " " << Array[i][j]<<" |";
			}
			else if (Array3[i][j]==1)
			{
				PrintXY(1, 192);
				cout << " " << "F" << " ";
				PrintXY(1, 112);
				cout << "|";
			}
			else if (Array2[i][j]==0 && Array3[i][j]==0)
			{
				cout << " " << " " << " |";
			}
		}
		PrintXY(0, 0);
		cout << endl << "   ";
		PrintXY(1, 112);
		for (int i = 0; i < 41; i++)
		{
			cout << "-";
		}
		cout << endl;
		PrintXY(0, 0);
	}


	cout <<endl;
}




void play_game(int Array[][Cols],int Array2[][Cols], int Array3[][Cols], int &Number_of_mines, bool &game_Over, bool &game_won) {
	char Input_Char,col;
	int row = 0,col_Number=0,mines_flaged=0;
	cout << "Input o to open a Cell or F to Flag a Cell: ";
	do
	{
		cin>>Input_Char;
		if (Input_Char!='O' && Input_Char!='o'&& Input_Char!='f' && Input_Char!='F')
		{
			cout << "You entered an invalid input please re-enter the correct input: ";
		}
	} while (Input_Char != 'O' && Input_Char != 'o' && Input_Char != 'f' && Input_Char != 'F');

	if (Input_Char == 'o' || Input_Char == 'O')
	{
		cout << "Enter Row Number: ";
		do
		{
			cin >> row;
			// This check Prevents the user from entering an invalid datatype and preventing an infinite loop 
			while (cin.fail())
			{
				cout<<"You entered an lnvalid Row Number, please enter a valid Row Number: ";
				cin.clear();
				cin.ignore();
				cin >> row;
			}
			if (row < 0 || row>9)
			{
				cout << "you Entered an incorrect row number please re-enter: ";
			}
		} while (row < 0 || row>9);

		cout << "Enter column Alphabet (lower case): ";

		do
		{
			cin >> col;
			if (col != 'a' && col != 'b' && col != 'c' && col != 'd' && col != 'e' && col != 'f' && col != 'g' && col != 'h' && col != 'i' && col != 'j')
			{
				cout << "you Entered an invalid column Alphabet please re-enter: ";
			}
		} while (col != 'a' && col != 'b' && col != 'c' && col != 'd' && col != 'e' && col != 'f' && col != 'g' && col != 'h' && col != 'i' && col != 'j');


		switch (col)
		{
		case 'a': col_Number = 0;
			break;
		case 'b': col_Number = 1;
			break;
		case 'c': col_Number = 2;
			break;
		case 'd': col_Number = 3;
			break;
		case 'e': col_Number = 4;
			break;
		case 'f': col_Number = 5;
			break;
		case 'g': col_Number = 6;
			break;
		case 'h': col_Number = 7;
			break;
		case 'i': col_Number = 8;
			break;
		case 'j': col_Number = 9;
			break;

		}


		if (Array3[row][col_Number]==1)
		{
			cout << "The Cell you are trying to open is flaged, cannot open it untill its unflaged\n";
			system("pause");
		}
		else if (Array[row][col_Number] !=0 && Array[row][col_Number]!=-1)
		{
			Array2[row][col_Number] = 1;
		}
	else if (Array[row][col_Number] == 0)
		{
			Array2[row][col_Number] = 1;
			if (row - 1 >= 0 && col_Number - 1 >= 0)
			{
				Array2[row - 1][col_Number - 1]=1;
			}
			if (row - 1 >= 0 && col_Number >= 0)
			{
				Array2[row - 1][col_Number]=1;
			}
			if (row - 1 >= 0 && col_Number + 1 < Cols)
			{
				Array2[row - 1][col_Number + 1]=1;
			}
			if (col_Number - 1 >= 0)
			{
				Array2[row][col_Number - 1]=1;
			}
			if (col_Number + 1<Cols)
			{
				Array2[row][col_Number + 1]=1;
			}
			if (row + 1<Row && col_Number - 1 >= 0)
			{
				Array2[row + 1][col_Number - 1]=1;
			}
			if (row + 1<Row)
			{
				Array2[row + 1][col_Number]=1;
			}
			if (row + 1<Row && col_Number + 1<Cols)
			{
				Array2[row + 1][col_Number + 1]=1;
			}
		}

		else if (Array[row][col_Number]==-1 && Array3[row][col_Number]==0)
		{
			game_Over = true;
			for (int i = 0; i < Row; i++)
			{
				for (int j = 0; j < Cols; j++)
				{
					if (Array[i][j]==-1)
					{
						Array2[i][j] = 1;
					}
				}
			}
		}
	}
			
	if (Input_Char == 'f' || Input_Char == 'F')
	{
		cout << "Enter Row Number: ";
		do
		{
			cin >> row;
			while (cin.fail())
			{
				//This check Prevents the user from entering an invalid datatype and preventing an infinite loop
				cout << "You entered a Invalid Row Number, please enter a valid row Number: ";
				cin.clear();
				cin.ignore();
				cin >> row;
			}
			if (row < 0 || row>9)
			{
				cout << "you Entered an incorrect row number please re-enter: ";
			}
		} while (row < 0 || row>9);

		cout << "Enter column Alphabet (lower case): ";

		do
		{
			cin >> col;
			if (col != 'a' && col != 'b' && col != 'c' && col != 'd' && col != 'e' && col != 'f' && col != 'g' && col != 'h' && col != 'i' && col != 'j')
			{
				cout << "you Entered an invalid column Alphabet please re-enter: ";
			}
		} while (col != 'a' && col != 'b' && col != 'c' && col != 'd' && col != 'e' && col != 'f' && col != 'g' && col != 'h' && col != 'i' && col != 'j');


		switch (col)
		{
		case 'a': col_Number = 0;
			break;
		case 'b': col_Number = 1;
			break;
		case 'c': col_Number = 2;
			break;
		case 'd': col_Number = 3;
			break;
		case 'e': col_Number = 4;
			break;
		case 'f': col_Number = 5;
			break;
		case 'g': col_Number = 6;
			break;
		case 'h': col_Number = 7;
			break;
		case 'i': col_Number = 8;
			break;
		case 'j': col_Number = 9;
			break;

		}
		if (Array2[row][col_Number]==1)
		{
			cout << "The Cell you are trying to flag is already reaveled therefore cant flag it\n";
			system("pause");
		}
		else if (Array3[row][col_Number]==1)
		{
			Array3[row][col_Number] = 0;
		}
		else
		{
			Array3[row][col_Number] = 1;
		}
		
	}
	// This loop Checks if the Array_for how many mine have been flaged, if all the mines are flaged then the game is won
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			if (Array[i][j]==-1 && Array3[i][j]==1)
			{
				mines_flaged++;
			}
		}
	}
	if (Number_of_mines - mines_flaged ==0)
	{
		game_won = true;
	}
	mines_flaged = 0;
}

void PrintXY(bool check, int color) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	if (check == 1) {
		SetConsoleTextAttribute(h, color);
	}
	else if (check == 0)
	{
		SetConsoleTextAttribute(h, 7);
	}
}



