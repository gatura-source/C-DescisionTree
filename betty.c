#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CSV_DELIMITER ","
#define PLACEHOLDER "EMPTY"

void parse_csv_entry(char *entry, char **output, int num_labels) {
    int idx = 0;
    char *start = entry;
    char *end = NULL;

    while (idx < num_labels) {
        // Find the next delimiter
        end = strchr(start, CSV_DELIMITER[0]);

        if (end == start) {
            // Consecutive commas, this is an empty field
            output[idx] = (char *)malloc(strlen(PLACEHOLDER) + 1);
            if (output[idx] != NULL) {
                strcpy(output[idx], PLACEHOLDER);
            }
            start++;  // Move past the comma to the next field
        } else if (end != NULL) {
            // Token found between commas
            size_t len = end - start;
            output[idx] = (char *)malloc(len + 1);
            if (output[idx] != NULL) {
                strncpy(output[idx], start, len);
                output[idx][len] = '\0';  // Null-terminate the string
            }
            start = end + 1;  // Move past the comma to the next field
        } else {
            // Last token, or no more commas
            output[idx] = (char *)malloc(strlen(start) + 1);
            if (output[idx] != NULL) {
                strcpy(output[idx], start);
            }
            start += strlen(start);  // End of string
        }

        idx++;
    }

    // If fewer fields are found, fill the remaining with PLACEHOLDER
    while (idx < num_labels) {
        output[idx] = (char *)malloc(strlen(PLACEHOLDER) + 1);
        if (output[idx] != NULL) {
            strcpy(output[idx], PLACEHOLDER);
        }
        idx++;
    }
}

int main() {
    char entry[] = ",,,,8.2,,,,,,,,4.0,,,Subcooled,,-42.0,,,,17.9,,,"; 
    int num_fields = 20;  // Example maximum number of fields
    char *output[num_fields];

    // Initialize output array to NULL
    for (int i = 0; i < num_fields; i++) {
        output[i] = NULL;
    }

    // Parse the CSV entry
    parse_csv_entry(entry, output, num_fields);

    // Print the parsed output
    for (int i = 0; i < num_fields; i++) {
        if (output[i] != NULL) {
            printf("Field %d: '%s'\n", i + 1, output[i]);
            free(output[i]);  // Don't forget to free the allocated memory
        }
    }

    return 0;
}
