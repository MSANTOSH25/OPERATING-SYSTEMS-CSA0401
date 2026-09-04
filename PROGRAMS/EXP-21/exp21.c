/*
 * Experiment 21: Worst Fit algorithm of memory management.
 */
#include <stdio.h>
#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) memory[i] = -1;
}

void displayMemory() {
    int count = 0;
    printf("Memory Status:\n");
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            count++;
            int j = i;
            while (j < MAX_MEMORY && memory[j] == -1) j++;
            printf("Free memory block %d-%d\n", i, j - 1);
            i = j - 1;
        }
    }
    if (count == 0) printf("No free memory available.\n");
}

void allocateMemory(int processId, int size) {
    int worstStart = -1, worstSize = 0;
    int i = 0;

    while (i < MAX_MEMORY) {
        if (memory[i] == -1) {
            int start = i, blockSize = 0;
            while (i < MAX_MEMORY && memory[i] == -1) { blockSize++; i++; }
            if (blockSize > worstSize) { worstSize = blockSize; worstStart = start; }
        } else {
            i++;
        }
    }

    if (worstSize >= size) {
        for (int k = worstStart; k < worstStart + size; k++) memory[k] = processId;
        printf("Allocated memory block %d-%d to Process %d\n", worstStart, worstStart + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++)
        if (memory[i] == processId) memory[i] = -1;
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();
    displayMemory();
    allocateMemory(1, 200);
    displayMemory();
    allocateMemory(2, 300);
    displayMemory();
    deallocateMemory(1);
    displayMemory();
    allocateMemory(3, 400);
    displayMemory();
    return 0;
}
