#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);
int compute_coleman_liau_index(int, int, int);

int main(void)
{
    string text;

    // get some text from the user
    text = get_string("Text: ");

    // get the letter count
    int letters = count_letters(text);

    // get the word count
    int words = count_words(text);

    // get the sentence count
    int sentences = count_sentences(text);

    // compute the coleman-liau index
    int index = compute_coleman_liau_index(letters, words, sentences);

    // conditional output if the index is below 1 or above 16
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// compute the Coleman-Liau index
int compute_coleman_liau_index(int letters, int words, int sentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the "average number of letters per 100 words"
    // S is the "average number of sentences per 100 words"
    float l = (float) letters / (((float) words) / 100);
    float s = (float) sentences / (((float) words) / 100);

    int index = (int) round(0.0588 * l - 0.296 * s - 15.8);
    return index;
}


// function to count the sentences in a string
int count_sentences(string s)
{
    int count = 0;
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            count++;
        }
        i++;
    }

    return count;
}

// function to count the words in a string
int count_words(string s)
{
    int count = 0;
    int i = 0;

    // if the first character is not the terminal, then there is 1 word
    if (s[0] != '\0')
    {
        count++;
    }

    // under the assumption that the string does not end in spaces,
    // then after the first word, each space means a word
    while (s[i] != '\0')
    {
        // if the current character is a letter add 1 to the letter count
        if (s[i] == ' ')
        {
            count++;
        }
        i++;
    }

    return count;
}

// function to count the letters in a string
int count_letters(string s)
{
    int count = 0;
    int i = 0;

    while (s[i] != '\0')
    {
        // if the current character is a letter add 1 to the letter count
        if ((s[i] >= 'a' && s[i] <= 'z') ||
            (s[i] >= 'A' && s[i] <= 'Z'))
        {
            count++;
        }
        i++;
    }

    return count;
}