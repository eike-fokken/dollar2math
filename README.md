### dollar2math
converts TeX style math ($math$ and $$aligned math$$) to amsmath style: \(math\)
and \[aligned math\] takes exactly one filename as input and outputs the
transformed file contents to std::out.

Written in C++20.

Seems to work only with clang and libc++, probably because the internal encoding
of std::string in libc++ is different from that in libstdc++.
Automatically chooses libc++, if clang is the compiler.

Doesn't work with gnu.

Almost surely doesn't work with MSVC++ (not tested) or any other compiler (not
tested).
