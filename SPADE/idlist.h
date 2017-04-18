#ifndef IDLIST_H
#define IDLIST_H

#include "sequence.h"
#include <map>
#include <vector>
#include <algorithm>

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
    bool isSid(unsigned int sid);
    vector <unsigned int>& getEventsBySid(unsigned int sid);

    typedef map<unsigned int, vector<unsigned int> >::iterator iterator;
    iterator begin(){
        return idlist.begin();
    }

    iterator end(){
        return idlist.end();
    }

    void updateSeqSupport(){
        sequence->setSupport(idlist.size());
    }

private:
    Sequence* sequence;
    map < unsigned int, vector<unsigned int> > idlist;

};

#endif // IDLIST_H
