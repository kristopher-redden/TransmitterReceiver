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
    void CommandT(string file1, string file2, int bitToFlip, bool NOTNeeded, bool NotNeeded2);
    void CommandR(string file1, string file2, bool ham, bool clientTransmitting);
    void CommandTWithError(string file1, string file2);
    void CommandTHam(string file1, string file2, bool ham, bool clientTransmitting);
    void CommandRHam(string file1, string file2, bool ham, bool clientTransmitting);
    ApplicationLayer();
    ~ApplicationLayer();

private:

};


#endif //TRANSMITTERRECEIVER_APPLICATIONLAYER_H
