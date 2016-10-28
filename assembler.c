#include "assembler.h"

#define LEFT 0
#define RIGHT 1


/**
 * Given a token, checks if it follows the following pattern:
 * it must only have alphanumeric characters or underscores and the first character 
 * must not be a number.
 * @param  tkn            token to be checked
 * @param  end            the last position minus 1 to be checked
 * @param  undesired_char a specific undesired char (if there is any)
 * @return FALSE		  if it does not follow the pattern
 * @return TRUE			  if it does follow the pattern
 */
int checkPattern(char tkn[], int end) {
	if(isdigit(tkn[0])) {
		return FALSE;
	}
	for(int i = 0; i < end; i++) {
		if(!isalnum(tkn[i])) {
			if(tkn[i] != '_') {
				return FALSE;
			}
		}
	}
	return TRUE;
}


/**
 * Given a token, checks if it is a comment
 * @param  	tkn 	token to be checked
 * @return	FALSE 	if it is not a comment
 * @return	TRUE	if it is a comment
 */
int checkComment(char tkn[]) {
	if(tkn[0] == '#') {
		return TRUE;
	}
	return FALSE;
}


/**
 * Given a word, checks if it is a directive
 * @param  tkn 		token to be checked
 * @return FALSE 	if it is not a directive
 * @return TRUE	 	if it is a directive
 */
int checkDirective(char tkn[]) {
	if(tkn[0] == '.') {
		return TRUE;
	}
	return FALSE;
}


/**
 * Given a token, checks if it is a label
 * @param  	tkn 	token to be checked
 * @return 	FALSE 	if it is not a label
 * @return	TRUE	if it is a label    
 */
int checkLabel(char tkn[]) {
	if((tkn[strlen(tkn)-1]) == ':') {
		return TRUE;
	}
	return FALSE;
}


/**
 * Given a list node which is likely a directive, checks if it is valid (if it is any of the given ones
 * and if its arguments are according to the specifications)
 * @param  	tk_conductor 	list node to be checked
 * @param  	error      	array of characters to keep an error message (if there is any)
 * @return	FALSE		if it is not a valid directive
 * @return	TRUE		if it is a valid directive
 */
int checkDirectiveType(struct tk_list_node **tk_conductor, char error[]) {

	if(strcmp((*tk_conductor)->token, ".set") == 0) {
		(*tk_conductor) = (*tk_conductor)->next;

		if(checkPattern((*tk_conductor)->token, strlen((*tk_conductor)->token)) == TRUE) {		//checks if it is a valid symbol
			(*tk_conductor) = (*tk_conductor)->next;

			if(checkDigit((*tk_conductor)->token) == TRUE) {							//if it is a decimal number (has only digits)

				if(checkInterval(0, 2147483647, (*tk_conductor)->token) == TRUE) {		//checks if it is within the range
					return 1;
				}
				else {
					sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
					return FALSE;
				}
			}
			else if(checkHexadecimal((*tk_conductor)->token) == TRUE) {		//if it is a hexadecimal number (begins with "0x")

				if(checkHexPattern((*tk_conductor)->token) == TRUE) {		//checks if it is valid
					return 1;
				}
				else {
					sprintf(error, "ERROR on line %d\n%s is not a valid hexadecimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
					return FALSE;
				}
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
		else {
			sprintf(error, "ERROR on line %d\n%s is not a valid symbol.\n", (*tk_conductor)->line, (*tk_conductor)->token);
			return FALSE;
		}
	}
	else if(strcmp((*tk_conductor)->token, ".org") == 0) {
		(*tk_conductor) = (*tk_conductor)->next;

		if(checkHexadecimal((*tk_conductor)->token) == TRUE) {

			if(checkHexPattern((*tk_conductor)->token) == TRUE) {	
				return 1;
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid hexadecimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
		else if(checkDigit((*tk_conductor)->token) == TRUE) {

			if(checkInterval(0, 1023, (*tk_conductor)->token) == TRUE) {	
				return 3;
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
		else {
			sprintf(error, "ERROR on line %d\n%s is not a valid number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
			return FALSE;
		}
	}
	else if(strcmp((*tk_conductor)->token, ".align") == 0) {
		(*tk_conductor) = (*tk_conductor)->next;

		if(checkDigit((*tk_conductor)->token) == TRUE) {

			if(checkInterval(1, 1023, (*tk_conductor)->token)) {
				return 4;
			}
		}
		else {
			sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
			return FALSE;
		}
	}
	else if(strcmp((*tk_conductor)->token, ".wfill") == 0) {
		(*tk_conductor) = (*tk_conductor)->next;

		if(checkInterval(1, 1023, (*tk_conductor)->token) == TRUE) {
			(*tk_conductor) = (*tk_conductor)->next;

			if(checkHexadecimal((*tk_conductor)->token) == TRUE) {

				if(checkHexPattern((*tk_conductor)->token) == TRUE) {
					return TRUE;
				}
				else {
					sprintf(error, "ERROR on line %d\n%s is not a valid hexadecimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
					return FALSE;
				}
			}
			else if (checkDigit((*tk_conductor)->token) == TRUE) {

				if(checkInterval(-2147483648, 2147483647, (*tk_conductor)->token) == TRUE) {
					return TRUE;
				}
				else {
					sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
					return FALSE;	
				}
			}										

			if(checkPattern((*tk_conductor)->token, strlen((*tk_conductor)->token))) {			//checks if it is a valid label or symbol
				return TRUE;
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid label or symbol.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
	}
	else if(strcmp((*tk_conductor)->token, ".word") == 0) {
		(*tk_conductor) = (*tk_conductor)->next;

		if(checkHexadecimal((*tk_conductor)->token) == TRUE) {

			if(checkHexPattern((*tk_conductor)->token) == TRUE) {
				return TRUE;
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid hexadecimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
		else if (checkDigit((*tk_conductor)->token) == TRUE) {

			if(checkInterval(0, 4294967295, (*tk_conductor)->token) == TRUE) {
				return TRUE;
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;	
			}
		}
		if(checkPattern((*tk_conductor)->token, strlen((*tk_conductor)->token)-1) == TRUE) {
			return TRUE;
		}
		else {
			sprintf(error, "ERROR on line %d\n%s is not a valid label or symbol.\n", (*tk_conductor)->line, (*tk_conductor)->token);
			return FALSE;
		}
	}
	//if the given directive is not any of the above, then it is not valid
	sprintf(error, "ERROR on line %d\n%s is not a valid directive.\n", (*tk_conductor)->line, (*tk_conductor)->token);
	return FALSE;
}


/**
 * Splits string into tokens and inserts each token and the given line value into a linked list. Comments are ignored.
 * @param line 		 	string to be splitted
 * @param tk_head	 	head of the list in which the tokens will be kept
 * @param line_num  	line number
 * @param delim			string that specifies a set of delimiters that may surround the token
 */
void tokenize(char line[], struct tk_list_node **tk_head, int line_num, char *delim) {
	char *wrd;
	wrd = strtok(line, delim);

	while(wrd != NULL && checkComment(wrd) == FALSE) {
		insertTkList(tk_head, wrd, line_num);
		wrd = strtok(NULL, delim);
	}
}


/**
 * Given an address, checks if it is either a decimal number, hexadecimal number, a label or symbol
 * @param  tk_conductor node that has the address
 * @param  endpoint1  interval minimum value of decimal type
 * @param  endpoint2  interval maximum value
 * @param  error      string that keeps an error message (if there is any)
 * @return 1          if it is a decimal number
 * @return 2 		  if it is a hexadecimal number
 * @return 3 		  if it is a label or a symbol
 * @return FALSE	  if it is none of the above
 */
int checkAddress(struct tk_list_node *tk_conductor, long long int endpoint1, long long int endpoint2, char error[]) {
	if(checkDigit(tk_conductor->token) == TRUE) {

		if(checkInterval(endpoint1, endpoint2, (tk_conductor)->token) == TRUE) {
			return 1;
		}
		else {
			sprintf(error, "ERROR on line %d\n%s is not a valid decimal number.\n", tk_conductor->line, tk_conductor->token);
			return FALSE;
		}
	}
	if(checkHexadecimal((tk_conductor)->token) == TRUE) {

		if(checkHexPattern(tk_conductor->token) == TRUE) {
			return 2;
		}
		sprintf(error, "ERROR on line %d\n%s is not a valid hexadecimal number.\n", tk_conductor->line, tk_conductor->token);
		return FALSE;
	}
	if(checkPattern((tk_conductor)->token, strlen((tk_conductor)->token)) == TRUE) {
		return 3;
	}
	else {
		sprintf(error, "ERROR on line %d\n%s is not a valid address.\n", tk_conductor->line, tk_conductor->token);
		return FALSE;
	}
}


/**
 * Given a node with an address of a mnemonic, checks if it follows the specifications:
 * starts and ends with quotation marks and it is either a label, a decimal or hexadecimal number
 * @param  tk_conductor node with the address
 * @param  error      string that keeps an error message (if there is any)
 * @return TRUE       if it follows the specifications
 * @return FALSE	  if it does not follow the specifications
 */
int checkMnemAddress(struct tk_list_node *tk_conductor, char error[]) {
	if(tk_conductor == NULL) {
		return FALSE;
	}
	int length = strlen(tk_conductor->token);

	if(tk_conductor->token[0] == '\"' && tk_conductor->token[length-1] == '\"') {
		char address[length+1];
		strcpy(address, tk_conductor->token);
		strncpy(tk_conductor->token, address+1, length-2);
		tk_conductor->token[length-2] = '\0';

		if(checkAddress(tk_conductor, 0, 1023, error) != FALSE) {
			return TRUE;
		}
	}
	sprintf(error, "ERROR on line %d\n%s is not a valid mnemonic address.\n", tk_conductor->line, tk_conductor->token);
	return FALSE;
}


/**
 * Given a token, checks if it is a valid mnemonic
 * @param  tk_conductor node with the token
 * @return            its opcode in decimal form if it is a valid mnemonic
 * @return FALSE	  if it is not a valid mnemonic
 */
int checkMnemonic(struct tk_list_node *tk_conductor) {
	if(strcmp(tk_conductor->token, "LD") == 0) {
		return 1;
	}
	else if(strcmp(tk_conductor->token, "LD-") == 0) {
		return 2;
	}
	else if(strcmp(tk_conductor->token, "LD|") == 0) {
		return 3;
	}
	else if(strcmp(tk_conductor->token, "LDmq") == 0) {
		return 10;
	}
	else if(strcmp(tk_conductor->token, "LDmq_mx") == 0) {
		return 9;
	}
	else if(strcmp(tk_conductor->token, "ST") == 0) {
		return 33;
	}
	else if(strcmp(tk_conductor->token, "JMP") == 0) {
		return 13;
	}
	else if(strcmp(tk_conductor->token, "JUMP+") == 0) {
		return 15;
	}
	else if(strcmp(tk_conductor->token, "ADD") == 0) {
		return 5;
	}
	else if(strcmp(tk_conductor->token, "ADD|") == 0) {
		return 7;
	}
	else if(strcmp(tk_conductor->token, "SUB") == 0) {
		return 6;
	}
	else if(strcmp(tk_conductor->token, "SUB|") == 0) {
		return 8;
	}
	else if(strcmp(tk_conductor->token, "MUL") == 0) {
		return 11;
	}
	else if(strcmp(tk_conductor->token, "DIV") == 0) {
		return 12;
	}
	else if(strcmp(tk_conductor->token, "STaddr") == 0) {
		return 18;
	}
	else if(strcmp(tk_conductor->token, "LSH") == 0) {
		return 20;
	}
	else if(strcmp(tk_conductor->token, "RSH") == 0) {
		return 21;
	}
	return FALSE;
}


/**
 * Given a token, checks if it is either a directive, a label or a mnemonic.
 * Writes an error message in the string if it is not any of them.
 * @param  tk_conductor node with the token to be checked
 * @param  error      string that keeps an error message (if there is any)
 * @return 1          if it is a label
 * @return 2 		  if it is a mnemonic
 * @return 3 		  if it is a directive
 * @return FALSE	  if it is none of the above
 */
int checkType(struct tk_list_node *tk_conductor, char error[]) {

	if(checkDirective(tk_conductor->token) == TRUE) {
		return 3;
	}
	else if(checkLabel(tk_conductor->token) == TRUE) {	
		return 1;
	}
	else if(checkMnemonic(tk_conductor) != FALSE) {
		return 2;
	}
	else {
		sprintf(error, "ERROR on line %d\n%s is not a valid mnemonic.\n", tk_conductor->line, tk_conductor->token);
		return FALSE;
	}
}


/**
 * Checks all the tokens of the file, according to their type, and verifies if they are valid.
 * Checks if the tokens of the same line are in the right order
 * @param  tk_head head of the list that contains the tokens
 * @param  error   string that keeps an error message (if there is any)
 * @return TRUE    if all the tokens of the file are valid
 * @return FALSE   if there is an invalid token or if the syntax is wrong
 */
int verifyFile(struct tk_list_node **tk_head, char error[]) {
	int sum = 0, cur_type = -1;
	struct tk_list_node *tk_conductor = *tk_head;

	while(tk_conductor != NULL) {
		cur_type = checkType(tk_conductor, error);

		if(cur_type == FALSE) { 	//if it is not a valid type
			return FALSE;
		}
		if(cur_type > sum) {	
			sum += cur_type;
		}
		else if(cur_type != -1) {	//if it is not in the right order
			sprintf(error, "ERROR on line %d\nWrong syntax.\n", tk_conductor->line);
			return FALSE;
		}
		if(cur_type == 3) {
			if(checkDirectiveType(&tk_conductor, error) == FALSE) {
				return FALSE;
			}
		}
		else if(cur_type == 1) {
			if(checkPattern(tk_conductor->token, strlen(tk_conductor->token)-1) == FALSE) {
				sprintf(error, "ERROR on line %d\n%s is not a valid label.\n", tk_conductor->line, tk_conductor->token);
				return FALSE;
			}
		}
		else if(cur_type == 2) {
			int mnem_type = checkMnemonic(tk_conductor);
			if(mnem_type != 20 && mnem_type != 21) {
				tk_conductor = tk_conductor->next;
				if(checkMnemAddress(tk_conductor, error) == FALSE) {
					return FALSE;
				}
			}
			else {
				//if a mnemonic that does not need an address has an address, it writes an error message
				if(checkMnemAddress(tk_conductor->next, error) == TRUE) {		
					sprintf(error, "ERROR on line %d\n%s does not require an address.\n", tk_conductor->line, tk_conductor->token);
					return FALSE;
				}
			}
		}
		if(tk_conductor->next != NULL) {
			if(tk_conductor->line != tk_conductor->next->line) {
				sum = 0;
				cur_type = -1;
			}
		}
		tk_conductor = tk_conductor->next;
	}
	return TRUE;
}


/**
 * Updates the position array, according to the value received. If the value is -1,
 * it moves half word. If the value is a positive number, updates the position to the left
 * side of the given value.
 * @param position position array
 * @param val      value
 */
void updatePosition(int position[], int val) {
	if(val != -1) {
		position[0] = val;
		position[1] = LEFT;
	}
	else if(position[1] == RIGHT) {
		position[0]++;
		position[1] = LEFT;
	}
	else {
		position[1] = RIGHT;
	}
}


/**
 * Adds the opcode of a instruction into a string
 * @param wrd         a word of memory
 * @param initial_pos the initial position where the opcode will be written
 * @param instr_type  the opcode of the instruction in decimal form
 */
void addInstruction(char wrd[], int initial_pos, int instr_type) {
	char instr[5];

	//adding the instruction 	
	sprintf(instr, "%02X", instr_type);		//converts decimal to hexadecimal
	for(int i = initial_pos, j = 0; i < initial_pos + 2; i++, j++) {
		wrd[i] = instr[j];
	}
}


/**
 * Adds the address of an instruction into the memory word, then adds the opcode of the instruction.
 * If an instruction does not need an address, adds zero.
 * @param  tk_conductor  node that contains the instruction
 * @param  wrd         memory word
 * @param  head        head of the list of labels
 * @param  initial_pos the initial position where the opcode will be written
 * @param  error       string that keeps an error message (if there is any)
 * @return FALSE       if the address is a label that does not exist
 * @return TRUE		   if the address and the instruction were added successfully
 */
int addInstrAddr(struct tk_list_node **tk_conductor, char wrd[], struct lbl_list_node *head, int initial_pos, char error[]) {
	char addr[7];
	
	int instr_type = checkMnemonic(*tk_conductor);	//gets the numerical value of the instruction in decimal form
	
	if(instr_type != 20 && instr_type != 21) {			//add the address if the instruction requires it
		(*tk_conductor) = (*tk_conductor)->next;
		int addr_type = checkAddress((*tk_conductor), 0, 1023, error);

		if(addr_type == 1) { 		//if the address is in decimal form
			int address = strtol((*tk_conductor)->token, NULL, 10);
			sprintf(addr, "%03X", address);

			for(int j = initial_pos, i = 0; j < initial_pos + 3; j++, i++) {
				wrd[j] = addr[i];
			}
		}
		else if(addr_type == 2) {	//if the address is in hexadecimal form
			for(int j = initial_pos, k = 9; j < initial_pos + 3; j++, k++) {
				wrd[j] = (*tk_conductor)->token[k];
			}
		}
		else if(addr_type == 3) {	//if the address is a label
			struct lbl_list_node *node = searchLblList(head, (*tk_conductor)->token);

			if(node != NULL) {
				sprintf(addr, "%03X", node->address);

				for(int j = initial_pos, i = 0; j < initial_pos + 3; j++, i++) {
					wrd[j] = addr[i];
				}
				if(instr_type == 13 || instr_type == 15 || instr_type == 18) {
					if(node->position == RIGHT) {
						addInstruction(wrd, initial_pos-3, ++instr_type);
						return TRUE;
					}
				}
			}
			else {
				sprintf(error, "ERROR on line %d\n%s is not a valid label.", (*tk_conductor)->line, (*tk_conductor)->token);
				return FALSE;
			}
		}
	}
	addInstruction(wrd, initial_pos-3, instr_type);
	return TRUE;
}


/**
 * Given a token containing either a decimal, 12-digit hexadecimal, label or symbol, gets its numeric value and
 * converts it to a 10-digit hexadecimal form.
 * @param  tk_conductor  token
 * @param  val_type    the token's type (decimal, hex, label or symbol)
 * @param  val         array where the hexadecimal form will be stored
 * @param  head        head of the label linked list
 * @param  slnode_head head of the symbol linked list
 * @return FALSE       if the token is neither a decimal, hexadecimal, label nor symbol
 * @return TRUE		   if the conversion was successful
 */
int convertToHexa(struct tk_list_node *tk_conductor, int val_type, char val[], struct lbl_list_node *head,
					struct sym_list_node *slnode_head) {
	if(val_type == 1) {
		//printf("WTF THIS IS A NUMERIC VALUE\n");
		long long int number = atoll((tk_conductor)->token);
		//printf("valor numerico:\n");
		if(number >= 0) {
			sprintf(val, "%010X", (unsigned) number);
		}
		else {
			char complement[11];
			twoComplement(number, complement);
			strcpy(val, complement);
		}
	}
	else if(val_type == 2) {
		memcpy(val, (tk_conductor)->token + 2, 11);
	}
	else if(val_type == 3) {
		struct lbl_list_node* lnode = searchLblList(head, (tk_conductor)->token);

		if(lnode != NULL) {
			sprintf(val, "%010X", lnode->address);
		}
		else {
			struct sym_list_node* slnode = searchSymList(slnode_head, (tk_conductor)->token);
			if(slnode != NULL) {
				memcpy(val, slnode->value + 2, 11);
			}
			else {
				return FALSE;
			}
		}
	}
	return TRUE;
}



/**
 * Given a string, converts it to the memory word form ("XX XXX XX XXX")
 * @param val [description]
 */
void convertStdForm(char val[]) {
	append(val, " ", 2);
	append(val, " ", 6);
	append(val, " ", 9);
}


/**
 * Executes the instructions the directives give to the assembler, i.e., adding memory words to the memory map,
 * controlling the location counter and defining the value of symbols
 * @param  tk_conductor  token containing the directive
 * @param  slnode_head head of the symbol linked list
 * @param  head        head of the label linked list
 * @param  pos         position counter
 * @param  root        root of the binary tree
 * @param  error       string that keeps an error message (if there is any)
 * @return TRUE        if the execution was successful
 * @return FALSE	   if there was an error during execution
 */
int treatDirective(struct tk_list_node **tk_conductor, struct sym_list_node **slnode_head,
					struct lbl_list_node *head, int pos[], struct node **root, char error[]) {
	struct sym_list_node *slnode;
	struct node* leaf;
	int val_type;

	if(strcmp((*tk_conductor)->token, ".set") == 0) {		//defines the value of a given symbol
		char hex_val[13] = "0x";
		(*tk_conductor) = (*tk_conductor)->next;
		val_type = checkAddress((*tk_conductor)->next, 0, 2147483647, error);

		if(convertToHexa((*tk_conductor)->next, val_type, hex_val+2, head, *slnode_head) == TRUE) {
			slnode = searchSymList(*slnode_head, (*tk_conductor)->token);

			if(slnode == NULL) {
				slnode = *slnode_head;
				insertSymList(&slnode, (*tk_conductor)->token, hex_val);
			}
			else {
				setValueSymList(slnode, hex_val);
			}
		}
		else {
			return FALSE;
		}
		(*tk_conductor) = (*tk_conductor)->next;
		if(*slnode_head == NULL) {
			*slnode_head = slnode;
		}
	}
	else if(strcmp((*tk_conductor)->token, ".org") == 0) {	//changes the location counter to the given number
		int address;
		(*tk_conductor) = (*tk_conductor)->next;
		val_type = checkAddress(*tk_conductor, 0, 1023, error);

		if(val_type == 1) {
			address = strtol((*tk_conductor)->token, NULL, 10);
		}
		
		else if(val_type == 2) {
			address = strtol((*tk_conductor)->token, NULL, 16);
		}
		updatePosition(pos, address);
	}
	else if(strcmp((*tk_conductor)->token, ".align") == 0) {	//changes the location counter to the next multiple of the given number
		int new_pos;
		(*tk_conductor) = (*tk_conductor)->next;
		int number = strtol((*tk_conductor)->token, NULL, 10);

		if(pos[0] % number == 0) {
			if(pos[1] == RIGHT) {
				new_pos = obtainMultiple(pos[0] + 1, number);
				updatePosition(pos, new_pos);
			}
		}
		else {
			new_pos = obtainMultiple(pos[0] + 1, number);
			updatePosition(pos, new_pos);
		}
		if(pos[0] > 1023) {
			sprintf(error, "ERROR on line %d\nAttempt to access an invalid memory location.\n", (*tk_conductor)->line);
			return FALSE;
		}
	}
	else if(strcmp((*tk_conductor)->token, ".wfill") == 0) {	//given two numerical values, x and y, writes the number y x times in the memory map
		char val[14];
		(*tk_conductor) = (*tk_conductor)->next;
		int size = strtol((*tk_conductor)->token, NULL, 10);

		if(pos[0] + size - 1 < 1024) {
			if(pos[1] == LEFT) {
				(*tk_conductor) = (*tk_conductor)->next;

				for(int i = 0; i < size; i++) {
					leaf = *root;
					leaf = searchTree(root, pos[0]);

					if(leaf == NULL) {
						leaf = *root;
						insertTree(&leaf, pos[0]);
						leaf = searchTree(&leaf, pos[0]);

						if(*root == NULL) {
							*root = leaf;
						}
					}
					val_type = checkAddress((*tk_conductor), -2147483648, 2147483647, error);

					if(convertToHexa((*tk_conductor), val_type, val, head, *slnode_head) == TRUE) {
						convertStdForm(val);
						setWrdTree(leaf, val);
						updatePosition(pos, pos[0] + 1);
					}
					else {
						sprintf(error, "ERROR on line %d\n%s is not a valid label or symbol.", (*tk_conductor)->line, (*tk_conductor)->token);
						return FALSE;
					}
				}
			}
			else {
				sprintf(error, "ERROR on line %d\nAttempt to allocate a 40-bit word to a 20-bit half-word.\n", (*tk_conductor)->line);
				return FALSE;
			}
		}
		else {
			sprintf(error, "ERROR on line %d\nAttempt to access an invalid memory location.\n", (*tk_conductor)->line);
			return FALSE;
		}
	}
	else {		//writes a word in the memory map
		if(pos[0] + 1 < 1024) {
			if(pos[1] == LEFT) {
				char val[14];
				leaf = *root;
				leaf = searchTree(root, pos[0]);

				if(leaf == NULL) {
					leaf = *root;
					insertTree(&leaf, pos[0]);
					leaf = searchTree(&leaf, pos[0]);

					if(*root == NULL) {
						*root = leaf;
					}
				}
				(*tk_conductor) = (*tk_conductor)->next;
				val_type =  checkAddress((*tk_conductor), 0, 4294967295, error);

				if(convertToHexa((*tk_conductor), val_type, val, head, *slnode_head) == TRUE) {
					convertStdForm(val);
					setWrdTree(leaf, val);
					updatePosition(pos, pos[0] + 1);
				}
				else {
					sprintf(error, "ERROR on line %d\n%s is not a valid label or symbol.", (*tk_conductor)->line, (*tk_conductor)->token);
					return FALSE;
				}
			}
			else {
				sprintf(error, "ERROR on line %d\nAttempt to allocate a 40-bit word to a 20-bit half-word.\n", (*tk_conductor)->line);
				return FALSE;
			}
		}
		else {
			sprintf(error, "ERROR on line %d\nAttempt to access an invalid memory location.\n", (*tk_conductor)->line);
			return FALSE;
		}
	}
	return TRUE;
}



/**
 * Creates a list with all the labels from the input file
 * @param  tk_conductor head of the list with all the tokens of the file
 * @param  head         head of the list where the labels will be added
 * @param  error        string that keeps an error message (if there is any)
 * @return FALSE        if there's more than one label with the same name
 * @return TRUE			if the procedure was successful
 */
int createLblList(struct tk_list_node *tk_conductor, struct lbl_list_node **head, char error[]) {
	struct lbl_list_node *lbl_conductor = *head;
	int type;
	while(tk_conductor != NULL) {
		type = checkType(tk_conductor, error);
		if(type == 1) {
			int length = strlen(tk_conductor->token);
			char temp[length];
			strncpy(temp, tk_conductor->token, length-1); //removes the colon from the label
			temp[length-1] = '\0';
			if(searchLblList(*head, temp) == NULL) {
				insertLblList(&lbl_conductor, 0, 0, temp); //initialize the labels with address 0 and position 0
				if(*head == NULL) {
					*head = lbl_conductor;
				}
			}
			else {
				sprintf(error, "ERROR on line %d\nLabel already exists.", tk_conductor->line);
				return FALSE;
			}
		}
		tk_conductor = tk_conductor->next;
	}
	return TRUE;
}


/**
 * Generates the memory map in a binary tree
 * @param  tk_head head of the linked list with all the tokens from the input file
 * @param  head    head of the linked list with all the labels from the input file
 * @param  root    root of the binary tree where the memory map will be generated
 * @param  error   string that keeps an error message (if there is any)
 * @return TRUE    if the procedure was successful
 * @return FALSE   if there was an error
 */
int createMemoryMap(struct tk_list_node *tk_head, struct lbl_list_node **head, struct node **root, char error[]) {
	struct lbl_list_node *conductor = *head;
	struct sym_list_node *slnode_head = NULL;
	struct tk_list_node *tk_conductor = tk_head;
	int position[2] = {0, 0};
	int type;
	char wrd[14];
	struct node *leaf = *root;

	while(tk_conductor != NULL) {
		if (position[0] >= 1024) {
			sprintf(error, "ERROR on line %d\nAttempt to access an invalid memory location.\n", (tk_conductor)->line);
			return FALSE;
		}
		type = checkType(tk_conductor, error);

		if(type == 1) {			//if it is a label
			int length = strlen(tk_conductor->token);
			char temp[length];
			strncpy(temp, tk_conductor->token, length-1); //removes the colon from the label
			temp[length-1] = '\0';
			conductor = searchLblList(*head, temp);
			setLblAddress(conductor, position[0]);
			setLblPosition(conductor, position[1]);
		}
		else if(type == 2) {	//if it is a mnemonic
			leaf = *root;
			leaf = searchTree(&leaf, position[0]);

			if(leaf == NULL) {
				strcpy(wrd, "00 000 00 000");
				leaf = *root;
				insertTree(&leaf, position[0]);
				leaf = searchTree(&leaf, position[0]);

				if(*root == NULL) {
					*root = leaf;
				}
			}
			else {
				strcpy(wrd, leaf->word);
			}
			if(position[1] == LEFT) {
				if(addInstrAddr(&tk_conductor, wrd, *head, 3, error) == FALSE) {
					return FALSE;
				}
			}
			else {				
				if(addInstrAddr(&tk_conductor, wrd, *head, 10, error) == FALSE) {
					return FALSE;
				}
			}
			setWrdTree(leaf, wrd);
			updatePosition(position, -1);		
		}
		else if(type == 3) {	//if it is a directive
			if(treatDirective(&tk_conductor, &slnode_head, *head, position, root, error) == FALSE) {
				return FALSE;
			}
		}
		tk_conductor = tk_conductor->next;
	}

	deallocateSymList(slnode_head);

	return TRUE;
}
