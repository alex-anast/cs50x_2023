# Bank

In a file called bank.py, a program that prompts the user for a greeting is implemented. If the greeting starts with “hello”, output is $0. If the greeting starts with an “h” (but not “hello”), output is $20. Otherwise, is output $100. Any leading whitespace is ignored in the user’s greeting, and the user’s greeting is treated case-insensitively.

## Testing

This is the introduction to the python language. This is one of the most basic programs. I took the initiative and started practicing in writing my own tests.

## PyTest Implementation

Steps to implement the most basic testing in PyTest:

- Create a test case for every functionality in the code. This is why modularity in development is a "best practice".
- Every function has to return something, printing happens from main.
- execute:

```lang-bash
$ pytest bank.py
```

Results:

========================================================== test session starts =========================================================== \
platform linux -- Python 3.10.6, pytest-7.3.1, pluggy-1.0.0                                                                                \
rootdir: /home/alex_anast/workspace/cs50x_2023/course5_Python/bank                                                                         \
collected 3 items                                                                                                                          \
bank.py ...                                                                                                                         [100%] \
============================================================ 3 passed in 0.04s ===========================================================
