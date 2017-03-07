#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

//function prototypes
void splashScreen();										//displays game's title and developer
void askForUserNames(string&, string&);						//requests username
string validateUserName();									//validates username
void resetGame(string[], bool&, bool&, int&);				//reset game
void displayGrid(string[]);									//displays game board
int switchPlayer(int);										//switches between players
void playerMakeMove(int, string, string, string[]);			//prompts player to make move, calls validatePlayersMove, checkPositionAvailability
string validatePlayersMove();								//validates input >= 0 and <= 8
void checkPositionAvailability(string, string[], int);		//validate position selected available
bool checkWin(string[]);									//check for a winning player
bool checkTie(string[]);									//check for a tie
void endScreen(int, string, string, bool);

//global constant
const int SIZE = 9;											//size of array

int main()
{
	string board[SIZE];
	string player1, player2, move;
	string continu = "y";
	bool isWin, isTie;
	int turn, user;

	splashScreen();
	askForUserNames(player1, player2);

	while (continu == "y" || continu == "Y")
	{
		resetGame(board, isWin, isTie, turn);

		do
		{
			displayGrid(board);
			user = switchPlayer(turn);
			playerMakeMove(user, player1, player2, board);
			if (turn > 3)									//checks if a player has won only after first player has had 3 or more turns
			{
				isWin = checkWin(board);
				isTie = checkTie(board);
			}
			turn++;
		} while (isWin == false && isTie == false);			//continues as long as no one has won or game not declared a tie

		system("cls");
		endScreen(turn, player1, player2, isTie);
		cout << "\ny/Y to play again, any other char to exit." << endl;
		getline(cin, continu);
	}
	system("cls");
	return 0;
}

void splashScreen()
{
	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;
	cout << setfill(' ') << setw(1) << "|" << setw(7) << " " << left << "Tic Tac Toe" << setw(7) << " " << "|" << endl;
	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;

	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;
	cout << setfill(' ') << setw(1) << "|" << setw(11) << " " << left << "by:" << setw(11) << " " << "|" << endl;
	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;

	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;
	cout << setfill(' ') << setw(1) << "|" << setw(5) << " " << left << "Manuel Paniagua" << setw(5) << " " << "|" << endl;
	cout << setfill('=') << setw(1) << "+" << setw(25) << "=" << setw(1) << "+" << endl;

	system("pause");
	system("cls");
}

void askForUserNames(string &p1, string &p2)
{
	cout << "Player1, enter your name!" << endl;
	p1 = validateUserName();

	system("cls");

	cout << "Player2, enter your name!" << endl;
	p2 = validateUserName();
}

string validateUserName()
{
	string name;
	int stringLength, counter = 0;

	getline(cin, name);

	stringLength = name.length();

	while (counter < stringLength || stringLength == 0)							//validates user's name is composed of only letters
	{
		if (!isalpha(name[counter]))
		{
			cout << "\nThis is not a valid name. Only alpha characters allowed!" << endl;
			cout << "Try again and press <ENTER>" << endl;
			getline(cin, name);
			stringLength = name.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
	return name;
}

void resetGame(string b[], bool &win, bool &tie, int &t)
{
	win = false;																//start of every game array is initialized as well as the variables turn, isWin, and isTie
	tie = false;
	t = 0;

	b[0] = "0", b[1] = "1", b[2] = "2", b[3] = "3", b[4] = "4",
		b[5] = "5", b[6] = "6", b[7] = "7", b[8] = "8";

	system("cls");
}

void displayGrid(string b[])
{
	system("cls");
	cout << "   Tic Tac Toe" << endl;

	cout << " _______________" << endl;
	cout << "|    |     |    |" << endl;
	cout << "| " << b[0] << "  |  " << b[1] << "  |  " << b[2] << " |" << endl;

	cout << "|____|_____|____|" << endl;
	cout << "|    |     |    |" << endl;

	cout << "| " << b[3] << "  |  " << b[4] << "  |  " << b[5] << " |" << endl;

	cout << "|____|_____|____|" << endl;
	cout << "|    |     |    |" << endl;

	cout << "| " << b[6] << "  |  " << b[7] << "  |  " << b[8] << " |" << endl;

	cout << "|____|_____|____|" << endl;
}

int switchPlayer(int t)
{
	if (t % 2 == 0)																//determines player turn.  even player 1, odd player 2
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void playerMakeMove(int u, string p1, string p2, string b[])
{
	string move;

	if (u == 1)
	{
		cout << "\nIt is " << p1 << "'s turn.\nYou are X, pick a square and press <ENTER>" << endl;		//prompts each player, using name they input
		move = validatePlayersMove();
		checkPositionAvailability(move, b, u);
	}
	else if (u == 2)
	{
		cout << "\nIt is " << p2 << "'s turn.\nYou are O, pick a square and press <ENTER>" << endl;
		move = validatePlayersMove();
		checkPositionAvailability(move, b, u);
	}
}

string validatePlayersMove()
{
	string m;

	getline(cin, m);

	while ((m < "0" || m > "8") || (m.size() != 1))									//validates input is a number between 0 and 8
	{
		cout << "Invalid input.  Enter a number between 0 and 8!" << endl;
		getline(cin, m);
	}

	return m;
}

void checkPositionAvailability(string m, string b[], int u)
{
	bool valid = false;
	//validates whether square is available
	do
	{
		if (u == 1)
		{
			if (m == "0" && b[0] == "0")
			{
				b[0] = "X";
				valid = true;
			}
			else if (m == "1" && b[1] == "1")
			{
				b[1] = "X";
				valid = true;
			}
			else if (m == "2" && b[2] == "2")
			{
				b[2] = "X";
				valid = true;
			}
			else if (m == "3" && b[3] == "3")
			{
				b[3] = "X";
				valid = true;
			}
			else if (m == "4" && b[4] == "4")
			{
				b[4] = "X";
				valid = true;
			}
			else if (m == "5" && b[5] == "5")
			{
				b[5] = "X";
				valid = true;
			}
			else if (m == "6" && b[6] == "6")
			{
				b[6] = "X";
				valid = true;
			}
			else if (m == "7" && b[7] == "7")
			{
				b[7] = "X";
				valid = true;
			}
			else if (m == "8" && b[8] == "8")
			{
				b[8] = "X";
				valid = true;
			}
			else
			{
				cout << "Invalid move. Select a different square and press <ENTER>" << endl;	//prompts user to select another square
				getline(cin, m);

				while ((m < "0" || m > "8") || (m.size() != 1))									//validates input is a number between 0 and 8
				{
					cout << "Invalid input.  Enter a number between 0 and 8!" << endl;
					getline(cin, m);
				}
			}
		}
		else if (u == 2)
		{
			if (m == "0" && b[0] == "0")
			{
				b[0] = "O";
				valid = true;
			}
			else if (m == "1" && b[1] == "1")
			{
				b[1] = "O";
				valid = true;
			}
			else if (m == "2" && b[2] == "2")
			{
				b[2] = "O";
				valid = true;
			}
			else if (m == "3" && b[3] == "3")
			{
				b[3] = "O";
				valid = true;
			}
			else if (m == "4" && b[4] == "4")
			{
				b[4] = "O";
				valid = true;
			}
			else if (m == "5" && b[5] == "5")
			{
				b[5] = "O";
				valid = true;
			}
			else if (m == "6" && b[6] == "6")
			{
				b[6] = "O";
				valid = true;
			}
			else if (m == "7" && b[7] == "7")
			{
				b[7] = "O";
				valid = true;
			}
			else if (m == "8" && b[8] == "8")
			{
				b[8] = "O";
				valid = true;
			}
			else
			{
				cout << "Invalid move. Select a different square and press <ENTER>" << endl;
				getline(cin, m);
				while ((m < "0" || m > "8") || (m.size() != 1))
				{
					cout << "Invalid input.  Enter a number between 0 and 8!" << endl;
					getline(cin, m);
				}
			}
		}
	} while (valid == false);

}

bool checkWin(string square[])
{																							//checks every possible winnnig combination, returns true if win detected
	if (square[0] == square[1] && square[1] == square[2])
	{
		return true;
	}
	else if (square[3] == square[4] && square[4] == square[5])
	{
		return true;
	}
	else if (square[6] == square[7] && square[7] == square[8])
	{
		return true;
	}
	else if (square[0] == square[3] && square[3] == square[6])
	{
		return true;
	}
	else if (square[1] == square[4] && square[4] == square[7])
	{
		return true;
	}
	else if (square[2] == square[5] && square[5] == square[8])
	{
		return true;
	}
	else if (square[0] == square[4] && square[4] == square[8])
	{
		return true;
	}
	else if (square[2] == square[4] && square[4] == square[6])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkTie(string square[])
{																									//checks whether all squares have been chosen.  If no win, tie declared
	if (square[0] != "0" && square[1] != "1" && square[2] != "2"
		&& square[3] != "3" && square[4] != "4" && square[5] != "5"
		&& square[6] != "6" && square[7] != "7" && square[8] != "8")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void endScreen(int t, string p1, string p2, bool tie)
{
	if (tie == false)																			//end game screen.  if no tie, determines winner and displays ascii art
	{
		if ((t - 1) % 2 == 0)
		{
			cout << "     __________________" << endl <<
				"    (`-----------------')" << endl <<
				"     '-.             .-'" << endl <<
				"      ,| _||_  .-.   |," << endl <<
				"     //| -||- |/||   |\\\\" << endl <<
				"    || |        ||   | ||" << endl <<
				"     \\\\|       _||_  |//" << endl <<
				"      `\\      '----' /`" << endl <<
				"        '.___   ___.'" << endl <<
				"             | |" << endl <<
				"           __| |__" << endl <<
				"         _/       \\_" << endl <<
				"        |           |" << endl <<
				"        '-----------'" << endl;

			cout << "Congratulations " << p1 << ", you are the winner!" << endl;
		}
		else
		{
			cout << "     __________________" << endl <<
				"    (`-----------------')" << endl <<
				"     '-.             .-'" << endl <<
				"      ,| _||_  .-.   |," << endl <<
				"     //| -||- |/||   |\\\\" << endl <<
				"    || |        ||   | ||" << endl <<
				"     \\\\|       _||_  |//" << endl <<
				"      `\\      '----' /`" << endl <<
				"        '.___   ___.'" << endl <<
				"             | |" << endl <<
				"           __| |__" << endl <<
				"         _/       \\_" << endl <<
				"        |           |" << endl <<
				"        '-----------'" << endl;

			cout << "Congratulations " << p2 << ", you are the winner!" << endl;
		}
	}
	else
	{
		cout << "Tie game!  Well played " << p1 << " and " << p2 << endl;
	}

}