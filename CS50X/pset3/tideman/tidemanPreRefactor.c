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
    int winningVoteCount;
}
pair;

typedef struct
{
    int winningVoteCount;
    int losingVoteCount;
    int winningFactor;
}
pairExtra;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pairExtra pairsExtra[MAX * (MAX - 1) / 2];

pair sortedPairs[MAX * (MAX - 1) / 2];
pairExtra sortedPairsExtra[MAX * (MAX - 1) / 2];

int pair_count;
int sortedPairCount;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void clearPairAtIndex(int index);
bool CheckForLoopInLockedPairs(int candidateToWatchFor, int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
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
    for (int ranking = 0; ranking < candidate_count-1; ranking++)
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

            if(votesForFirstCandidate > votesForSecondCandidate)
            {
                pairs[pair_count].winner = candidateNumber;
                pairs[pair_count].loser = rivalNumber;
                pairs[pair_count].winningVoteCount = votesForFirstCandidate;
                pairsExtra[pair_count].losingVoteCount = votesForSecondCandidate;
                pairsExtra[pair_count].winningFactor = votesForFirstCandidate - votesForSecondCandidate;
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

            int currentIndexHighestVoteCount = preferences[pairs[currentIndex].winner][pairs[currentIndex].loser];
            int nextIndexHighestVoteCount = preferences[pairs[nextIndex].winner][pairs[nextIndex].loser];

            if (currentIndexHighestVoteCount < nextIndexHighestVoteCount)
            {
                pair temp = pairs[currentIndex];
                pairs[currentIndex] = pairs[nextIndex];
                pairs[nextIndex] = temp;
            }
        }
    }
    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winnerOfThisPair = pairs[i].winner;
        int loserOfThisPair = pairs[i].loser;

        // Check for loop in Graph
        bool isALoop = CheckForLoopInLockedPairs(winnerOfThisPair, winnerOfThisPair, loserOfThisPair);

        if(!isALoop)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winningCandidateNumber = -1;
    bool winnerFound = false;

    // Winner is whoever has all false in their locked looser array
    for (int counter = 0; counter < candidate_count; counter++)
    {
        bool isLooser = false;
        winningCandidateNumber = counter;

        for (int candidateNumber = 0; candidateNumber < candidate_count; candidateNumber++)
        {
            if(locked[candidateNumber][counter] == true)
            {
                isLooser = true;
                break;
            }
        }

        if (!isLooser)
        {
            winnerFound = true;
            break;
        }
    }

    printf("%s\n", candidates[winningCandidateNumber]);

    return;
}

void clearPairAtIndex(int index)
{
    pairs[index].winner = 0;
    pairs[index].loser = 0;
    pairsExtra[index].winningVoteCount = 0;
    pairsExtra[index].losingVoteCount = 0;
    pairsExtra[index].winningFactor = 0;

    return;
}

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