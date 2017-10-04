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
    //void Framing(string dataField, string fileToWriteTo);
    void Framing(unsigned char *dataField, string fileToWriteTo, int charLength);
    unsigned char* Deframing(string fileToRead, int fileLength);
    void Print(string value, string file);
    DataLinkLayer();
    ~DataLinkLayer();
private:
    unsigned char syn = '\026';

};


#endif //TRANSMITTERRECEIVER_DATALINKLAYER_H
