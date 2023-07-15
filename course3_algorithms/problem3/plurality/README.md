# Plurality

This program simulates a plurality vote election, where every voter gets to vote for one candidate and the candidate with the greatest number of votes is declared the winner of the election.

## Background

Elections come in all shapes and sizes. In the UK, the Prime Minister is officially appointed by the monarch, who generally chooses the leader of the political party that wins the most seats in the House of Commons. The United States uses a multi-step Electoral College process where citizens vote on how each state should allocate Electors who then elect the President.

Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”).

## Specification

This program includes two functions:

1. vote: takes a single argument, a string called name, representing the name of the candidate who was voted for. If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot. If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot.
2. print_winner: prints out the name of the candidate who received the most votes in the election, and then prints a newline. It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. In that case, you should output the names of each of the winning candidates, each on a separate line.

## Usage

To run the program, use the following command:

```lang-bash
$ ./plurality [candidate1] [candidate2] ...
```

Once the program is running, the user will be prompted to enter the number of voters, and then to enter each voter's selection. The program will then output the name of the winning candidate(s).

## Learning Goals

- Understanding of algorithms and data structures, such as arrays and structs.

## Extra

The problem had a tricky specification: if two people are both winners, then they should be both printed out. There are numerous ways to solve this:

1. sort the struct and print the first elements with equal votes
2. find the maximum and then print any candidate with as many votes (unsorted, simpler)
3. create a temporary data struct that will keep the winners while we traverse the original struct (too much space)
4. etc.

I chose the first option; I implemented Mergesort and I played around with the algorithm. Of course this is not the most efficient way to do it, but it was fun for sure.
