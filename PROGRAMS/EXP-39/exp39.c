/*
 * Experiment 39: Simulate the C-SCAN (Circular SCAN) disk scheduling
 * algorithm. The arm moves in one direction, jumps to the beginning
 * at the end of the disk, and continues in the same direction.
 */
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i, head, diskSize, totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (i = 0; i < n; i++) scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &diskSize);

    qsort(requests, n, sizeof(int), cmpfunc);

    int left[n], right[n];
    int leftCount = 0, rightCount = 0;

    for (i = 0; i < n; i++) {
        if (requests[i] < head) left[leftCount++] = requests[i];
        else right[rightCount++] = requests[i];
    }

    printf("\nSeek Sequence (moving towards higher end, wrap around): %d ", head);
    int current = head;

    for (i = 0; i < rightCount; i++) {
        totalMovement += abs(right[i] - current);
        current = right[i];
        printf("-> %d ", current);
    }

    // Move to the end of disk, then jump to 0
    totalMovement += abs((diskSize - 1) - current);
    current = diskSize - 1;
    printf("-> %d ", current);

    totalMovement += (diskSize - 1); // jump from end to start counted as movement
    current = 0;
    printf("-> %d ", current);

    for (i = 0; i < leftCount; i++) {
        totalMovement += abs(left[i] - current);
        current = left[i];
        printf("-> %d ", current);
    }

    printf("\n\nTotal Head Movement: %d\n", totalMovement);
    printf("Average Seek Length: %.2f\n", (float)totalMovement / n);

    return 0;
}
