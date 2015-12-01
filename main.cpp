// main.cpp

// Author: Ryan Canty

// Date: 11/13/15

// Course: CSC1610

// Description: This file reads in a randomly generated word from a .txt file.  It then plays
// the game Hangman.  It covers the word with asterisks and then asks the user for a letter.
// If the guess is correct, the user is notified and the letter is shown in the word.  If they
// are wrong, they are notified and they lose a life.  The user starts with the length of the 
// word plus 4 lives.  When the game is over, the user is asked if they would like to play
// the game again.

// Input: One user-defined character collected from the standard input stream
// (keyboard).

// Output: If the user's guess is correct or incorrect, how many lives the user has left, what
// letters of the word they have guessed correctly.

#include <cstdlib>
#include <fstream>
#include <cassert>
#include <iostream> 
using namespace std;

const string fileName = "wordsEn.txt";
const int MAX_WORDS = 120000;

// This function populates the words array and counts
//  the number of words available.
// Precondition: The file "wordsEn.txt" exists
// Postconddition: words array populated with the words
//  from "wordsEn.txt" and arraySize stores number of words
void readWordsFile(string words[], int& arraySize)
{
  ifstream inF(fileName.c_str());
  assert(inF);

  arraySize = 0;

  while (!inF.eof())
  {
    getline(inF, words[ arraySize++ ]);
  } // end of while

  cout << arraySize << " words read in successfully." << endl;
}

// This function returns one of the words from the long list of words
//  at random
// Precondition: numWords > 0
// Postcondition: A random word from the list is returned
string getRandomWord(const string words[], const int numWords)
{
  assert(numWords > 0);
  return words[ rand() % numWords ];
}
//Description: This function hides the random word with asterisks
//Precondition: wordLength > 0
//Postcondition: randomWord is returned with asterisks hiding it
string hideWord( string randomWord, int wordLength )
{
    assert( wordLength > 0);
    
    for( int i = 0; i <= wordLength; i++)
    {
        randomWord[i] = '*'; //Replace every letter of randomWord with an asterisk
    }
    return randomWord;
}
//Description: This function makes the player turn.  It tells the user how many lives they have
//left and then prompts them to guess a letter of the word.  The user is told if the guess is
//correct or not.  If they are wrong, it subtracts one life.
//Precondition: wordLength must be greater than 0.  
//Postcondition: The hiddenWord is changed and passed-by-reference so it is outputted differently
//each time the function is called.  Lives can be decremented by 1 if the user guesses wrong.
void playerTurn( string& randomWord, string& hiddenWord, int& wordLength, int& lives )
{
    assert( wordLength > 0 );
    
    cout << "You have " << lives << " lives left." << endl;
    char userGuess; //char variable that will store the user's guess
    cout << "What is your guess?" << endl; //Prompt user
    cin >> userGuess; //Take in the user's guess
    
    for( int i = 0; i <= wordLength; i++ )
    {
        if( randomWord[i] == userGuess )
        {
            hiddenWord[i] = randomWord[i]; //If the userGuess is equal to any index of the
        }                                    //random word, display the guess where it is in
    }                                        // the hiddenWord
     
    int find = randomWord.find( userGuess ); //Integer that finds the index in which the userGuess
    if( find >= 0 )                           // is located
    {
        cout << "Correct!" << endl; //If the userGuess is found, tell the user they are correct
        if( hiddenWord != randomWord )
        {
            cout << "-----------------" << endl; //Output a line if the user has not guessed the
        }                                         //word yet
    }
    else if ( find < 0 )
    {
        cout << "Wrong!" << endl; //If the userGuess is not found, tell the user they are wrong
        lives--; //Decrement lives by 1
        if( lives == 0 )
        {
            cout << endl; //If the user has no lives left, do nothing
        }
        else if( hiddenWord != randomWord )
        {
            cout << "-----------------" << endl; //If the user has not guessed the correct word,
        }                                         //output a line
    }
}
//Description: This function asks the user if they want to play the game again.
//Precondition: userAnswer must be a 'Y' or 'y' if they want to play again.
//Postcondition: If the user wants to play again, return true. If not, return false.
bool playAgain()
{
  string userAnswer; //string that will store the answer to a question
  cout << "Would you like to play again? 'Y' or 'N'." << endl; //Ask question
  cin >> userAnswer; //Store the user's answer
  if( userAnswer == "Y" )
  {
      return true; //If the user wants to play again, return true
  }
  else if( userAnswer == "y")
  {
      return true; //If the user wants to play again, return true
  }
  else
  {
      return false; //If the user doesn't want to play again, return false
  }
}
int main()
{
    // DO NOT TOUCH THIS LINE
    srand(37); // Seed the random number generator

    string words[MAX_WORDS];
    int numWords;
    readWordsFile(words, numWords);
    do
    {       
        string randomWord = getRandomWord( words, numWords ); //Generate random word and store
        int wordLength = randomWord.length() - 1; //Integer that holds the length of the word
        cout << "-----------------" << endl;      //subtracting 1 because the index starts at 0
        //output line
        int lives; //Integer that stores the number of lives the user has
        lives = wordLength + 5; //Lives is equal to 4 more than the length of the word
  
        string hiddenWord = hideWord( randomWord, wordLength ); //Hide the random word
        cout << hiddenWord << endl; //output the hidden word
        cout << endl;
  
        do
        {
            playerTurn( randomWord, hiddenWord, wordLength, lives ); //Make the player turn
            if( lives == 0 )
            {
                cout << "Better luck next time! The word was " << randomWord << endl;
            } //If the user runs out of lives, tell them they lost and show the word
            else if( hiddenWord != randomWord )
            {
                cout << hiddenWord << endl; //Output the hidden word if the user hasn't 
            }                                //guessed correctly
        
            if( hiddenWord == randomWord )
            {
                cout << "You win! The word was " << randomWord << "!" << endl;
            }  //Tell the user the win if they guess the word
        }
        while( hiddenWord.find('*') != -1 && lives != 0 ); //Do all of the above until there
    }                                                       //are no asterisks left or the user
    while( playAgain() == true );                        //has no lives left
    //Do the whole lope again if the user wants to play again
    return 0;
}


