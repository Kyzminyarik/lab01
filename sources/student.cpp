// Copyright 2020 Your Name <your_email>

#include <student.hpp>


void from_json(const json& j, student_t& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

auto get_name(const json& j) -> std::string {
  return j.get<std::string>();
}//норм

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string> >();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}

// парсер
void print(const student_t& student, std::ostream& ostream){
  if (student.name.empty()){
    ostream << "| 0\t|";
  } else {
    ostream << "| " << student.name << "\t|";
  }

  if (student.group.type() == typeid(std::nullptr_t)){
    ostream << "null|";
  } else if (student.group.type() == typeid(std::string)){
    if (std::any_cast<std::string>(student.group).length() == 1){
      ostream << " " << std::any_cast<std::string>(student.group) << "\t\t\t|";
    } else {
      ostream << " " << std::any_cast<std::string>(student.group) << "\t|";
    }
  } else {
    ostream << " " << std::any_cast<std::size_t>(student.group)
       << " group\t|";
  }

  if (student.avg.type() == typeid(std::nullptr_t)){
    ostream << "null\t|";
  } else if (student.avg.type() == typeid(std::string)){
    ostream << " " << std::any_cast<std::string>(student.avg) << "\t|";
  } else if (student.avg.type() == typeid(std::double_t)){
    ostream << " " << std::any_cast<std::double_t>(student.avg) << "\t|";
  } else {
    ostream << " " << std::any_cast<std::size_t>(student.avg) << "\t\t|";
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    ostream << " null\t\t|" << std::endl;
  } else if (student.debt.type() == typeid(std::string)) {
    ostream << " " << std::any_cast<std::string>(student.debt)
       << "\t\t|" <<  std::endl;
  } else {
    ostream
        << " " << std::any_cast<std::vector<std::string>>(student.debt).size()
        << " items\t|" << std::endl;
  }
}

void print(const std::vector<student_t>& students, std::ostream& ostream) {
  ostream << "| name          | group     | avg   | debt      |\n";
  ostream << "|---------------|-----------|-------|-----------|\n";
  for (auto const& student : students) {
    print(student, ostream);
    ostream << "|---------------|-----------|-------|-----------|\n";
  }
}

std::vector<student_t> read_file(json data) {
  std::vector<student_t> students;
  for (auto const &item : data.at("items")) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }
  return students;
}