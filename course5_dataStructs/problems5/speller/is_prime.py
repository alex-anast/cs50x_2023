import math


def is_prime(n):
    """Return True if n is prime, else False."""
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


for i in range(1000, 1200):
    if is_prime(i):
        print(i)
