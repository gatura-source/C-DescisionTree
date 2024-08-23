#include "main.h"

/**
 * debug - Debugs program output
 * @string- debug message
 * @symbol: Error Code
 **/
void debug(char *string, int symbol)
{
	switch(symbol){
	case 1:
		printf("[FILE IO ERROR: %s]", string);
		break;
	case 2:
		printf("[MEM ERROR: %s]", string);
		break;
	default:
		printf("[ERROR: %s]", string);
		break;
	}
	
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
	if (fd != -1)
	{
		memset(line_buffer, 0, sizeof(line_buffer));
		//operations goes around here
		char char_buffer;
		int idx;

		idx = 0;

		while (read(fd, &char_buffer, 1) > 0)
		{
			if (char_buffer == '\n')
			{
				break;
			}
			line_buffer[idx++] = char_buffer;
		}
		line_buffer[idx] = '\0';
		//printf("Line buffer: %s\n", line_buffer);
		return idx;
	}
	return -1;
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
	char *error_msg;
	int num_labels;
	char **labels;
	char *token;
	Dataset *Ds;



	
	num_labels = 0;
	
	Ds = (Dataset *)err_malloc(sizeof(Dataset));
	Ds->l_abels = (Labels * )err_malloc(sizeof(Labels));
	Ds->ex = (Examples *)err_malloc(sizeof(Examples));
	//open file
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		
		error_msg = (char *)err_malloc(sizeof(char) * SET_ERROR_BUFFER_SIZE);
		snprintf(error_msg, 256, "Failed to open %s", filepath);
		debug(error_msg, 1);
		free(error_msg);
		exit(EXIT_FAILURE);

	}
	Ds->file_descriptor = fd;
	//read the first line
	//allocate buffer for the keys
	key_buffer = (char *)err_malloc(sizeof(char) * 1024);
	if (key_buffer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (read_line(fd, key_buffer) == -1)
	{
		free(key_buffer);
		exit(EXIT_FAILURE);
	}
	//printf("Keys: %s\n", key_buffer);
	//free(key_buffer);

	//get number of labels
	char *temp_buffer = key_buffer;
	while(*temp_buffer != '\0')
	{
		if (*temp_buffer == ',')
		{
			num_labels++;
		}
		temp_buffer++;
	}
	num_labels++;

	Ds->l_abels->num_labels = num_labels;
	Ds->l_abels->labels = (char **)err_malloc(num_labels * sizeof(char **));
	if (Ds->l_abels->labels == NULL)
	{
		free(Ds->l_abels);
		free(key_buffer);
		close(fd);
		exit(EXIT_FAILURE);
	}
	//printf("Keys again: %s\n", key_buffer);
	token = strtok(key_buffer, CSV_DELIMITER);
	//printf("Token: %s\n", key_buffer);

	/*Get the labels*/
	for (int j = 0; j < num_labels; j++)
	{
		if (token != NULL)
		{
			//printf("Token: %s\n", key_buffer);
			Ds->l_abels->labels[j] = strdup(token);
			//printf("T: %s - Idx: %d\n", token, j);
			token = strtok(NULL, CSV_DELIMITER);
		}
		

	}
	//allocate mem for each row in table
	for (int table = 0; table < TABLE_SIZE; table++)
	{
		Ds->ex->table[table] = (example **)err_malloc(sizeof(example));
		if (Ds->ex->table[table] == NULL)
		{
			//free labels
			free(Ds->l_abels->labels);
			free(Ds->l_abels);
			free(Ds);
			for (int t = 0; t < table; t++)
			{
				free(Ds->ex->table[t]);
			}
			exit(EXIT_FAILURE);
		}
		Ds->ex->table[table] = (example **)err_malloc(sizeof(char *) * 3);
		if (Ds->ex->table[table] == NULL)
		{
			for (int i = 0; i <= table; i++)
			{
				free(Ds->ex->table[i]);
			}
			exit(EXIT_FAILURE);
		}
		//read lines
		if (read_line(fd, key_buffer) != -1)
		{
			token = strtok(key_buffer, CSV_DELIMITER);
			int idx_counter = 0;
			//printf("IDx: %d\n", table);
			while (token != NULL)
			{
				printf("Idx: %d\n", table);
				example *ex = (example *)strdup(token);
				Ds->ex->table[table][idx_counter] = ex;
				idx_counter++;
				token = strtok(NULL, CSV_DELIMITER);
			}

		}
		else
		{
			break;
		}
		
	}
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