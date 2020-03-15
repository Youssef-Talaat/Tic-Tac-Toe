// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
enum WinType { not_yet, row, column, right_diagonal, left_diagonal, no_winner };

void First_Print(char XO[3][3]);
void Reset_Array(char XO[3][3]);
void BoxtoPlace(int x, int& r, int& c);
void PlacetoBox(int& x, int r, int c);
void start_with_which(int& temp);
void X_or_O(char& var, int& temp);
bool Chech_place(const char XO[3][3], int r, int c);
void Input(char XO[3][3], int r, int c, char var);
void Print(const char XO[3][3]);
WinType Check_winner(const char XO[3][3], int r, int c, char var);
void S_Winner(WinType W, int r, int c, char var);
void M_Winner(WinType W, int r, int c, char var);
bool Play_again(int& choice);
void Single_Player_Hard(char XO[3][3], int& r, int& c, int counter, int Temp_Row, int Temp_Col);
void Single_Player_Easy(char XO[3][3], int& r, int& c, int counter, int Temp_Row, int Temp_Col);

int main()
{
	int Box, Row, Col, c_p, choice, temp, counter, Temp_Row = 9, Temp_Col = 9;
	char var, GameType, S_level;
	WinType W;
	char XO[3][3];
	cout << "This is Tic-tac-toe Game.\n";
	do
	{
		First_Print(XO);
		Reset_Array(XO);
		W = not_yet;
		cout << "Press 's' for Single-Player & 'm' for Multi-Player.\n";
		cin >> GameType;
		if (GameType == 'm' || GameType == 'M')
		{
			start_with_which(temp);
			cout << "Now enter the number of the Box.\n";
			while (W == not_yet)
			{
				X_or_O(var, temp);
				cin >> Box;
				if (Box > 0 && Box < 10)
				{
					BoxtoPlace(Box, Row, Col);
					c_p = Chech_place(XO, Row, Col);
					if (c_p == 1)
					{
						Input(XO, Row, Col, var);
						Print(XO);
					}
					else
					{
						Print(XO);
						temp++;
					}
					W = Check_winner(XO, Row, Col, var);
				}
				else
				{
					cout << "Make sure you entered the box correctly.\n";
					temp++;
				}
			}
			M_Winner(W, Row, Col, var);
		}
		else if (GameType == 's' || GameType == 'S')
		{
			cout << "Press 'h' for Hard & 'e' for Easy.\n";
			cin >> S_level;
			counter = 0;
			cout << "Now enter the number of the Box.\n";
			while (W == not_yet)
			{
				if (counter % 2 == 0)
				{
					var = 'x';
					cin >> Box;
					if (Box > 0 && Box < 10)
					{
						BoxtoPlace(Box, Row, Col);
						c_p = Chech_place(XO, Row, Col);
						if (c_p == 1)
						{
							Input(XO, Row, Col, var);
							Print(XO);
						}
						else
						{
							Print(XO);
							counter--;
						}
						W = Check_winner(XO, Row, Col, var);
					}
					else
					{
						cout << "Make sure you entered the box correctly.\n";
						counter--;
					}
				}
				else if (counter % 2 != 0)
				{
					var = 'o';
					if (S_level == 'h' || S_level == 'H')
						Single_Player_Hard(XO, Row, Col, counter, Temp_Row, Temp_Col);
					else if (S_level == 'e' || S_level == 'E')
						Single_Player_Easy(XO, Row, Col, counter, Temp_Row, Temp_Col);
					c_p = Chech_place(XO, Row, Col);
					if (c_p == 1)
					{
						Input(XO, Row, Col, var);
						Print(XO);
					}
					else
					{
						Print(XO);
						counter--;
					}
					Temp_Row = Row;
					Temp_Col = Col;
					W = Check_winner(XO, Row, Col, var);
				}
				counter++;
			}
			S_Winner(W, Row, Col, var);
		}
		else
			cout << "Make sure you entered the letter correctly.\n";
		Play_again(choice);
	} while (choice == 1);
	return 0;
}

void First_Print(char XO[3][3])
{
	XO[0][0] = '7';
	XO[0][1] = '8';
	XO[0][2] = '9';
	XO[1][0] = '4';
	XO[1][1] = '5';
	XO[1][2] = '6';
	XO[2][0] = '1';
	XO[2][1] = '2';
	XO[2][2] = '3';
	Print(XO);
}

void Reset_Array(char XO[3][3])
{
	XO[0][0] = ' ';
	XO[0][1] = ' ';
	XO[0][2] = ' ';
	XO[1][0] = ' ';
	XO[1][1] = ' ';
	XO[1][2] = ' ';
	XO[2][0] = ' ';
	XO[2][1] = ' ';
	XO[2][2] = ' ';
}

void start_with_which(int& temp)
{
	char ch;
	cout << "Do you want to start with x or o ?\n";
	temp = 10;
	while (temp != 0 && temp != 1)
	{
		cin >> ch;
		if (ch == 'x' || ch == 'X')
			temp = 0;
		else if (ch == 'o' || ch == 'O')
			temp = 1;
		else
			cout << "Make sure you entered the letter correctly.\n";
	}
}

void X_or_O(char& var, int& temp)
{
	if (temp == 2)
		temp = 0;
	if (temp == 3)
		temp = 1;
	if (temp == 0)
		var = 'x';
	else if (temp == 1)
		var = 'o';
	temp++;
}

void BoxtoPlace(int x, int& r, int& c)
{
	switch (x)
	{
	case 1:
	{
		r = 2;
		c = 0;
		break;
	}
	case 2:
	{
		r = 2;
		c = 1;
		break;
	}
	case 3:
	{
		r = 2;
		c = 2;
		break;
	}
	case 4:
	{
		r = 1;
		c = 0;
		break;
	}
	case 5:
	{
		r = 1;
		c = 1;
		break;
	}
	case 6:
	{
		r = 1;
		c = 2;
		break;
	}
	case 7:
	{
		r = 0;
		c = 0;
		break;
	}
	case 8:
	{
		r = 0;
		c = 1;
		break;
	}
	case 9:
	{
		r = 0;
		c = 2;
		break;
	}
	}
}

void PlacetoBox(int& x, int r, int c)
{
	if (r == 0 && c == 0)
		x = 7;
	else if (r == 0 && c == 1)
		x = 8;
	else if (r == 0 && c == 2)
		x = 9;
	else if (r == 1 && c == 0)
		x = 4;
	else if (r == 1 && c == 1)
		x = 5;
	else if (r == 1 && c == 2)
		x = 6;
	else if (r == 2 && c == 0)
		x = 1;
	else if (r == 2 && c == 1)
		x = 2;
	else if (r == 2 && c == 2)
		x = 3;

}

bool Chech_place(const char XO[3][3], int r, int c)
{
	if (r < 3 && c < 3)
	{
		if (XO[r][c] == ' ')
		{
			return true;
		}
		else
		{
			cout << "This place is already filled.\n";
			cout << endl;
			return false;
		}
	}
	else
	{
		cout << "Make sure you entered the box correctly.\n";
		return false;
	}
}

void Input(char XO[3][3], int r, int c, char var)
{
	XO[r][c] = var;
}

void Print(const char XO[3][3])
{
	int row, col;

	cout << endl;
	for (row = 0; row < 3; row++)
	{
		cout << "\t\t";
		for (col = 0; col < 3; col++)
		{
			cout << "| " << XO[row][col] << " |";
		}
		cout << endl;
		if (row < 2)
		{
			cout << "\t\t---------------" << endl;
		}
	}
	cout << endl;
}

WinType Check_winner(const char XO[3][3], int r, int c, char var)
{
	if (XO[r][0] == var&&XO[r][1] == var&&XO[r][2] == var)
	{
		return row;
	}
	else if (XO[0][c] == var&&XO[1][c] == var&&XO[2][c] == var)
	{
		return column;
	}
	else if (XO[0][0] == var&&XO[1][1] == var&&XO[2][2] == var)
	{
		return left_diagonal;
	}
	else if (XO[0][2] == var && XO[1][1] == var&&XO[2][0] == var)
	{
		return right_diagonal;
	}
	else if (XO[0][0] != ' ' &&XO[0][1] != ' ' &&XO[0][2] != ' ' &&XO[1][0] != ' ' &&XO[1][1] != ' ' &&XO[1][2] != ' ' &&XO[2][0] != ' ' &&XO[2][1] != ' ' &&XO[2][2] != ' ')
		return no_winner;
	else
		return not_yet;
}

void M_Winner(WinType W, int r, int c, char var)
{
	if (W == row)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << var << " by the Row number : " << r + 1 << endl;
	}

	else if (W == column)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << var << " by the Column number : " << c + 1 << endl;
	}

	else if (W == right_diagonal)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << var << " by the Right-Diagonal" << endl;
	}
	else if (W == left_diagonal)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << var << " by the Left-Diagonal" << endl;
	}
	else if (W == no_winner)
	{
		cout << "Game Over.\n";
		cout << "There is no Winner.\n";
	}
}

void S_Winner(WinType W, int r, int c, char var)
{
	string str;
	if (var == 'x' || var == 'X')
		str = "You";
	else if (var == 'o' || var == 'O')
		str = "Computer";
	if (W == row)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << str << " by the Row number : " << r + 1 << endl;
	}

	else if (W == column)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << str << " by the Column number : " << c + 1 << endl;
	}

	else if (W == right_diagonal)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << str << " by the Right-Diagonal" << endl;
	}
	else if (W == left_diagonal)
	{
		cout << "Game Over.\n";
		cout << "The Winner is : " << str << " by the Left-Diagonal" << endl;
	}
	else if (W == no_winner)
	{
		cout << "Game Over.\n";
		cout << "There is no Winner.\n";
	}
}

bool Play_again(int& choice)
{
	cout << "Do you want to play again ? (yes = 1 & no = 0).\n";
	choice = 2;
	while (choice != 0 && choice != 1)
	{
		cin >> choice;
		if (choice == 1)
			return true;
		else if (choice == 0)
			return false;
		else
			cout << "Make sure that you entered '1' for yes or '0' for no.\n";
	}
}

void Single_Player_Hard(char XO[3][3], int& r, int& c, int counter, int Temp_Row, int Temp_Col)
{
	int i, box;
	int XO1379[4] = { 1,3,7,9 };
	char X = 'x', O = 'o';
	if (counter == 1)
	{
		if (r == 1 && c == 1)
		{
			srand(time(0));
			i = rand() % 4;
			box = XO1379[i];
			BoxtoPlace(box, r, c);
		}
		else
		{
			box = 5;
			BoxtoPlace(box, r, c);
		}
	}
	else if (XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[Temp_Row][0] == O && XO[Temp_Row][1] == O && XO[Temp_Row][2] == ' ')
	{
		r = Temp_Row;
		c = 2;
	}
	else if (XO[Temp_Row][0] == O && XO[Temp_Row][2] == O && XO[Temp_Row][1] == ' ')
	{
		r = Temp_Row;
		c = 1;
	}
	else if (XO[Temp_Row][1] == O && XO[Temp_Row][2] == O && XO[Temp_Row][0] == ' ')
	{
		r = Temp_Row;
		c = 0;
	}
	else if (XO[0][Temp_Col] == O && XO[1][Temp_Col] == O && XO[2][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 2;
	}
	else if (XO[0][Temp_Col] == O && XO[2][Temp_Col] == O && XO[1][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 1;
	}
	else if (XO[1][Temp_Col] == O && XO[2][Temp_Col] == O && XO[0][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 0;
	}
	else if (XO[0][0] == O && XO[1][1] == O && XO[2][2] == ' ')
	{
		r = 2;
		c = 2;
	}
	else if (XO[0][0] == O && XO[2][2] == O && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[1][1] == O && XO[2][2] == O && XO[0][0] == ' ')
	{
		r = 0;
		c = 0;
	}
	else if (XO[0][2] == O && XO[1][1] == O && XO[2][0] == ' ')
	{
		r = 2;
		c = 0;
	}
	else if (XO[0][2] == O && XO[2][0] == O && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[2][0] == O && XO[1][1] == O && XO[0][2] == ' ')
	{
		r = 0;
		c = 2;
	}
	else if (XO[r][0] == X && XO[r][1] == X && XO[r][2] == ' ')
	{
		r = r;
		c = 2;
	}
	else if (XO[r][0] == X && XO[r][2] == X && XO[r][1] == ' ')
	{
		r = r;
		c = 1;
	}
	else if (XO[r][1] == X && XO[r][2] == X && XO[r][0] == ' ')
	{
		r = r;
		c = 0;
	}
	else if (XO[0][c] == X && XO[1][c] == X && XO[2][c] == ' ')
	{
		c = c;
		r = 2;
	}
	else if (XO[0][c] == X && XO[2][c] == X && XO[1][c] == ' ')
	{
		c = c;
		r = 1;
	}
	else if (XO[1][c] == X && XO[2][c] == X && XO[0][c] == ' ')
	{
		c = c;
		r = 0;
	}
	else if (XO[0][0] == X && XO[1][1] == X && XO[2][2] == ' ')
	{
		r = 2;
		c = 2;
	}
	else if (XO[0][0] == X && XO[2][2] == X && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[1][1] == X && XO[2][2] == X && XO[0][0] == ' ')
	{
		r = 0;
		c = 0;
	}
	else if (XO[0][2] == X && XO[1][1] == X && XO[2][0] == ' ')
	{
		r = 2;
		c = 0;
	}
	else if (XO[0][2] == X && XO[2][0] == X && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[2][0] == X && XO[1][1] == X && XO[0][2] == ' ')
	{
		r = 0;
		c = 2;
	}
	else
	{
		if (counter == 3 && XO[1][1] == XO[0][0] || XO[1][1] == XO[0][2] || XO[1][1] == XO[2][0] || XO[1][1] == XO[2][2])
		{
			if (XO[0][0] == ' ')
			{
				r = 0;
				c = 0;
			}
			else if (XO[0][2] == ' ')
			{
				r = 0;
				c = 2;
			}
			else if (XO[2][0] == ' ')
			{
				r = 2;
				c = 0;
			}
			else if (XO[2][2] == ' ')
			{
				r = 2;
				c = 2;
			}
		}
		else if (XO[0][1] == ' ')
		{
			r = 0;
			c = 1;
		}
		else if (XO[1][0] == ' ')
		{
			r = 1;
			c = 0;
		}
		else if (XO[1][2] == ' ')
		{
			r = 1;
			c = 2;
		}
		else if (XO[2][1] == ' ')
		{
			r = 2;
			c = 1;
		}
		else if (XO[0][0] == ' ')
		{
			r = 0;
			c = 0;
		}
		else if (XO[0][2] == ' ')
		{
			r = 0;
			c = 2;
		}
		else if (XO[2][0] == ' ')
		{
			r = 2;
			c = 0;
		}
		else if (XO[2][2] == ' ')
		{
			r = 2;
			c = 2;
		}
		else if (XO[1][1] == ' ')
		{
			r = 1;
			c = 1;
		}
	}
}

void Single_Player_Easy(char XO[3][3], int& r, int& c, int counter, int Temp_Row, int Temp_Col)
{
	int i, box;
	int XO2468[4] = { 2,4,6,8 };
	char X = 'x', O = 'o';
	if (counter == 1)
	{
		srand(time(0));
		i = rand() % 4;
		box = XO2468[i];
		BoxtoPlace(box, r, c);
	}
	else if (XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[Temp_Row][0] == O && XO[Temp_Row][1] == O && XO[Temp_Row][2] == ' ')
	{
		r = Temp_Row;
		c = 2;
	}
	else if (XO[Temp_Row][0] == O && XO[Temp_Row][2] == O && XO[Temp_Row][1] == ' ')
	{
		r = Temp_Row;
		c = 1;
	}
	else if (XO[Temp_Row][1] == O && XO[Temp_Row][2] == O && XO[Temp_Row][0] == ' ')
	{
		r = Temp_Row;
		c = 0;
	}
	else if (XO[0][Temp_Col] == O && XO[1][Temp_Col] == O && XO[2][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 2;
	}
	else if (XO[0][Temp_Col] == O && XO[2][Temp_Col] == O && XO[1][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 1;
	}
	else if (XO[1][Temp_Col] == O && XO[2][Temp_Col] == O && XO[0][Temp_Col] == ' ')
	{
		c = Temp_Col;
		r = 0;
	}
	else if (XO[0][0] == O && XO[1][1] == O && XO[2][2] == ' ')
	{
		r = 2;
		c = 2;
	}
	else if (XO[0][0] == O && XO[2][2] == O && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[1][1] == O && XO[2][2] == O && XO[0][0] == ' ')
	{
		r = 0;
		c = 0;
	}
	else if (XO[0][2] == O && XO[1][1] == O && XO[2][0] == ' ')
	{
		r = 2;
		c = 0;
	}
	else if (XO[0][2] == O && XO[2][0] == O && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[2][0] == O && XO[1][1] == O && XO[0][2] == ' ')
	{
		r = 0;
		c = 2;
	}
	else if (XO[r][0] == X && XO[r][1] == X && XO[r][2] == ' ')
	{
		r = r;
		c = 2;
	}
	else if (XO[r][0] == X && XO[r][2] == X && XO[r][1] == ' ')
	{
		r = r;
		c = 1;
	}
	else if (XO[r][1] == X && XO[r][2] == X && XO[r][0] == ' ')
	{
		r = r;
		c = 0;
	}
	else if (XO[0][c] == X && XO[1][c] == X && XO[2][c] == ' ')
	{
		c = c;
		r = 2;
	}
	else if (XO[0][c] == X && XO[2][c] == X && XO[1][c] == ' ')
	{
		c = c;
		r = 1;
	}
	else if (XO[1][c] == X && XO[2][c] == X && XO[0][c] == ' ')
	{
		c = c;
		r = 0;
	}
	else if (XO[0][0] == X && XO[1][1] == X && XO[2][2] == ' ')
	{
		r = 2;
		c = 2;
	}
	else if (XO[0][0] == X && XO[2][2] == X && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[1][1] == X && XO[2][2] == X && XO[0][0] == ' ')
	{
		r = 0;
		c = 0;
	}
	else if (XO[0][2] == X && XO[1][1] == X && XO[2][0] == ' ')
	{
		r = 2;
		c = 0;
	}
	else if (XO[0][2] == X && XO[2][0] == X && XO[1][1] == ' ')
	{
		r = 1;
		c = 1;
	}
	else if (XO[2][0] == X && XO[1][1] == X && XO[0][2] == ' ')
	{
		r = 0;
		c = 2;
	}
	else
	{
		if (XO[0][1] == ' ')
		{
			r = 0;
			c = 1;
		}
		else if (XO[1][0] == ' ')
		{
			r = 1;
			c = 0;
		}
		else if (XO[1][2] == ' ')
		{
			r = 1;
			c = 2;
		}
		else if (XO[2][1] == ' ')
		{
			r = 2;
			c = 1;
		}
		else if (XO[0][0] == ' ')
		{
			r = 0;
			c = 0;
		}
		else if (XO[0][2] == ' ')
		{
			r = 0;
			c = 2;
		}
		else if (XO[2][0] == ' ')
		{
			r = 2;
			c = 0;
		}
		else if (XO[2][2] == ' ')
		{
			r = 2;
			c = 2;
		}
		else if (XO[1][1] == ' ')
		{
			r = 1;
			c = 1;
		}
	}
}



