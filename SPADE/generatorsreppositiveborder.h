#ifndef GENERATORSREPPOSITIVEBORDER_H
#define GENERATORSREPPOSITIVEBORDER_H
#include "representation.h"
#include "sequence.h"
#include <string>
#include <unordered_map>

class GeneratorsRepPositiveBorder: public Representation
{
public:
    GeneratorsRepPositiveBorder(string& generatorsFile, string& positiveBorderFile, unordered_map<string, unsigned int>& nameToCode);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);
};

#endif // GENERATORSREPPOSITIVEBORDER_H
