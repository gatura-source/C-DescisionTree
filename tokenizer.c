#include "main.h"

/**
 * next - Retrieves next token
 * @token - input string
 * Returns: next token based on the delimiter passed
 **/
char *next(Token *token) {
    char *output;
    int idx = 0;

    if (token == NULL || token->input_str == NULL || token->pos >= (int)strlen(token->input_str)) {
        return NULL;
    }

    // Allocate memory for the token output
    output = (char *)malloc(sizeof(char) * TOKEN_SIZE);
    if (output == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Initialize output as an empty string
    memset(output, '\0', TOKEN_SIZE);

    // Iterate through the input string starting from the current position
    while (token->input_str[token->pos] != '\0') {
        if (token->input_str[token->pos] == token->delimiter) 
        {
            break;
        } 
        else 
        {
            // Append character to the output token
            output[idx++] = token->input_str[token->pos];
        }
        token->pos++;
    }

    // Move past the delimiter
    token->pos++;

    // Return the extracted token
    if (strlen(output) == 0)
    {
       snprintf(output, strlen(PLACEHOLDER) + 1, "%s", PLACEHOLDER);
    }
    return output;
}