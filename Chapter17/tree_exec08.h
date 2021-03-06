/* tree.h -- binary search tree                          */
/*           no duplicate items are allowed in this tree */
#ifndef _TREE_H_
#define _TREE_H_
#include<stdbool.h>

#define SLEN 20
#define MAXNODES 10
#define MAXITEMS 20

/* redefine Item as appropriate */
typedef struct item
{
    char petname[SLEN];
    char petkind[SLEN];
} Item;

typedef struct list
{
    char petname[SLEN];
    Item entries[MAXITEMS];
    int items;
} List;

typedef struct trnode
{
    List * list;
    struct trnode * left;  /* pointer to left branch */
    struct trnode * right; /* pointer to right branch */
} Trnode;

typedef struct tree
{
    Trnode * root;         /* pointer to root of tree */
    int node_size;              /* number of nodes in tree */
    int item_size;         /* number of items in tree */
} Tree;

/* function prototypes */
/* operation:        initializen a tree to empty */
/* precondition:     ptree points to a tree */
/* postcondition:    the tree is initialized to empty */
void InitializeTree(Tree * ptree);

/* operation:        determine if tree is empty */
/* precondition:     ptree points to a tree */
/* postcondition:    function returns true if tree is */
/*                   empty and returns false otherwise */
bool TreeIsEmpty(const Tree * ptree);

/* operation:        determine if tree reaches its maximum limitation */
/* precondition:     ptree points to a tree */
/* postcondition:    function returns true if tree reaches */
/*                   its maximum limitation and returns false otherwise */
bool TreeIsFull(const Tree * ptree);

/* operatoin:        determine numbers of items in tree */
/* precondition:     ptree points to a tree */
/* postcondition:    function returns number of items in */
/*                   tree                                */
int TreeItemCount(const Tree * ptree);

/* operation:        add an item to a tree */
/* precondition:     pi is address of item to be added */
/*                   ptree points to an initialized tree */
/* postcondition:    if possible, function add item to */
/*                   tree and returns true; otherwise */
/*                   the function returns false */
bool AddItem(const Item * pi, Tree * ptree);

/* operation:        find an item in a tree */
/* precondition:     pi points to an item */
/*                   ptree points to an initialized tree */
/* postcondition:    function returns true if item is in */
/*                   tree and returns false otherwise */
Trnode * InTree(const char * name, const Tree * ptree);

/* operation:        delete an item from a tree */
/* precondition:     pi is address of item to be deleted */
/*                   ptree points to an initialized tree */
/* postcondition:    if possible, function delete item */
/*                   from tree and returns true; */
/*                   otherwise the function returns false */
bool DeleteItem(const Item * pi, Tree * ptree);

/* operation:        apply a function to each item the tree */
/* precondition:     ptree points to a tree */
/*                   pfun points to a function that takes */
/*                   an Item argument and has no return value */
/* postcondition:    the function pointed to by pfun is */
/*                   executed once for each item in tree */
void Traverse(const Tree * ptree, void (* pfun)(Item item));

/* operation:        delete everything from a tree */
/* precondition:     ptree points to an initialized tree */
/* postcondition:    tree is empty */
void DeleteAll(Tree * ptree);

#endif