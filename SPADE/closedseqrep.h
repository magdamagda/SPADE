#ifndef CLOSEDSEQREP_H
#define CLOSEDSEQREP_H

#include<vector>
#include<sequence.h>
#include<set>


class ClosedSeqRep
{
public:
    ClosedSeqRep();
    void prepareRepresentaion(vector<set<Sequence*> > frequentSequence);

private:
    vector<Sequence> findClosedSequences(vector<set<Sequence*> > &frequentSequence);
};

#endif // CLOSEDSEQREP_H
