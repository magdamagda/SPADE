#ifndef GENERATORSREPNEGATIVEBORDER_H
#define GENERATORSREPNEGATIVEBORDER_H

#include "representation.h"
#include <string>

using namespace std;

class GeneratorsRepNegativeBorder: public Representation
{
public:
    GeneratorsRepNegativeBorder(string& generatorsFile, string& negativeBorderFile, string& codesFile);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);
};

#endif // GENERATORSREPNEGATIVEBORDER_H

