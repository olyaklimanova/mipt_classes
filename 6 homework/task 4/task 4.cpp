#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <filesystem>
#include "json.hpp"

using nlohmann::json;

struct Exam_result
{
    std::string name;
    std::string lastname;
    std::string group;
    std::map< std::string, int > marks;

    friend std::istream& operator>>(std::istream& stream, Exam_result& student)
    {
        if (stream)
        {
            stream >> student.name >> student.lastname >> student.group;

            for (auto i = 0U; stream.peek() != '\n' && stream; ++i)
            {
                std::string subject;
                stream >> subject >> student.marks[subject];
            }
        }


        return stream;
    }
};


int main(int argc, const char* argv[])
{
    std::vector< Exam_result > students(2);

    std::cin >> students[0] >> students[1];

    std::vector< json > j(2);
    for (auto i = 0U; i < students.size(); ++i)
    {
        j[i]["name"] = students[i].name;
        j[i]["last name"] = students[i].lastname;
        j[i]["group"] = students[i].group;
        for (const auto& c : students[i].marks)
            j[i]["Marks"][c.first] = c.second;
    }

    auto path = std::filesystem::current_path();

    std::filesystem::create_directory(path /= "data");

    for (auto i = 0U; i < j.size(); ++i)
    {
        std::fstream file_out((path / (students[i].name + ".json")).string(), std::ios::out);
        file_out << j[i].dump(4) << std::endl;
        file_out.close();
    }
    
    return 0;
}