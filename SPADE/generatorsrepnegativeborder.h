#ifndef GENERATORSREPNEGATIVEBORDER_H
#define GENERATORSREPNEGATIVEBORDER_H

#include "representation.h"
#include "sequence.h"
#include <string>
#include <unordered_map>

using namespace std;

class GeneratorsRepNegativeBorder: public Representation
{
public:
    GeneratorsRepNegativeBorder(string& generatorsFile, string& negativeBorderFile, unordered_map<string, unsigned int>& nameToCode);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);
};

#endif // GENERATORSREPNEGATIVEBORDER_H

