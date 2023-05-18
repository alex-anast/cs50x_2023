import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    # A dictionary where index is the state, and contents will be the date and the cases as another dictionary
    states_dict = {}

    # Can only be done once
    for row in reader:
        # Get the values of interest
        state = row["state"]
        date  = row["date"]
        cases = row["cases"]

        # Check if the state is already present in the dictionary
        if state in states_dict:
            # Retrieve the dictionary of cases by date for the state
            cases_by_date_dict = states_dict[state]
        else:
            # Create a new dictionary for the state
            cases_by_date_dict = {}

        # Add the cases to the dictionary for the corresponding date
        cases_by_date_dict[date] = cases

        # Update the dictionary for the state
        states_dict[state] = cases_by_date_dict
        
    # Create a new dictionary to store the 14 most recent days of new cases by state
    states_dict_new = {}

    # Iterate over the dictionary and keep only the most recent values
    for state, cases_by_date_dict in states_dict.items():
        # Get the dates and sort them in reverse order
        dates_list = sorted(cases_by_date_dict.keys(), reverse=True)

        # Create a new dictionary for the state with the most recent 14 days
        cases_by_date_dict_new = {}
        for date in dates_list[:15]:  # Include the most recent 14 days
            cases_by_date_dict_new[date] = cases_by_date_dict[date]
        
        new_cases = cases_by_date_dict_new
        # Calculate the new cases for each day and update the dictionary
        for i in range(1, len(dates_list)):
            current_date = dates_list[i]
            previous_date = dates_list[i - 1]
            current_cases = int(cases_by_date_dict[current_date])
            previous_cases = int(cases_by_date_dict[previous_date])
            new_cases[current_date] = current_cases - previous_cases
        new_cases[dates_list[0]] = 0 # set the first day as default 0
        
        # Update the dictionary for the state
        states_dict_new[state] = new_cases

    return states_dict_new


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        cases = 0  # Reset cases to 0 for each state
        for date in new_cases[state]:  # Sorted in increasing order
            cases += int(new_cases[state][date])
        average = cases / 14
        print(f"{average:.2f}")


main()
