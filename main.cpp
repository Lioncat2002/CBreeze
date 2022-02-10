#include <toml.hpp> // that's all! now you can use it.
#include <iostream>

int main()
{
    std::ifstream ifs("test.toml", std::ios::binary);
    assert(ifs.good());
    const auto data = toml::parse(ifs, /*optional -> */ "test.toml"); 
    
    const auto title = toml::find<std::string>(data, "title");
    std::cout << "the title is " << title << std::endl;
    return 0;
}