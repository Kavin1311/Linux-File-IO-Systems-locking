#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>  // Include unistd.h for read and write
#include <stdio.h>   // Include stdio.h for perror

int main() {
    char block[1024];
    int in, out;
    ssize_t nread;  // Use ssize_t for read size

    // Open the source file for reading
    in = open("filecopy.c", O_RDONLY);
    if (in == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing
    out = open("file.out", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (out == -1) {
        perror("Error opening destination file");
        close(in);  // Close the input file before exiting
        exit(EXIT_FAILURE);
    }

    // Read from the source file and write to the destination file
    while ((nread = read(in, block, sizeof(block))) > 0) {
        if (write(out, block, nread) != nread) {
            perror("Error writing to destination file");
            close(in);
            close(out);
            exit(EXIT_FAILURE);
        }
    }

    // Check for read error
    if (nread == -1) {
        perror("Error reading from source file");
    }

    // Close the file descriptors
    close(in);
    close(out);

    exit(EXIT_SUCCESS);
}

