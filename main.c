#include "main.h"
int main(int argc, char const *argv[])
{
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
	return 0;
}