get_next_line
An exercise in text files and static variables

This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming: static variables.

Completed goals:
- Function get_next_line reads one line from a file descriptor and returns it.
- Arbitrary nonzero buffer size
- Free of memory leaks
- Can read from stdin/redirection

To be done:
- Compact static variables into one
- Allow for more file descriptors to be used simultaneously.

Function descriptions:

get_next_line:
Finds the next line in a file descriptor minus the terminating newline, returning a string with said line.
Parameters:
- fd: File descriptor to read from
- line: Pointer to a string to write the output to.
Return value: 1 if line is read, 0 if end of file is reached, -1 on error.

find_next_line:
Finds the next newline character in a string and returns the index.
Parameters:
- buf: String (buffer) to search.
- i: Starting index
- c: Pointer to an integer giving the maximum number of places to read, returning the excess.
Return value: The index of the first newline after 'i'.

copy_str:
Copies a string from one char array to another, always null-terminating.
Parameters:
- dst: Pointer to the destination array to copy into.
- src: The source array to copy from.
- start: Index of 'dst' to start copying to.
- len: Number of characters to copy, minus null.
Return value: None

refresh:
Empties a string and turns it into a single null character.
Parameters:
- line: Pointer to the string to clear.
- first: Determines if the string only has to be allocated or also freed (all consecutive times).
- ind: Index to be initialized.
Return value: 1 if allocation was successful, 0 if not.

append:
Attaches one string to the end of another, expanding as much size as needed to still null-terminate the destination string.
Parameters:
- line: Destination string to append to.
- buf: Source string to append.
- start: Index of the source to start copying from.
- end: Index of the source where copying is stopped.
Return value: 1 if allocation was successful, 0 if not.
