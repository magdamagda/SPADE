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
        this->idlist[sid].push_back(eid);
    }
    else if(find(idlist[sid].begin(), idlist[sid].end(), eid)==idlist[sid].end()){
        this->idlist[sid].push_back(eid);
    }
}

bool IdList::isSid(unsigned int sid){
    return this->idlist.find(sid)!=this->idlist.end();
}

vector <unsigned int>& IdList::getEventsBySid(unsigned int sid){
    return this->idlist.at(sid);
}

void IdList::sortEvents(){
    for(auto item:this->idlist){
        sort(item.second.begin(), item.second.end());
    }
}
