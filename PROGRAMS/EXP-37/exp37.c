/*
 * Experiment 37: Simulate the First Come First Served (FCFS) disk
 * scheduling algorithm.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (i = 0; i < n; i++) scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence: %d ", head);
    for (i = 0; i < n; i++) {
        totalMovement += abs(requests[i] - head);
        head = requests[i];
        printf("-> %d ", head);
    }

    printf("\n\nTotal Head Movement: %d\n", totalMovement);
    printf("Average Seek Length: %.2f\n", (float)totalMovement / n);

    return 0;
}
