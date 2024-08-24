#include "main.h"
int main(int argc, char const *argv[])
{
	if((argc) < 2)
	{
		char *err_msg = (char *)err_malloc(SET_ERROR_BUFFER_SIZE * sizeof(char));
		snprintf(err_msg, SET_ERROR_BUFFER_SIZE, "Supply filename: %s <filename> <cols>\n ", argv[0]);
		debug(err_msg, 3);
		free(err_msg);
		exit(EXIT_FAILURE);
	}
	int collen;
	Dataset *csv_fd;

	csv_fd = (Dataset *)err_malloc(sizeof(Dataset));
	collen = 0;
	//printf("Implementing the CART learning algoithm in C\n\n");
	csv_fd = read_csv(argv[1]);
	if(argv[2] != NULL)
	{
		if((csv_fd->n_labels - atoi(argv[2])) >= 0)
		{
			collen = atoi(argv[2]);
		}
		else
		{
			collen = csv_fd->n_labels;
		}
	}
	else
	{
		collen = csv_fd->n_labels;
	}
    //printf("Labels:\n");
    printf("\n");
    print_separator(collen);
	for (int i = 0; i < collen; i++) {
    	printf("|%-*s", COLUMN_WIDTH, csv_fd->label_s[i]);
	}
	 //print_separator(collen);
	printf("|\n");

	// values
	for (int i = 0; i < csv_fd->n_examples; i++) {
    	for (int j = 0; j < collen; j++) {
        	printf("|%-*s", COLUMN_WIDTH, csv_fd->example_s[i][j]);
    	}
    printf("|\n");
    print_separator(collen);
}
	return 0;
}