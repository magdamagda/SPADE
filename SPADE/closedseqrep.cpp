#include "closedseqrep.h"


ClosedSeqRep::ClosedSeqRep()
{

}

void ClosedSeqRep::prepareRepresentaion(vector<set<Sequence *> > frequentSequence){
    vector<Sequence> closedSequence = this->findClosedSequences(frequentSequence);
    //save to file
    //for(auto sequence:frequentSequence){



}

vector<Sequence> ClosedSeqRep::findClosedSequences(vector<set<Sequence *> > &frequentSequence){
    return vector<Sequence>();
}
