#include <iostream>
#include <string>
#include "spade.h"
#include "datasetreader.h"


int main(int argc, char *argv[])
{
    int minSup=1;
    string filename="../datasets/zaki.txt";
    DataSetReader* dataReader = new DataSetReader();
    Spade spade;
    spade.calculate(filename, dataReader, minSup);


    return 0;
}
