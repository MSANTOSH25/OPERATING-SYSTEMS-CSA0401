/*
 * Experiment 25: Implement I/O system calls of UNIX
 * (fcntl, lseek, stat, opendir, readdir).
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void demoFcntl(const char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) { perror("open"); return; }

    int flags = fcntl(fd, F_GETFL);
    printf("File descriptor flags for '%s': %d\n", filename, flags);

    close(fd);
}

void demoSeek(const char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) { perror("open"); return; }

    write(fd, "0123456789", 10);
    off_t pos = lseek(fd, 5, SEEK_SET);
    printf("Seeked to position: %ld\n", (long)pos);

    char c;
    read(fd, &c, 1);
    printf("Character at position 5: %c\n", c);

    close(fd);
}

void demoStat(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) { perror("stat"); return; }

    printf("File size: %ld bytes\n", (long)st.st_size);
    printf("Permissions: %o\n", st.st_mode & 0777);
    printf("Last modified time: %ld\n", (long)st.st_mtime);
}

void demoDirectory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) { perror("opendir"); return; }

    struct dirent *entry;
    printf("Contents of directory '%s':\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

int main() {
    const char *filename = "iodemo.txt";

    demoFcntl(filename);
    demoSeek(filename);
    demoStat(filename);
    demoDirectory(".");

    remove(filename);
    return 0;
}
