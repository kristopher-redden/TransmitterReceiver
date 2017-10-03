//
// Created by kristopher on 9/30/17.
//

#include "ApplicationLayer.h"
#include "PhysicalLayer.h"
#include "DataLinkLayer.h"

#include <iostream>
#include <string>
#include <fstream>

ApplicationLayer::ApplicationLayer()
{

}

ApplicationLayer::~ApplicationLayer()
{

}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandT(string file1, string file2)
{
    //Clear out the file in case it exists, this way we can simply append to it later on.
    ofstream ofs(file2, ios::out | ios::trunc);
    DataLinkLayer dl;
    ifstream ifs(file1, ios::in | ios::binary);
    if (ifs.good())
    {
        char character;
        string dataField;
        int charCount = 0;
        while (ifs.get(character))
        {
            charCount++;
            dataField += character;
            //Works for ASCII.
            if (charCount == 8)
            {
                dl.Framing(dataField, file2);
                dataField = "";
                charCount = 0;
            }
        }
        dl.Framing(dataField, file2);
    }
}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandR(string file1, string file2)
{
    ofstream ofs(file2, ios::out | ios::trunc);
    DataLinkLayer dl;
    ifstream ifs(file1, ios::in | ios::binary);
    if (ifs.good())
    {
        char character;
        string frame;
        int charCount = 0;
        while (ifs.get(character))
        {
            charCount++;
            frame += character;
            //Works for ASCII.
            if (charCount == 88) //SYN + CTRL + Data (Max of 8) + SYN = 88 chars
            {
                dl.Deframing(frame, file2, charCount / 8);
                frame = "";
                charCount = 0;
            }
        }
        dl.Deframing(frame, file2, charCount / 8);
    }
}

void ApplicationLayer::CommandTWithError(string file1, string file2)
{

}

void ApplicationLayer::CommandTAndR(string file1, string file2, string file3)
{

}

void ApplicationLayer::CommandTRAndError(string file1, string file2)
{

}

