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
void DataLinkLayer::Framing(unsigned char* allData, string fileToWriteTo, int allCharsInFrame, int fullFrames, int extraFrameDataLength, int bitToFlip)
{
    unsigned char *frames = new unsigned char[allCharsInFrame];
    for (int loc = 0; loc < fullFrames; loc++)
    {
        frames[loc * 67] = '\x16';
        frames[loc * 67 + 1] = (unsigned char) 64;
        for (int characterLoc = 0; characterLoc < 64; characterLoc++)
        {
            //Initially it will be 2 - 65.
            //Offset by 2 handles the SYN and CTRL.
            frames[loc * 67 + characterLoc + 2] = allData[loc * 64 + characterLoc];
        }
        frames[(loc + 1) * 67 - 1] = '\x16';
    }
    //Now that we have taken care of the full frames, do the last smaller frame.
    frames[fullFrames * 67] = '\x16';
    frames[fullFrames * 67 + 1] = (unsigned char) extraFrameDataLength;

    for (int charLocation = 0; charLocation < extraFrameDataLength; charLocation++)
    {
        //Offset by 2 handles the SYN and CTRL.
        frames[fullFrames * 67 + charLocation + 2] = allData[fullFrames * 64 + charLocation];
    }
    frames[fullFrames * 67 + extraFrameDataLength + 2] = '\x16';

    PhysicalLayer pl;
    pl.Encode(frames, fileToWriteTo, allCharsInFrame, bitToFlip);
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