#include <sstream>
#include <fstream>
#include <string>
#include <regex>

std::string delete_comments(const std::string& data, std::regex pattern);

int main(int argc, const char* argv[])
{
    std::ifstream file_in("test.txt");
    std::ofstream file_out("output.txt");

    std::string str(std::istreambuf_iterator< char >(file_in), (std::istreambuf_iterator< char >()));

    std::regex comment_pattern(R"((/\*((.|[\r\n])*?)\*/)|(//.{0,}))");

    file_out << delete_comments(str, comment_pattern);


    return 0;
}

// Remove comments from code not touching them in literals
std::string delete_comments(const std::string& data, std::regex pattern)
{
    std::stringstream ss;

    std::regex literal_pattern(R"([\"|\']((.|[\r\n])*?)[^\\][\"|\'])");

    std::smatch sm;

    std::regex_search(std::string::const_iterator(data.begin()), std::string::const_iterator(data.end()), sm, literal_pattern);

    std::string k = (sm.empty() ? data : sm.prefix().str());
    std::regex_replace(std::ostreambuf_iterator< char >(ss), k.begin(), k.end(), pattern, " ");

    ss << sm[0];

    if (!sm.empty())
    {
        ss << delete_comments(sm.suffix().str(), pattern);
    }

    return ss.str();
}