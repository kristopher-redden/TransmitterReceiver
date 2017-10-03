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

void DataLinkLayer::Deframing(string frame, string fileToWriteTo, int charCount)
{
    PhysicalLayer pl;
    unsigned char *bytes;
    unsigned char currentChar;
    bytes = pl.Decode(frame, fileToWriteTo, charCount);
    if (bytes == nullptr)
    {
        //We are done, don't print anything because the frame contained a parity that failed.
    }
    else
    {
        unsigned char firstSYN = bytes[0];
        unsigned char lastSYN = bytes[charCount - 1];
        unsigned char ctrl = bytes[1];
        //We have an invalid frame because we don't have two SYN characters.
        if (firstSYN != syn || lastSYN != syn)
        {
            cerr << "We have an invalid frame.  No SYN characters present";
            return;
        }
        //We have a valid frame, construct the data to print.
        string print;
        for (int i = 2; i < charCount - 1; i++)
        {
            currentChar = bytes[i];
            print += currentChar;
        }
        Print(print, fileToWriteTo);
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