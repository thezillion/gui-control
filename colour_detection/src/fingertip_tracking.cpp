#include <string>
#include <ctime>
#include <chrono>
#include "../include/fingertip_tracking.hpp"
#include "../include/gesture_execution.hpp"

void FingertipTrackingModule::track(Hand a){
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    int dis, dir;
    if (count > 0 && a.fingers == 0) {
        flush();
    } else if (count == 0) {
        buffer.push_back(a);
        count++;
    } else {
        // std::cout<<a.fingers<<"\n";
        Hand last = buffer.back();
        last.distanceAndDirectionFrom(a,dis,dir);
        if (last.fingers != a.fingers) {
            if (jitter.size() <= 2) {
                jitter.push_back(a);
            } else{
                std::cout << ctime(&timenow) << "Too much jitter in finger count. Buffer flushed!\n";
                flush();
            }
            flush();
        } else if (dis < DISTANCE_THRESHOLD) {
            std::cout << ctime(&timenow) << "Too slow. Buffer flushed!\n";
            flush();
        } else {
            // if (direction != 0 && direction != dir) {
            //     if (jitter.size() <= 2) {
            //         jitter.push_back(a);
            //     } else{
            //         std::cout << ctime(&timenow) << "Too much jitter in direction. Buffer flushed!\n";
            //         flush();
            //     }
            // } else {
                if (count > BUFFER_SIZE) {
                    last = buffer.back();
                    Gesture ges(last.fingers, direction);
                    gm.execute(ges);
                    // std::cout << buffer[0] << " " << buffer[10] << "\n";
                    gm.newExecute(buffer);
                    Mat pic = cv::Mat::zeros(125,250,CV_8U);
                    std::string str = std::to_string(buffer.back().fingers) + std::string(" Finger ");
                    std::string str1;
                    switch (direction) {
                        case 1: str1 = "Left Swipe";
                                break;
                        case 2: str1 = "Right Swipe";
                                break;
                        case 3: str1 = "Up Swipe";
                                break;
                        case 4: str1 = "Down Swipe";
                                break;                        
                    }
                    str += str1;
                    putText(pic, str,cv::Point(25,25*(pos+1)), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255),1,8,false);
                    pos = (pos + 1)%3;
                    imshow( "Stats", pic);
                    flush();
                } else {
                    buffer.push_back(a);
                    count++;
                    direction = dir;
                }
            // }
        }
    }

    Mat canvas = Mat::zeros(size, CV_8UC3);
    // circle(canvas, current, 5, Scalar(255, 255, 255), -1);
    


    for (int i = 0; i<count-1; i++) {
        line(canvas, buffer[i], buffer[i+1], Scalar(255, 255, 255), 2);
    }
    imshow( "Hand", canvas);
    // imshow( "Stats", pic);
}

void FingertipTrackingModule::flush(){
    buffer.clear();
    count = 0;
    jitter.clear();
    direction = 0;
}