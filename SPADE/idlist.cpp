#include "idlist.h"

IdList::IdList()
{
}

IdList::IdList(Sequence *s)
{
    this->sequence = s;
}

void IdList::addSidEid(unsigned int sid, unsigned int eid){
    if(this->idlist.find(sid)==this->idlist.end()){
        this->idlist[sid];
    }
    this->idlist[sid].push_back(eid);
}
