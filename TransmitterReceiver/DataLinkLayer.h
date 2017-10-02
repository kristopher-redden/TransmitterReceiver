//
// Created by kristopher on 9/30/17.
//

#ifndef TRANSMITTERRECEIVER_DATALINKLAYER_H
#define TRANSMITTERRECEIVER_DATALINKLAYER_H

#include <string>

using namespace std;
class DataLinkLayer
{
public:
    void Framing(string dataField, string fileToWriteTo);
    string Deframing(string frame);
    DataLinkLayer();
    ~DataLinkLayer();
private:

};


#endif //TRANSMITTERRECEIVER_DATALINKLAYER_H
