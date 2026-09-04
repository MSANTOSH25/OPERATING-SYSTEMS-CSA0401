/*
 * Experiment 27: Simulate the function of the ls UNIX command.
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char fullPath[1024];

    printf("Contents of directory '%s':\n\n", path);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (stat(fullPath, &st) == 0) {
            printf("%c%c%c%c%c%c%c%c%c  %8ld  %s\n",
                   S_ISDIR(st.st_mode) ? 'd' : '-',
                   (st.st_mode & S_IRUSR) ? 'r' : '-',
                   (st.st_mode & S_IWUSR) ? 'w' : '-',
                   (st.st_mode & S_IXUSR) ? 'x' : '-',
                   (st.st_mode & S_IRGRP) ? 'r' : '-',
                   (st.st_mode & S_IWGRP) ? 'w' : '-',
                   (st.st_mode & S_IXGRP) ? 'x' : '-',
                   (st.st_mode & S_IROTH) ? 'r' : '-',
                   (st.st_mode & S_IWOTH) ? 'w' : '-',
                   (long)st.st_size,
                   entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
