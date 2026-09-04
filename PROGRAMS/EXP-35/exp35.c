/*
 * Experiment 35: Simulate Indexed file allocation strategy.
 * An index block holds pointers to each block of the file.
 */
#include <stdio.h>

#define MAX_BLOCKS 20

int main() {
    int n, indexBlock[MAX_BLOCKS];
    int i;

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    printf("Enter the disk block numbers for each file block:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: ", i);
        scanf("%d", &indexBlock[i]);
    }

    printf("\nIndex Block Table:\n");
    printf("File Block No.\tDisk Block No.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\n", i, indexBlock[i]);
    }

    int fileBlockNum;
    printf("\nEnter file block number to access: ");
    scanf("%d", &fileBlockNum);

    if (fileBlockNum < 0 || fileBlockNum >= n) {
        printf("Invalid block number.\n");
    } else {
        printf("Accessing disk block %d directly via the index block.\n", indexBlock[fileBlockNum]);
    }

    return 0;
}
