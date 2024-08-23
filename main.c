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
	char *buffer;

	csv_fd = (Dataset *)err_malloc(sizeof(Dataset));

	printf("Implementing the CART learning algoithm in C\n\n");
	csv_fd = read_csv(argv[1]);
	
	//file desc
	printf("The file descriptor = %d\n", csv_fd->file_descriptor);
	//The number labels
	printf("The number of labels: %d\n", csv_fd->l_abels->num_labels);
	
	//the labels
	printf("The labels: \n");
	for (int i = 0; i  < csv_fd->l_abels->num_labels; i++)
	{
		printf("Label %d : %s\n",i, csv_fd->l_abels->labels[i]);
	}
	//examples
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (csv_fd->ex->table[i][0] != NULL)
		{
			printf("Length: %d\n", strlen(csv_fd->ex->table[i]));
			printf("Sample %d -> %s\n", i, csv_fd->ex->table[i][0]);
		}
	}
	return 0;
}