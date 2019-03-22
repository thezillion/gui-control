#include <fstream>
#include <iostream>
#include <regex>
#include "../include/gesture_execution.hpp"

std::regex num("[0-9]+");

GestureExecutionModule::GestureExecutionModule(){
    std::ifstream saved;
    saved.open("./saved_gestures.txt");
    std::string line;
    while(getline(saved, line)){
        std::smatch m;
        std::regex_search(line,m,num);
        int fingers;
        std::stringstream(m.str())>>fingers;
        line = m.suffix();
        std::regex_search(line,m,num);
        int direction;
        std::stringstream(m.str())>>direction;
        line = m.suffix();
        line = line.substr(2,line.length()-3);

        Gesture ges(fingers,direction);
        saved_gestures.insert(std::pair<Gesture,std::string>(ges,line));
    }
    for ( auto it = saved_gestures.begin(); it != saved_gestures.end(); it++ ){
        std::cout << it->first.fingers  // string (key)
                << ':'
                << it->first.direction   // string's value 
                << " => "
                << it->second
                << std::endl ;
    }
}

void GestureExecutionModule::execute(Gesture ges){
    auto t = saved_gestures.find(ges);
    if(t!=saved_gestures.end())
        system(t->second.c_str());
        // std::cout<<t->second<<"\n";
    else std::cout<<"Not found\n";
}