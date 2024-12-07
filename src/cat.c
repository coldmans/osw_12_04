#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void my_cat(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    char buffer[1024];
    ssize_t n;
    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(STDOUT_FILENO, buffer, n) != n)
        {
            perror("write");
            close(fd);
            return;
        }
    }
    if (n == -1)
    {
        perror("read");
    }
    close(fd);
}