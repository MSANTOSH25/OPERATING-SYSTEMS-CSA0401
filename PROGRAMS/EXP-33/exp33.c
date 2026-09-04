/*
 * Experiment 33: Simulate the Optimal paging technique of memory management.
 */
#include <stdio.h>

int findFarthest(int ref[], int pages, int frame[], int frames, int current) {
    int farthestIdx = -1, farthestUse = -1;

    for (int j = 0; j < frames; j++) {
        int k;
        for (k = current + 1; k < pages; k++) {
            if (frame[j] == ref[k]) break;
        }
        if (k == pages) return j; // never used again
        if (k > farthestUse) { farthestUse = k; farthestIdx = j; }
    }
    return farthestIdx;
}

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

    int faults = 0;

    printf("\nRef\tFrames\n");
    for (i = 0; i < pages; i++) {
        int found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) { found = 1; break; }
        }

        if (!found) {
            int emptyIdx = -1;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) { emptyIdx = j; break; }
            }
            if (emptyIdx != -1) {
                frame[emptyIdx] = ref[i];
            } else {
                int replaceIdx = findFarthest(ref, pages, frame, frames, i);
                frame[replaceIdx] = ref[i];
            }
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
