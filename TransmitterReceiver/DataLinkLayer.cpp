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
    theFrame += '\x16';
    theFrame += (unsigned char)dataField.length();
    //theFrame += reinterpret_cast<unsigned char&>(22);
    //theFrame += reinterpret_cast<unsigned char&>(22);
    //theFrame += reinterpret_cast<unsigned char&>(dataField.length());  //Cast ignoring semantics.
    //theFrame += syn + syn + dfLength;
    theFrame += dataField;
    PhysicalLayer pl;
    pl.Encode(theFrame, fileToWriteTo);
}