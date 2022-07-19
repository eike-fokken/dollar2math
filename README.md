### dollar2math
converts TeX style math ( \$ math \$ and \$\$aligned math\$\$) to amsmath style: \\(math\\)
and \\[aligned math\\] takes exactly one filename as input and outputs the
transformed file contents to std::out.

Written in C++17 (for the filesystem library).

Seems to work (tested only on my linux machine) with clang++ and g++ on the test.tex file provided.
No other compilers were tested.

This probably only works with utf-8 or ascii encoded files.
Differently encoded file contents may be corrupted
during transformation (of course the files themselves are not modified, as
output is only sent to std::cout).

So please check the output before blindly removing your old file.

## Installation
Run

```sh
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
```

followed by 

```sh
cmake --build build
```

and find the binary under `./build/dollar2math`.

## Usage
Call like

```sh
dollar2math oldstyle.tex
```

to get output in the terminal.

On UNIX shells call like

```sh
dollar2math oldstyle.tex > newstyle.tex
```
to get a file with the amsmath style.
