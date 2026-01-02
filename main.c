#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int line_count;

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        printf("Or: %s <filename> | cat (to read from stdin)\n", argv[0]);
        return (1);
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Could not open file '%s'\n", argv[1]);
        return (1);
    }
    
    printf("=== Reading file: %s ===\n\n", argv[1]);
    line_count = 0;
    
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        line_count++;
        printf("[Line %d]: %s", line_count, line);
        free(line);
    }
    
    close(fd);
    printf("\n=== End of file (Total lines: %d) ===\n", line_count);
    
    return (0);
}

