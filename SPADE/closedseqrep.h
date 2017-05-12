#ifndef CLOSEDSEQREP_H
#define CLOSEDSEQREP_H

#include<vector>
#include<sequence.h>


class ClosedSeqRep
{
public:
    ClosedSeqRep();
    void prepareRepresentaion(vector<Sequence> &frequentSequence);

private:
    vector<Sequence> findClosedSequences(vector<Sequence> &frequentSequence);
};

#endif // CLOSEDSEQREP_H
