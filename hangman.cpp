#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>

using namespace std;

class Hangman
{
public:
	Hangman();	//constructor

	void displayWelcome();

	void displayChances();

	void displayProgress();

	void displayAnswer();

	void displayHangman();

	void takeInput();

	void displayResult();

	bool checkStatus();

private:
	string placesNames[15] = { "pakistan", "qatar", "china", "morocco", "mexico", "germany", "tokyo", "thailand", "whales", "nigeria", "nepal"
	, "india", "bhutan", "australia", "egypt"};

	string chosenPlace;
	
	char *progress;
	
	int placeNameLength = 0;

	int chances = 8;
};

//constructor to select country and determines the equivalent length
Hangman::Hangman()
{
	srand(time(NULL));

	int randomPlaceNumber = rand() % 14 + 0;		//chooses a random number to select a country

	chosenPlace = placesNames[randomPlaceNumber];

	for (int i = 0; true; i++)					//determines the length of the string
	{
		if (chosenPlace[i] != '\0')
		{
			placeNameLength++;
		}
		else
		{
			break;
		}
	}

	progress = new char[placeNameLength];

	for (int i = 0; i < placeNameLength; i++)		//assigns empty places to characters
	{
		progress[i] = '_';
	}

	cout << chosenPlace;
	cout << placeNameLength;
}

void Hangman::displayWelcome()
{
	cout << endl;

	cout << "------Welcome to Hang The Man!------\n\n";
}

void Hangman::displayChances()
{
	cout << "\nChances remaining : " << chances;
}

void Hangman::displayProgress()
{
	cout << "\n\nYour Progress:\n";

	for (int i = 0; i < placeNameLength; i++)
	{
		cout << progress[i] << " ";
	}

}

void Hangman::displayAnswer()
{
	cout << "\n\nAnswer:\n";

	for (int i = 0; i < placeNameLength; i++)
	{
		cout << chosenPlace[i] << " ";
	}
}

void Hangman::displayHangman()
{
	cout << "Hangman : \n" << endl;

	switch (chances)
	{
	case 8:
		cout << "";
		break;
	case 7:
		cout << "\t O";
		break;
	case 6:
		cout << "\t O" << endl;
		cout << "\t |" << endl;
		break;
	case 5:
		cout << "\t O" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		break;
	case 4:
		cout << "\t O" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		break;
	case 3:
		cout << "\t O" << endl;
		cout << "\t/|" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		break;
	case 2:
		cout << "\t O" << endl;
		cout << "\t/|\\" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		break;
	case 1:
		cout << "\t O" << endl;
		cout << "\t/|\\" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		cout << "\t/" << endl;
		break;
	case 0:
		cout << "\t O" << endl;
		cout << "\t/|\\" << endl;
		cout << "\t |" << endl;
		cout << "\t |" << endl;
		cout << "\t/ \\" << endl;
		break;
	}

	cout << endl;
}

void Hangman::takeInput()
{
	char character;

	bool Exit = false;
	bool wrongChosen = true;
	bool displayed = false;

	int count= 0;

	do
	{

		cout << "\n\nGuess a character: ";
		cin >> character;

		character = (char)tolower(character);

		for (int i = 0; i < placeNameLength; i++)
		{
			count++;

			if (character == chosenPlace[i])
			{
				if (character == progress[i])
				{
					if (displayed == false)
					{
						cout << "\nCharacter is already chosen. Please choose again";

						displayed = true;
					}
					
					wrongChosen = false;
				}
				else
				{
					progress[i] = character;
					Exit = true;

					if (displayed == false)
					{
						cout << "\nGood Guess!" << endl;
						
						displayed = true;
					}
				}
			}
		}

		if (count == placeNameLength && Exit == false && wrongChosen == true)
		{
			cout << "\nBad Guess!";
			cout << "\nChance - 1" << endl;

			chances--;

			Exit = true;
		}

		wrongChosen = true;
		displayed = false;

	} while (Exit == false);

	
}

void Hangman::displayResult()
{

	cout << "\t\t---Game Over!---\n";

	displayHangman();

	displayAnswer();

	displayProgress();

	cout << endl;

	displayChances();

	cout << endl;

	if (chances > 0)
	{
		cout << "\n-------------------";
		cout << "\n  You Guessed It!";
		cout << "\n-------------------";
	}
	else
	{
		cout << "\n-----------------------";
		cout << "\nYou ran Out of Guesses!";
		cout << "\n-----------------------";
	}
}

bool Hangman::checkStatus()
{
	int correctPlaces = 0;

	for (int i = 0; i < placeNameLength; i++)
	{
		if (progress[i] == chosenPlace[i])
		{
			correctPlaces++;
		}
	}

	if (correctPlaces == placeNameLength || chances < 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void displayCountdown()
{
	int seconds = 3;

	cout << "\n";

	while (seconds >= 0)
	{
		cout << "\rPlease wait [" << seconds << "]";
		Sleep(300);
		seconds--;
	}
}

int main()
{
	Hangman game;
	
	bool gameOver;

	game.displayWelcome();

	do
	{
		game.displayHangman();

		game.displayChances();

		game.displayProgress();

		game.takeInput();

		displayCountdown();

		system("CLS");			//clears screen

		gameOver = game.checkStatus();

	} while (gameOver == false);

	game.displayResult();		//displays results

	return 0;
}