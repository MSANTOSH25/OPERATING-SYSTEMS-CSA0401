/*
 * Experiment 31: Simulate the First In First Out (FIFO) paging technique
 * of memory management.
 */
#include <stdio.h>

int main() {
    int frames, pages, i, j;

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages in reference string: ");
    scanf("%d", &pages);

    int ref[pages];
    printf("Enter the reference string:\n");
    for (i = 0; i < pages; i++) scanf("%d", &ref[i]);

    int frame[frames];
    for (i = 0; i < frames; i++) frame[i] = -1;

    int faults = 0, front = 0;

    printf("\nRef\tFrames\n");
    for (i = 0; i < pages; i++) {
        int found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) { found = 1; break; }
        }

        if (!found) {
            frame[front] = ref[i];
            front = (front + 1) % frames;
            faults++;
        }

        printf("%d\t", ref[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf(found ? "(hit)\n" : "(fault)\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}
