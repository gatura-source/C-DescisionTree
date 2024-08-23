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

	//printf("Implementing the CART learning algoithm in C\n\n");
	csv_fd = read_csv(argv[1]);
	
	
	//the labels
	for (int i = 0; i  < csv_fd->l_abels->num_labels; i++)
	{
		printf("|%s\t",csv_fd->l_abels->labels[i]);
	}
	printf("|\n");
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (csv_fd->ex->table[i][0] != NULL)
		{
			for (int j = 0; j < csv_fd->l_abels->num_labels; j++)
			{
				printf("|%s\t", csv_fd->ex->table[i][j]);
			}
		}
		else
		{
			break;
		}
		printf("\n");
	}
	return 0;
}