#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for their text
    string text = get_string("Text: ");
    // Parse through the text and count variables
    double letteramt = count_letters(text);
    double wordamt = count_words(text);
    double sentenceamt = count_sentences(text);
    // Determine the index number
    double lettaverage = (letteramt / wordamt) * 100;
    double sentenceave = (sentenceamt / wordamt) * 100;
    double lindexur = (0.0588 * lettaverage) - (0.296 * sentenceave) - 15.8;
    double lindex = round(lindexur);
    //int lindexr = round(lindexur);
    //printf("%f", lindex);
    // Output the grade level
    if (lindex <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (lindex > 1 && lindex < 16)
    {
        printf("Grade %d\n", (int)lindex);
    }
    else if (lindex >= 16)
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int letteramt = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        // Gets character
        char och = text[i];
        // Converts character to uppercase
        char ch = toupper(och);
        // Gets the ascii value of each character
        int asciival = (int) ch;
        // Determines if letter
        if (asciival >= 65 && asciival <= 90)
        {
            letteramt++;
        }
        else
        {
            letteramt += 0;
        }
    }
    return  letteramt;
}

int count_words(string text)
{
    int wordamt = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char och = text[i];
        char ch = toupper(och);
        int asciival = (int) ch;
        // Determines if space
        if (asciival == 32)
        {
            wordamt++;
        }
        else
        {
            wordamt += 0;
        }
    }
    wordamt ++;
    return wordamt;
}

int count_sentences(string text)
{
    int sentenceamt = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char och = text[i];
        char ch = toupper(och);
        int asciival = (int) ch;
        // Determines if period, question mark, or exclamation point
        if (asciival == 33 || asciival == 46 || asciival == 63)
        {
            sentenceamt++;
        }
        else
        {
            sentenceamt += 0;
        }
    }
    return sentenceamt;
}
