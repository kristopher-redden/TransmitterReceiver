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
    void CommandT(string file1, string file2, int bitToFlip);
    void CommandR(string file1, string file2);
    void CommandTWithError(string file1, string file2);
    ApplicationLayer();
    ~ApplicationLayer();

private:

};


#endif //TRANSMITTERRECEIVER_APPLICATIONLAYER_H
