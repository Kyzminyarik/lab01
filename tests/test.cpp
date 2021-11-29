// Copyright 2020 Your Name <your_email>

#include "student.hpp"
const std::string &jsonPath =  JFile;

TEST(ParserTest, EmptyPath) {
  EXPECT_FALSE(jsonPath.empty());
}

TEST(ParserTest, FileExists) {
  std::ifstream file{jsonPath};
  EXPECT_FALSE(!file);
}

TEST(ParserTest, ItemsInArray) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  EXPECT_TRUE( data.at("items").is_array());
}

TEST(ParserTest, Meta){
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  students = read_file(data);
  size_t tmp1 = data.at("_meta").at("count");
  size_t tmp2 = students.size();
  EXPECT_EQ(tmp1, tmp2);
}


TEST(ParserTest, TypeGroup) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.group.type() == typeid(std::string)) {
      res = true;
    } else if (student.group.type() == typeid(size_t)) {
      res  = true;
    }
    EXPECT_TRUE( res);
  }
}

TEST(ParserTest, TypeAvg) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.avg.type() == typeid(std::nullptr_t)) {
      res = true;
    } else if (student.avg.type() == typeid(std::string)) {
      res = true;
    } else if (student.avg.type() == typeid(double)) {
      res = true;
    } else if(student.avg.type() == typeid(size_t)){
      res = true;
    }
    EXPECT_TRUE( res);
  }
}

TEST(ParserTest, TypeDebt) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.debt.type() == typeid(std::nullptr_t)) {
      res = true;
    } else if (student.debt.type() == typeid(std::string)) {
      res = true;
    } else if(student.debt.type() == typeid(std::vector<std::string>)){
      res = true;
    }
    EXPECT_TRUE( res);
  }
}

