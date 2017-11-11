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
void DataLinkLayer::Framing(unsigned char* allData, string hostname, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool hamming, bool clientTransmitting)
{
    if (hamming)
        Hamming(allData, hostname, allCharsInFrame, fullFrames, extraFrameDataLength, bitToFlip, clientTransmitting);
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
unsigned char* DataLinkLayer::Deframing(bool hamming, bool clientTransmitter, string hostname)
{
    PhysicalLayer *pl = new PhysicalLayer(clientTransmitter, hostname);
    unsigned char *hammingDoubledArray;
    unsigned char currentChar;
    string allData = pl->ReadValues();
    int allDataLength = allData.length() / 8;//Number of chars from hamming.
    hammingDoubledArray = pl->Decode(allData);
    unsigned char *unhammingedM1Frame = DeHamming(hammingDoubledArray, allDataLength);

//    int fullFrames = allDataLength / 131;
//    int extraFrame = allDataLength % 131;
//    int originalFrameM1 = fullFrames * 67 + (extraFrame - 3) / 2 + 3; //Get rid of the SYN, CTRL, and SYN to get actual data count.
    int fullFrameCount = everyByteInEveryFrame / 67;
    int lastFrameLength = everyByteInEveryFrame % 67;
    int lastFrameChecked = -1;
    //unsigned char *bytesToWriteToFile = new unsigned char[fullFrameCount * 64 + lastFrameLength - 3];
    unsigned char *bytesToWriteToFile = new unsigned char[everyByteInEveryFrame];

    int bytesToWriteIndex = 0;

    //If all the parity checked out, being the deframing.
    unsigned char firstSYN;
    unsigned char lastSYN;
    unsigned char ctrl;
    //Go through the entire set of chars from each full frame.
    for (int fullFrames = 0; fullFrames < fullFrameCount; fullFrames++)
    {
        firstSYN = unhammingedM1Frame[fullFrames * 67];
        lastSYN = unhammingedM1Frame[(fullFrames + 1) * 67 - 1];
        ctrl = unhammingedM1Frame[fullFrames * 67 + 1];

        //If the first and last character of a frame are not a SYN, then we have an invalid frame.
        if (firstSYN != syn || lastSYN != syn)
            throw 1;

        lastFrameChecked++;
        //Otherwise, we have a valid frame, construct the data to print.
        for (int partOfFrame = 0; partOfFrame < 64; partOfFrame++)
        {
            bytesToWriteToFile[bytesToWriteIndex] = unhammingedM1Frame[fullFrames * 67 + 2 + partOfFrame];
            bytesToWriteIndex++;
        }
    }
    //We have a frame that is not the full length.  We know the previous frame we checked,
    //so go to the next one that doesn't have a full length.
    if (lastFrameLength != 0)
    {
        //If lastFrameChecked is 0, then we know that we had a file length of less than 64 data characters.
        //Set the value to -1 so that we can fill in the only frame (which is less than 64 data characters.)

        firstSYN = unhammingedM1Frame[(lastFrameChecked + 1) * 67];
        lastSYN = unhammingedM1Frame[(lastFrameChecked + 1) * 67 + lastFrameLength - 1];
        ctrl = unhammingedM1Frame[(lastFrameChecked + 1) * 67 + 1];
        //If the first and last character of a frame are not a SYN, then we have an invalid frame.
        if (firstSYN != syn || lastSYN != syn)
            throw 1;

        //Otherwise, we have a valid frame, construct the data to print.
        for (int partOfFrame = 0; partOfFrame < lastFrameLength - 3; partOfFrame++)
        {
            bytesToWriteToFile[bytesToWriteIndex] = unhammingedM1Frame[(lastFrameChecked + 1) * 67 + 2 + partOfFrame];
            bytesToWriteIndex++;
        }
    }
    return bytesToWriteToFile;
}

void DataLinkLayer::Hamming(unsigned char *allData, string hostname, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip, bool clientTransmitting)
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
            unsigned char theChar = allData[loc * 64 + characterLoc];//Mul by 64 since allData contains the original file data.
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
        unsigned char theChar = allData[fullFrames * 64 + charLocation];
        uint16_t  twoChars = HammingValues[theChar];
        unsigned char low = (unsigned char) twoChars & 0xff;
        unsigned char high = (unsigned char) ((twoChars >> 8) & 0xff);

        frames[(fullFrames * 131) + (charLocation * 2) + 2] = high;
        frames[(fullFrames * 131) + (charLocation * 2 + 1) + 2] = low;
    }
    frames[fullFrames * 131 + extraFrameLength - 1] = '\x16';

    PhysicalLayer *pl = new PhysicalLayer(clientTransmitting, hostname);

    pl->Encode(frames, allCharsInEveryFrame, bitToFlip);
}

unsigned char* DataLinkLayer::DeHamming(unsigned char* charArrayDoubledData, int allDataLength)
{
    uint8_t low = 0x0;
    uint8_t high = 0x0;
    uint8_t checkBits = 0x0;
    uint8_t top = 0x0;
    uint8_t middle = 0x0;
    uint8_t bottom = 0x0;
    uint8_t constructingRealValue = 0x0;
    uint16_t hamming = 0x0;
    int fullFrames = allDataLength / 131;
    int extraFrame = allDataLength % 131;
    everyByteInEveryFrame = fullFrames * 67 + (extraFrame - 3) / 2 + 3; //Get rid of the SYN, CTRL, and SYN to get actual data count. (- 3 div) 2 + 3
    dehammingCharCount = fullFrames * 64 + (extraFrame - 3) / 2;//Only the dehamming char count.
    unsigned char *correctData = new unsigned char[everyByteInEveryFrame];
    int correctDataLoc = 0;
    for (int hamValueLoc = 0; hamValueLoc < allDataLength; hamValueLoc++)
    {
        //Skip the SYN, CTRL and SYN located in the first, second and last location of the frame. (0, 1 and 130)  Make sure you skip the SYN char on the non full frame. == 22 handles this.
        if (hamValueLoc % 131 == 0 || hamValueLoc % 131 == 1 || hamValueLoc % 131 == 130 || charArrayDoubledData[hamValueLoc] == 22)
        {
            unsigned char synOrCtrl = (unsigned char)charArrayDoubledData[hamValueLoc];

            correctData[correctDataLoc] = synOrCtrl;
            correctDataLoc++;
            continue;
        }
        else
        {
            high = low = checkBits = top = middle = bottom = constructingRealValue = 0x0;
            hamming = 0x00;
            high = charArrayDoubledData[hamValueLoc];
            low = charArrayDoubledData[hamValueLoc + 1];
            hamValueLoc++;//Skip ahead so we don't repeat the same char.
            //Clear the parity.
            high &= 0x7f;
            low &= 0x7f;
            //only need the five bits in the low byte.  Remove the padding.
            low >>= 2;
            hamming |= high;
            //Shift left 5 since the low byte only has 5 more bits to get.
            hamming <<= 5;
            hamming |= low;

            //Now we have the 12 bits that we need.
            //Get c1, c2, c3, and c4.
            //c4
            if (((~((hamming << 1)^(hamming << 2)^(hamming << 3) ^ (hamming << 4))) & 0x10) != (hamming & 0x10))
                checkBits |= 0x8;
            //c3
            if (((~((hamming << 1)^(hamming << 2)^(hamming << 3) ^ (hamming << 8))) & 0x100) != (hamming & 0x100))
                checkBits |= 0x4;
            //c2
            if (((~((hamming << 1)^(hamming << 4)^(hamming << 5) ^ (hamming << 8) ^ (hamming << 9))) & 0x400) != (hamming & 0x400))
                checkBits |= 0x2;
            //c1
            if (((~((hamming << 2)^(hamming << 4)^(hamming << 6) ^ (hamming << 8) ^ (hamming << 10))) & 0x800) != (hamming & 0x800))
                checkBits |= 0x1;

            if (checkBits != 0x0)
            {
                //hamming << checkBits;
                hamming ^= hamming << checkBits;
                //number ^= 1UL << x;
            }
            hamming &= 0x2EF; //Clear the check bits.

            //unsigned char theRealChar = (unsigned char)(hamming & 0x0FF | (hamming >> 1) | (hamming >> 2));
            unsigned char theRealChar;
            top |= (((hamming & 0x200) >> 1) >> 8);//Get m1
            constructingRealValue |= top;
            constructingRealValue <<= 3;

            middle |= (((hamming & 0x0E0) >> 1) >> 4);//Get m2, m3, m4
            constructingRealValue |= middle;
            constructingRealValue <<= 4;

            bottom |= ((hamming & 0x00F));//Get m5, m6, m7, m8.
            constructingRealValue |= bottom;

            theRealChar = (unsigned char)constructingRealValue;

            correctData[correctDataLoc] = theRealChar;
            correctDataLoc++;
        }
    }
    return correctData;
}

int DataLinkLayer::NumberOfPrintableChars()
{
    return dehammingCharCount;
}
void DataLinkLayer::CRC()
{

}