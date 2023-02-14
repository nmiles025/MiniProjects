#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isint(string chkstring);
int rotateupper(int key, int asciival);
int rotatelower(int key, int asciival);
int getkey(int thekey);

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument
    string skey = argv[1];
    if (argc == 2 && isint(skey) != 0)
    {
        int newkey = atoi(skey);
        int key = getkey(newkey);
        string ptext = get_string("plaintext: ");

        //Rotate the characters
        int len = strlen(ptext);
        printf("ciphertext: ");
        for (int i = 0; i < len; i++)
        {
            char ch = ptext[i];
            int asciival = (int) ch;
            // Calls the function to rotate the uppercase characters
            if (asciival >= 65 && asciival <= 90)
            {
                int newasciival = rotateupper(key, asciival);
                printf("%c", newasciival);
            }
            // Calls the function to rotate the lowercase characters
            else if (asciival >= 97 && asciival <= 122)
            {
                int newasciival = rotatelower(key, asciival);
                printf("%c", newasciival);
            }
            // Returns non-alpha characters
            else
            {
                printf("%c", ch);
            }
        }
        printf("\n");
    }
    // Makes sure the user inputs correctly
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

// Make sure every character in argv[1] is a digit
int isint(string chkstring)
{
    int counter = 0;
    string c = chkstring;
    //printf("%s\n", chkstring);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
        //char ch = chkstring[i];
        if (isdigit(chkstring[i]) != 0)
        {
            counter ++;
        }
        else
        {
            return 0;
        }

    return counter;
}

// Gets the key and ensures it is under 26
int getkey(int thekey)
{
    if (thekey > 26)
    {
        int newkey = thekey % 26;
        return newkey;
    }
    else
    {
        int newkey = thekey;
        return newkey;
    }

}

// Rotates the uppercase characters
int rotateupper(int key, int asciival)
{
    int newasc = asciival + key;
    if (newasc > 90)
    {
        return newasc - 26;
    }
    else
    {
        return newasc;
    }
}

// Rotates the lowercase characters
int rotatelower(int key, int asciival)
{
    int newasc = asciival + key;
    if (newasc > 122)
    {
        return newasc - 26;
    }
    else
    {
        return newasc;
    }
}
