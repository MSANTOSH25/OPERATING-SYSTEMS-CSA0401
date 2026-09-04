/*
 * Experiment 28: Simulation of the GREP UNIX command.
 * Usage: ./exp28 <pattern> <filename>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    char pattern[256], filename[256];

    if (argc == 3) {
        strcpy(pattern, argv[1]);
        strcpy(filename, argv[2]);
    } else {
        printf("Enter search pattern: ");
        scanf("%s", pattern);
        printf("Enter file name: ");
        scanf("%s", filename);
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE];
    int lineNum = 0, found = 0;

    while (fgets(line, MAX_LINE, fp) != NULL) {
        lineNum++;
        if (strstr(line, pattern) != NULL) {
            printf("%d: %s", lineNum, line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Pattern '%s' not found in '%s'.\n", pattern, filename);
    }

    fclose(fp);
    return 0;
}
