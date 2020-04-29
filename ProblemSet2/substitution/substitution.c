// implement a substitution cipher

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string convert_to_upper(string);
bool valid_key(string);
string cipher(string, string);

int main(int argc, string argv[])
{
    // must have exactly the program and one input string
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // convert the key (second argument) to all upper case
    string key = argv[1];
    key = convert_to_upper(key);

    if (valid_key(key) != 1)
    {
        printf("Invalide Key - must be 26 unique letters\n");
        return 1;
    }

    // we've got a valid key at this point -- now get some plaintext to convert
    string plaintext = get_string("plaintext: ");
    string ciphertext = cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string cipher(string s, string key)
{
    int len = strlen(s);
    string c = s;

    for (int i = 0; i < len; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            // upper case condition
            c[i] = key[s[i] - 'A'];
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            // lower case condition
            c[i] = tolower(key[toupper(s[i]) - 'A']);
        }
        else
        {
            c[i] = s[i];
        }
    }

    return c;
}

// validate the key - assume already converted to all uppercase
bool valid_key(string k)
{
    // must be 26 characters
    if (strlen(k) != 26)
    {
        return 0;
    }

    // create an array of characters initialized to all zeros to indicate that letters haven't been used
    int used_letters[26];
    for (int i = 0; i < 26; i++)
    {
        used_letters[i] = 0;
    }

    // go through the key and make sure all characters are letters and only used once
    for (int i = 0; i < 26; i++)
    {
        // the ith character is valide if it is a letter and not already used
        if (k[i] >= 'A' && k[i] <= 'Z' && used_letters[k[i] - 'A'] == 0)
        {
            // the character is valid, so set the letter to used and move on
            used_letters[k[i] - 'A'] = 1;
        }
        else
        {
            // the character is not valid so return 0
            return 0;
        }
    }

    // at this point, the key is all letters and each letter is only used once
    return 1;
}

// convert each character to upper case for consistency
string convert_to_upper(string s)
{
    int i = 0;

    while (s[i] != '\0')
    {
        s[i] = toupper(s[i]);
        i++;
    }

    return s;
}