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

void DataLinkLayer::Framing(string dataField, string fileToWriteTo)
{
    string theFrame;

    theFrame += '\x16'; //static_cast<char>(22);
    theFrame += (unsigned char)dataField.length();
    //int dataLeng = (unsigned char)dataField.length();
    theFrame += dataField;
    theFrame += '\x16';

    PhysicalLayer pl;
    pl.Encode(theFrame, fileToWriteTo);
}

//void DataLinkLayer::Deframing(string frame, string fileToWriteTo, int charCount)
//{
//    PhysicalLayer pl;
//    unsigned char *bytes;
//    unsigned char currentChar;
//    bytes = pl.Decode(frame, fileToWriteTo, charCount);
//    if (bytes == nullptr)
//    {
//        //We are done, don't print anything because the frame contained a parity that failed.
//    }
//    else
//    {
//        unsigned char firstSYN = bytes[0];
//        unsigned char lastSYN = bytes[charCount - 1];
//        unsigned char ctrl = bytes[1];
//        //We have an invalid frame because we don't have two SYN characters.
//        if (firstSYN != syn || lastSYN != syn)
//        {
//            cerr << "We have an invalid frame.  No SYN characters present";
//            return;
//        }
//        //We have a valid frame, construct the data to print.
//        string print;
//        for (int i = 2; i < charCount - 1; i++)
//        {
//            currentChar = bytes[i];
//            print += currentChar;
//        }
//        Print(print, fileToWriteTo);
//    }
//}

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