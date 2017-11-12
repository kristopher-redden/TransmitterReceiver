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
    void Framing(unsigned char *allData, string hostname, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool hamming, bool clientTransmitting);
    unsigned char* Deframing(bool hamming, bool clientTransmitter, string hostname);
    void Hamming(unsigned char *allData, string hostname, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool clientTransmitting);
    unsigned char* DeHamming(unsigned char* charArrayDoubledData, int allDataLength);
    int NumberOfPrintableChars();
    void CRC(unsigned char* allData, string hostname, int allCharsInFrame, int fullFrames, int extraFrameDataLength, bool clientTransmitting);
    DataLinkLayer();
    ~DataLinkLayer();
private:
    unsigned char syn = '\026';
    int everyByteInEveryFrame = 0;
    int dehammingCharCount = 0;
    uint16_t *HammingValues;
};


#endif //TRANSMITTERRECEIVER_DATALINKLAYER_H
