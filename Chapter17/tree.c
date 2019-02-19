/* tree.c -- tree support functions */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tree.h"

/* local data type */
typedef struct pair
{
    Trnode * parent;
    Trnode * child;
} Pair;

/* prototypes for local functions */
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void InOrder(const Trnode * root, void (* pfun)(Item item));
static Pair SeekNode(const Item * pi, const Tree * ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode * ptr);

/* function definitions */
void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
    return (ptree->root == NULL) ? true: false;
}

bool TreeIsFull(const Tree * ptree)
{
    return (ptree->size == MAXITEMS) ? true: false;
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

bool AddItem(const Item * pi, Tree * ptree)
{
    Trnode * new_node;
    Pair look = SeekNode(pi, ptree);

    if (TreeIsFull(ptree))
    {
        fprintf(stderr, "Tree is full\n");
        return false;
    }
    if (look.child != NULL)
    {
        fprintf(stderr, "Attempted to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi);    /* points to new node */
    if (new_node == NULL)
    {
        fprintf(stderr, "Couldn't create node\n");
        return false;
    }
    /* succeeded in creating a new node */
    ptree->size++;

    if (ptree->root == NULL)       /* case 1: tree is empty */
        ptree->root = new_node;    /* new node is tree root */
    else
    {
        if (ToLeft(pi, &(look.parent->item)))
            look.parent->left = new_node;
        else
            look.parent->right = new_node;
    }
    return true;
}

bool InTree(const Item * pi, const Tree * ptree)
{
    return (SeekNode(pi, ptree).child == NULL) ? false: true;
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
    Pair look;

    look = SeekNode(pi, ptree);
    if (look.child == NULL)
        return false;
    
    if (look.parent == NULL)    /* delete root item */
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;

    return true;
}

void Traverse(const Tree  * ptree, void(* pfun)(Item item))
{
    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

/* local functions */
static void InOrder(const Trnode * root, void (*pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun)(root->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode * root)
{
    Trnode * pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

static bool ToLeft(const Item * i1, const Item * i2)
{
    int comp1;

    if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
        return true;
    else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
        return true;
    else
        return false;
}

static bool ToRight(const Item * i1, const Item * i2)
{
    int comp1;

    if((comp1 = strcmp(i1->petname, i2->petname)) > 0)
        return true;
    else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
        return true;
    else
        return false;
}

static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;
    
    new_node = (Trnode *) malloc(sizeof(Trnode));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

static Pair SeekNode(const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;
    
    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else        /* must be same if not to left or right    */
            break;  /* look.child is address of node with item */
    }

    return look;    /* successful return */
}

static void DeleteNode(Trnode **ptr)
/* ptr is address of parent member pointing to target node */
{
    Trnode * temp;
    
    if ((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
    }
    else /* deleted node has two children */
    {
        temp = (*ptr)->left;
        /* find where to reattach right subtree */
        while (temp->right != NULL)
            temp = temp->right;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
    }

    free(temp);
}