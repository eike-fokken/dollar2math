cmake_minimum_required(VERSION 3.0)
project(test C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


## for debug builds use the debug configuration of the standard libraries:
## Unfortunately MacOS doesn't ship the debug versions of standard types,
## therefore we forego the debug macro for Apple's Clang.

if(NOT (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang"))
  add_compile_definitions("$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG;_LIBCPP_DEBUG>")
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("-stdlib=libc++")
  add_link_options("-stdlib=libc++")
  message(STATUS "Will compile with libc++.")
endif()




set(my_debug_options -O0 -Werror -Wconversion -pedantic-errors -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wundef
  -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wunused -Wno-error=unused-parameter -Wno-error=unused -Wno-error=unused-variable -Wno-error=unused-value -Wdelete-non-virtual-dtor -Wno-error=undef -Wsuggest-override)

set(debug_clang_options "-Wunreachable-code;-fcolor-diagnostics;-Wno-error=unused-private-field;-Wmissing-prototypes;-Wdocumentation")
set(debug_gcc_options "-fdiagnostics-color;-Wno-error=strict-overflow;-Wno-error=unused-but-set-variable")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<CONFIG:DEBUG>:${my_debug_options}>")
  add_compile_options("$<$<CONFIG:DEBUG>:${debug_clang_options}>")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options("$<$<CONFIG:DEBUG>:${my_debug_options}>")
  add_compile_options("$<$<CONFIG:DEBUG>:${debug_gcc_options}>")
endif()


add_executable(dollar2math dollar2math.cpp)
target_include_directories(dollar2math PUBLIC include)
