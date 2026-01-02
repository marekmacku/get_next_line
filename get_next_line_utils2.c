#include "get_next_line.h"

static char *ft_strcpy(char *dest, const char *src)
{
    char *start;

    start = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return (start);
}

static char *ft_strdup(const char *s)
{
    char *dup;
    const char *orig;
    int len;

    if (!s)
        return (NULL);
    orig = s;
    len = 0;
    while (*s++)
        len++;
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    ft_strcpy(dup, orig);
    return (dup);
}

static char *ft_substr(const char *s, int start, int len)
{
    char *result;
    int i;

    if (!s)
        return (NULL);
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (i < len)
    {
        result[i] = s[start + i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

char *ft_extract_line(char **stash)
{
    char *new_line_pos;
    char *line;
    char *remainder;
    int new_line_len;

    if (!stash || !*stash)
        return (NULL);
    new_line_pos = ft_strchr(*stash, '\n');
    if (!new_line_pos)
        return (NULL);
    new_line_len = new_line_pos - *stash + 1;
    line = ft_substr(*stash, 0, new_line_len);
    remainder = ft_strdup(new_line_pos + 1);
    free(*stash);
    *stash = remainder;
    return (line);
}

