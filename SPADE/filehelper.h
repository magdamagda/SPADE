#ifndef SEQUENCESWRITER_H
#define SEQUENCESWRITER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "sequence.h"

class FileHelper
{
public:
    FileHelper();
    void writeSequencesToFile(const string& fileName, const vector<Sequence*>& sequences);
    void writeEncodedSequencesToFile(const string& fileName, const vector<Sequence*>& sequences, const unordered_map<unsigned int, string>& codeToName);
    void writeCodeToNameMapToFile(const string &fileName, const unordered_map<unsigned int, string> &codeToName);
    unordered_map<string, unsigned int> readNameToCodeMap(const string &fileName);
};

#endif // SEQUENCESWRITER_H
