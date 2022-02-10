#include <toml.hpp> // that's all! now you can use it.
#include <iostream>
#include <map>

#define BREEZE_TOMLFILE "breeze.toml"



void python3_cmd(std::map<std::string, std::string> dependencies){

    for(const auto& deps : dependencies)
    {
        std::cout<<"Installing: "+deps.first+"=="+deps.second<<std::endl;

        const std::string command="pip3 install "+deps.first+"=="+deps.second;

        const char* b=command.c_str();

        system(b);
    }

}

auto read_toml(std::string filename){
    std::ifstream ifs(filename, std::ios::binary);
    assert(ifs.good());
    const auto data = toml::parse(ifs, filename);
    return data;
}

int main()
{
     
    const auto data=read_toml(BREEZE_TOMLFILE);
    const auto title = toml::find<std::string>(data, "title");
    std::cout << "the title is: " << title << std::endl;

    const auto dependencies = toml::find<std::map<std::string, std::string>>(data, "dependencies");

    python3_cmd(dependencies);
    
    return 0;
}