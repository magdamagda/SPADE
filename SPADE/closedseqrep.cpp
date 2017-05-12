#include "closedseqrep.h"


ClosedSeqRep::ClosedSeqRep()
{

}

void ClosedSeqRep::prepareRepresentaion(vector<Sequence> &frequentSequence){
    vector<Sequence> closedSequence = this->findClosedSequences(frequentSequence);
    //save to file
}

vector<Sequence> ClosedSeqRep::findClosedSequences(vector<Sequence> &frequentSequence){
    return vector<Sequence>();
}
