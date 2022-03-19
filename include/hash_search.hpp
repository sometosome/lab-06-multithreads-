// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_HASH_SEARCH_HPP_
#define INCLUDE_HASH_SEARCH_HPP_

#include <../include/picosha2.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <csignal>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

struct hash_item {
  std::string hash_string;
  int hash_source;
  std::chrono::duration<int64_t, std::ratio<1, 1000>>::rep search_time;
};

class HashSearch {
  static bool flag;
  static std::vector<hash_item> hash_list;

 public:
  HashSearch() {
    flag = true;
  }
  static void hash_counting();
  static void interrupt_handler(int interrupt);
  static void start_hash_search(std::string threadsNum);
  static void json_filling();
};

auto example() -> void;

#endif // INCLUDE_HASH_SEARCH_HPP_
