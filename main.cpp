#include <toml.hpp> // that's all! now you can use it.
#include <iostream>
#include <map>
#include <fstream>
#define BREEZE_TOMLFILE "test.toml"



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

void create_env(toml::value data){

    const auto project_title=toml::find<std::string>(data, "title");
    const std::string command="python3 -m venv "+project_title;

}

void install_dependencies(toml::value data){
    
    const auto dependencies = toml::find<std::map<std::string, std::string>>(data, "dependencies");
    python3_cmd(dependencies);

}
void write_data(toml::value data){
    std::ofstream breezefile;
    breezefile.open("test.toml");

    breezefile<<std::setw(0)<<data<<std::endl;
    breezefile.close();

}
int main(int argc, char** argv)
{
     
    //const auto data=read_toml(BREEZE_TOMLFILE);
    //install_dependencies(data);
    //const auto title = toml::find<std::string>(data, "title");
    //std::cout << "the title is: " << title << std::endl;
    //std::cout<<"What is the title of your project? ";
    std::string command="Some_random_project";
    if(argc>=2){
        command=argv[1];
    }
    
    if(command=="init"){
        
        std::cout<<"Initializing "+command<<std::endl;
        
            std::string title=argv[2];
            toml::value d{
                {"python","3"},
                {"repository",""},
                {"author",""},
                {"title",title}
                };
            write_data(d);
        
        

    }
    else if(command=="fetch"){
        const auto data=read_toml(BREEZE_TOMLFILE);
        install_dependencies(data);

    }
    else if(command=="help"){
        std::cout<<"use \"breeze init <project_name>\" - To create a new project"<<std::endl;
        std::cout<<"Eg: \"breeze init hellow_breeze\""<<std::endl;
        std::cout<<"use \"breeze fetch\" - To fetch the dependencies"<<std::endl;
        
    }
    else{
        std::cout<<"use \"help\" command for how to use"<<std::endl;
    }
    
    

    //const toml::value d{{"pussy",{{"qux","hello pussy wussy"}}}};

    //std::cout << std::setw(0)<<d<< std::endl;
    
    return 0;
}