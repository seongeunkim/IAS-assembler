#ifndef _LIST_H_
#define _LIST_H_

#define WORD_SIZE 65	//maximum number of characters per word

struct lbl_list_node {
	int position;
	int address;
	char data[WORD_SIZE];
	struct lbl_list_node *next;
};

struct sym_list_node {
	char symbol[WORD_SIZE];
	char value[13];
	struct sym_list_node *next;
};

struct tk_list_node {
	char token[WORD_SIZE];
	int line;
	struct tk_list_node *next;
};

struct tk_list_node* newTkListNode(char token[], int value);
void insertTkList(struct tk_list_node **tknode, char token[], int value);
struct tk_list_node* searchTkList(struct tk_list_node *head, int data);
void deallocateTkList(struct tk_list_node *head);
struct lbl_list_node* newLblListNode(int new_address, int pos, char token[]);
void insertLblList(struct lbl_list_node **lnode, int new_address, int pos, char token[]);
struct lbl_list_node* searchLblList(struct lbl_list_node *head, char data[]);
void setLblAddress(struct lbl_list_node *node, int new_address);
void setLblPosition(struct lbl_list_node *node, int new_pos);
void deallocateLblList(struct lbl_list_node *head);
struct sym_list_node* newSymListNode(char symbol[], char val[]);
void insertSymList(struct sym_list_node **slnode, char symbol[], char val[]);
struct sym_list_node* searchSymList(struct sym_list_node *head, char data[]);
void setValueSymList(struct sym_list_node *slnode, char val[]);
void deallocateSymList(struct sym_list_node *head);

#endif
