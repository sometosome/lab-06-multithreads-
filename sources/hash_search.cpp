// Copyright 2021 Your Name <your_email>

#include <hash_search.hpp>

std::vector<hash_item> HashSearch::hash_list;
bool HashSearch::flag;

void HashSearch::hash_counting() {
  unsigned int temp = abs(static_cast<int>(std::clock()));
  int hash_source = rand_r(&temp);
  std::string hash = picosha2::hash256_hex_string(std::to_string(hash_source));
  auto start = std::chrono::high_resolution_clock::now();
  while (flag) {
    if (hash.substr(60) == "0000") {
      auto end = std::chrono::high_resolution_clock::now();
      auto time =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      BOOST_LOG_TRIVIAL(info)
          << "Search Time: " << time.count() << ", Hash: " << hash
          << ", Data: " << std::hex << hash_source;
      hash_item item{hash, hash_source, time.count()};
      hash_list.push_back(item);
    }
    temp = abs(static_cast<int>(std::clock()));
    hash_source = rand_r(&temp);
    hash = picosha2::hash256_hex_string(std::to_string(hash_source));
  }
}

void HashSearch::json_filling() {
  nlohmann::json j;
  std::stringstream stream;
  std::ofstream o("../log.json");
  for (unsigned int i = 0; i < hash_list.size(); i++) {
    stream << std::hex << hash_list[i].hash_source;
    j = nlohmann::json{
        {"DATA", stream.str()},
        {"HASH", hash_list[i].hash_string},
        {"SEARCH TIME", std::to_string(hash_list[i].search_time)}};
    o << j << std::endl;
    stream.str("");
  }
}

void HashSearch::start_hash_search(std::string threadsNum) {
  size_t num = std::stoi(threadsNum);
  if ((num > std::thread::hardware_concurrency()) || (num == 0))
    num = std::thread::hardware_concurrency();
  for (size_t i = 0; i < num; i++) {
    std::thread thread(hash_counting);
    thread.join();
  }
}

void HashSearch::interrupt_handler(int interrupt) {
  json_filling();
  std::cout << interrupt << std::endl;
  flag = false;
}

auto example() -> void
{
  throw std::runtime_error("not implemented");
}
