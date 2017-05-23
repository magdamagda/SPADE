#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>
#include "sequence.h"
#include <string>

using namespace std;

class Representation
{
public:
    Representation();
    virtual int calculateSupport(Sequence* sequence)=0;
    virtual void calculateSupport(string& inputFile, string& outputFile)=0;

};

#endif // REPRESENTATION_H
