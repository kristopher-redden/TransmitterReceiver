//
// Created by kristopher on 9/30/17.
//

#include <string>

#ifndef TRANSMITTERRECEIVER_APPLICATIONLAYER_H
#define TRANSMITTERRECEIVER_APPLICATIONLAYER_H

using namespace std;
class ApplicationLayer
{
public:
    void CommandT(string hostname, string fileToReadFrom, int bitToFlip, bool NOTNeeded, bool NotNeeded2);
    void CommandR(string file1, string file2, bool ham, bool clientTransmitting);
    void CommandTHam(string hostname, string fileToReadFrom, bool ham, bool clientTransmitting);
    void CommandRHam(string hostname, string fileToWriteTo, bool ham, bool clientTransmitting);
    void CommandTCrc(string hostname, string fileToReadFrom, bool crc, bool clientTransmitting);
    void CommandRCrc(string hostname, string fileToWriteTo, bool crc, bool clientTransmitting);
    ApplicationLayer();
    ~ApplicationLayer();

private:

};


#endif //TRANSMITTERRECEIVER_APPLICATIONLAYER_H
