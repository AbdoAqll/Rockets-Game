
#include <bits/stdc++.h>

using namespace std;

int** Board;
int NUMBER_OF_PIECES;

void initialize(int size)
{
	NUMBER_OF_PIECES = size - 2;
	Board = new int *[size];
	for (int i = 0; i < size; i++)
	{
		Board[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == 0 && j >= 1 && j < size - 1)
			{
				Board[i][j] = 1;
			}
			else if (j == 0 && i >= 1 && i < size - 1)
			{
				Board[i][j] = 2;
			}
			else
			{
				Board[i][j] = 0;
			}
		}
	}
}

void printBoard(int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << Board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void move(int pieceXpos, int pieceYpos, int PlayerNumber)
{
	if (PlayerNumber == 1)
	{
		if (Board[pieceXpos + 1][pieceYpos] == 2)
		{
			Board[pieceXpos][pieceYpos] = 0;
			Board[pieceXpos + 2][pieceYpos] = 1;
		}
		else
		{
			Board[pieceXpos][pieceYpos] = 0;
			Board[pieceXpos + 1][pieceYpos] = 1;
		}
	}
	if (PlayerNumber == 2)
	{
		if (Board[pieceXpos][pieceYpos + 1] == 1)
		{
			Board[pieceXpos][pieceYpos] = 0;
			Board[pieceXpos][pieceYpos + 2] = 2;
		}
		else
		{
			Board[pieceXpos][pieceYpos] = 0;
			Board[pieceXpos][pieceYpos + 1] = 2;
		}
	}
}
void demove(int xpos, int ypos, int PlayerNumber)
{
	if (PlayerNumber == 1)
	{
		if (Board[xpos + 1][ypos] == 2)
		{
			Board[xpos][ypos] = 1;
			Board[xpos + 2][ypos] = 0;
		}
		else
		{
			Board[xpos][ypos] = 1;
			Board[xpos + 1][ypos] = 0;
		}
	}
	if (PlayerNumber == 2)
	{
		if (Board[xpos][ypos + 1] == 1)
		{
			Board[xpos][ypos] = 2;
			Board[xpos][ypos + 2] = 0;
		}
		else
		{
			Board[xpos][ypos] = 2;
			Board[xpos][ypos + 1] = 0;
		}
	}

}


int isWinner()
{
	int count = 0;
	for (int i = 1; i <= NUMBER_OF_PIECES ; i++)
	{
		if (Board[NUMBER_OF_PIECES + 1][i] == 1)
		{
			count++;
		}
	}
	if (count == NUMBER_OF_PIECES)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	count = 0;
	for (int i = 1; i <= NUMBER_OF_PIECES; i++)
	{
		if (Board[i][NUMBER_OF_PIECES + 1] == 2)
		{
			count++;
		}
	}
	if (count == NUMBER_OF_PIECES)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}





void Player(int PlayerNumber)
{
	int pieceXpos, pieceYpos;
	cout << "Player " << PlayerNumber << " Enter the X position of the piece you want to move: ";
	cin >> pieceXpos;
	cout << "Player " << PlayerNumber << " Enter the Y position of the piece you want to move: ";
	cin >> pieceYpos;
	if (Board[pieceXpos][pieceYpos] != PlayerNumber )
	{
		cout << "You can't move this piece" << endl;
		Player(PlayerNumber);
	}
	else if (PlayerNumber == 1 && Board[pieceXpos + 1][pieceYpos] == 2 && Board[pieceXpos + 2][pieceYpos] == 2)
	{
		cout << "You can't move this piece" << endl;
		Player(PlayerNumber);
	}
	else if (PlayerNumber == 2 && Board[pieceXpos][pieceYpos + 1] == 1 && Board[pieceXpos][pieceYpos + 2] == 1)
	{
		cout << "You can't move this piece" << endl;
		Player(PlayerNumber);
	}
	else
	{
		move(pieceXpos, pieceYpos, PlayerNumber);
	}
}


bool isValid(int xpos, int ypos , int PlayerNumber)
{
	if (PlayerNumber == 1)
	{
		if (Board[xpos][ypos] == 1 && Board[xpos + 1][ypos] == 2 && Board[xpos + 2][ypos] == 2)
		{
			return false;
		}
		else if (Board[xpos][ypos] != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	if (PlayerNumber == 2)
	{
		if (Board[xpos][ypos] == 2 && Board[xpos][ypos + 1] == 1 && Board[xpos][ypos + 2] == 1)
		{
			return false;
		}
		else if (Board[xpos][ypos] != 2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
}



// Creat ComputerPlayer using minmax algorithm
int MineMax(int depth, bool isMaxmizing , bool FirstTime = true)
{
	int result = isWinner();
	if (result != 0 || depth == 0)
	{
		return result;
	}

	if (isMaxmizing)
	{
		int finalScore = -1000;
		int finalI, finalJ;
		for (int i = 0; i < NUMBER_OF_PIECES + 1; i++)
		{
			for (int j = 1; j < NUMBER_OF_PIECES + 1; j++)
			{
				if (isValid(i , j , 1))
				{
					move(i, j, 1);
					int score = MineMax(depth - 1, false, false);
					demove(i, j, 1);
					if (finalScore < score)
					{
						finalScore = score;
						finalI = i;
						finalJ = j;
					}
					if (FirstTime)
					{
						cout << "Score for position (" << i << "," << j << ") is " << score << endl;
					}
				}
			}
		}
		if (FirstTime)
		{
			move(finalI , finalJ , 1);
		}
		return finalScore;
	}
	else
	{
		int finalScore = 1000;
		for (int i = 1; i < NUMBER_OF_PIECES + 1; i++)
		{
			for (int j = 0; j < NUMBER_OF_PIECES + 1; j++)
			{
				if (isValid(i , j , 2))
				{
					move(i, j, 2);
					int score = MineMax(depth - 1, true, false);
					demove(i, j, 2);
					if (finalScore > score)
					{
						finalScore = score;
					}
				}
			}
		}
		return finalScore;
	}
}

void PlayerWithPlayer()
{
	int size;
	cout << "Enter the size of the board: ";
	cin >> size;
	initialize(size);
	printBoard(size);
	int turn = 0;
	while (true)
	{
		if (turn == 0)
		{
			turn += 1;
			turn %= 2;
			Player(1);
			printBoard(size);
			if (isWinner() == 1)
			{
				cout << "Player 1 is the winner" << endl;
				for (int i = 0; i < NUMBER_OF_PIECES + 2; i++)
				{
					delete[] Board[i];
				}
				delete[] Board;
				break;
			}
		}
		else
		{
			turn += 1;
			turn %= 2;
			Player(2);
			printBoard(size);
			if (isWinner() == -1)
			{
				cout << "Player 2 is the winner" << endl;
				for (int i = 0; i < NUMBER_OF_PIECES + 2; i++)
				{
					delete[] Board[i];
				}
				delete[] Board;
				break;
			}
		}
	}
}

void PlayerWithComputer()
{
	int size;
	cout << "Enter the size of the board: ";
	cin >> size;
	initialize(size);
	printBoard(size);
	int turn = 0;
	while (true)
	{
		if (turn == 0)
		{
			turn += 1;
			turn %= 2;
			MineMax(5, true);
			printBoard(size);
			if (isWinner() == 1)
			{
				cout << "Player 1 is the winner" << endl;
				for (int i = 0; i < NUMBER_OF_PIECES + 2; i++)
				{
					delete[] Board[i];
				}
				delete[] Board;
				break;
			}
		}
		else
		{
			turn += 1;
			turn %= 2;
			Player(2);
			printBoard(size);
			if (isWinner() == -1)
			{
				cout << "Player 2 is the winner" << endl;
				for (int i = 0; i < NUMBER_OF_PIECES + 2; i++)
				{
					delete[] Board[i];
				}
				delete[] Board;
				break;
			}
		}
	}
}


void GameLoop()
{
	int choice;
	cout << "1- Player with Player" << endl;
	cout << "2- Player with Computer" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		PlayerWithPlayer();
	}
	else if (choice == 2)
	{
		PlayerWithComputer();
	}
	else
	{
		cout << "Invalid choice" << endl;
	}
}

int main()
{
	GameLoop();
	return 0;
}
