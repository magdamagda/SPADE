#include "spade.h"

Spade::Spade()
{

}

void Spade::calculate(string& input, DataSetReader* dataReader, unsigned int minSup){
    vector<IdList*> freqOneSeq = this->readFrequentOneSeq(input, dataReader, minSup);
    vector<IdList*> freqTwoSeq = this->readFrequentTwoSeq(freqOneSeq, minSup);
    temporalJoin(freqOneSeq[0], freqOneSeq[1]);
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

vector <IdList*> Spade::readFrequentTwoSeq(vector <IdList*>& freqOneSeq, unsigned int minSup){

}

unsigned int Spade::addToAtoms(string atom){
    unsigned int code = this->atomsNameToCode.size();
    this->atomsNameToCode[atom] = code;
    this->atomsCodeToName[code] = atom;
    return code;
}

vector <IdList*> Spade::temporalJoin(IdList* first, IdList* second){
    vector <IdList*> result;
    Sequence* seq1 = first->getSequence();
    Sequence* seq2 = second->getSequence();

    Sequence* eventAtomSeq = new Sequence(seq1);
    eventAtomSeq->addElementToLastEvent(seq2->getLastElement());
    IdList* eventAtom = new IdList(eventAtomSeq);

    Sequence* firstSecondSeq = new Sequence(seq1);
    firstSecondSeq->addEvent(seq2->getLastElement());
    IdList* firstSecond = new IdList(firstSecondSeq);

    Sequence* secondFirstSeq = new Sequence(seq2);
    secondFirstSeq->addEvent(seq1->getLastElement());
    IdList* secondFirst = new IdList(secondFirstSeq);

    for (auto& sequence:(*first)){
        unsigned int sid = sequence.first;
        if(second->isSid(sid)){
            for(unsigned int eid1:sequence.second){
                for(unsigned int eid2:second->getEventsBySid(sid)){
                    if (eid1<eid2){
                        firstSecond->addSidEid(sid, eid2);
                    } else if(eid1>eid2){
                        secondFirst->addSidEid(sid, eid1);
                    } else {
                        eventAtom->addSidEid(sid, eid1);
                    }
                }
            }
        }
    }

    if(eventAtom->size()>0){
        eventAtom->updateSeqSupport();
        result.push_back(eventAtom);
    }
    if(firstSecond->size()>0){
        firstSecond->updateSeqSupport();
        result.push_back(firstSecond);
    }
    if(secondFirst->size()>0){
        secondFirst->updateSeqSupport();
        result.push_back(secondFirst);
    }

    return result;
}

void Spade::EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup){

}
