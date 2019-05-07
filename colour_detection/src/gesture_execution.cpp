#include <fstream>
#include <iostream>
#include <regex>
#include "../include/gesture_execution.hpp"
#include "../include/dtw_distance.hpp"

std::regex num("[0-9]+");


GestureExecutionModule::GestureExecutionModule(){
    std::ifstream saved;
    saved.open("./saved_gestures.txt");
    std::string line;
    while(getline(saved, line)){
        std::smatch m;
        std::regex_search(line, m, num);
        int fingers;
        std::stringstream(m.str()) >> fingers;
        line = m.suffix();
        std::regex_search(line, m, num);
        int direction;
        std::stringstream(m.str()) >> direction;
        line = m.suffix();
        line = line.substr(2, line.length()-3);

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
    if(t != saved_gestures.end())
        system(t->second.c_str());
        // std::cout<<t->second<<"\n";
    else std::cout<<"Not found\n";
}

void GestureExecutionModule::newExecute(std::deque<Hand>& hands) {

    std::deque<Hand> gesture_rightswipe;

    gesture_rightswipe.push_back(Hand(112, 241));
    gesture_rightswipe.push_back(Hand(112, 241));
    gesture_rightswipe.push_back(Hand(112, 241));
    gesture_rightswipe.push_back(Hand(111, 241));
    gesture_rightswipe.push_back(Hand(113, 240));
    gesture_rightswipe.push_back(Hand(120, 240));
    gesture_rightswipe.push_back(Hand(136, 241));
    gesture_rightswipe.push_back(Hand(150, 244));
    gesture_rightswipe.push_back(Hand(204, 251));
    gesture_rightswipe.push_back(Hand(240, 253));
    gesture_rightswipe.push_back(Hand(281, 253));
    gesture_rightswipe.push_back(Hand(364, 254));
    gesture_rightswipe.push_back(Hand(391, 252));
    gesture_rightswipe.push_back(Hand(430, 253));
    gesture_rightswipe.push_back(Hand(452, 255));
    gesture_rightswipe.push_back(Hand(501, 239));
    gesture_rightswipe.push_back(Hand(522, 247));
    gesture_rightswipe.push_back(Hand(542, 296));
    gesture_rightswipe.push_back(Hand(565, 306));

    double result = TimeSeriesUtils::CalculateDynamicTimeWarpedDistance(gesture_rightswipe, hands);

    std::cout << "Distance value: " << result << "\n";

    // if (result < 30) {
        // std::cout << "DTW match: Swipe\n";
    int distance, direction_h, direction_v;
    (hands.back()).distanceAndDirectionFrom(hands.front(), distance, direction_v, direction_h);
    std::cout << "Direction: " << direction_v << " " << direction_h << "\n";
    // }

}