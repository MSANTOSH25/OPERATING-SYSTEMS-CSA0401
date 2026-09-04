/*
 * Experiment 32: Simulate the Least Recently Used (LRU) paging technique
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
    int lastUsed[frames];
    for (i = 0; i < frames; i++) { frame[i] = -1; lastUsed[i] = -1; }

    int faults = 0;

    printf("\nRef\tFrames\n");
    for (i = 0; i < pages; i++) {
        int found = -1;
        for (j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) { found = j; break; }
        }

        if (found != -1) {
            lastUsed[found] = i;
        } else {
            int replaceIdx = -1;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) { replaceIdx = j; break; }
            }
            if (replaceIdx == -1) {
                int minIdx = 0;
                for (j = 1; j < frames; j++)
                    if (lastUsed[j] < lastUsed[minIdx]) minIdx = j;
                replaceIdx = minIdx;
            }
            frame[replaceIdx] = ref[i];
            lastUsed[replaceIdx] = i;
            faults++;
        }

        printf("%d\t", ref[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf(found != -1 ? "(hit)\n" : "(fault)\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}
