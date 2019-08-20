#pragma once


int Mod10(const int num) {
    return num - (num / 10 * 10);
}


int Mod10_Float(const int num) {
    //Use static_cast<int> instead of std::floor() to avoid float accuracy issue
    return num - (static_cast<int>(static_cast<double>(num) * 0.1) * 10);
}
