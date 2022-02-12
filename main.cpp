#include <toml.hpp> // that's all! now you can use it.
#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>
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

void create_env(std::string title){

    std::filesystem::create_directories("./"+title+"/");
    std::string command="python3 -m venv "+title+"/"+title;
    const char* b=command.c_str();
    system(b);
    
}

void install_dependencies(toml::value data){
    
    const auto dependencies = toml::find<std::map<std::string, std::string>>(data, "dependencies");
    const auto& config=toml::find(data, "config");
    std::string title=toml::find<std::string>(config,"title");

    std::cout<<title<<std::endl;
    
    python3_cmd(dependencies);

}
void write_data(toml::value data,std::string dir_name){
    std::ofstream breezefile;
    //std::cout<<data["title"]<<std::endl;
    std::filesystem::create_directories("./"+dir_name+"/");
    breezefile.open(dir_name+"/"+BREEZE_TOMLFILE);

    breezefile<<std::setw(0)<<data<<std::endl;
    breezefile<<std::setw(0)<<"[dependencies]"<<std::endl;
    breezefile.close();

}

int main(int argc, char** argv)
{
     
    
    std::string command="Some_random_project";
   
    
    if(argc>=2){
        command=argv[1];
    }
    else{
        std::cout<<"Error";
    }
    
    if(command=="init"){
        
        std::cout<<"Initializing project"<<std::endl;
        
            std::string title=argv[2];
            toml::value d
            {
               {
                   "config",{
                    {"python","3"},
                    {"repository",""},
                    {"author",""},
                    {"title",title}
                },
                
               } 
                
                };
            write_data(d,title);
        create_env(title);
        std::cout<<"Environment created and activated successfully"<<std::endl;
        

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
    
    return 0;
}