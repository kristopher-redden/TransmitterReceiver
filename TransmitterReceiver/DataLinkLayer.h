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
    string Framing(string dataField);
    string Deframing(string frame);
    DataLinkLayer();
    ~DataLinkLayer();
private:

};


#endif //TRANSMITTERRECEIVER_DATALINKLAYER_H
