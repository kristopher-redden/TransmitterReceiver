//
// Created by kristopher on 9/30/17.
//

#include "DataLinkLayer.h"
#include "PhysicalLayer.h"

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

void DataLinkLayer::Deframing(string frame, string fileToWriteTo)
{
    PhysicalLayer pl;
    pl.Decode(frame, fileToWriteTo);
}