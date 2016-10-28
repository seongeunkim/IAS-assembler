#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"


/**
 * Utility function that creates a new binary tree node
 * @param  address address to be added to the tree node
 * @return         the new node
 */
struct node* newTreeNode(int address) {
	struct node* leaf = malloc(sizeof(struct node));
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->address = address;
	strcpy(leaf->word, "             ");
	return leaf;
}


/**
 * Inserts a new node with given key into a binary tree
 * @param  leaf        root of the binary tree in which the node will be added
 * @param  new_address address to be added
 */
void insertTree(struct node **leaf, int new_address) {
	if(*leaf == NULL) {
		*leaf = newTreeNode(new_address);
	}
	else {
		if(new_address < (*leaf)->address) {
			insertTree(&((*leaf)->left), new_address);
		}
		else {
			insertTree(&((*leaf)->right), new_address);
		}
	}
}


/**
 * Searches for a leaf with the given key in the binary tree
 * @param  leaf root of the binary tree
 * @param  key  key of the leaf to be found
 * @return      if the leaf was found, returns it. Else, it return NULL
 */
struct node* searchTree(struct node **leaf, int key) {
	if(*leaf != NULL) {
		if(key == (*leaf)->address) {
			return *leaf;
		}
		else if(key < (*leaf)->address) {
			return searchTree(&((*leaf)->left), key);
		}
		else {
			return searchTree(&((*leaf)->right), key);
		}
	}
	else {
		return NULL;
	}
}


/**
 * Sets the word of a given node af a binary tree
 * @param leaf node of the binary tree
 * @param wrd  new word to be set
 */
void setWrdTree(struct node *leaf, char wrd[]) {
	strcpy(leaf->word, wrd);
}


/**
 * Given a FILE handle, writes the binary tree in inorder to the output stream to which it points
 * @param fp   FILE handle
 * @param tree head of the binary tree that will be printed
 */
void printInorder(FILE *fp, struct node * tree) {
    if (tree) {
        printInorder(fp, tree->left);
        fprintf(fp, "%03X %s\n",tree->address, tree->word);
        printInorder(fp, tree->right);
    }
}


/**
 * Deallocates all the memory allocated by the binary tree
 * @param leaf root of the tree
 */
void deallocateTree(struct node *leaf) {
	if(leaf == NULL) {
		return;
	}
	deallocateTree(leaf->left);
	deallocateTree(leaf->right);
	free(leaf);
}
