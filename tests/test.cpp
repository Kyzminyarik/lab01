// Copyright 2020 Your Name <your_email>

#include "student.hpp"

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(ExistFile, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  bool val = file.fail();
  EXPECT_EQ(val, false);
}

TEST(Meta, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  size_t val1 = data.at("_meta").at("count");
  size_t val2 = students.size();
  EXPECT_EQ(val1, val2);
}


TEST(Table, Test){
  std::string tmp = R"(| name          | group     | avg   | debt      |
|---------------|-----------|-------|-----------|
| Ivanov Petr	| 1			| 4.25	| null		|
|---------------|-----------|-------|-----------|
| Sidorov Ivan	| 31 group	| 4		| C++		|
|---------------|-----------|-------|-----------|
| Pertov Nikita	| IU8-31	| 3.33	| 3 items	|
|---------------|-----------|-------|-----------|
)";

  std::string jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  std::stringstream os;
  print(students, os);
  EXPECT_EQ(tmp, os.str());
}

TEST(isArray, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  bool val1 = data["items"].is_array();
  EXPECT_EQ(val1, true);
}

TEST(ValidInfo, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  EXPECT_EQ(std::any_cast<std::string>(students[0].name),"Ivanov Petr");
  EXPECT_EQ(std::any_cast<std::string>(students[0].group),"1");
  EXPECT_EQ(std::any_cast<std::string>(students[0].avg),"4.25");
  EXPECT_EQ(std::any_cast<std::nullptr_t>(students[0].debt), nullptr);

  EXPECT_EQ(std::any_cast<std::string>(students[1].name),"Sidorov Ivan");
  EXPECT_EQ(std::any_cast<std::size_t>(students[1].group),31);
  EXPECT_EQ(std::any_cast<std::size_t>(students[1].avg),4);
  EXPECT_EQ(std::any_cast<std::string>(students[1].debt), "C++");

  EXPECT_EQ(std::any_cast<std::string>(students[2].name),"Pertov Nikita");
  EXPECT_EQ(std::any_cast<std::string>(students[2].group),"IU8-31");
  EXPECT_EQ(std::any_cast<std::double_t>(students[2].avg),3.33);
  std::vector<std::string> tmp;
  tmp.push_back("C++");
  tmp.push_back("Linux");
  tmp.push_back("Network");
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(students[2].debt), tmp);
}

TEST(DebtType, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  bool debt_flag = false;
  for (auto const& student : students) {
    if (student.debt.type() == typeid(std::nullptr_t)){
      debt_flag = true;
    } else if (student.debt.type() == typeid(std::string)){
      debt_flag = true;
    } else if (student.debt.type() == typeid(std::vector<std::string>)){
      debt_flag = true;
    }
  }
  EXPECT_EQ(debt_flag, true);
}

TEST(GroupType, Test){
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  bool flag = false;
  for (auto const& student : students) {
    if (student.group.type() == typeid(std::size_t)){
      flag = true;
    } else if (student.group.type() == typeid(std::string)){
      flag = true;
    }
  }
  EXPECT_EQ(flag, true);
}

TEST(AvgType, Test) {
  std::string jsonPath;
  jsonPath = PATH_TO_JSON;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<Student> students;
  students = read_file(data);
  bool flag = false;
  for (auto const &student : students) {
    if (student.avg.type() == typeid(std::size_t)) {
      flag = true;
    } else if (student.avg.type() == typeid(std::string)) {
      flag = true;
    } else if (student.avg.type() == typeid(std::double_t)) {
      flag = true;
    }
  }
  EXPECT_EQ(flag, true);
}