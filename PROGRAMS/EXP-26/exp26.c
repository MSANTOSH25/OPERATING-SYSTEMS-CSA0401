/*
 * Experiment 26: Implement file management operations
 * (create, open, read, write, rename, delete).
 */
#include <stdio.h>
#include <stdlib.h>

void createFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) { printf("Error creating file.\n"); return; }
    printf("File '%s' created.\n", filename);
    fclose(fp);
}

void writeFile(const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) { printf("Error opening file.\n"); return; }
    char text[200];
    printf("Enter text to write: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    fputs(text, fp);
    fclose(fp);
    printf("Data written to '%s'.\n", filename);
}

void readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { printf("Error opening file.\n"); return; }
    char ch;
    printf("Contents of '%s':\n", filename);
    while ((ch = fgetc(fp)) != EOF) putchar(ch);
    fclose(fp);
}

void renameFileOp(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0)
        printf("File renamed from '%s' to '%s'.\n", oldName, newName);
    else
        perror("rename");
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0)
        printf("File '%s' deleted.\n", filename);
    else
        perror("remove");
}

int main() {
    char filename[100], newName[100];
    int choice;

    do {
        printf("\n1. Create\t2. Write\t3. Read\t4. Rename\t5. Delete\t6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", filename);
                createFile(filename);
                break;
            case 2:
                printf("Enter file name: ");
                scanf("%s", filename);
                writeFile(filename);
                break;
            case 3:
                printf("Enter file name: ");
                scanf("%s", filename);
                readFile(filename);
                break;
            case 4:
                printf("Enter current file name: ");
                scanf("%s", filename);
                printf("Enter new file name: ");
                scanf("%s", newName);
                renameFileOp(filename, newName);
                break;
            case 5:
                printf("Enter file name: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;
            case 6:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
