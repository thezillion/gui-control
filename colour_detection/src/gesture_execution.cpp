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
    std::deque<Hand> gesture;

    gesture.push_back(Hand(10, 190));
    gesture.push_back(Hand(12, 190));
    gesture.push_back(Hand(14, 190));
    gesture.push_back(Hand(17, 190));
    gesture.push_back(Hand(21, 190));
    gesture.push_back(Hand(26, 194));
    gesture.push_back(Hand(29, 194));
    gesture.push_back(Hand(30, 190));
    gesture.push_back(Hand(33, 190));
    gesture.push_back(Hand(36, 190));
    gesture.push_back(Hand(40, 190));
    gesture.push_back(Hand(42, 190));
    gesture.push_back(Hand(45, 190));
    gesture.push_back(Hand(49, 190));
    gesture.push_back(Hand(53, 190));
    gesture.push_back(Hand(57, 190));
    gesture.push_back(Hand(59, 190));
    gesture.push_back(Hand(65, 190));
    gesture.push_back(Hand(71, 190));
    gesture.push_back(Hand(77, 190));
    gesture.push_back(Hand(83, 190));
    gesture.push_back(Hand(92, 190));
    gesture.push_back(Hand(96, 190));
    gesture.push_back(Hand(103, 190));
    gesture.push_back(Hand(110, 190));
    gesture.push_back(Hand(118, 190));
    gesture.push_back(Hand(121, 190));
    gesture.push_back(Hand(125, 190));
    gesture.push_back(Hand(133, 190));
    gesture.push_back(Hand(140, 190));
    gesture.push_back(Hand(149, 190));
    gesture.push_back(Hand(157, 190));
    gesture.push_back(Hand(161, 190));
    gesture.push_back(Hand(167, 190));
    gesture.push_back(Hand(173, 190));
    gesture.push_back(Hand(178, 190));
    gesture.push_back(Hand(182, 190));
    gesture.push_back(Hand(186, 190));
    gesture.push_back(Hand(189, 190));
    gesture.push_back(Hand(192, 190));
    gesture.push_back(Hand(193, 190));
    gesture.push_back(Hand(196, 190));
    gesture.push_back(Hand(199, 190));
    gesture.push_back(Hand(202, 190));
    gesture.push_back(Hand(205, 190));
    gesture.push_back(Hand(209, 190));
    gesture.push_back(Hand(211, 190));
    gesture.push_back(Hand(215, 190));
    gesture.push_back(Hand(220, 190));
    gesture.push_back(Hand(225, 190));
    gesture.push_back(Hand(230, 190));
    gesture.push_back(Hand(233, 190));
    gesture.push_back(Hand(238, 190));
    gesture.push_back(Hand(242, 190));
    gesture.push_back(Hand(247, 190));
    gesture.push_back(Hand(249, 190));
    gesture.push_back(Hand(254, 190));
    gesture.push_back(Hand(258, 190));
    gesture.push_back(Hand(262, 190));
    gesture.push_back(Hand(263, 190));
    gesture.push_back(Hand(267, 190));
    gesture.push_back(Hand(271, 190));
    gesture.push_back(Hand(276, 191));
    gesture.push_back(Hand(279, 193));
    gesture.push_back(Hand(281, 194));
    gesture.push_back(Hand(286, 195));
    gesture.push_back(Hand(289, 197));
    gesture.push_back(Hand(294, 200));
    gesture.push_back(Hand(297, 201));
    gesture.push_back(Hand(303, 203));
    gesture.push_back(Hand(305, 204));
    gesture.push_back(Hand(309, 205));
    gesture.push_back(Hand(314, 207));
    gesture.push_back(Hand(319, 208));
    gesture.push_back(Hand(323, 210));
    gesture.push_back(Hand(326, 211));
    gesture.push_back(Hand(329, 211));
    gesture.push_back(Hand(330, 212));
    gesture.push_back(Hand(333, 212));
    gesture.push_back(Hand(336, 212));
    gesture.push_back(Hand(339, 212));
    gesture.push_back(Hand(342, 212));
    gesture.push_back(Hand(345, 212));
    gesture.push_back(Hand(346, 212));
    gesture.push_back(Hand(349, 212));
    gesture.push_back(Hand(352, 212));
    gesture.push_back(Hand(355, 212));
    gesture.push_back(Hand(358, 212));
    gesture.push_back(Hand(359, 212));
    gesture.push_back(Hand(362, 212));
    gesture.push_back(Hand(364, 212));
    gesture.push_back(Hand(367, 212));
    gesture.push_back(Hand(370, 212));
    gesture.push_back(Hand(373, 212));
    gesture.push_back(Hand(376, 212));
    gesture.push_back(Hand(378, 212));
    gesture.push_back(Hand(383, 212));
    gesture.push_back(Hand(387, 212));
    gesture.push_back(Hand(391, 212));
    gesture.push_back(Hand(394, 212));
    gesture.push_back(Hand(399, 212));
    gesture.push_back(Hand(401, 212));
    gesture.push_back(Hand(403, 212));
    gesture.push_back(Hand(412, 212));
    gesture.push_back(Hand(418, 211));
    gesture.push_back(Hand(422, 210));
    gesture.push_back(Hand(426, 208));
    gesture.push_back(Hand(428, 208));
    gesture.push_back(Hand(431, 206));
    gesture.push_back(Hand(434, 205));
    gesture.push_back(Hand(437, 203));
    gesture.push_back(Hand(440, 202));
    gesture.push_back(Hand(441, 201));
    gesture.push_back(Hand(444, 200));
    gesture.push_back(Hand(446, 198));
    gesture.push_back(Hand(449, 197));
    gesture.push_back(Hand(452, 195));
    gesture.push_back(Hand(455, 194));
    gesture.push_back(Hand(456, 193));
    gesture.push_back(Hand(458, 191));
    gesture.push_back(Hand(459, 190));
    gesture.push_back(Hand(461, 189));
    gesture.push_back(Hand(463, 187));
    gesture.push_back(Hand(464, 186));
    gesture.push_back(Hand(465, 185));
    gesture.push_back(Hand(466, 183));
    gesture.push_back(Hand(468, 183));
    gesture.push_back(Hand(469, 182));
    gesture.push_back(Hand(471, 182));
    gesture.push_back(Hand(472, 182));
    gesture.push_back(Hand(473, 181));
    gesture.push_back(Hand(475, 181));
    gesture.push_back(Hand(476, 181));

    double result = TimeSeriesUtils::CalculateDynamicTimeWarpedDistance(gesture, hands);

    std::cout << "Distance value: " << result << "\n";

}