*This project has been created as part of the 42 curriculum by mmacku.*

# get_next_line

## Description

**get_next_line** is a function that reads a file descriptor line by line. This project is part of the 42 curriculum and focuses on file I/O operations, memory management, and static variables in C.

### Goal

The primary goal of this project is to implement a function that can read a text file line by line, regardless of the buffer size used for reading. The function must handle edge cases such as:
- Files with or without newline characters at the end
- Empty files
- Very long lines (longer than the buffer size)
- Error handling

### Overview

The implementation uses a static variable to maintain a "stash" of leftover data between function calls. This allows the function to read data in chunks (defined by `BUFFER_SIZE`) while still returning complete lines. When a newline character is found, the function extracts the line up to and including the newline, and stores any remaining data in the stash for the next call.

## Instructions

### Compilation

To compile the project, use `cc` with the following flags:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> get_next_line.c get_next_line_utils.c -o get_next_line
```

Replace `<size>` with your desired buffer size (e.g., `42`, `1`, `1000`).

**Example:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

### Usage

The `get_next_line` function can be used in your own programs:

```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```
### Buffer Size

The `BUFFER_SIZE` is defined at compile time using the `-D` flag. If not specified, it defaults to `42` as defined in `get_next_line.h`. You can compile with different buffer sizes:

```bash
# Compile with buffer size of 1
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o get_next_line

# Compile with buffer size of 1000
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c -o get_next_line
```

## Algorithm Explanation and Justification

### Algorithm Overview

The `get_next_line` function implements a **stash-based line reading algorithm** that efficiently handles reading lines of arbitrary length using a fixed buffer size.

### How It Works

1. **Static Stash**: A static variable `stash` is used to store leftover data between function calls. This allows the function to maintain state across multiple invocations.

2. **Initial Check**: On each call, the function first checks if the stash already contains a complete line (indicated by the presence of a newline character). If so, it immediately extracts and returns that line.

3. **Reading Loop**: If no complete line is found in the stash, the function enters a reading loop:
   - Allocates a buffer of size `BUFFER_SIZE + 1`
   - Reads `BUFFER_SIZE` bytes from the file descriptor
   - Handles EOF (returns remaining stash or NULL) and errors (returns NULL)
   - Joins the newly read data with the existing stash using `ft_strjoin`
   - Checks if a newline character is present in the combined data

4. **Line Extraction**: When a newline is found:
   - `ft_extract_line` extracts the line up to and including the newline
   - The remainder (data after the newline) is stored back in the stash
   - The extracted line is returned

5. **Memory Management**: The function properly frees all allocated memory, including the buffer and old stash data when it's replaced.

### Justification

**Why a static stash?**
- The static variable allows the function to maintain state between calls without requiring the caller to manage it
- This provides a clean API where the caller simply calls `get_next_line(fd)` repeatedly
- The stash efficiently handles cases where a line spans multiple buffer reads

**Why read in chunks?**
- Reading the entire file at once would be memory-inefficient for large files
- The chunk-based approach allows the function to work with files of any size
- It's more efficient than reading character by character

**Why join stash with buffer?**
- When a line is longer than `BUFFER_SIZE`, it requires multiple reads
- By joining the stash (which may contain partial line data) with the new buffer, we can detect when a complete line is formed
- This approach handles lines of any length gracefully

**Error Handling:**
- The function checks for invalid file descriptors and buffer sizes
- It properly handles read errors and EOF conditions
- All allocated memory is freed in error cases to prevent leaks

## Resources

### Classic References

- **Read function**: [Input-output system calls](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/) 
- **Static Variables in C**: [GeeksforGeeks - Static Variables](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- **Static variable wiki**: [Static variable](https://en.wikipedia.org/wiki/Static_variable)

### AI Usage

AI was used in the following parts of this project:

- **README.md Creation**: AI was used to help with the README structure and to better format my words.
- **Code Review**: AI-assisted in reviewing the implementation for potential memory leaks and edge case handling.
- **Understanding concepts** - AI was used to understand the concepts needed for the project.

