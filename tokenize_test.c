#include "main.h"

char *next(Token *token) {
    char *output;
    int idx = 0;

    if (token == NULL || token->input_str == NULL || token->pos >= strlen(token->input_str)) {
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

int main() 
{
    Token tokenizer;
    tokenizer.input_str = "Bedan,35,Male,3500000";
    tokenizer.delimiter = ',';
    tokenizer.pos = 0;
    tokenizer.next = next;

    char *token;
    while ((token = tokenizer.next(&tokenizer)) != NULL) {
        printf("Token: %s: Pos %d\n", token, tokenizer.pos);
        free(token); // Free memory for each token after usage
    }

    return 0;
}