# StringFinder - example cross-platform project #

This project provides ability to search string in files for Windows and Linux OS, writed with c++11.

### Usage help ###


```
-p      - Path
-m      - File mask
-i      - File with search string
-s      - Search string
-o      - Output file (write to console otherwise)
-a      - Extended output (with lines and line numbers)
-d      - Show stat info (time and file numbers)
-h      - Show this help
-b      - Read files with binary flag
-c      - Chunk count (0 - read line by line, otherwise - read block by block) incompatible with -a flag
```

*Base Chunk(Block) size is search string size*

Example commands:

`StringFinder.exe -p ..\ -m "*.cpp" -s "unsigned" -d -a`

`StringFinder.exe -p ..\ -m "*.*" -i "String.txt" -d -b -c 100 -o "Result.txt"`

### Windows compile ###

To compile on windows, open *StringFinder.sln* and press build

### Linux compile ###


```
cd StringFinder
make
```
