#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include "misc.h"
#include "btree.h"
#include "list.h"

#define FALSE -1
#define TRUE 1


int checkPattern(char tkn[], int end);
int checkComment(char tkn[]);
int checkDirective(char tkn[]);
int checkLabel(char tkn[]);
int checkDirectiveType(struct tk_list_node **tk_conductor, char error[]);
void tokenize(char line[], struct tk_list_node **tk_head, int line_num, char *delim);
int checkAddress(struct tk_list_node *tk_conductor, long long int endpoint1, long long int endpoint2, char error[]);
int checkMnemAddress(struct tk_list_node *tk_conductor, char error[]);
int checkMnemonic(struct tk_list_node *tk_conductor);
int checkType(struct tk_list_node *tk_conductor, char error[]);
int verifyFile(struct tk_list_node **tk_head, char error[]);
void updatePosition(int position[], int val);
void addInstruction(char wrd[], int initial_pos, int instr_type);
int addInstrAddr(struct tk_list_node **tk_conductor, char wrd[], struct lbl_list_node *head, int initial_pos, char error[]);
int convertToHexa(struct tk_list_node *tk_conductor, int val_type, char val[], struct lbl_list_node *head,
					struct sym_list_node *slnode_head);
void convertStdForm(char val[]);
int treatDirective(struct tk_list_node **tk_conductor, struct sym_list_node **slnode_head,
					struct lbl_list_node *head, int pos[], struct node **root, char error[]);
int createLblList(struct tk_list_node *tk_conductor, struct lbl_list_node **head, char error[]);
int createMemoryMap(struct tk_list_node *tk_head, struct lbl_list_node **head, struct node **root, char error[]);

#endif
