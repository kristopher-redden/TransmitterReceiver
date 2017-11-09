//
// Created by kristopher on 9/30/17.
//

#ifndef TRANSMITTERRECEIVER_PHYSICALLAYER_H
#define TRANSMITTERRECEIVER_PHYSICALLAYER_H

#include <string>

/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

//////////Added ///////////////////
#include <iostream>
#include <fstream>

///////////////////////

#define PORT "3498" // the port client will be connecting to

#define MAXDATASIZE 1048 // max number of bytes we can get at once. Frame is 131 bytes * 8 bytes to represent each bit in the byte.

#define BACKLOG 10     // how many pending connections queue will hold

/////////////////////////////Only thing different from server
#include <sys/wait.h>
#include <signal.h>
/////////////////////////////

using namespace std;
class PhysicalLayer
{
public:
    void Encode(unsigned char* frame, string outputFile, int allCharsInFrame, int bitToFlip);
    unsigned char* Decode(string fileToRead, int fileLength);
    void WaitForConnection();
    void ReadValues();
    string entireEncodedFile = "";
    PhysicalLayer();
    PhysicalLayer(bool clientTrans, string hostname);
    ~PhysicalLayer();

private:
    int charLocation = 0;
    unsigned char syn = '\026';
    int sockfd;
    int new_fd;  // listen on sock_fd, new connection on new_fd

};


#endif //TRANSMITTERRECEIVER_PHYSICALLAYER_H
