/*
 * Experiment 40: Illustrate the various File Access Permissions and
 * different types of users in Linux (Owner, Group, Others) using a
 * C program built on UNIX system calls.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void printPermissions(mode_t mode) {
    printf("Permissions: ");
    printf((S_ISDIR(mode)) ? "d" : "-");

    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");

    printf("\n");
}

int main() {
    char filename[100];
    struct stat st;

    printf("Enter file name to inspect: ");
    scanf("%s", filename);

    if (stat(filename, &st) == -1) {
        perror("stat");
        return 1;
    }

    printPermissions(st.st_mode);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    printf("Owner (User): %s\n", pw ? pw->pw_name : "unknown");
    printf("Group: %s\n", gr ? gr->gr_name : "unknown");
    printf("Others: all remaining users on the system\n");

    printf("\nChanging permissions to rwxr-xr-- (750)...\n");
    if (chmod(filename, 0750) == 0) {
        stat(filename, &st);
        printPermissions(st.st_mode);
    } else {
        perror("chmod");
    }

    return 0;
}
