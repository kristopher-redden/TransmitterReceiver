//
// Created by kristopher on 9/30/17.
//

#include "ApplicationLayer.h"
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
void ApplicationLayer::CommandT(string file1, string file2, int bitToFlip, bool ham, bool clientTransmitting)
{
    file1 = "/home/kristopher/Documents/TestTextFile/ZeroToNine.txt";
    //Clear out the file in case it exists, this way we can simply append to it later on.
    //ofstream ofs(file2, ios::out | ios::trunc);
    DataLinkLayer dl;
    ifstream ifsLeng(file1, ios::in | ios::ate);
    int fileLength = ifsLeng.tellg();
    ifsLeng.close();

    //Open the file and get the data length of the extra frame's.
    ifstream ifs (file1, ios::in | ios::binary);
    int extraFrameCharLength = fileLength % 64;
    if (ifs.good())
    {
        char character;
        //We will have 131 chars in the frame, get the data for 2 - 130.
        int fullFrames = fileLength / 64;
        int extraFrameDataLength = fileLength % 64;
        int allCharactersInFrame = fullFrames * 67 + extraFrameDataLength + 3;
        int onlyDataCharacters = fullFrames * 64 + extraFrameDataLength;
        unsigned char *chars = new unsigned char[onlyDataCharacters];
        int charCount = 0;
        while (ifs.get(character))
        {
            //Location 0 and 1 is SYN and ctrl, location 66 is the other SYN Char.
            chars[charCount] = character;
            charCount++;
        }

        dl.Framing(chars, file2, allCharactersInFrame, fullFrames, extraFrameDataLength, bitToFlip, ham, clientTransmitting);

        ifs.close();
    }
    else
        throw 3;
}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandR(string file1, string file2, bool ham, bool clientTransmitting)
{
    //ifstream ifs(file1, ios::in | ios::ate);
    int fileLength = 100;//ifs.tellg();
    //ifs.close();
    //if (fileLength == -1)
        //throw 3;
    DataLinkLayer dl;
    unsigned char *values;
    values = dl.Deframing(file1, fileLength, ham, clientTransmitting);
    //Grab the number of chars that will make up the decoded file.

    int charLength = fileLength / 8;
    int printableChars = 0;
    int tempFileLength;
    while(charLength > 0)
    {
        tempFileLength = charLength;
        charLength -= 67;
        //In case we don't grab the last non full frame, we need to get the char count of that one.
        if (charLength < 0)
        {
            tempFileLength -= 3;
            printableChars += tempFileLength;
            break;
        }
        //We've accounted for the frame, but we will only print 64 chars from the frame.
        tempFileLength -= 67;
        printableChars += 64;
    }
    //We have all of the chars, write them to the file.
    ofstream ofs(file2, ios::out | ios::trunc);
    if (ofs.good())
    {
        unsigned char character;
        for (int charCount = 0; charCount < printableChars; charCount++)
        {
            character = values[charCount];
            ofs.put(character);
        }
        ofs.flush();
        ofs.close();
    }
    else
        throw 3;

}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandTWithError(string file1, string file2)
{
    ifstream ifs(file1, ios::in | ios::ate);
    if (ifs.good())
    {
        int fileLength = ifs.tellg();
        int fullFrames = fileLength / 64;
        int extraFrameDataLength = fileLength % 64;
        int allCharactersInFrame = fullFrames * 67 + extraFrameDataLength + 3;
        srand(time(NULL));
        ifs.close();
        //Generate a random number that is between 0 and the fileLength.
        int bitToFlip = rand() % (allCharactersInFrame * 8);//Each char is made up of 8 1's and 0's.
        //Generate the file of 1's and 0's.
        //CommandT(file1, file2, bitToFlip);
    }
    else
        throw 3;
}

void ApplicationLayer::CommandTHam(string file1, string file2, bool ham, bool clientTransmitting)
{
    CommandT(file1, file2, -1, ham, clientTransmitting);
}

void ApplicationLayer::CommandRHam(string file1, string file2, bool ham, bool clientTransmitting)
{
    CommandR(file1, file2, true, false);
}




