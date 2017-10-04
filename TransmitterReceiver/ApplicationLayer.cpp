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
//void ApplicationLayer::CommandR(string file1, string file2)
//{
//    ofstream ofs(file2, ios::out | ios::trunc);
//    DataLinkLayer dl;
//    ifstream ifs(file1, ios::in | ios::binary);
//    if (ifs.good())
//    {
//        char character;
//        string frame;
//        int charCount = 0;
//        while (ifs.get(character))
//        {
//            charCount++;
//            frame += character;
//            //Works for ASCII.
//            if (charCount == 88) //SYN + CTRL + Data (Max of 8) + SYN = 88 chars
//            {
//                dl.Deframing(frame, file2, charCount / 8);
//                frame = "";
//                charCount = 0;
//            }
//        }
//        dl.Deframing(frame, file2, charCount / 8);
//    }
//}

void ApplicationLayer::CommandR(string file1, string file2)
{
    ifstream ifs(file1, ios::in | ios::ate);
    int fileLength = ifs.tellg();
    ifs.close();

    DataLinkLayer dl;
    unsigned char *values;
    values = dl.Deframing(file1, fileLength);
    int charLength = fileLength / 8;
    int printableChars = 0;
    int tempFileLength;
    while(charLength > 0)
    {
        tempFileLength = charLength;
        charLength -= 11;
        //In case we don't grab the last non full frame, we need to get the char count of that one.
        if (charLength < 0)
        {
            tempFileLength -= 3;
            printableChars += tempFileLength;
            break;
        }
        tempFileLength -= 11;
        printableChars += 8;
    }
    //Now that we have the entire binary number with parity bits included, write these values to a file.
    ofstream ofs(file2, ios::out | ios::trunc);

    unsigned char character;
    for (int charCount = 0; charCount < printableChars; charCount++)
    {
        character = values[charCount];
        ofs.put(character);
    }
    ofs.flush();
    ofs.close();
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

