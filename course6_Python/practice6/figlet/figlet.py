import pyfiglet
import sys
import random
import io
from contextlib import redirect_stdout
import unittest


all_fonts = pyfiglet.FigletFont.getFonts()


def main():
    mode = check_input()
    text = user_input()
    print(format_text(mode, text))


def check_input():
    number_of_arguments = len(sys.argv)
    # mode Zero == random font
    if number_of_arguments == 1:
        return 0
    # mode Two  == specific font
    elif number_of_arguments == 3:
        if sys.argv[1] in ["-f", "--font"] and sys.argv[2] in all_fonts:
            return 2
        else:
            print("Invalid usage")
            sys.exit(1)
    else:
        print("Invalid usage")
        sys.exit(1)


def user_input():
    u_i = input("Write something: ")
    return u_i


def format_text(mode, text):
    if mode == 0:
        return pyfiglet.figlet_format(text=text, font=random.choice(all_fonts))
    else:  # can only be mode == 2 now
        return pyfiglet.figlet_format(text=text, font=sys.argv[2])


if __name__ == "__main__":
    main()
