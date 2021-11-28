#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_
#include <any>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <gtest/gtest.h>

using nlohmann::json;

struct student_t {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};


void from_json(const json& j, student_t& s);

auto get_name(const json& j) -> std::string;

auto get_debt(const json& j) -> std::any;

auto get_avg(const json& j) -> std::any;

auto get_group(const json& j) -> std::any;


std::vector<student_t> read_file(json data);
void print(const std::vector<student_t>& students, std::ostream& output);
void print(const student_t& student, std::ostream& output);

#endif // INCLUDE_STUDENT_HPP_