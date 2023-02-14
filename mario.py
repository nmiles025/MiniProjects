from cs50 import get_int

# Gets the input from the user and converts it to an integer
while True:
    n = get_int("Height: ")
    if n <= 8 and n >= 1:
        break


# Prints the correct amount of rows
space = " "
tag = "#"
counter = 0
# Loops through each row and column and prints the correct number of hashes
for i in range(n, 0, -1):
    counter += 1
    spaceAmount = n - (counter + 1)
    tagAmount = n - i + 1
    if i > 1:
        print(" " * spaceAmount, "#" * tagAmount)
    else:
        print("#" * tagAmount)