//
// Created by kristopher on 9/30/17.
//

#include "DataLinkLayer.h"
#include "PhysicalLayer.h"

#include <iostream>
#include <fstream>
DataLinkLayer::DataLinkLayer()
{
    uint8_t low = 0x0;
    uint8_t high = 0x0;
    uint16_t hamming = 0x0;
    HammingValues = new uint16_t[128];
    for (uint8_t theChar = 0; theChar < 128; theChar++)
    {
        low = high = hamming = 0x0;
        int x = 0;//0  1  2  3  4  5  6  7  8  9 10 11 12 13  14  15
        //Hamming message is of the form p1 c1 c2 m1 c4 m2 m3 m4 p2 c8 m5 m6 m7 m8 pad1 pad2
        //Fill the higher byte first, which is 0  1  2  3  4  5  6  7
                                             //p1 c1 c2 m1 c4 m2 m3 m4

        //H = 48 = 0  1  0  0  1  0  0  0
        //Message= 1  2  3  4  5  6  7  8
        //HammLoc= 3  5  6  7  9  10 11 12
        //We need to place first check bit in position 2 of the high byte.  Place in position 2 when XORing.
        //Check bit 1 checks Hamming bits: 3, 5, 7, 9, 11.
        //H =        0                1          0                1                0
        //Mes =      1                2          3                4                5
        //Ham =      3                5          4                9                11
        //Check bit 1 checks 3, 5, 7, 9, 11 of hamming.                                                                         0100 0000
        high = (uint8_t )(((~((theChar >> 1) ^ theChar ^ (theChar << 2) ^ (theChar << 3) ^ (theChar << 5))) & 0x40) | high);

        //H = 48 = 0  1  0  0  1  0  0  0
        //Message= 1  2  3  4  5  6  7  8
        //HammLoc= 3  5  6  7  9  10 11 12
        //We need to place second check bit in position 3 of the high byte.  Place in position 3 when XORing.
        //Check bit 2 checks Hamming bits:
        //H =        0                0          0                0                0
        //Mes =      1                3          4                6                7
        //Ham =      3                6          7                10               11
        //Check bit 2 checks 3, 6, 7, 10, 11                                                                       0010 0000
        high = (uint8_t )(((~((theChar >> 2) ^ theChar ^ (theChar << 1) ^ (theChar << 3) ^ (theChar << 4))) & 0x20) | high);

        //Message bit 1 goes into the location 4 of hamming.
        high = (uint8_t )(((theChar >> 3) & 0x10) | high);

        //H = 48 = 0  1  0  0  1  0  0  0
        //Message= 1  2  3  4  5  6  7  8
        //HammLoc= 3  5  6  7  9  10 11 12
        //We need to place third check bit in position 5 of the high byte.  Place in position 5 when XORing.
        //Check bit 3 checks Hamming bits:
        //H =        1                0                 0                1
        //Mes =      2                3                 4                8
        //Ham =      5                6                 7                12
        //Check bit 3 checks 5, 6, 7, 12                                                 1000
        high = (uint8_t )(((~((theChar >> 3) ^ (theChar >> 2) ^ (theChar >> 1) ^ (theChar << 3))) & 0x8) | high);

        //Message bit 2, 3, 4 go in positions 6, 7 and 8 of the hamming message.
        high = (uint8_t )(((theChar >> 4) & 0x07) | high);

                                        //0  1  2  3  4  5  6  7  8  9 10 11 12 13  14  15
        //Hamming message is of the form p1 c1 c2 m1 c4 m2 m3 m4 p2 c8 m5 m6 m7 m8 pad1 pad2
        //Fill the lower byte next, which is 0  1  2  3  4  5  6  7
        //p2 c8 m5 m6 m7 m8 pad1 pad2

        //H = 48 = 0  1  0  0  1  0  0  0
        //Message= 1  2  3  4  5  6  7  8
        //HammLoc= 3  5  6  7  9  10 11 12
        //We need to place third check bit in position 5 of the high byte.  Place in position 2 when XORing.
        //Check bit 4 checks Hamming bits:
        //H =        1                0                 0                1
        //Mes =      5                6                 7                8
        //Ham =      9                10                11               12
        //Check bit 4 checks 5, 6, 7, 12                                                 0100 0000
        low = (uint8_t )(((~((theChar << 3) ^ (theChar << 4) ^ (theChar << 5) ^ (theChar << 6))) & 0x40) | low);

        //Message bit 5, 6, 7, 8 go in positions 3, 4, 5, 6.
        low = (uint8_t )(((theChar << 2) & 0x3c) | low);

        hamming |= high;
        hamming <<= 8;
        hamming |= low;

        HammingValues[(int)theChar] = hamming;
    }
}
DataLinkLayer::~DataLinkLayer()
{

}

//Format the data into frames: SYN + CTRL + Data + SYN
void DataLinkLayer::Framing(unsigned char* allData, string fileToWriteTo, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool hamming, bool clientTransmitting)
{
    if (hamming)
        Hamming(allData, fileToWriteTo, allCharsInFrame, fullFrames, extraFrameDataLength, bitToFlip, clientTransmitting);
    else
        CRC();
//    unsigned char *frames = new unsigned char[allCharsInFrame];
//    for (int loc = 0; loc < fullFrames; loc++)
//    {
//        frames[loc * 67] = '\x16';
//        frames[loc * 67 + 1] = (unsigned char) 64;
//        for (int characterLoc = 0; characterLoc < 64; characterLoc++)
//        {
//            //Initially it will be 2 - 65.
//            //Offset by 2 handles the SYN and CTRL.
//            frames[loc * 67 + characterLoc + 2] = allData[loc * 64 + characterLoc];
//        }
//        frames[(loc + 1) * 67 - 1] = '\x16';
//    }
//    //Now that we have taken care of the full frames, do the last smaller frame.
//    frames[fullFrames * 67] = '\x16';
//    frames[fullFrames * 67 + 1] = (unsigned char) extraFrameDataLength;
//
//    for (int charLocation = 0; charLocation < extraFrameDataLength; charLocation++)
//    {
//        //Offset by 2 handles the SYN and CTRL.
//        frames[fullFrames * 67 + charLocation + 2] = allData[fullFrames * 64 + charLocation];
//    }
//    frames[fullFrames * 67 + extraFrameDataLength + 2] = '\x16';
//
//    PhysicalLayer pl;
//    pl.Encode(frames, fileToWriteTo, allCharsInFrame, bitToFlip);
}

//We will call the physical layer to check the parity of all of the characters in the encoded file.
//If we return from the physical layer, then we know all of the parity passed.  Check the frames to
//make sure that the first and last characters are SYN characters.
unsigned char* DataLinkLayer::Deframing(string fileToRead, int fileLength, bool hamming, bool clientTransmitter)
{
    PhysicalLayer *pl = new PhysicalLayer(clientTransmitter, "Hostname");
    unsigned char *bytes;
    unsigned char currentChar;
    bytes = pl->Decode(fileToRead, fileLength);

    int fullFrameCount = fileLength / 536;
    int lastFrameLength = fileLength % 536 / 8;
    int lastFrameChecked;
    unsigned char *bytesToWriteToFile = new unsigned char[fullFrameCount * 64 + lastFrameLength - 3];
    int bytesToWriteIndex = 0;

    //If all the parity checked out, being the deframing.
    unsigned char firstSYN;
    unsigned char lastSYN;
    unsigned char ctrl;
    //Go through the entire set of chars from each full frame.
    for (int fullFrames = 0; fullFrames < fullFrameCount; fullFrames++)
    {
        firstSYN = bytes[fullFrames * 67];
        lastSYN = bytes[(fullFrames + 1) * 67 - 1];
        ctrl = bytes[fullFrames * 67 + 1];

        //If the first and last character of a frame are not a SYN, then we have an invalid frame.
        if (firstSYN != syn || lastSYN != syn)
            throw 1;

        lastFrameChecked = fullFrames;
        //Otherwise, we have a valid frame, construct the data to print.
        for (int partOfFrame = 0; partOfFrame < 64; partOfFrame++)
        {
            bytesToWriteToFile[bytesToWriteIndex] = bytes[fullFrames * 67 + 2 + partOfFrame];
            bytesToWriteIndex++;
        }
    }
    //We have a frame that is not the full length.  We know the previous frame we checked,
    //so go to the next one that doesn't have a full length.
    if (lastFrameLength != 0)
    {
        //If lastFrameChecked is 0, then we know that we had a file length of less than 64 data characters.
        //Set the value to -1 so that we can fill in the only frame (which is less than 64 data characters.)
        if (lastFrameChecked == 0)
            lastFrameChecked = -1;
        firstSYN = bytes[(lastFrameChecked + 1) * 67];
        lastSYN = bytes[(lastFrameChecked + 1) * 67 + lastFrameLength - 1];
        ctrl = bytes[(lastFrameChecked + 1) * 67 + 1];
        //If the first and last character of a frame are not a SYN, then we have an invalid frame.
        if (firstSYN != syn || lastSYN != syn)
            throw 1;

        //Otherwise, we have a valid frame, construct the data to print.
        for (int partOfFrame = 0; partOfFrame < lastFrameLength - 3; partOfFrame++)
        {
            bytesToWriteToFile[bytesToWriteIndex] = bytes[(lastFrameChecked + 1) * 67 + 2 + partOfFrame];
            bytesToWriteIndex++;
        }
    }
    return bytesToWriteToFile;
}

void DataLinkLayer::Hamming(unsigned char *allData, string fileToWriteTo, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool clientTransmitting)
{
    int fullFrameLength = fullFrames * 131;//Every full frame has 131 chars. SYN + CTRL + 128 Data chars + SYN
    int extraFrameLength = extraFrameDataLength * 2 + 3;//The extraFrameDataLength is the data length of the extra frame.
    int allCharsInEveryFrame = fullFrameLength + extraFrameLength;
    //Multiple it by 2 so that each data character is made up of 2 hamming chars above and add 3 for SYN + CTRL + SYN.
    //unsigned char *frames = new unsigned char[allCharsInFrame];
    unsigned char *frames = new unsigned char[allCharsInEveryFrame];
    //Frame length is SYN + CTRL + 64 Data chars from the file + SYN
    //64 * 2 chars to represent + 3 = 131.
    for (int loc = 0; loc < fullFrames; loc++)
    {
        frames[loc * 131] = '\x16';
        frames[loc * 131 + 1] = (unsigned char) 64;
        for (int characterLoc = 0; characterLoc < 64; characterLoc++)
        {
            //Initially it will be 2 - 130.
            //Offset by 2 handles the SYN and CTRL.
            //Get the char from the input file.
            unsigned char theChar = allData[loc * 128 + characterLoc];
            uint16_t  twoChars = HammingValues[theChar];
            unsigned char low = (unsigned char) twoChars & 0xff;
            unsigned char high = (unsigned char) ((twoChars >> 8) & 0xff);

            frames[(loc * 131) + (characterLoc * 2) + 2] = high;
            frames[(loc * 131) + (characterLoc * 2 + 1) + 2] = low;
        }
        frames[(loc + 1) * 131 - 1] = '\x16';
    }
    //Now that we have taken care of the full frames, do the last smaller frame.
    frames[fullFrames * 131] = '\x16';
    frames[fullFrames * 131 + 1] = (unsigned char) extraFrameDataLength;

    for (int charLocation = 0; charLocation < extraFrameDataLength; charLocation++)
    {
        //Offset by 2 handles the SYN and CTRL.
        //frames[fullFrames * 131 + charLocation + 2] = allData[fullFrames * 128 + charLocation];
        unsigned char theChar = allData[fullFrames * 128 + charLocation];
        uint16_t  twoChars = HammingValues[theChar];
        unsigned char low = (unsigned char) twoChars & 0xff;
        unsigned char high = (unsigned char) ((twoChars >> 8) & 0xff);

        frames[(fullFrames * 131) + (charLocation * 2) + 2] = high;
        frames[(fullFrames * 131) + (charLocation * 2 + 1) + 2] = low;
    }
    frames[fullFrames * 131 + extraFrameLength - 1] = '\x16';

    PhysicalLayer *pl = new PhysicalLayer(clientTransmitting, "hostname");
    pl->Encode(frames, fileToWriteTo, allCharsInEveryFrame, bitToFlip);
}

void DataLinkLayer::CRC()
{

}