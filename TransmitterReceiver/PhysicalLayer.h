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
    void Encode(string character);
    void Decode(string character);
    PhysicalLayer();
    ~PhysicalLayer();

private:


};


#endif //TRANSMITTERRECEIVER_PHYSICALLAYER_H
