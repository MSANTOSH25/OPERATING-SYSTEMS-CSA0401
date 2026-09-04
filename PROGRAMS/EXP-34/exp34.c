/*
 * Experiment 34: Simulate Sequential (Contiguous) file allocation strategy.
 * Records are stored one after another; a record can only be accessed
 * by reading all previous records.
 */
#include <stdio.h>

#define MAX_FILES 10

struct File {
    char name[20];
    int startBlock;
    int length;
};

int main() {
    int n, i, j;
    struct File files[MAX_FILES];

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nFile %d name: ", i + 1);
        scanf("%s", files[i].name);
        printf("Start block: ");
        scanf("%d", &files[i].startBlock);
        printf("Length (number of blocks): ");
        scanf("%d", &files[i].length);
    }

    printf("\nFile Name\tStart Block\tLength\tBlocks Allocated\n");
    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t", files[i].name, files[i].startBlock, files[i].length);
        for (j = 0; j < files[i].length; j++) {
            printf("%d ", files[i].startBlock + j);
        }
        printf("\n");
    }

    int recordNum;
    printf("\nEnter file index (0 to %d) to access a record from: ", n - 1);
    scanf("%d", &i);
    printf("Enter record number to access (0-indexed): ");
    scanf("%d", &recordNum);

    if (recordNum >= files[i].length) {
        printf("Invalid record number.\n");
    } else {
        printf("To access record %d of file '%s', blocks 0 to %d must be read sequentially.\n",
               recordNum, files[i].name, recordNum);
        printf("Block accessed: %d\n", files[i].startBlock + recordNum);
    }

    return 0;
}
