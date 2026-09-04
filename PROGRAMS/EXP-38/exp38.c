/*
 * Experiment 38: Simulate the SCAN disk scheduling algorithm.
 * The disk arm moves in one direction servicing requests, reverses
 * at the end of the disk, and services the remaining requests.
 */
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i, head, diskSize, direction, totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (i = 0; i < n; i++) scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &diskSize);
    printf("Enter direction (1 for towards higher end, 0 for towards lower end): ");
    scanf("%d", &direction);

    qsort(requests, n, sizeof(int), cmpfunc);

    int left[n], right[n];
    int leftCount = 0, rightCount = 0;

    for (i = 0; i < n; i++) {
        if (requests[i] < head) left[leftCount++] = requests[i];
        else right[rightCount++] = requests[i];
    }

    printf("\nSeek Sequence: %d ", head);
    int current = head;

    if (direction == 1) {
        for (i = 0; i < rightCount; i++) {
            totalMovement += abs(right[i] - current);
            current = right[i];
            printf("-> %d ", current);
        }
        totalMovement += abs((diskSize - 1) - current);
        current = diskSize - 1;
        printf("-> %d ", current);

        for (i = leftCount - 1; i >= 0; i--) {
            totalMovement += abs(current - left[i]);
            current = left[i];
            printf("-> %d ", current);
        }
    } else {
        for (i = leftCount - 1; i >= 0; i--) {
            totalMovement += abs(current - left[i]);
            current = left[i];
            printf("-> %d ", current);
        }
        totalMovement += abs(current - 0);
        current = 0;
        printf("-> %d ", current);

        for (i = 0; i < rightCount; i++) {
            totalMovement += abs(right[i] - current);
            current = right[i];
            printf("-> %d ", current);
        }
    }

    printf("\n\nTotal Head Movement: %d\n", totalMovement);
    printf("Average Seek Length: %.2f\n", (float)totalMovement / n);

    return 0;
}
