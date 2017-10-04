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

//void DataLinkLayer::Framing(string dataField, string fileToWriteTo)
//{
//    string theFrame;
//
//    theFrame += '\x16'; //static_cast<char>(22);
//    theFrame += (unsigned char)dataField.length();
//    theFrame += dataField;
//    theFrame += '\x16';
//
//    PhysicalLayer pl;
//    pl.Encode(theFrame, fileToWriteTo);
//}

void DataLinkLayer::Framing(unsigned char* dataField, string fileToWriteTo, int charLength)
{
    string theFrame;
    //We know that we have a full frame.
    dataField[0] = '\x16';
    dataField[1] = (unsigned char) charLength;
    if (charLength == 8)
        dataField[10] = '\x16';
    //We know that we are at the last frame. If charLength is 1, the last SYN is in location 3.
    else
        dataField[charLength + 2] = '\x16';

    PhysicalLayer pl;
    pl.Encode(dataField, fileToWriteTo, charLength);
}

unsigned char* DataLinkLayer::Deframing(string fileToRead, int fileLength)
{
    PhysicalLayer pl;
    unsigned char *bytes;
    unsigned char currentChar;
    bytes = pl.Decode(fileToRead, fileLength);

    int fullFrameCount = fileLength / 88;
    int lastFrameLength = fileLength % 88 / 8;
    int lastFrameChecked;
    unsigned char *bytesToWriteToFile = new unsigned char[fullFrameCount * 8 + lastFrameLength - 3];
    int bytesToWriteIndex = 0;
    if (bytes == nullptr)
    {
        return nullptr;
        //We are done, there was an error when checking the parity.
    }
    //If all the parity checked out, being the deframing.
    else
    {
        unsigned char firstSYN;
        unsigned char lastSYN;
        unsigned char ctrl;
        for (int fullFrames = 0; fullFrames < fullFrameCount; fullFrames++)
        {
            firstSYN = bytes[fullFrames * 11];
            lastSYN = bytes[(fullFrames + 1) * 11 - 1];
            ctrl = bytes[fullFrames * 11 + 1];

            //If the first and last character of a frame are not a SYN, then we have an invalid frame.
            if (firstSYN != syn || lastSYN != syn)
            {
                string error = "Frame: " + to_string(fullFrames) + " does not have a starting and ending SYN";
                cerr << error;
            }
            lastFrameChecked = fullFrames;
            //Otherwise, we have a valid frame, construct the data to print.
            for (int partOfFrame = 0; partOfFrame < 8; partOfFrame++)
            {
                bytesToWriteToFile[bytesToWriteIndex] = bytes[fullFrames * 11 + 2 + partOfFrame];
                bytesToWriteIndex++;
            }
        }
        //We have a frame that is not the full length.  We know the previous frame we checked, so go to the next one that doesn't have a full length.
        if (lastFrameLength != 0)
        {
            firstSYN = bytes[(lastFrameChecked + 1) * 11];
            lastSYN = bytes[(lastFrameChecked + 1) * 11 + lastFrameLength - 1];
            ctrl = bytes[(lastFrameChecked + 1) * 11 + 1];
            //If the first and last character of a frame are not a SYN, then we have an invalid frame.
            if (firstSYN != syn || lastSYN != syn)
            {
                string error = "Frame: " + to_string(lastFrameChecked + 1) + " does not have a starting and ending SYN";
                cerr << error;
            }
            //Otherwise, we have a valid frame, construct the data to print.
            for (int partOfFrame = 0; partOfFrame < lastFrameLength - 3; partOfFrame++)
            {
                bytesToWriteToFile[bytesToWriteIndex] = bytes[(lastFrameChecked + 1) * 11 + 2 + partOfFrame];
                bytesToWriteIndex++;
            }
        }
        return bytesToWriteToFile;
    }

}

void DataLinkLayer::Print(string value, string file)
{
    //Now that we have the entire data part of the frame, write these chars to a file.
    ofstream ofs(file, ios::out | ios::app);
    for (int loc = 0; loc < value.length(); loc++)
    {
        unsigned char character = (unsigned char) value.at(loc);
        ofs.put(character);
    }
    ofs.flush();
    ofs.close();
}