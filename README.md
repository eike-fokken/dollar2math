### dollar2math
converts TeX style math ($math$ and $$aligned math$$) to amsmath style: \(math\)
and \[aligned math\] takes exactly one filename as input and outputs the
transformed file contents to std::out.

Written in C++17 (for the filesystem library).

Seems to work (tested only on my linux machine) with clang++ and g++ on the test.tex file provided.
No other compilers were tested.

I'm not sure how this works with other file encodings, as the complete contents
of a file are read into a `std::string`.

So please check the output before blindly removing your old file.

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
