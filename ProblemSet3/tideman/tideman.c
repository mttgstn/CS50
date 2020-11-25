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
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_locked(void);
bool reachable(int i, int j);

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
    // find the candidate name and record the ranks[rank] as that candidates index
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // add one to preferences[i][j] every time a candidate ranks higher than another
    // iterate through the ranks array of preferences for a single voter
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // add a pair of winner/loser for each pair of candidates where one pair is prefered over the other
    // for each pair increment pair_count
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // use selection sort since its easy to implement
    for (int i = 0; i < pair_count - 1; i++)
    {
        int biggest_preference = preferences[pairs[i].winner][pairs[i].loser];
        int biggest_pair = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > biggest_preference)
            {
                biggest_preference = preferences[pairs[j].winner][pairs[j].loser];
                biggest_pair = j;
            }
        }
        // if biggest_pair is not i then swap the biggest pair with the i_th pair
        if (biggest_pair != i)
        {
            pair temp_pair;
            temp_pair.winner = pairs[i].winner;
            temp_pair.loser = pairs[i].loser;
            pairs[i].winner = pairs[biggest_pair].winner;
            pairs[i].loser = pairs[biggest_pair].loser;
            pairs[biggest_pair].winner = temp_pair.winner;
            pairs[biggest_pair].loser = temp_pair.loser;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (reachable(pairs[i].loser, pairs[i].winner) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool reachable(int i, int j)
{
    // is j already reachable from i
    if (locked[i][j] == true)
    {
        return true;
    }
    else
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[i][k] == true && k != i && k != j)
            {
                if (reachable(k, j) == true)
                {
                    return true;
                }
            }
        }
    }

    return false;

}

void print_locked(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("1 ");
            }
            else if (locked[i][j] == false)
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Print the winner of the election
void print_winner(void)
{
    // find the source node in locked - the node with no edges pointing to it
    for (int i = 0; i < candidate_count; i++)
    {
        int out_edges = 0;
        int in_edges = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                out_edges++;
            }
            if (locked[j][i] == true)
            {
                in_edges++;
            }
        }

        if (out_edges > 0 && in_edges == 0)
        {
            // this is the source - with assumption that there is only one source
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

