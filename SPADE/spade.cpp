#include "spade.h"

Spade::Spade()
{

}

void Spade::calculate(string& input, DataSetReader* dataReader, unsigned int minSup){
    vector<IdList*> freqOneSeq = this->readFrequentOneSeq(input, dataReader, minSup);

}

vector <IdList*> Spade::readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup){
    dataReader->open(input);
    vector <IdList*> oneSeq;
    map<unsigned int, IdList*> atomsIdLists;
    Transaction* t = dataReader->getTransaction();
    while(t!=nullptr){
        for (string &itemName:t->items){
            unsigned int item;
            if (this->atomsNameToCode.find(itemName) == this->atomsNameToCode.end()){
                item = this->addToAtoms(itemName);
                atomsIdLists[item] = new IdList(new Sequence(item));
            }
            else{
                item = this->atomsNameToCode[itemName];
            }
            atomsIdLists[item]->addSidEid(t->sid, t->eid);
        }
        delete t;
        t = dataReader->getTransaction();
    }
    dataReader->close();

    for(auto & atomIdList:atomsIdLists){
        unsigned int support = atomIdList.second->size();
        atomIdList.second->getSequence()->setSupport(support);
        if(support > minSup){
            oneSeq.push_back(atomIdList.second);
            this->freqSequences.push_back(atomIdList.second->getSequence());
        }
        else{
            this->minInfreqGenerators.push_back(atomIdList.second->getSequence());
        }
    }

    return oneSeq;
}

vector <IdList*> Spade::readFrequentTwoSeq(){

}

unsigned int Spade::addToAtoms(string atom){
    unsigned int code = this->atomsNameToCode.size();
    this->atomsNameToCode[atom] = code;
    this->atomsCodeToName[code] = atom;
    return code;
}
