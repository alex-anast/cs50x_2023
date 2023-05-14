def main():
    ui = user_input()
    print(greet(ui))


# prompt the user for a greeting
def user_input():
    return input("Give me a greeting: ")


def greet(user_input):
    # if the greeting starts with hello
    if user_input[:5].lower() == "hello":
        return "$0"
    # else if it starts with just 'h'
    elif user_input[0].lower() == 'h':
        return "$20"
    else:
        return "$1000"

# executed only if it's not imported by someone else
if __name__ == '__main__':
    main()

def test_hello():
    assert greet("Hello, world!") == "$0"

def test_h():
    assert greet("Hi, there!") == "$20"

def test_default():
    assert greet("Goodbye.") == "$1000"