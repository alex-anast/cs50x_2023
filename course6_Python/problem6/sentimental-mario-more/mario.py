def main():
    # get pyramid height with correct check - implement do-while loop
    while True:
        try:
            pyramid_height = int(input("Give height of the pyramid: "))
            # accept answer if only:
            if pyramid_height > 0 and pyramid_height < 9:
                break
        except:
            ...

    print_pyramid(pyramid_height)


def print_pyramid(size):
    """print pyramid per the input size, where size is  pyramid height"""
    # for each line
    for i in range(size):
        # initialize string
        line = ""
        # add the necessary spaces before the hashes for the mirroring effect
        for j in range(size - i - 1):
            line += " "
        # print the necessary number of hashes
        for hash in range(i + 1):
            line += "#"
        # add two spaces
        line += "  "
        # and repeat the hashes for the mirroring effect
        for hash in range(i + 1):
            line += "#"
        # and print:
        print(line)


# set up main
if __name__ == "__main__":
    main()
