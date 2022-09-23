#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int numberOfPlayers = 2;
string playersWords[2];
int playersScores[2];

int currentHighestScore = 0;
int playerWithHighestScore = 0;
int playerNumberForTies = -1;

void PlayGame();
void AskPlayerForWord(int currentPlayer);
void FindPlayersWordScore(int currentPlayer);
int ComputeWordScore(int currentPlayer, string word);
void EvaluateScoreRankings(int currentPlayer, int currentPlayersScore);
void SetCurrentHighestScore(int newPlayerWithHighestScore, int newHighestScore);
void PrintWinnerToScreen();

int main(void)
{
    // Get input words from both players
    PlayGame();

    // TODO: Print the winner
    PrintWinnerToScreen();
}

void PlayGame()
{
    // Get input words for all players
    for (int currentPlayer = 0; currentPlayer < numberOfPlayers; currentPlayer++)
    {
        AskPlayerForWord(currentPlayer);
        FindPlayersWordScore(currentPlayer);
        EvaluateScoreRankings(currentPlayer, playersScores[currentPlayer]);
    }
}

void AskPlayerForWord(int currentPlayer)
{
    playersWords[currentPlayer] = get_string("Player %i: ", currentPlayer + 1);
}

void FindPlayersWordScore(int currentPlayer)
{
    playersScores[currentPlayer] = ComputeWordScore(currentPlayer, playersWords[currentPlayer]);
}

int ComputeWordScore(int currentPlayer, string word)
{
    // TODO: Compute and return score for string
    int lengthOfWord = strlen(word);
    int wordScore = 0;

    for (int characterIndex = 0; characterIndex < lengthOfWord; characterIndex++)
    {
        char currentCharacter = word[characterIndex];

        if (isalpha(currentCharacter))
        {
            char upperCaseCurrentCharacter = toupper(currentCharacter);
            int pointsArrayIndex = (int)upperCaseCurrentCharacter - 'A';
            int letterScore = POINTS[pointsArrayIndex];
            wordScore += letterScore;
        }
    }

    return wordScore;
}

void EvaluateScoreRankings(int currentPlayer, int currentPlayersScore)
{
    if (currentPlayersScore == currentHighestScore)
    {
        SetCurrentHighestScore(playerNumberForTies, currentPlayersScore);
    }
    else if (currentPlayersScore > currentHighestScore)
    {
        SetCurrentHighestScore(currentPlayer, currentPlayersScore);
    }
}

void SetCurrentHighestScore(int newPlayerWithHighestScore, int newHighestScore)
{
    currentHighestScore = newHighestScore;
    playerWithHighestScore = newPlayerWithHighestScore;
}

void PrintWinnerToScreen()
{
    if (playerWithHighestScore == -1)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", playerWithHighestScore + 1);
    }
}