#include "hash_search.hpp"

int main(int argc, char* argv[]) {
  HashSearch hashSearch;
  std::signal(SIGINT, hashSearch.interrupt_handler);
  if (argc > 1)
  {
    hashSearch.start_hash_search(static_cast<std::string>(argv[1]));
  } else {
    hashSearch.start_hash_search("0");
  }
}
