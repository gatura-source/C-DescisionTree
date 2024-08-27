#include "main.h"
#include <string.h>
/**
 * debug - Debugs program output
 * @string- debug message
 * @symbol: Error Code
 **/
void debug(char *string, int symbol)
{
	switch(symbol){
	case 1:
		printf("[FILE IO ERROR: %s]\n", string);
		break;
	case 2:
		printf("[MEM ERROR: %s]\n", string);
		break;
	default:
		printf("[ERROR: %s]\n", string);
	}
	
}

/**
 * free_dataset - free Dataset type
 * @dataset - Dataset to free
 * Returns: void
 **/
void free_dataset(Dataset *dataset) {
    if (dataset == NULL) {
        return;
    }

    // Free each label string
    for (int i = 0; i < dataset->n_labels; i++) {
        free(dataset->label_s[i]);
    }
    // Free the array of labels
    free(dataset->label_s);

    //close the file
    close(dataset->file_descriptor);
    // Free each example (each example is an array of strings)
    for (int i = 0; i < dataset->n_examples; i++) {
        for (int j = 0; j < dataset->n_labels; j++) {
            free(dataset->example_s[i][j]);
        }
        // Free the array of strings for each example
        free(dataset->example_s[i]);
    }
    // Free the array of examples
    free(dataset->example_s);

    // Finally, free the dataset structure itself
    free(dataset);
}


/**
 * err_malloc - error checking malloc
 * @memsize: memory size to allocate
 **/
void *err_malloc(size_t memsize)
{
	void *buffer = malloc(memsize);
	if (buffer != NULL)
	{
		return buffer;
	}
	debug("allocation failed at err_malloc", 2);
	return NULL;
}

/**
 * read_line - reads a file line
 * @fd - file dscriptor
 * @line_buffer- buffer to hold the line
 * Returns: buffer
 **/
int read_line(int fd, char *line_buffer)
{
    if (fd == -1)
        return -1;

    memset(line_buffer, 0, 1025);
    char char_buffer;
    int idx = 0;
    ssize_t bytes_read;

    while (idx < 1024)  // Prevent overflow by leaving space for the null terminator
    {
        bytes_read = read(fd, &char_buffer, 1);
        if (bytes_read == -1)
        {
            // Handle error
            perror("read");
            return -1;
        }
        else if (bytes_read == 0)
        {
            // End of file
            break;
        }

        if (char_buffer == '\n')
        {
            break;
        }
        line_buffer[idx] = char_buffer;
        idx++;
    }
    line_buffer[idx] = '\0';
    return idx;
}

/**
 * read_csv - reads csv files
 * @filepath- filename supplied to the function
 * Returns: Dataset on success
 **/
Dataset *read_csv(const char *filepath)
{
	int fd;
	char *key_buffer;
	char *temp_buffer;
	char *error_msg;
	int num_labels;
	char *token;
	Dataset *Ds;
	Token tokenizer;

	//try opening file
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		
		error_msg = (char *)err_malloc(sizeof(char) * SET_ERROR_BUFFER_SIZE);
		snprintf(error_msg, 256, "Failed to open %s", filepath);
		debug(error_msg, 1);
		free(error_msg);
		exit(EXIT_FAILURE);

	}
	//Initalize Dataset
	Ds = (Dataset *)err_malloc(sizeof(Dataset));
	if(Ds == NULL)
	{
		exit(EXIT_FAILURE);
	}

	//add file descriptor to Ds
	Ds->file_descriptor = fd;

	//get the labels from the first line of the file
	num_labels = 0;

	//allocate buffer for the keys
	key_buffer = (char *)err_malloc(1 + (sizeof(char) * 1024));
	if (key_buffer == NULL)
	{
		free_dataset(Ds);
		// free(Ds);
		exit(EXIT_FAILURE);
	}
	if (read_line(fd, key_buffer) == -1)
	{
		free_dataset(Ds);
		// free(Ds);
		free(key_buffer);
		exit(EXIT_FAILURE);
	}

	//get number of labels
	temp_buffer = key_buffer;
	while(*temp_buffer != '\0')
	{
		if (*temp_buffer == ',')
		{
			num_labels++;
		}
		temp_buffer++;
	}
	num_labels++;
	
	//add number of labels to the Ds
	Ds->n_labels = num_labels;

	//Now getting the labels
	Ds->label_s = (char **)err_malloc(1 + num_labels * sizeof(char *));
	if (Ds->label_s == NULL)
	{
		free(key_buffer);
		free_dataset(Ds);
		exit(EXIT_FAILURE);
	}

	//initalize tokenizer
	token = strtok(key_buffer, CSV_DELIMITER);

	/*Get the labels*/
	for (int j = 0; j < num_labels; j++)
	{
		if (token != NULL)
		{
			Ds->label_s[j] = (char *)err_malloc(20 * sizeof(char));
			if (!Ds->label_s[j])
			{
				free_dataset(Ds);
				exit(EXIT_FAILURE);
			}
			snprintf(Ds->label_s[j], 20, "%s", token);
			token = strtok(NULL, CSV_DELIMITER);
		}
		

	}
	
	//count the lines
	int line_count = 0;
	while(1)
	{
		if (read_line(fd, key_buffer) <= 0)
		{
			break;
		}
		line_count++;
		//printf("%d\n", line_count);
	}
	//printf("SIGSEGV");
	//Get examples
	Ds->example_s = (char ***)err_malloc(line_count * sizeof(char **));
	//printf("SIGSEGV");
	if (Ds->example_s == NULL)
	{
		//free
	}
	Ds->n_examples = line_count;
	//rewind file pointer
	//printf("rewind");
	lseek(fd, 0, SEEK_SET);
	read_line(fd, key_buffer);
	for(int i = 0; i < line_count; i++)
	{
		Ds->example_s[i] = (char **)err_malloc((num_labels * sizeof(char *)));
		if (Ds->example_s[i] == NULL)
		{
			//free
			free(Ds);
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < line_count; i++)
	{
		int idx = 0;

		if (read_line(fd, key_buffer) != -1)
		{
			tokenizer.input_str = key_buffer;
			tokenizer.delimiter = ',';
			tokenizer.pos = 0;
			tokenizer.next = next;
			while( (token = tokenizer.next(&tokenizer)) != NULL && idx < num_labels)
			{

				Ds->example_s[i][idx] = (char *)err_malloc((sizeof(char) * (TOKEN_SIZE)));
				if (Ds->example_s[i][idx] == NULL)
				{
					//free
					free_dataset(Ds);
					exit(EXIT_FAILURE);
				}
				if (strlen(token) == 1)
				{
					snprintf(Ds->example_s[i][idx], strlen(PLACEHOLDER)+1, "%s", PLACEHOLDER);
				}
				else
				{
					snprintf(Ds->example_s[i][idx], strlen(token)+1, "%s", token);
				}
				free(token);
				idx++;
			}
			//printf("IDX: %d\n", idx);
		}
	}
	;
	free(key_buffer);
	return Ds;
}

/**
 * get_current_pos - getting current file pos
 * @fd- file fd
 * Returns: file pos
 **/
off_t get_current_pos(int fd)
{
	return lseek(fd, 0, SEEK_CUR);
}
/**
 * print_separator - rows separator
 * @collen - column length
 **/
void print_separator(int collen) {
    for (int i = 0; i < collen; i++) {
        printf("+");
        for (int j = 0; j < COLUMN_WIDTH; j++) {
            printf("-");
        }
    }
    printf("+\n");
}

