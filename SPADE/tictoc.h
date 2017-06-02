#ifndef TICTOC_H
#define TICTOC_H

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

class TicToc
{
public:
    TicToc();
    static void tic();
    static void toc(string name="");

private:
    static high_resolution_clock::time_point t1;
};

#endif // TICTOC_H
