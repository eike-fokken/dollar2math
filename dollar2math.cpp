#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::u8string::iterator find_next_real_doubledollar(
    std::u8string::iterator it, std::u8string &filecontents) {
  std::u8string::iterator ending_it = it;
  while (ending_it != filecontents.end()) {
    ending_it = std::find(ending_it, filecontents.end(), '$');

    if (ending_it == filecontents.end()) {
      break;
    }

    if (*(ending_it - 1) == '\\') {
      ++ending_it;
      continue;
    }
    if ((ending_it + 1 == filecontents.end()) or (*(ending_it + 1) != '$')) {
      ++ending_it;
      continue;
    }
    if (ending_it != filecontents.end()) {
      break;
    }
  }
  return ending_it;
}

static std::u8string::iterator
find_next_real_dollar(std::u8string::iterator it, std::u8string &filecontents) {
  auto ending_it = it;
  while (ending_it != filecontents.end()) {
    ending_it = std::find(ending_it, filecontents.end(), '$');
    if (ending_it == filecontents.begin()) {
      break;
    }
    if (*(ending_it - 1) == '\\') {
      ++ending_it;
      continue;
    }
    if (ending_it != filecontents.end()) {
      break;
    }
  }
  return ending_it;
}

namespace fs = std::filesystem;
int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "You must provide a latex file" << std::endl;
    return 1;
  }

  fs::path file = argv[1];

  std::u8string filecontents;
  {
    std::basic_ifstream<char8_t> t(file);
    std::basic_stringstream<char8_t> buffer;
    buffer << t.rdbuf();
    filecontents = buffer.str();
  }

  {
    auto it = filecontents.begin();
    while (it != filecontents.end()) {
      it = find_next_real_doubledollar(it, filecontents);
      if (it == filecontents.end()) {
        break;
      }
      auto ending_it = find_next_real_doubledollar(it + 2, filecontents);
      if (ending_it == filecontents.end()) {
        std::cout << "There was an unmatched $$ in the file." << std::endl;
        return 1;
      }

      // std::cout << filecontents << std::endl;
      *it = '\\';
      *(it + 1) = '[';
      *ending_it = '\\';
      *(ending_it + 1) = ']';
      it = ending_it + 1;
      // std::cout << "After:\n" << filecontents << std::endl;
    }
  }
  {
    auto it = filecontents.begin();
    while (it != filecontents.end()) {
      it = find_next_real_dollar(it, filecontents);
      if (it == filecontents.end()) {
        break;
      }
      auto ending_it = find_next_real_dollar(it + 1, filecontents);
      if (ending_it == filecontents.end()) {
        std::cout << "There was an unmatched $ in the file." << std::endl;
        return 1;
      }

      // std::cout << filecontents << std::endl;
      // filecontents.insert(ending_it + 1, endmath.begin(), endmath.end());
      // filecontents.erase(ending_it);
      *ending_it = '\\';
      filecontents.insert(ending_it + 1, ')');
      // std::cout << "First:\n" << filecontents << std::endl;
      *it = '\\';
      filecontents.insert(it + 1, '(');
      // it = filecontents.begin() + ending_pos + 2;
      it = ending_it + 1;
      // std::cout << "After:\n" << filecontents << std::endl;
    }
  }

  std::basic_ofstream<char8_t> s("output.tex");
  s << filecontents;
}
