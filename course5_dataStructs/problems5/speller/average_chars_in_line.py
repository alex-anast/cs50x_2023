with open("dictionaries/large", "r") as file:
    lines = file.readlines()
    total_chars = 0
    for line in lines:
        line = line.strip() # remove newline character at the end of the line
        line_chars = len(line)
        total_chars += line_chars
        # print(f"Line {lines.index(line)+1}: {line_chars} characters")
    avg_chars = total_chars / len(lines)
    print(f"Average character count: {avg_chars:.2f}")