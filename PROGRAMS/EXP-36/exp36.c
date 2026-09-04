/*
 * Experiment 36: Simulate Linked file allocation strategy.
 * Each file is a linked list of disk blocks; the directory holds
 * pointers to the first and last blocks; each block points to the next.
 */
#include <stdio.h>

#define MAX_BLOCKS 20

struct Block {
    int blockNum;
    int next;
};

int main() {
    int n, i;
    struct Block blocks[MAX_BLOCKS];

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    printf("Enter the disk block number for each block:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: ", i);
        scanf("%d", &blocks[i].blockNum);
    }

    for (i = 0; i < n; i++) {
        blocks[i].next = (i == n - 1) ? -1 : blocks[i + 1].blockNum;
    }

    printf("\nFirst Block: %d\tLast Block: %d\n", blocks[0].blockNum, blocks[n - 1].blockNum);

    printf("\nBlock No.\tNext Block\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t", blocks[i].blockNum);
        if (blocks[i].next == -1) printf("NULL (end of file)\n");
        else printf("%d\n", blocks[i].next);
    }

    printf("\nTraversal of file blocks: ");
    int current = blocks[0].blockNum;
    for (i = 0; i < n; i++) {
        printf("%d ", blocks[i].blockNum);
        if (blocks[i].next != -1) printf("-> ");
    }
    printf("\n");

    return 0;
}
