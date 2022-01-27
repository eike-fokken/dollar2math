#include <algorithm>
#include <cassert>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

static std::string::iterator find_next_real_doubledollar(
    std::string::iterator it, std::string &filecontents) {
  std::string::iterator ending_it = it;
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

static std::string::iterator
find_next_real_dollar(std::string::iterator it, std::string &filecontents) {
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

  std::string filecontents;
  {
    // std::basic_ifstream<char8_t> t(file);
    // std::basic_stringstream<char8_t> buffer;
    std::ifstream t(file);
    std::stringstream buffer;
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
      auto ending_pos
          = static_cast<size_t>(std::distance(filecontents.begin(), ending_it));
      *it = '\\';
      auto starting_pos
          = static_cast<size_t>(std::distance(filecontents.begin(), it));
      assert(*ending_it == filecontents[ending_pos]);
      assert(*it == filecontents[starting_pos]);

      filecontents.insert(ending_pos + 1, ")");
      filecontents.insert(starting_pos + 1, "(");

      it = filecontents.begin();
      std::advance(it, ending_pos);
      it = it + 3;
      assert(*(it - 1) == *")");
      assert(*(it - 2) == '\\');
    }
  }

  std::cout << filecontents << std::endl;
}
