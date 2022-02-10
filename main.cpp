#include <toml.hpp> // that's all! now you can use it.
#include <iostream>
#include <map>

#define BREEZE_TOMLFILE "breeze.toml"

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

    const auto tab = toml::find<std::map<std::string, std::string>>(data, "tab");

    for(const auto& elem : tab)
    {
        std::cout<<"Installing: "+elem.first+"=="+elem.second<<std::endl;
        const std::string command="pip3 install "+elem.first+"=="+elem.second;
        const char* b=command.c_str();
        system(b);
    }
    
    return 0;
}