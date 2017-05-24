#include "closedseqrep.h"


ClosedSeqRep::ClosedSeqRep(string &closedSeqFile, unordered_map<string, unsigned int> &nameToCode)
{
    this->atomsNameToCode = nameToCode;
    //read closed sequence and save
}

int ClosedSeqRep::calculateSupport(Sequence* sequence){
    return 0;
}

void ClosedSeqRep::calculateSupport(string& inputFile, string& outputFile){
    //read sequences from inputFile
    //for each calculate support
    //save it to file outputFile
}
