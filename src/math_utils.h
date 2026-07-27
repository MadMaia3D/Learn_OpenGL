#ifndef MATH_UTILS_H
#define MATH_UTILS_H


float remap(float value, float from_min, float from_max, float to_min, float to_max) {
    return (value - from_min) / (from_max - from_min) * (to_max - to_min) + to_min;
}


#endif