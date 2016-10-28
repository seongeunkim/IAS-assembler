/**
 * Nome: Seong Eun Kim
 * RA: 177143
 * Turma: B
 */


#define LINE_SIZE 201	//maximum number of characters per line

#include "assembler.h"
#include "misc.h"
#include "list.h"
#include "btree.h"

int main(int argc, char* argv[]) {
	char line[LINE_SIZE], error[81];
	int cur_line = 1;

	struct node *root = NULL;
	struct lbl_list_node *head = NULL;
	struct tk_list_node *tk_head = NULL;

	FILE *infile = NULL;		//input file
	FILE *outfile = stdout;		//output file

	if(argc == 3) {	//if there is an output file, it points to it
		outfile = fopen(argv[2], "w");
	}

	infile = fopen(argv[1], "r");
	if(infile == NULL) {
		printf("ERROR\nCould not open file\n");
	}
	else {
		while(fgets(line, LINE_SIZE, infile)) {
			tokenize(line, &tk_head, cur_line, " \t\n");
			cur_line++;
		}
		if(verifyFile(&tk_head, error) == TRUE && createLblList(tk_head, &head, error) == TRUE &&
			createMemoryMap(tk_head, &head, &root, error) == TRUE) {
			createMemoryMap(tk_head, &head, &root, error);
			printInorder(outfile, root);
		}
		else {
			printMessage(outfile, error);
		}
		deallocateTree(root);
		deallocateLblList(head);
		deallocateTkList(tk_head);

		fclose(infile);
		if(outfile != stdout) {
			fclose(outfile);
		}
	}
}
