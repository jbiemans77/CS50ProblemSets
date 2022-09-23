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
void PopulateCandidatesArray(string argv[]);
void ClearGraphOfLockedInPairs();
int QueryForVotes(int voter_count);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool CheckForLoopInLockedPairs(int candidateToWatchFor, int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Throw error if over maximum number of candadates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
    PopulateCandidatesArray(argv);

    // Clear graph of locked in pairs
    ClearGraphOfLockedInPairs();

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    int voteQueryResults = QueryForVotes(voter_count);

    // If results were not 0 return value as error code
    if (voteQueryResults != 0)
    {
        return voteQueryResults;
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

void PopulateCandidatesArray(string argv[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }
}

void ClearGraphOfLockedInPairs()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
}

int QueryForVotes(int voter_count)
{
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool isValidName = false;

    // Check if candidate name is valid;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            isValidName = true;
            ranks[rank] = i;
            return true;
        }
    }

    // Check if name has already been used (future implimentation)
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int ranking = 0; ranking < candidate_count - 1; ranking++)
    {
        for (int secondCounter = ranking + 1; secondCounter < candidate_count; secondCounter++)
        {
            preferences[ranks[ranking]][ranks[secondCounter]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int candidateNumber = 0; candidateNumber < candidate_count; candidateNumber++)
    {
        for (int rivalNumber = 0; rivalNumber < candidate_count; rivalNumber++)
        {
            int votesForFirstCandidate = preferences[candidateNumber][rivalNumber];
            int votesForSecondCandidate = preferences[rivalNumber][candidateNumber];

            if (votesForFirstCandidate > votesForSecondCandidate)
            {
                pairs[pair_count].winner = candidateNumber;
                pairs[pair_count].loser = rivalNumber;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int unsortedPairsCounter = pair_count - 1; unsortedPairsCounter >= 0 ; unsortedPairsCounter--)
    {
        for (int currentIndex = 0; currentIndex <= unsortedPairsCounter - 1; currentIndex++)
        {
            int nextIndex = currentIndex + 1;

            int currentIndexStrengthOfVictory = preferences[pairs[currentIndex].winner][pairs[currentIndex].loser];
            int nextIndexStrengthOfVictory = preferences[pairs[nextIndex].winner][pairs[nextIndex].loser];

            if (currentIndexStrengthOfVictory < nextIndexStrengthOfVictory)
            {
                pair temp = pairs[currentIndex];
                pairs[currentIndex] = pairs[nextIndex];
                pairs[nextIndex] = temp;
            }
        }
    }
    return;
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

            //printf("1 Check if [%i][%i] is locked.\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
            if (locked[pairs[pairCounter].loser][pairs[secondPairCounter].loser] == true)
            {
                //printf("Lock found at [%i][%i]\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
                //printf("Found lock.  pairCounter = %i.  secondPairCounter = %i.  [%i][%i]\n", pairCounter, secondPairCounter, pairs[pairCounter].loser, pairs[secondPairCounter].loser);

                for (int fourthPairCounter = 0; fourthPairCounter < pair_count; fourthPairCounter++)
                {
                    //printf("Looping fourthPairCounter: %i\n", fourthPairCounter);
                    //printf("2 Check if [%i][%i] is locked.\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                    if(locked[pairs[thirdPairCounter].loser][pairs[fourthPairCounter].loser] == true)
                    {
                        //printf("Lock found at [%i][%i]\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                        //printf("Found lock second loop.  thirdPairCounter = %i.  fourthPairCounter = %i.  [%i][%i]\n", thirdPairCounter, fourthPairCounter, pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);

                        //printf("3 Check if [%i] = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);
                        if (pairs[fourthPairCounter].loser == pairs[pairCounter].winner)
                        {
                            //printf("[%i] DOES = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);

                            //printf("looser fourthPairCounter == winner pairCounter\n");
                            //printf("UNLOCKING PAIR [%i][%i] to false <----------------------------------\n", pairs[pairCounter].winner, pairs[pairCounter].loser);
                            locked[pairs[pairCounter].winner][pairs[pairCounter].loser] = false;
                            secondPairCounter = pair_count;
                            break;
                        }
                        else
                        {
                            //printf("[%i] DOES NOT = [%i].\n", pairs[fourthPairCounter].loser, pairs[pairCounter].winner);
                            //printf("Resetting fourthPairCounter\n");
                            thirdPairCounter = fourthPairCounter;
                            fourthPairCounter = 0;
                        }
                    }
                    //printf("Lock NOT found at [%i][%i]\n", pairs[thirdPairCounter].loser, pairs[fourthPairCounter].loser);
                }
            }
            else
            {
                //printf("Lock NOT found at [%i][%i]\n", pairs[pairCounter].loser, pairs[secondPairCounter].loser);
                locked[pairs[pairCounter].winner][pairs[pairCounter].loser] = true;
                //printf("Locking pair [%i][%i] <---------------------------------\n", pairs[pairCounter].winner, pairs[pairCounter].loser);
            }
        }
    }
}

/*
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winnerOfThisPair = pairs[i].winner;
        int loserOfThisPair = pairs[i].loser;

        // Check for loop in Graph
        bool isALoop = CheckForLoopInLockedPairs(winnerOfThisPair, winnerOfThisPair, loserOfThisPair);

        if (!isALoop)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}
*/

// Recursion function to check for a loop
bool CheckForLoopInLockedPairs(int candidateToWatchFor, int winner, int loser)
{
    bool loopFound = false;

    for (int counter = 0; counter < candidate_count; counter++)
    {
        if (loopFound)
        {
            return true;
        }

        if (loser == candidateToWatchFor)
        {
            return true;
        }

        if (locked[loser][counter])
        {
            loopFound = CheckForLoopInLockedPairs(candidateToWatchFor, loser, counter);
        }

    }

    return loopFound;
}

// Print the winner of the election
void print_winner(void)
{
    int possibleWinningCandidateNumber = -1;
    int winningCandidateNumber = -1;
    bool winnerFound = false;

    // Winner is whoever has all false in their locked looser array
    for (int counter = 0; counter < candidate_count; counter++)
    {
        bool isLooser = false;
        possibleWinningCandidateNumber = counter;

        for (int candidateNumber = 0; candidateNumber < candidate_count; candidateNumber++)
        {
            // If the candidate ever lost a locked pair, they are not the winner
            if (locked[candidateNumber][possibleWinningCandidateNumber] == true)
            {
                isLooser = true;
                break;
            }
        }

        // If they are not the looser, than they must be the winner!
        if (!isLooser)
        {
            winnerFound = true;
            winningCandidateNumber = possibleWinningCandidateNumber;
            break;
        }
    }

    printf("%s\n", candidates[winningCandidateNumber]);

    return;
}