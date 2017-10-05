//
// Created by kristopher on 9/30/17.
//

#ifndef TRANSMITTERRECEIVER_PHYSICALLAYER_H
#define TRANSMITTERRECEIVER_PHYSICALLAYER_H

#include <string>
using namespace std;
class PhysicalLayer
{
public:
    void Encode(unsigned char* frame, string outputFile, int charLength);
    unsigned char* Decode(string fileToRead, int fileLength);
    PhysicalLayer();
    ~PhysicalLayer();

private:
    int charLocation = 0;
    unsigned char syn = '\026';

};


#endif //TRANSMITTERRECEIVER_PHYSICALLAYER_H
