class Jar:
    def __init__(self, capacity=12):
        '''
        Initialize a cookie jar with the given capacity,
        which represents the maximum number of cookies
        that can fit in the cookie jar. 
        '''
        self._capacity = capacity # convention to use internally in the class
        self._cookies = 0
        if self._capacity < 0:
            raise ValueError

    def __str__(self):
        '''
        return n times the cookie symbol 🍪
        where n is the number of cookies in the cookie jar.
        '''
        return self._cookies * "🍪"

    def deposit(self, n):
        '''
        add n cookies to the cookie jar.
        '''
        if self._cookies + n > self._capacity:
            raise ValueError
        self._cookies += n

    def withdraw(self, n):
        '''
        withdraw n cookies from the cookie jar.
        '''
        if self._cookies < n:
            raise ValueError
        self._cookies -= n

    @property
    def capacity(self):
        '''
        returns the cookie jar's capacity.
        '''
        return self._capacity

    @property
    def size(self):
        '''
        return the number of cookies in the cookie jar.
        '''
        return self._cookies


def main():
    jar = Jar(capacity=10)
    print(str(jar.capacity))    # test capacity
    print(str(jar))             # test __str__
    print(str(jar.size))        # test size == number of cookies
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))


main()
