#include "main.h"
int main(int argc, char const *argv[])
{
	if((argc) < 2)
	{
		char *err_msg = (char *)err_malloc(SET_ERROR_BUFFER_SIZE * sizeof(char));
		snprintf(err_msg, SET_ERROR_BUFFER_SIZE, "Supply filename: %s <filename> <cols> <rows>\n ", argv[0]);
		debug(err_msg, 3);
		free(err_msg);
		exit(EXIT_FAILURE);
	}
	int collen;
	int rowlen;
	Dataset *csv_fd;
	collen = 0;
	rowlen = 0;
	csv_fd = (Dataset *)err_malloc(sizeof(Dataset));

	csv_fd = read_csv(argv[1]);
	if (argv[2] != NULL) 
	{
    	int cols = atoi(argv[2]);
    	if (cols > 0 && cols <= csv_fd->n_labels) 
    	{
        	collen = cols;
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

	if (argv[3] != NULL) 
	{
    	int rows = atoi(argv[3]);
    	if (rows > 0 && rows <= csv_fd->n_examples) 
    	{
        	rowlen = rows;
    	} 
    	else 
    	{
        	rowlen = csv_fd->n_examples;
    	}
	} 
	else 
	{
    	rowlen = csv_fd->n_examples;
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
	for (int i = 0; i < rowlen; i++) {
    	for (int j = 0; j < collen; j++) {
        	printf("|%-*s", COLUMN_WIDTH, csv_fd->example_s[i][j]);
    	}
    	printf("|\n");
    	print_separator(collen);
    }
    printf("Size of Ds: %ld\n", sizeof(csv_fd->n_labels));
    free_dataset(csv_fd);
	return 0;
}