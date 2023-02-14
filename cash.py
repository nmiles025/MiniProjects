from cs50 import get_float


def calculate_quarters(cents):
    quarts = cents // 0.25
    return quarts


def calculate_dimes(cents):
    dims = cents // 0.10
    return dims


def calculate_nickels(cents):
    nicks = cents // 0.05
    return nicks


def calculate_pennies(cents):
    penns = cents // 0.01
    return penns
    

# Ask how many cents the customer is owed
n = -1
while n < 0:
    cents = get_float("How much change do you need back: ")
    n = cents

# Calculate the number of quarters to give the customer
quarters = calculate_quarters(cents)
cents = (cents - quarters * 0.25)
cents = round(cents, 2)

# Calculate the number of dimes to give the customer
dimes = calculate_dimes(cents)
cents = (cents - dimes * 0.10)
cents = round(cents, 2)

# Calculate the number of nickels to give the customer
nickels = calculate_nickels(cents)
cents = (cents - nickels * 0.05)
cents = round(cents, 2)

# Calculate the number of pennies to give the customer
pennies = calculate_pennies(cents)
cents = (cents - pennies * 0.01)
cents = round(cents, 2)

# Sum coins
coins = quarters + dimes + nickels + pennies

# Print total number of coins to give the customer
print("Change owed: {0}".format(int(coins)))