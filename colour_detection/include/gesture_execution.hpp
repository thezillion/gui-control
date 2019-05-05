#ifndef GESTURE_EXECUTION_TRACKING
#define GESTURE_EXECUTION_TRACKING

#include "fingertip.hpp"
#include <map>
#include <string>

class GestureExecutionModule{
    std::map<Gesture,std::string> saved_gestures;
    public:
        GestureExecutionModule();
        void execute(Gesture ges);
        void newExecute(std::deque<Hand>&);
};

#endif