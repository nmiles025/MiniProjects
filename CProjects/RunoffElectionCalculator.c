#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // look for candidate called name
    for (int i = 0; i < candidate_count; i++)
    {
        string lname = (string) candidates[i].name;
        //int sname = ;
        if (strcmp((string) name, (string) lname) == 0)
        {
            // If found update preferences so they are the voters rank prefernce and return true
            // preferences[i][j] is jth preference for voter i
            preferences[voter][rank] = i;
            return true;
        }
    }
    // Else return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loops through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Determines the highest ranking candidate
        int j = 0;
        for (int x = 0; x < candidate_count; x++)
        {
            int mainpref = preferences[i][j];
            if (candidates[mainpref].eliminated == false)
            {
                candidates[mainpref].votes++;
                break;
            }
            else if (candidates[mainpref].eliminated == true)
            {
                j++;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int votecount = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        votecount += candidates[i].votes;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > votecount / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int counter = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes > 0 && candidates[i].votes < counter)
        {
            counter = candidates[i].votes;
        }
    }
    return counter;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int counter[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            counter[i] = 0;
        }
        else if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            counter[i] = 0;
        }
        else
        {
            return false;
        }

    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}