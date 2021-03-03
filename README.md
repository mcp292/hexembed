# hexembed

hexembed is a very small utility to help embed files in C or C++ programs in an easy, cross-platform way.

This fork implements `hexembed_fast.c` and records performance statistics ([Performance](#performance)).

## Usage

```
> gcc hexembed.c -o hexembed
> hexembed some_file.jpg > some_file.c
> cat some_file.c

/* Embedded file: some_file.jpg */
const int fsize = 1873;
const unsigned char *file = {
0x2f,0x2a,0x0a,0x20,0x2a,0x20,0x68,0x65,0x78,0x65,0x6d,0x62,0x65,0x64,0x20,0x2d,
0x20,0x61,0x20,0x73,0x69,0x6d,0x70,0x6c,0x65,0x20,0x75,0x74,0x69,0x6c,0x69,0x74,
0x79,0x20,0x74,0x6f,0x20,0x68,0x65,0x6c,0x70,0x20,0x65,0x6d,0x62,0x65,0x64,0x20,
0x66,0x69,0x6c,0x65,0x73,0x20,0x69,0x6e,0x20,0x43,0x20,0x70,0x72,0x6f,0x67,0x72,
    ...
};
```

Now you can simply `#include "some_file.c"` file in your program, and you have access to that file's data.


You can find more info and alternative methods here: https://codeplea.com/embedding-files-in-c-programs

## Performance

I set out to make a faster `hexembed`. Turns out what I did was slower. What I learned is it's 
faster to read into memory than to make continous file calls. 

```txt
Time for one file (small):
hexembed     : 5.347 milliseconds
hexembed_fast: 5.270 milliseconds

Time for one file (large):
hexembed     : 1079.141 milliseconds
hexembed_fast: 1122.878 milliseconds

Average time per file (small):
hexembed     : 4.215 milliseconds
hexembed_fast: 4.402 milliseconds

Average time per file (large):
hexembed     : 1078.356 milliseconds
hexembed_fast: 1143.385 milliseconds
```

The popular `xxd` program might make the same mistake I did. I'm basing this off the fact 
that they print the size at the end. [TODO: confirm]

Benchmark on your own system by running [`benchmark.py`](test/benchmark.py).
