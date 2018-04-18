# StringFinder - example cross-platform project #

This project provides ability to search string in files for Windows and Linux OS, writed with c++11.

### Usage help ###


```
-p      - Path
-m      - File mask
-p      - Path
-i      - File with search string
-s      - Search string
-o      - Output file (write to console otherwise)
-a      - Extended output (with lines and line numbers)
-d      - Show stat info (time and file numbers)
-h      - Show this help
```

Example command `StringFinder.exe -p ..\ -m "*.cpp" -s "unsigned" -d -a`

### Windows compile ###

To commpile on windows, open *StringFinder.sln* and press build

### Linux compile ###


```
cd StringFinder
make
```