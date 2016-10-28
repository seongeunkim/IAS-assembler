#ifndef _BTREE_H
#define _BTREE_H

struct node {
	int address;
	char word[14];
	struct node *left, *right;
};

struct node* newTreeNode(int address);
void insertTree(struct node **leaf, int new_address);
struct node* searchTree(struct node **leaf, int key);
void setWrdTree(struct node *leaf, char wrd[]);
void printInorder(FILE *fp, struct node * tree);
void deallocateTree(struct node *leaf);

#endif
