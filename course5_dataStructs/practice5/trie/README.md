# Trie

## Learning Goals

- Learn more about data structures
- Work with a trie

## Background

Imagine you just rescued a dog and you’re deciding on a name. You found a file online with a list of about 150 of the most popular dog names! You are curious as to whether or not the names you are considering are on this list. Tries are great for data lookups; complete the functionalities with this data structure.

## Understanding

Trie is a data structure able to cover the acts of Insertion, Deletion and Lookup in a fixed amount of time, or in software engineering terms, in O(1), but with the cost of expensive memory usage. The implementation consists of pointer handling.

## Implementation

The trie itself is implemented through the creative use of several structs called node. Each node in a trie has an array of (potential) children, with size 26 — one potential child for each letter of the alphabet. Adding words to this trie, notice that — for every letter in a word — we create a new node child whose parent is either the root node (for the first letter) or the previous letter (if not the first letter). On the very last letter, we set the is_word attribute of the child node to true. Now, checking if a word is in our trie is as easy as following each letter of that word through our trie. If we get to the final letter and see that is_word is true, well, that name is in our trie.

## Usage

```lang-bash
......
```

## Thought Question

When might you want to use a trie as a data structure? When might you not?

A trie, also known as a prefix tree, is a tree-like data structure commonly used in computer science and information retrieval applications. It is particularly useful when working with large datasets and searching for patterns or prefixes.

Pros and usecases:

- **Autocomplete or suggestion systems**: Tries are commonly used in autocomplete or suggestion systems, such as search engines or typing assistants, where the system needs to suggest or complete words based on user input.
- **Spell-checking**: Tries can be used to implement spell-checking algorithms, where the system needs to check if a word is spelled correctly or not.
- **Dictionary implementations**: Tries can be used to implement dictionaries or other data structures where you need to search for a key based on a prefix or partial match.
- **IP routing**: Tries can be used to represent and search routing tables for IP addresses in computer networks.

Cons and when to avoid:

- **Limited character sets**: Tries can be less efficient when working with a limited character set, such as binary digits or DNA sequences. In such cases, other data structures may be more efficient. Having to go several layers deep almost makes it have a linked list functionality.
- **Memory constraints**: Tries can require a lot of memory, especially when working with large datasets or long strings. In memory-constrained environments, other data structures may be more appropriate.
- **Low fan-out**: If the fan-out, or the number of branches at each level of the tree, is low, then the trie may be less efficient. In such cases, other data structures may be more appropriate. Similar problem to the first.
