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
    void Encode(string dataField, string outputFile);
    void Decode(string frame, string outputFile);
    void Print(string value, string file);
    PhysicalLayer();
    ~PhysicalLayer();

private:
    int frameCount = 0;
    int charLocation = 0;
    unsigned char syn = '\026';

};


#endif //TRANSMITTERRECEIVER_PHYSICALLAYER_H
