#ifndef GENERATORSREPPOSITIVEBORDER_H
#define GENERATORSREPPOSITIVEBORDER_H
#include "representation.h"
#include <string>

class GeneratorsRepPositiveBorder: public Representation
{
public:
    GeneratorsRepPositiveBorder(string& generatorsFile, string& positiveBorderFile, string &codesFile);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);
};

#endif // GENERATORSREPPOSITIVEBORDER_H
