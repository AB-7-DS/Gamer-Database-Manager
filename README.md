
# Gamers DataBase Management


This project implements a Database Management System (DBMS) for managing player and game datasets. The objective is to efficiently store, search, retrieve, delete, and modify player and game records. The dataset is stored in memory using Binary Search Trees (BST) to ensure efficient data operations like insertion, search, and deletion. The system also supports saving data to a CSV file, displaying tree layers, and identifying the players who play the most games.

## Authors

- [Abdullah Bin Asim](https://github.com/AB-7-DS)


## Features


- **Data Storage:** Data is stored in a binary search tree (BST) to allow efficient insertion, deletion, and search operations.
- **Insertion:** New players and games can be inserted into the tree. Conflicts in primary keys (duplicate entries) are handled appropriately.
- **Search and Retrieval:** Search for player and game entries based on primary keys, and retrieve corresponding data.
- **Deletion:** Deletion of entries is supported, ensuring no memory leaks occur.
- **Saving Data:** The tree structure is saved to a CSV file using Preorder Traversal, allowing the program to restore the structure when restarted.
- **Show Layers:** Display all entries up to a specified number of layers of the binary search tree.
- **Layer Number:** Given a primary key, display the layer number of the corresponding node in the tree.
- **Show Path:** Print the Preorder Traversal path taken to find an entry.
- **Edit Entry:** Modify any entry, including the primary key. The node is repositioned in the tree if necessary.
- **Top N Players:** Display the top N players who have played the most games.
- **Show Details:** Search for a player and display their details, along with all the games they have played.
- **Has Played:** Search if a player has played a specific game. The search should demonstrate a time complexity of at most O(log n).

 Task Breakdown
--------------

### 1.1 Store the Dataset in Memory

*   **Data Structure**: The dataset is stored in memory using **Binary Search Trees (BST)**.
    
*   **Random Line Skipping**: Before inserting players into the tree,starting, I generated a number ’seed’ which is  my your batch and roll number **232621**. With this seed, I skipped  lines while reading the dataset for players. I generated a random number from 0 to 1000 based on following condition: If the number is less than **21(last 2 digits of my roll number) × 10 + 100= 310**,  the lines are skipped; otherwise, read the line and add the node to your DBMS in memory..

### 1.2 Insertion

*   Insert new players and games into their respective BSTs.
    
*   Check for primary key conflicts (duplicate entries) and display an error message if the key already exists.
    

### 1.3 Search and Retrieval

*   Implement a function that searches for player or game entries based on the primary key (Player ID or Game ID) and returns the corresponding node for viewing or modification.
    

### 1.4 Deletion

*   Implement a function that allows deletion of player or game entries, ensuring there are no memory leaks and the tree structure is maintained after deletion.
    

### 1.5 Save Data

*   Use **Preorder Traversal** to save the tree structure to a CSV file, which can later be loaded back to restore the tree.
    

### 1.6 Show N Layers

*   Display the entries up to a specified number of layers in the binary search tree.
    
*   If the number of layers exceeds the tree’s depth, print a warning message.
    

### 1.7 Show Layer Number

*   Allow the user to input a primary key and return the layer number of the corresponding node in the tree.
    

### 1.8 Show Path

*   Print the **Preorder Traversal path** taken to locate a specific player or game.
    

### 1.9 Edit Entry

*   Allow the editing of any entry, including the primary key. The node is repositioned in the tree as necessary after editing.
    

### 1.10 Top N Players

*   Find and display the top N players who have played the most games in the dataset.
    

### 1.11 Show Details

*   Search for a player and display their details along with all the games they have played.
    

### 1.12 Has Played

*   Search if a player has played a specific game using a time complexity of **O(log n)**.
    

Data Structures Used
--------------------

*   **Binary Search Tree (BST)**: For storing players and games, ensuring efficient search, insertion, and deletion operations.
    
*   **Nodes**: Each player and game is represented by a node that stores the respective details and references to other nodes (for child nodes in the tree).
    

Future Improvements
-------------------

*   Implement **balanced binary trees** (such as AVL or Red-Black Trees) to ensure the tree remains balanced and search operations are consistently efficient.
    
*   Support for other query types based on user feedback and additional requirements.
    

Conclusion
----------

This project demonstrates how to efficiently manage a dataset using binary search trees and how to provide a dynamic, flexible database system for storing and querying player and game data. The goal is to provide a system that is easy to use, efficient, and can be easily extended for future features.

