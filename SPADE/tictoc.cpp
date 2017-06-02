#include "tictoc.h"

TicToc::TicToc()
{

}

void TicToc::tic(){
    t1 = high_resolution_clock::now();
}

void TicToc::toc(string name){
    auto duration = duration_cast<microseconds>( high_resolution_clock::now() - t1 ).count();
    cout<<name<<": "<<duration<<" ms"<<endl;
}

high_resolution_clock::time_point TicToc::t1 = high_resolution_clock::time_point();
