def main():
    # define menu
    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }
    # ask user for item until control + d is inserted
    try:
        sum = 0
        while True:
            user_item = input("Item: ").title()
            # print the cost of the item from the menu
            try:
                sum += menu[user_item]
                print(f"${sum:.2f}")
            except KeyError:
                ...
    except EOFError as cntrl_d:
        ...

main()
