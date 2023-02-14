from cs50 import get_string


def count_letters(text):
    letteramt = 0
    for i in text:
        # Gets character
        och = i
        # Converts character to uppercase
        ch = och.upper()
        # Gets the ascii value of each character
        asciival = ord(ch)
        # Determines if letter
        if asciival >= 65 and asciival <= 90:
            letteramt += 1
        else:
            letteramt += 0
    return letteramt


def count_words(text):
    wordamt = 0
    for i in text:
        och = i
        ch = och.upper()
        asciival = ord(ch)
        # Determines if space
        if asciival == 32:
            wordamt += 1
        else:
            wordamt += 0
    wordamt += 1
    return wordamt


def count_sentences(text):
    sentenceamt = 0
    for i in text:
        och = i
        ch = och.upper()
        asciival = ord(ch)
        # Determines if period, question mark, or exclamation point
        if asciival == 33 or asciival == 46 or asciival == 63:
            sentenceamt += 1
        else:
            sentenceamt += 0
    return sentenceamt


# Prompt the user for their text
text = get_string("Text: ")
# Parse through the text and count variables
letteramt = count_letters(text)
wordamt = count_words(text)
sentenceamt = count_sentences(text)
# Determine the index number
lettaverage = (letteramt / wordamt) * 100
sentenceave = (sentenceamt / wordamt) * 100
lindexur = (0.0588 * lettaverage) - (0.296 * sentenceave) - 15.8
lindex = round(lindexur)

if lindex <= 1:
    print("Before Grade 1\n")

elif lindex > 1 and lindex < 16:
    print("Grade {0}".format(lindex))

elif (lindex >= 16):
    print("Grade 16+\n")