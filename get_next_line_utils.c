#include "get_next_line.h"

static size_t ft_strlen(const char *s)
{
    size_t len;

    if (!s)
        return (0);
    len = 0;
    while (s[len])
        len++;
    return (len);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    size_t len1;
    size_t len2;
    size_t i;

    if (!s1 && !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return (NULL);
    i = 0;
    len1 = 0;
    while (s1 && s1[len1])
        result[i++] = s1[len1++];
    len1 = 0;
    while (s2 && s2[len1])
        result[i++] = s2[len1++];
    result[i] = '\0';
    return (result);
}

static char *ft_strdup(const char *s)
{
    char *dup;
    char *start;
    int len;

    if (!s)
        return (NULL);
    len = 0;
    while (s[len])
        len++;
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    start = dup;
    while (*s)
    {
        *dup = *s;
        dup++;
        s++;
    }
    *dup = '\0';
    return (start);
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
