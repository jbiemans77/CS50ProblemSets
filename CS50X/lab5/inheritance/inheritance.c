// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;
const int NUMBER_OF_PARENTS = 2;

// Function Prototypes:
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();
person *InitializeGeneration(person *currentPerson, int generations);
//person *InitializeTopGeneration(person *currentPerson);
char GetRandomAlleleFromParents(person *person);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *currentPerson = malloc(sizeof(person));
    currentPerson = InitializeGeneration(currentPerson, generations);

    // TODO: Return newly created person
    return currentPerson;
}

person *InitializeGeneration(person *currentPerson, int generations)
{
    for (int parentCounter = 0; parentCounter < NUMBER_OF_PARENTS; parentCounter++)
    {
        // Start with final generation
        person *parent = NULL;
        char allele = random_allele();

        // If there are still generations left to create, revise variables for new generation.
        if (generations > 1)
        {
            parent = create_family(generations - 1);
            allele = GetRandomAlleleFromParents(parent);
        }

        // TODO: Set parent pointers for current person
        currentPerson -> parents[parentCounter] = parent;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        currentPerson -> alleles[parentCounter] = allele;
    }

    return currentPerson;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p -> parents[0]);
    free_family(p -> parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

// Randomly chooses a blood type allele.
char GetRandomAlleleFromParents(person *person)
{
    int r = rand() % 2;
    if (r == 0)
    {
        return person -> alleles[0];
    }
    else
    {
        return person -> alleles[1];
    }
}
