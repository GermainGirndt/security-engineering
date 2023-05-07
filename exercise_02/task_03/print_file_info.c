#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define ACCESS_PERMISSIONS_MASK (S_IRWXU | S_IRWXG | S_IRWXO)

// Print the file type based on the mode
void print_file_type(mode_t mode)
{
    if (S_ISLNK(mode))
    {
        printf("File type: Symbolic link\n");
    }
    else if (S_ISREG(mode))
    {
        printf("File type: Regular file\n");
    }
    else if (S_ISDIR(mode))
    {
        printf("File type: Directory\n");
    }
    else if (S_ISFIFO(mode))
    {
        printf("File type: Pipe\n");
    }
    else if (S_ISSOCK(mode))
    {
        printf("File type: Socket\n");
    }
    else if (S_ISCHR(mode))
    {
        printf("File type: Character device\n");
    }
    else if (S_ISBLK(mode))
    {
        printf("File type: Block device\n");
    }
    else
    {
        printf("File type: Unknown\n");
    }
}

// Print the user and group information
void print_user_group(uid_t uid, gid_t gid)
{
    // retrives user information (pw = password, which is historically an user related struct)
    struct passwd *pw = getpwuid(uid);
    // retrivers group information
    struct group *gr = getgrgid(gid);
    if (pw != NULL && gr != NULL)
    {
        printf("User: %s (UID: %d), Group: %s (GID: %d)\n",
               pw->pw_name, uid, gr->gr_name, gid);
    }
    else
    {
        printf("User or group information not available\n");
    }
}

// Print the access permissions in octal format
void print_access_permissions(mode_t mode)
{
    // A macro ACCESS_PERMISSIONS_MASK is defined to represent the bitmask for extracting the file access permissions.
    // A macro in C is a preprocessor directive that defines a symbolic name or a function-like construct. It is a way to perform text substitution in the code before the actual compilation takes place
    printf("Access permissions: %o\n", mode & ACCESS_PERMISSIONS_MASK);
}

// Print the time based on the provided label
void print_time(const char *label, time_t timestamp)
{
    char *timeString = ctime(&timestamp);
    if (timeString != NULL)
    {
        // Remove the newline character from the end of the string
        timeString[strlen(timeString) - 1] = '\0';
        printf("%s: %s\n", label, timeString);
    }
    else
    {
        printf("Time information not available\n");
    }
}

// Retrieve and print file information
void print_file_info(const char *filename)
{
    struct stat file_info;

    // Retrieve file information and populate the file_info structure
    if (lstat(filename, &file_info) == -1)
    {
        // errorno is the global integer variable set by certain library functions, defined in the errorno.h header
        // ENOENT is set, when the file does not exist
        if (errno == ENOENT)
        {
            fprintf(stderr, "File '%s' does not exist\n\n", filename);
        }
        else
        {
            // error message to the standard error stream
            perror("Error retrieving file information");
        }
        return;
    }

    printf("File: %s\n", filename);

    print_file_type(file_info.st_mode);
    print_user_group(file_info.st_uid, file_info.st_gid);
    print_access_permissions(file_info.st_mode);
    print_time("Last access time", file_info.st_atime);
    print_time("Last inode change time", file_info.st_ctime);
    print_time("Last modification time", file_info.st_mtime);

#ifdef __APPLE__
    // Print the creation time (for macOS)
    print_time("Creation time", file_info.st_birthtime);
#else
    // Print the creation time (for other systems)
    print_time("Creation time", file_info.st_ctime);
#endif

    printf("\n");
}

int main(int argc, char *argv[])
{
    // Check if file names are provided
    if (argc < 2)
    {
        printf("Please provide file names as arguments.\n");
        return 1;
    }

    // Print information for each specified file
    for (int i = 1; i < argc; i++)
    {
        printf("%d\n", i);
        print_file_info(argv[i]);
    }

    return 0;
}
