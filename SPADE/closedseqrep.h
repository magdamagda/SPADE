#ifndef CLOSEDSEQREP_H
#define CLOSEDSEQREP_H

#include <vector>
#include "sequence.h"
#include "representation.h"
#include <string>
#include "filehelper.h"
#include <unordered_map>

using namespace std;

class ClosedSeqRep: public Representation
{
public:
    ClosedSeqRep(string& closedSeqFile, unordered_map<string, unsigned int>& nameToCode);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);


};

#endif // CLOSEDSEQREP_H
