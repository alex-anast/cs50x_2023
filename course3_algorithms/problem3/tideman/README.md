# Tideman

A program that runs a Tideman election.

## Background

Plurality vote has a simple algorithm to determine the winner of an election. Every voter gets one vote, and the candidate with the most votes wins. But the plurality vote does have some disadvantages. What happens, for instance, in an election with three candidates, and the ballots are cast in such a way that there is a tie between Alice and Bob?

There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate, and rank them in order of preference. Ranked choice voting can also solve yet another potential drawback of plurality voting.

The Tideman voting method (also known as “ranked pairs”) is a ranked-choice voting method that’s guaranteed to produce the Condorcet winner of the election if one exists. The Tideman method works by constructing a “graph” of candidates, where an arrow (i.e. edge) from candidate A to candidate B indicates that candidate A wins against candidate B in a head-to-head matchup.

## Implementation

The Tideman algorithm works by constructing a “graph” of candidates, where an arrow (i.e. edge) from candidate A to candidate B indicates that candidate A wins against candidate B in a head-to-head matchup.

The Tideman algorithm must be careful to avoid creating cycles in the candidate graph. The algorithm locks in the strongest edges first, since those are arguably the most significant. In particular, the Tideman algorithm specifies that matchup edges should be “locked in” to the graph one at a time, based on the “strength” of the victory (the more people who prefer a candidate over their opponent, the stronger the victory). So long as the edge can be locked into the graph without creating a cycle, the edge is added; otherwise, the edge is ignored.

The program should prompt the user for the number of voters, and then should prompt the user for each voter’s ranks for all candidates. The program should then compute the Tideman winner and print it out.

## Usage

```lang-bash
$ ./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
```

## Learning Goals

- Implement the Tideman voting method, which is a ranked-choice voting method that guarantees the Condorcet winner (if one exists) of the election.
- Understand how to represent a graph using data structures, and how to implement graph algorithms such as topological sort and depth-first search.
- Implement an algorithm that locks in edges of a graph based on the strength of the victory to avoid creating cycles in the candidate graph.

## Graph Theory - Basic Concepts

- **Vertices (or Nodes)**: These are the individual points or objects in a graph. They can be represented using integers or any other data type depending on the problem.
- **Edges**: These are the connections between vertices. They can be *directed or undirected*, *weighted or unweighted*, depending on the problem.
- **Degree**: The degree of a vertex is the number of edges incident to that vertex.
- **Path**: A path is a sequence of edges that connect two vertices.
- **Cycle**: A cycle is a path that starts and ends at the same vertex.
- **Connectedness**: A graph is connected if there is a path between any two vertices.
- **Weighted Graphs**: In a weighted graph, each edge is assigned a weight, which can represent any kind of value depending on the problem.

## Common Graph Algorithms 

1. **Depth-First Search (DFS)**: This algorithm is used to traverse a graph or search for a specific node in the graph. It starts at the root node and explores as far as possible along each branch before backtracking.
2. **Breadth-First Search (BFS)**: This algorithm is also used to traverse a graph or search for a specific node in the graph. It explores all the neighbor nodes at the present depth before moving on to the nodes at the next depth level.
3. **Dijkstra's algorithm**: This algorithm is used to find the shortest path between two nodes in a graph with non-negative edge weights.
4. **Bellman-Ford algorithm**: This algorithm is used to find the shortest path between two nodes in a graph that may have negative edge weights.
5. **Kruskal's algorithm**: This algorithm is used to find the minimum spanning tree of a graph.
6. **Prim's algorithm**: This algorithm is also used to find the minimum spanning tree of a graph.
7. **Floyd-Warshall algorithm**: This algorithm is used to find the shortest path between all pairs of nodes in a graph.
8. **Topological sorting:** This algorithm is used to sort the nodes of a directed acyclic graph (DAG) in such a way that for every directed edge (u, v), node u comes before node v in the ordering.

## Extra

In the implementation, I sorted the pairs by Strength of Victory as defined in the exercise, using **Mergesort**.

For the creation of the edges in the graph, the problem requests that *no edge should be added if it creates a cycle*. The graph is **Directed / Unidirectional** and to solve this I implemented the recursive Deapth First Search Traversal algorithm. This was definitely the hardest part of the problem.

I also added an *is_source* function to find a node without any outgoing edges, which is defined as the winner of the tideman algorithm, hence the election. After that, the prining was easy.
