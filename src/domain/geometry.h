#pragma once
#include <cmath>

double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance;
}

//double abs(double a){
//    if(a < 0){
//        return -a;
//    }
//    return a;
//}

