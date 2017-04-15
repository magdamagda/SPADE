#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Sequence
{
public:
    Sequence(vector<vector<unsigned int> > &events);
    void addEvent(vector<unsigned int> event);
    bool isSubset(Sequence &other);
    bool isSuperset(Sequence &other);
    bool isLastSingleton();
    vector < vector<unsigned int> > getEventsWithoutLastElement();
    string printSequence();

    vector < vector<unsigned int> >& getEvents(){
        return events;
    }

private:
    vector < vector<unsigned int> > events;
    bool isSubset(const vector < vector<unsigned int> > &otherEvents);


};

#endif // SEQUENCE_H
