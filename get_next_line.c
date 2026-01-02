#include "get_next_line.h"

static char *handle_eof(char *buffer, char **stash)
{
    free(buffer);
    if (*stash && (*stash)[0] != '\0')
    {
        char *line = *stash;
        *stash = NULL;
        return (line);
    }
    return (NULL);
}

static char *handle_error(char *buffer, char **stash)
{
    free(buffer);
    if (*stash)
    {
        free(*stash);
        *stash = NULL;
    }
    return (NULL);
}

static char *read_loop(int fd, char *buffer, char **stash)
{
    ssize_t bytes_read;

    while (1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == 0)
            return (handle_eof(buffer, stash));
        if (bytes_read == -1)
            return (handle_error(buffer, stash));
        buffer[bytes_read] = '\0';
        *stash = ft_strjoin(*stash, buffer);
        if (ft_strchr(*stash, '\n'))
        {
            free(buffer);
            return (ft_extract_line(stash));
        }
    }
}

char *get_next_line(int fd)
{
    static char *stash;
    char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (stash && ft_strchr(stash, '\n'))
        return (ft_extract_line(&stash));
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    return (read_loop(fd, buffer, &stash));
}
/**
Read return values:
    > 0 ==> Success
    0 ==> EOF
    -1 ==> Error
*/