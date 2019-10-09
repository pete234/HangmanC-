#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>

void variables(vector<string> wordlist);
void printGuess(char letter, string word, string dashes, string alphabet, int wguessesleft, int cguesses, int wordlength, vector<string> wordlist);
void guessLetter(char letter, string word, string dashes, string alphabet, int wguessesleft, int cguesses, int wordlength, vector<string> wordlist);
void endGame(int wguessesleft, string word, vector<string> wordlist);
int randomNumber(vector<string> wordlist);

int main(int argc, char *argv[])
{	
	
	string filename;
	ifstream fileread;			//Creates an object so files can be read
	if (argc > 1)
		filename = argv[1];		//If it is given an argument then it will take that and use the name given as the words file. 
	else
		filename = "wordslist.txt";
	vector<string> wordlist;		//a Vector to store all the words read from a file
	string x;					//A temp variable to store the line read from the file
	fileread.open(filename);

	if (!fileread.is_open())
	{
		cout << "Could not open file" << endl;
		exit(0);
	}

	for (int i = 0; i < 5; i++)
	{
		getline(fileread, x);
		wordlist.push_back(x);
	}
	variables(wordlist);

	return 0;
}
void variables(vector<string> wordlist)
{
	int rand = randomNumber(wordlist);		//Store a random number to be used to chose the word from the vector, but uses the length of the vector.
	string word = wordlist[rand];
	string dashes;
	for (int i = 0; i < word.length(); i++)
		dashes.insert(i, "-");
	int wguessesleft = 8;
	int cguesses = 0;
	int wordlength = word.length();
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	char letter = NULL;

	printGuess(letter, word, dashes, alphabet, wguessesleft, cguesses, wordlength, wordlist);
}

void printGuess(char letter, string word, string dashes, string alphabet, int wguessesleft, int cguesses, int wordlength, vector<string> wordlist)
{
	cout << "Guess a letter for the word: " <<  dashes << endl;
	cout << "You can guess wrongly " << wguessesleft << " more times, you have guessed " << cguesses << " out of " << wordlength << " letters" << endl;
	cout << "Posible letters you can use: " << alphabet << endl;

	cin >> letter;

	letter = tolower(letter);

	if (!((letter >= 'a' && letter <= 'z')))	//if letter is null cause nothing/a number was entered it will say so
	{
		cout << "\nThat is not a letter\n" << endl;
		printGuess(letter, word, dashes, alphabet, wguessesleft, cguesses, wordlength, wordlist);
	}

	guessLetter(letter, word, dashes, alphabet, wguessesleft, cguesses, wordlength, wordlist);
}

void guessLetter(char letter, string word, string dashes, string alphabet, int wguessesleft, int cguesses, int wordlength, vector<string> wordlist)
{
	string let (1, letter);

	if(alphabet.find(letter) < 26)
	{
		alphabet.replace(alphabet.find(letter), 1, ".");
			
		if (word.find(letter) < word.length())
		{
			cout << "\nCorrect guess!\n\n" << endl;

			for (int i = 0; i < word.length(); i++)
			{
				if (word[i] == letter)
				{
					dashes.replace(i, 1, let);
					cguesses++;
				}
			}	
		}
		else
		{
			cout << "\nIncorrect guess\n" << endl;
			wguessesleft--;
		}
	}
	else
	{
		cout << "\nYou have already guessed that\n" << endl;
	}

	if (cguesses == wordlength || wguessesleft == 0)		
		endGame(wguessesleft, word, wordlist);

	printGuess(letter, word, dashes, alphabet, wguessesleft, cguesses, wordlength, wordlist);

}

void endGame(int wguessesleft, string word, vector<string> wordlist)
{
	char yesorno = NULL;
	cout << "-----------------------------------------------------------\n" << endl;
	cout << "The word was \n" << word << endl;
	if (wguessesleft > 0)
		cout << "\nCongratulations you finished with incorrect guesses left " <<  wguessesleft << endl;
	else
		cout << "You ran out of gueses" << endl;

	while (true)
	{
		cout << "\nTry again? y/n" << endl;
		cin >> yesorno;

		if (yesorno == 'y')
		{
			cout << "\n\n" << endl;
			variables(wordlist);
		}
		else if (yesorno == 'n')
			exit(0);
		else
			cout << "INCORRECT CHARACTER INPUT\n\n" << endl;
	}
}

int randomNumber(vector<string> wordlist)
{
	time_t t;
	srand((unsigned)time(&t));
	int random = rand() % wordlist.size();

	return random;
}