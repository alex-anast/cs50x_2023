# Data Structures

This is a summary for my personal future reference in a basic implementation on Data Structures.

For a cheatsheet on the Big-O time and space complexity, look here: [Big-O Notation Cheatsheet](https://www.bigocheatsheet.com/).

## Array

An array is a linear data structure that stores a collection of elements of the same data type. Each element is accessed using an index. Arrays have a fixed size and can be used to efficiently store and access data.

Common functions for an array are:

```lang-markdown
**access**:     Θ(1)     O(1)
**search**:     Θ(n)     O(n)
**insert**:     Θ(n)     O(n)
**destroy**:    Θ(n)     O(n)
```

Basic Implementation:

```lang-C
int main()
{
    int arr[MAX_SIZE];
    int i;

    // Initialize the array
    for (i = 0; i < MAX_SIZE; i++)
    {
        arr[i] = i;
    }

    // Print the array
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
```

## Singly-Linked List

A singly linked list is a linear data structure that consists of nodes that contain data and a pointer to the next node in the list. The last node points to NULL. Singly linked lists can be used to efficiently insert and remove elements from the list.

Common functions for a singly-linked list are:

```lang-markdown
**access**:     Θ(n)     O(n)
**search**:     Θ(n)     O(n)
**insert**:     Θ(1)     O(1)
**destroy**:    Θ(1)     O(1)
```

Basic Implementation:

```lang-C
// Define a node in the singly-linked list
struct Node
{
    int data;
    struct Node* next;
};

// Insert a new node at the end of the list
void insert(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    // Add it to the end of the list
    last->next = new_node;
    return;
}

// Print the singly linked list
void print_list(struct Node* node) 
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    struct Node* head = NULL;

    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);

    print_list(head);

    return 0;
}
```

## Doubly-Linked List

A doubly linked list is a linear data structure that consists of nodes that contain data and pointers to the previous and next nodes in the list. The first node's previous pointer and the last node's next pointer points to NULL. Doubly linked lists can be used to efficiently insert and remove elements from the list and can be traversed in both forward and backward directions.

Common functions for a doubly-linked list are:

```lang-markdown
**access**:     Θ(n)     O(n)
**search**:     Θ(n)     O(n)
**insert**:     Θ(1)     O(1)
**destroy**:    Θ(1)     O(1)
```

Basic Implementation:

```lang-C
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head;

// Function to create a new node and return it
struct Node* getNewNode(int x)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtHead(int x)
{
    struct Node* newNode = getNewNode(x);
    if(head == NULL)
    {
        head = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}

// Function to insert a node at the end of the list
void insertAtTail(int x)
{
    struct Node* newNode = getNewNode(x);
    if(head == NULL)
    {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the list from head to tail
void printForward()
{
    printf("List (head to tail): ");
    struct Node* temp = head;
    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to print the list from tail to head
void printBackward()
{
    printf("List (tail to head): ");
    struct Node* temp = head;
    if(temp == NULL) return;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main()
{
    head = NULL; // empty list
    insertAtTail(2); printForward(); printBackward();
    insertAtHead(1); printForward(); printBackward();
    insertAtTail(3); printForward(); printBackward();
    insertAtTail(4); printForward(); printBackward();
    return 0;
}
```

## Hash Table

A Hash Table is a data structure that stores key-value pairs and provides constant-time average performance for operations like adding, removing, and searching for an element. It uses a hash function to map keys to a bucket where the corresponding value is stored. A good hash function tries to distribute keys evenly among the buckets to minimize collisions, which can degrade the performance of the hash table.

Common functions for a hash table are:

```lang-markdown
**access**:     instant instant
**search**:     Θ(1)     O(n)
**insert**:     Θ(1)     O(n)
**destroy**:    Θ(1)     O(n)
```

Basic Implementation:

```lang-C
#define TABLE_SIZE 1000

typedef struct node {
    char* key;
    int value;
    struct node* next;
} node_t;

node_t* table[TABLE_SIZE];

// hash is defined as the mathematical or logical function that matches the input with the hash table index (hash array)
unsigned int hash(char* key)
{
    unsigned int hashval = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hashval = key[i] + (hashval << 5) - hashval;
    }
    return hashval % TABLE_SIZE;
}

// or find, or search
node_t* lookup(char* key) {
    unsigned int hashval = hash(key);
    node_t* current = table[hashval];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insert(char* key, int value) {
    unsigned int hashval = hash(key);
    node_t* current = table[hashval];
    // traverse all the array until you find it
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    node_t* new_node = malloc(sizeof(node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next = table[hashval];
    table[hashval] = new_node;
}

void delete(char* key)
{
    unsigned int hashval = hash(key);
    node_t* current = table[hashval];
    node_t* previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
            {
                table[hashval] = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int main() {
    insert("one", 1);
    insert("two", 2);
    insert("three", 3);

    node_t* node = lookup("two");
    if (node != NULL)
    {
        printf("%s = %d\n", node->key, node->value);
    }

    delete("two");

    node = lookup("two");
    if (node != NULL)
    {
        printf("%s = %d\n", node->key, node->value);
    }
    else
    {
        printf("not found\n");
    }

    return 0;
}
```

## Trie

Trie is a tree-like data structure that stores strings, where each node represents a single character of the string. It is also known as a *prefix tree* or a *digital tree*.
Tries are commonly used in **search applications** where there is a large set of strings that need to be searched.

Common functions for a trie are:

```lang-markdown
**access**:     Θ(n)     O(n)
**search**:     Θ(n)     O(n)
**insert**:     Θ(n)     O(n)
**destroy**:    Θ(n)     O(n)
```

Basic Implementation:

```lang-C
#define ALPHABET_SIZE 26

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end_of_word;
};

struct TrieNode* create_node(void)
{
    struct TrieNode* node = (struct TrieNode*) malloc(sizeof(struct TrieNode));
    // error handling missing
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    node->is_end_of_word = false;
    return node;
}

void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* node = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!node->children[index])
        {
            node->children[index] = create_node();
        }
        node = node->children[index];
    }
    node->is_end_of_word = true;
}

bool search(struct TrieNode* root, const char* word) {
    struct TrieNode* node = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!node->children[index])
        {
            return false;
        }
        node = node->children[index];
    }
    return (node != NULL && node->is_end_of_word);
}

void destroy(struct TrieNode* root)
{
    // error handling
    if (root)
    {
        // until the size is 1, which means we have hit the bottom of the path
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            // recursive
            destroy(root->children[i]);
        }
        free(root);
    }
}
```

## Binary Seach Tree

Common functions for a trie are:

```lang-markdown
**access**:     Θ(log(n))     O(n)
**search**:     Θ(log(n))     O(n)
**insert**:     Θ(log(n))     O(n)
**destroy**:    Θ(log(n))     O(n)
```

Basic Implementation:

```lang-C
// Define the structure of a node in the tree
typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
} node;

// Function to create a new node with the given data
node* newNode(int data)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the tree
node* insert(node* root, int data)
{
    // If the root is NULL, create a new node with the given data
    if (root == NULL)
    {
        return newNode(data);
    }

    // Otherwise, traverse the tree to find the appropriate position to insert the new node
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    // Return the root of the updated tree
    return root;
}

// Function to search for a node with the given data in the tree
node* search(node* root, int data)
{
    // If the root is NULL or the root's data is equal to the target data, return the root
    if (root == NULL || root->data == data)
    {
        return root;
    }

    // If the target data is less than the root's data, search the left subtree
    if (data < root->data)
    {
        return search(root->left, data);
    }

    // Otherwise, search the right subtree
    return search(root->right, data);
}

// Function to print the inorder traversal of the tree (left, root, right)
void inorder(node* root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Main function to test the implementation
int main()
{
    node* root = NULL;

    // Insert nodes into the tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Print the inorder traversal of the tree
    printf("Inorder traversal of the tree: ");
    inorder(root);

    // Search for a node in the tree
    int searchKey = 60;
    node* searchResult = search(root, searchKey);
    if (searchResult != NULL)
    {
        printf("\n%d found in the tree.\n", searchKey);
    }
    else
    {
        printf("\n%d not found in the tree.\n", searchKey);
    }

    return 0;
}
```

## Stack

A stack is a linear data structure that follows the Last In First Out (LIFO) principle. It has two main operations:

**push**: adds an element to the top of the stack \
**pop**:  removes an element from the top of the stack

It can be implemented using arrays or linked lists.

Common functions for a trie are:

```lang-markdown
**access**:     Θ(n)     O(n)
**search**:     Θ(n)     O(n)
**insert**:     Θ(1)     O(1)
**destroy**:    Θ(1)     O(1)
```

Basic Implementation:

```lang-C
struct Stack {
    int items[MAX_SIZE];
    int top;
};

// Push operation
void push(struct Stack* stack, int item)
{
    if (stack->top == MAX_SIZE - 1)
    {
        printf("Stack overflow");
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Pop operation
int pop(struct Stack* stack)
{
    if (stack->top == -1)
    {
        printf("Stack underflow");
        return -1;
    }
    int item = stack->items[stack->top];
    stack->top--;
    return item;
}

// Main function
int main()
{
    struct Stack stack;
    stack.top = -1;

    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);

    printf("%d\n", pop(&stack));  // Output: 3
    printf("%d\n", pop(&stack));  // Output: 2
    printf("%d\n", pop(&stack));  // Output: 1

    return 0;
}
```

## Queue

A queue is a linear data structure that follows the First In First Out (**FIFO**) principle. It has two primary operations:

**enqueue**: adds an element to the back of the queue \
**dequeue**: removes the element from the front of the queue

Common functions for a trie are:

```lang-markdown
**access**:     Θ(n)     O(n)
**search**:     Θ(n)     O(n)
**insert**:     Θ(1)     O(1)
**destroy**:    Θ(1)     O(1)
```

Basic Implementation:

```lang-C
#define MAX_SIZE 100

// Define the queue structure
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Create an empty queue
Queue* createQueue()
{
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(Queue* q)
{
    if(q->rear == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Check if the queue is full
int isFull(Queue* q)
{
    if(q->rear == MAX_SIZE-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Add an element to the back of the queue
void enqueue(Queue* q, int value)
{
    if(isFull(q))
    {
        printf("Queue is full\n");
    }
    else
    {
        if(q->front == -1)
        {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Remove an element from the front of the queue
int dequeue(Queue* q)
{
    int item;
    if(isEmpty(q))
    {
        printf("Queue is empty\n");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
    }
    return item;
}

int main()
{
    Queue* q = createQueue();
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    printf("Dequeued item: %d\n", dequeue(q));
    printf("Dequeued item: %d\n", dequeue(q));
    printf("Dequeued item: %d\n", dequeue(q));
    return 0;
}
```
