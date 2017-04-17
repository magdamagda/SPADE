#ifndef IDLIST_H
#define IDLIST_H

#include "sequence.h"
#include <map>
#include <vector>

using namespace std;


class IdList
{
public:
    IdList();
    IdList(Sequence* s);

    Sequence* getSequence(){
        return sequence;
    }

    int size(){
        return this->idlist.size();
    }

    void addSidEid(unsigned int sid, unsigned int eid);

private:
    Sequence* sequence;
    map < unsigned int, vector<unsigned int> > idlist;

};

#endif // IDLIST_H
