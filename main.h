#ifndef MAIN_H
#define MAIN_H

#define MAX_DEPTH 10
#define MIN_SAMPLES 2
#define SET_ERROR_BUFFER_SIZE 128
#define CSV_DELIMITER ","
#define SET_TABLE_SIZE 100
#define COLUMN_WIDTH 20
#define PLACEHOLDER "(null)"  // Define a placeholder for missing values
#define TOKEN_SIZE 32



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct DecisionTree
{
	int max_depth;
	int min_sample_splits;
	int root;
} DecisionTree;

typedef struct TreeNode
{
	char feature;
	float threshold;
	float left;
	float right;
	float prediction;
	
} TreeNode;

typedef struct Dataset
{
	int file_descriptor;
	int n_labels;
	int n_examples;
	char **label_s; //pointer to type Labels
	char ***example_s; //pointer to type Example
} Dataset;

typedef struct Token {
    int pos;          // Position of the token in the original string
    char delimiter;
    char *input_str;      // The actual token (substring)
    char *(*next)(struct Token *); //next function
} Token;

char *next(Token *token);
Dataset *read_csv(const char *filepath);
int read_json(char *filename);
void *err_malloc(size_t);
int read_line(int, char*);
int information_gain();
float entropy();
int predict();
void debug(char*, int);
off_t get_current_pos(int);
void print_separator(int collen);
void free_dataset(Dataset *dataset);
void parse_csv_entry(char *entry, char **output, int num_labels);


#endif