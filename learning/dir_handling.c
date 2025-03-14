#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

/*
cp dir_handling.c ~ // not needed on my machine
cd ~
cc -Wall -Wextra -Werror dir_handling.c && ./a.out
*/
int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return (1);
    }
    struct  dirent *entry;
    struct stat file_stat;
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                printf("[DIR] %s\n", entry->d_name);
            } else if (S_ISREG(file_stat.st_mode)) {
                printf("[FILE] %s\n", entry->d_name);
            } else {
                printf("[OTHER] %s\n", entry->d_name);
            }
        } else {
            perror("stat");
        }
    }
    closedir(dir);
    return (0);
}

/*
1. Definition of struct dirent
The struct dirent is defined in <dirent.h> and typically looks like this:

c
Copy
Edit
struct dirent {
    ino_t          d_ino;       // Inode number
    off_t          d_off;       // Offset to next dirent
    unsigned short d_reclen;    // Length of this record
    unsigned char  d_type;      // Type of file (not always available)
    char           d_name[];    // File name (null-terminated)
};
d_ino – The inode number of the file. Used for identifying files uniquely within a filesystem.
d_off – Offset to the next directory entry (mostly used internally).
d_reclen – Length of this record (important for variable-length entries).
d_type – File type (e.g., regular file, directory, symbolic link). Not always supported on all systems.
d_name – The name of the file or directory (null-terminated string).

On some filesystems (e.g., network filesystems), d_type may not be available. In that case, use stat():
struct dirent is useful for iterating over directory contents.
d_name contains the file name.
d_type helps differentiate between files and directories, but is not always available.
stat() provides more reliable file information.

cp dir_handling.c ~
~ = home directory (/home/username in Linux).

Since your original directory was inside /mnt/c/... (which is the Windows NTFS filesystem mounted in WSL), d_type was likely unavailable. Copying the file to ~ places it in the Linux-native file system where d_type works correctly.
*/