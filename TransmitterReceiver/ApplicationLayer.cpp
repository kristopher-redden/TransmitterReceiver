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

////file1 is the file to read from, file2 is the file to write to.
//void ApplicationLayer::CommandT(string file1, string file2)
//{
//    //Clear out the file in case it exists, this way we can simply append to it later on.
//    ofstream ofs(file2, ios::out | ios::trunc);
//    DataLinkLayer dl;
//    ifstream ifs(file1, ios::in | ios::binary);
//    if (ifs.good())
//    {
//        char character;
//        string dataField;
//        int charCount = 0;
//        while (ifs.get(character))
//        {
//            charCount++;
//            dataField += character;
//            //Works for ASCII.
//            if (charCount == 8)
//            {
//                dl.Framing(dataField, file2);
//                dataField = "";
//                charCount = 0;
//            }
//        }
//        dl.Framing(dataField, file2);
//    }
//}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandT(string file1, string file2)
{
    //Clear out the file in case it exists, this way we can simply append to it later on.
    ofstream ofs(file2, ios::out | ios::trunc);
    DataLinkLayer dl;
    ifstream ifsLeng(file1, ios::in | ios::ate);
    int fileLength = ifsLeng.tellg();
    ifsLeng.close();

    ifstream ifs (file1, ios::in | ios::binary);
    int fullFrameLength = fileLength / 8;
    int extraFrameLength = fileLength % 8;
    if (ifs.good())
    {
        char character;
        unsigned char *chars = new unsigned char[11];
        int charCount = 0;
        while (ifs.get(character))
        {
            //Location 0 and 1 is SYN and ctrl, location 11 is the other SYN Char.
            chars[charCount + 2] = character;
            charCount++;
            //Works for ASCII.
            if (charCount == 8)
            {
                dl.Framing(chars, file2, 8);
                charCount = 0;
            }
        }
        //Copy the chars to a new byte array.
        unsigned char *smallChars = new unsigned char[extraFrameLength + 3];
        for (int smallCount = 0; smallCount < extraFrameLength; smallCount++)
        {
            smallChars[smallCount + 2] = chars[smallCount + 2];
        }
        dl.Framing(smallChars, file2, extraFrameLength);
        ifs.close();
    }
}
//file1 is the file to read from, file2 is the file to write to.
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

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandTWithError(string file1, string file2)
{
    ifstream ifs(file1, ios::in | ios::ate);
    int fileLength = ifs.tellg();
    ifs.close();

    int toggleFirstBit = rand() % fileLength;
    int toggleSecondBit = rand() % fileLength;
    int toggleThirdBit = rand() % fileLength;
}


