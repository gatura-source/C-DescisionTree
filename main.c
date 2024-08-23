#include "main.h"
int main(int argc, char const *argv[])
{
	if((argc) < 2)
	{
		char *err_msg = (char *)err_malloc(SET_ERROR_BUFFER_SIZE * sizeof(char));
		snprintf(err_msg, SET_ERROR_BUFFER_SIZE, "Supply filename: %s filename\n", argv[0]);
		debug(err_msg, 3);
		free(err_msg);
		exit(EXIT_FAILURE);
	}
	Dataset *csv_fd;

	csv_fd = (Dataset *)err_malloc(sizeof(Dataset));

	//printf("Implementing the CART learning algoithm in C\n\n");
	csv_fd = read_csv(argv[1]);
    // Use the dataset
    printf("Labels:\n");
    for (int i = 0; i < csv_fd->n_labels; i++) {
        printf("%s\t", csv_fd->label_s[i]);
    }
    printf("\nNo. labels: %d\nsamples:\n", csv_fd->n_labels);
    for (int i = 0; i < csv_fd->n_examples; i++) {
    	for (int j = 0; j < csv_fd->n_labels; j++)
    	{
        	printf("%s\t", csv_fd->example_s[i][2]);
        }
    }
    
	return 0;
}