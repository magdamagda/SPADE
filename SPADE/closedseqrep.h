#ifndef CLOSEDSEQREP_H
#define CLOSEDSEQREP_H

#include <vector>
#include "sequence.h"
#include "representation.h"
#include <string>
#include "filehelper.h"

using namespace std;

class ClosedSeqRep: public Representation
{
public:
    ClosedSeqRep(string& closedSeqFile, string& codesFile);
    virtual int calculateSupport(Sequence* sequence);
    virtual void calculateSupport(string& inputFile, string& outputFile);


};

#endif // CLOSEDSEQREP_H
