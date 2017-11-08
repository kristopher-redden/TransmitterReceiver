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
    void Framing(unsigned char *allData, string fileToWriteTo, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool hamming, bool clientTransmitting);
    unsigned char* Deframing(string fileToRead, int fileLength, bool hamming, bool clientTransmitter);
    void Hamming(unsigned char *allData, string fileToWriteTo, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool clientTransmitting);
    void CRC();
    DataLinkLayer();
    ~DataLinkLayer();
private:
    unsigned char syn = '\026';
    uint16_t *HammingValues;

};


#endif //TRANSMITTERRECEIVER_DATALINKLAYER_H
