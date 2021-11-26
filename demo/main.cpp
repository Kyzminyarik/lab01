#include <student.hpp>


int main() {
  const std::string &jsonPath =
      "/home/kuzminyarik/students.json";
  if (jsonPath.empty()) throw std::runtime_error{"Invalid path"};

  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"Unable to open json: " + jsonPath};
  }

  json data;
  file >> data;

  if (data["_meta"]["count"] != data["items"].size()){
    throw std::runtime_error{"meta is incorrect"};
  }

  if (!data["items"].is_array()){
    throw std::runtime_error{"items is not array"};
  }

  std::vector <student_t> students;

  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  print(students, std::cout);
  return 0;
}