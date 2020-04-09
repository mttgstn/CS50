// program to build two adjacent pyramids out of blocks - using hashes (#)
// like in Nintendo's Super Mario Brothers

#include <cs50.h>
#include <stdio.h>

int get_int_in_range(int, int);
void build_double_pyramid(int);

int main(void)
{
    // start by getting a height (int) within a range x,y
    int x = 1;
    int y = 8; 
    int height = get_int_in_range(x, y);

    build_double_pyramid(height);    
}

// function to build a double pyramid of height h
// e.g. for heigh 3
//   #  #  
//  ##  ##
// ###  ###
void build_double_pyramid(int h)
{
    // for each level
    for (int i = 1; i <= h ; i++)
    {
        // left pyramid
        for (int j = 0; j < h; j++)
        {
            // spaces until we get to row number than hashes
            if ((h - j) > i) 
            {
                printf(" ");
            }
            else 
            {
                printf("#");
            }
        }

        // build gap
        printf("  ");

        // right pyramid - no extra whitespace
        for (int j = 0; j < h; j++)
        {
            // hashes until we get to row number than spaces
            if (j < i) 
            {
                printf("#");
            }
        }

        // start a new row
        printf("\n");
    }
}

// function to get an integer in range [i,j] from user
int get_int_in_range(int i, int j)
{
    int input = 0;
    do 
    {
        input = get_int("Height: "); 
    }
    while (input < i || input > j);

    return input; 
}
