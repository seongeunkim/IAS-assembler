#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * A utility function that creates a new linked list node of the token type
 * @param  token token to be added
 * @param  value line number to be added
 * @return       the new node created
 */
struct tk_list_node* newTkListNode(char token[], int value) {
	struct tk_list_node *new_tk_node = malloc(sizeof(struct tk_list_node));
	strcpy(new_tk_node->token, token);
	new_tk_node->line = value;
	new_tk_node->next = NULL;
	return new_tk_node;
}


/**
 * Inserts a new node with given token and value to the linked list of the token type
 * @param tknode head of the linked list in which the node will be added
 * @param token  a token to be added in the node
 * @param value  a value to be added in the node
 */
void insertTkList(struct tk_list_node **tknode, char token[], int value) {
	if(*tknode == NULL) {
		*tknode = newTkListNode(token, value);
	}
	else {
		struct tk_list_node *current = *tknode;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = newTkListNode(token, value);
	}
}


/**
 * Searches for a leaf with the given data in the linked list of the token type
 * @param  head head of the list
 * @param  data data of the node being searched for
 * @return      the searched node if found. Null if not found
 */
struct tk_list_node* searchTkList(struct tk_list_node *head, int data) {
	if(head == NULL) {
		return NULL;
	}
	struct tk_list_node *temp = head;
	while(temp != NULL) {
		if(temp->line == data) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


/**
 * Deallocates all the memory allocated by the token linked list
 * @param head head of the token linked list
 */
void deallocateTkList(struct tk_list_node *head) {
	struct tk_list_node *node;
	while(head != NULL) {
		node = head;
		head = head->next;
		free(node);
	}
}


/**
 * A utility function that creates a new linked list node of the label type
 * @param  new_address address of the label
 * @param  pos         position of the label
 * @param  token       name of the label
 * @return             the new node
 */
struct lbl_list_node* newLblListNode(int new_address, int pos, char token[]) {
	struct lbl_list_node* lnode = malloc(sizeof(struct lbl_list_node));
	lnode->address = new_address;
	lnode->position = pos;
	lnode->next = NULL;
	strcpy(lnode->data, token);
	return lnode;
}


/**
 * Inserts a new node with given token, address and position into the linked list of the label type
 * @param  lnode       node from the list in which the node will be added
 * @param  new_address address of the node to be added
 * @param  pos         position of the node to be added
 * @param  token       label name to be added
 */
void insertLblList(struct lbl_list_node **lnode, int new_address, int pos, char token[]) {
	struct lbl_list_node* new_node = newLblListNode(new_address, pos, token);
	if(*lnode == NULL) {
		*lnode = new_node;
	}
	else {
		while((*lnode)->next != NULL) {
			(*lnode) = (*lnode)->next;
		}
		(*lnode)->next = new_node;
	}
	

}


/**
 * Searches for a leaf with the given data in the linked list of the label type
 * @param  head head of the list
 * @param  data data of the node we are searching for
 * @return      the searched node if found. Null if not found.
 */
struct lbl_list_node* searchLblList(struct lbl_list_node *head, char data[]) {
	if(head == NULL) {
		return NULL;
	}
	else {
		struct lbl_list_node *temp = head;
		while(temp != NULL) {
			if(strcmp(data, temp->data) == 0) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
}


/**
 * Sets the address of a given node from the label linked list
 * @param node        node in which the address will be changed
 * @param new_address the new address
 */
void setLblAddress(struct lbl_list_node *node, int new_address) {
	node->address = new_address;
}


/**
 * Sets the position of a given node from a label linked list
 * @param node    node in which the position will be changed
 * @param new_pos the new position
 */
void setLblPosition(struct lbl_list_node *node, int new_pos) {
	node->position = new_pos;
}


/**
 * Deallocates all the memory allocated by the label linked list
 * @param head head of the label linked list
 */
void deallocateLblList(struct lbl_list_node *head) {
	struct lbl_list_node *node;
	while(head != NULL) {
		node = head;
		head = head->next;
		free(node);
	}
}


/**
 * A utility function that creates a new linked list node of the symbol type
 * @param  symbol symbol to be added
 * @param  val    value to be added
 * @return        the new node
 */
struct sym_list_node* newSymListNode(char symbol[], char val[]) {
	struct sym_list_node *new_sym_node = malloc(sizeof(struct sym_list_node));
	strcpy(new_sym_node->symbol, symbol);
	strcpy(new_sym_node->value, val);
	new_sym_node->next = NULL;
	return new_sym_node;
}


/**
 * Inserts a new node with given token, address and position into the linked list of the symbol type
 * @param slnode a node from the linked list where the new node will be added
 * @param symbol symbol to be added
 * @param val    value to be added
 */
void insertSymList(struct sym_list_node **slnode, char symbol[], char val[]) {
	if(*slnode == NULL) {
		*slnode = newSymListNode(symbol, val);
	}
	else {
		while((*slnode)->next != NULL) {
			(*slnode) = (*slnode)->next;
		}
		(*slnode)->next = newSymListNode(symbol, val);
	}
}


/**
 * Searches for a leaf with the given data in the linked list of the symbol type
 * @param  head head of the list
 * @param  data data of the node being searched for
 * @return      the searched node if found. Null if not found
 */
struct sym_list_node* searchSymList(struct sym_list_node *head, char data[]) {
	if(head == NULL) {
		return NULL;
	}
	else {
		struct sym_list_node *temp = head;
		while(temp != NULL) {
			if(strncmp(data, temp->symbol, strlen(data)-1) == 0) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
}


/**
 * Given a node from a linked list, sets its value
 * @param slnode node of the linked list of the symbol type
 * @param val    new value
 */
void setValueSymList(struct sym_list_node *slnode, char val[]) {
	strcpy(slnode->value, val);
}


/**
 * Deallocates all the memory allocated by the symbol linked list
 * @param head head of the symbol linked list
 */
void deallocateSymList(struct sym_list_node *head) {
	struct sym_list_node *node;
	while(head != NULL) {
		node = head;
		head = head->next;
		free(node);
	}
}

