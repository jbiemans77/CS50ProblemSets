#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;


// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
void lock_pairs(void);
void AutomaticallyPopulatePairsForTesting(int numberOfPairs, bool forceLoop);
bool CheckForLoopInLockedPairs(int candidateToWatchFor, int winner, int loser);
void ManuallyPopulatePairsForTesting();
void PrintPairsToScreen();
void PrintLockedPairsToScreen();
void PrintAllLocksToScreen();
int main()
{
    //AutomaticallyPopulatePairsForTesting(6, false);
    ManuallyPopulatePairsForTesting();

    lock_pairs();

    PrintPairsToScreen();


    bool printOnlyLockedPairs = false;
    PrintLockedPairsToScreen();

    PrintAllLocksToScreen();

    return 0;
}

void PrintPairsToScreen()
{
    printf("-------------\n");
    printf("|   PAIRS   |\n");
    printf("-------------\n");
    printf("\n");

    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair %i Winner [%i][%i] Looser\n", i , pairs[i].winner, pairs[i].loser);
    }

    printf("\n");
}

void PrintLockedPairsToScreen()
{
    printf("-------------\n");
    printf("|   LOCKS   |\n");
    printf("-------------\n");
    printf("\n");

    for (int i = 0; i < pair_count; i++)
    {
        printf("Lock %i [%i][%i] ", i , pairs[i].winner, pairs[i].loser);
        printf("%s", locked[pairs[i].winner][pairs[i].loser] ? "true\n" : "false\n");
    }

    printf("\n");
}

void PrintAllLocksToScreen()
{
    printf("-------------\n");
    printf("| All LOCKS  |\n");
    printf("-------------\n");
    printf("\n");

    for (int firstCounter = 0; firstCounter < MAX; firstCounter++)
    {
        for (int secondCounter = 0; secondCounter < MAX; secondCounter++)
        {
            printf("Lock [%i][%i] ", firstCounter, secondCounter);
            printf("%s", locked[firstCounter][secondCounter] ? "true  <-------\n" : "false\n");
        }
    }

    printf("\n");
}


void ManuallyPopulatePairsForTesting()
{
    pairs[0].winner = 0;
    pairs[0].loser = 1;

    pairs[1].winner = 1;
    pairs[1].loser = 2;

    pairs[2].winner = 2;
    pairs[2].loser = 0;

    pairs[3].winner = 2;
    pairs[3].loser = 3;

    pairs[4].winner = 3;
    pairs[4].loser = 4;

    pairs[5].winner = 4;
    pairs[5].loser = 5;

    /*pairs[6].winner = 2;
    pairs[6].loser = 4;

    pairs[7].winner = 3;
    pairs[7].loser = 0;

    pairs[8].winner = 3;
    pairs[8].loser = 2;

    pairs[9].winner = 3;
    pairs[9].loser = 4;*/

    /*pairs[6].winner = 2;
    pairs[6].loser = 4;

    pairs[6].winner = 2;
    pairs[6].loser = 4; */

    pair_count = 6;
    candidate_count = 3;
}

void AutomaticallyPopulatePairsForTesting(int numberOfPairs, bool forceLoop)
{
    for(int i = 0; i < numberOfPairs; i++)
    {
        pairs[i].winner = i;
        pairs[i].loser = i + 1;

        pair_count = i;
        candidate_count = i + 1;
    }

    if (forceLoop)
    {
        pairs[candidate_count].winner = candidate_count;
        pairs[candidate_count].loser = 0;
        pair_count++;
    }
}

void lock_pairs(void)
{
    for (int pairCounter = 0; pairCounter < pair_count; pairCounter++)
    {
        //printf("Looping pairCounter: %i pairCounter\n", pairCounter);
        for (int secondPairCounter = 0; secondPairCounter < pair_count; secondPairCounter++)
        {
            //printf("Looping x: %i\n", secondPairCounter);
            int thirdPairCounter = secondPairCounter;

            printf("1 Check if [%i][%i] is locked.\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
            if (locked[pairs[pairCounter].loser][pairs[secondPairCounter].loser] == true)
            {
                printf("Lock found at [%i][%i]\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
                //printf("Found lock.  pairCounter = %i.  secondPairCounter = %i.  [%i][%i]\n", pairCounter, secondPairCounter, pairs[pairCounter].loser, pairs[secondPairCounter].loser);

                for (int fourthPairCounter = 0; fourthPairCounter < pair_count; fourthPairCounter++)
                {
                    //printf("Looping fourthPairCounter: %i\n", fourthPairCounter);
                    printf("2 Check if [%i][%i] is locked.\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                    if(locked[pairs[thirdPairCounter].loser][pairs[fourthPairCounter].loser] == true)
                    {
                        printf("Lock found at [%i][%i]\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                        //printf("Found lock second loop.  thirdPairCounter = %i.  fourthPairCounter = %i.  [%i][%i]\n", thirdPairCounter, fourthPairCounter, pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);

                        printf("3 Check if [%i] = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);
                        if (pairs[fourthPairCounter].loser == pairs[pairCounter].winner)
                        {
                            printf("[%i] DOES = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);

                            //printf("looser fourthPairCounter == winner pairCounter\n");
                            printf("UNLOCKING PAIR [%i][%i] to false <----------------------------------\n", pairs[pairCounter].winner, pairs[pairCounter].loser);
                            locked[pairs[pairCounter].winner][pairs[pairCounter].loser] = false;
                            secondPairCounter = pair_count;
                            break;
                        }
                        else
                        {
                            printf("[%i] DOES NOT = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);
                            printf("Resetting fourthPairCounter\n");
                            thirdPairCounter = fourthPairCounter;
                            fourthPairCounter = 0;
                        }
                    }
                    printf("Lock NOT found at [%i][%i]\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                }
            }
            else
            {
                printf("Lock NOT found at [%i][%i]\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
                locked[pairs[pairCounter].winner][pairs[pairCounter].loser] = true;
                printf("Locking pair [%i][%i] <---------------------------------\n", pairs[pairCounter].winner, pairs[pairCounter].loser);
                BlankRecursionCall();
            }
        }
    }
}

void