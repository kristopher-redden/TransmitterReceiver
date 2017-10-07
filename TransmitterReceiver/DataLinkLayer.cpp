//
// Created by kristopher on 9/30/17.
//

#include "DataLinkLayer.h"
#include "PhysicalLayer.h"

#include <iostream>
#include <fstream>
DataLinkLayer::DataLinkLayer()
{

}
DataLinkLayer::~DataLinkLayer()
{

}

//Format the data into frames: SYN + CTRL + Data + SYN
void DataLinkLayer::Framing(unsigned char* dataField, string fileToWriteTo, int charLength)
{
    //We know that we have a full frame.
    dataField[0] = '\x16';
    dataField[1] = (unsigned char) charLength;
    if (charLength == 64)
        dataField[66] = '\x16';
    //We know that we are at the last frame. If charLength is 1, the last SYN is in location 3.
    else
        dataField[charLength + 2] = '\x16';

    PhysicalLayer pl;
    pl.Encode(dataField, fileToWriteTo, charLength);
}

//We will call the physical layer to check the parity of all of the characters in the encoded file.
//If we return from the physical layer, then we know all of the parity passed.  Check the frames to
//make sure that the first and last characters are SYN characters.
unsigned char* DataLinkLayer::Deframing(string fileToRead, int fileLength)
{
    PhysicalLayer pl;
    unsigned char *bytes;
    unsigned char currentChar;
    bytes = pl.Decode(fileToRead, fileLength);

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