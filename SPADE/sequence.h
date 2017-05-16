#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Sequence
{
public:
    Sequence();
    Sequence(unsigned int atom);
    Sequence(vector<vector<unsigned int> > &events);
    Sequence(Sequence *other);
    void addEvent(vector<unsigned int> event);
    void addEvent(unsigned int element);
    void addElementToLastEvent(unsigned int element);
    unsigned int getLastElement();
    bool isSubset(Sequence &other);
    bool isSuperset(Sequence &other);
    bool isSubset(Sequence *other);
    bool isSuperset(Sequence *other);
    bool isLastSingleton();
    vector<vector<unsigned int> > getEventsWithoutLastElement();
    string printSequence();
    string printEncodedSequence(const unordered_map<unsigned int, string>& atomsCodeToName);
    bool operator==(Sequence & other);

    void setSupport(unsigned int s){
        this->support = s;
    }

    unsigned int getSupport(){
        return this->support;
    }

    vector < vector<unsigned int> >& getEvents(){
        return events;
    }

    bool isMarked(){
        return marked;
    }

    void mark(bool value){
        marked = value;
    }

    vector<Sequence*> getSubsequences();
    unsigned int getSize();

private:
    vector < vector<unsigned int> > events;
    bool isSubset(const vector < vector<unsigned int> > &otherEvents);
    unsigned int support;
    bool marked;

};

#endif // SEQUENCE_H
