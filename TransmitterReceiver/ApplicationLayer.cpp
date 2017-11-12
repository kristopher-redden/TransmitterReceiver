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
void ApplicationLayer::CommandT(string hostname, string fileToReadFrom, int bitToFlip, bool ham, bool clientTransmitting)
{
    DataLinkLayer dl;
    ifstream ifsLeng(fileToReadFrom, ios::in | ios::ate);
    int fileLength = ifsLeng.tellg();
    ifsLeng.close();

    //Open the file and get the data length of the extra frame's.
    ifstream ifs (fileToReadFrom, ios::in | ios::binary);
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

        dl.Framing(chars, hostname, allCharactersInFrame, fullFrames, extraFrameDataLength, bitToFlip, ham, clientTransmitting);

        ifs.close();
    }
    else
        throw 3;
}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandR(string hostname, string fileToWriteTo, bool ham, bool clientTransmitting)
{
    DataLinkLayer dl;
    unsigned char *values;
    values = dl.Deframing(ham, clientTransmitting, hostname);
    int dehammingCharCount = dl.NumberOfPrintableChars();
    ofstream ofs(fileToWriteTo, ios::out | ios::trunc);
    if (ofs.good())
    {
        unsigned char character;

        for (int charToGet = 0; charToGet < dehammingCharCount; charToGet++)
        {
            character = values[charToGet];
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
//    ifstream ifs(file1, ios::in | ios::ate);
//    if (ifs.good())
//    {
//        int fileLength = ifs.tellg();
//        int fullFrames = fileLength / 64;
//        int extraFrameDataLength = fileLength % 64;
//        int allCharactersInFrame = fullFrames * 67 + extraFrameDataLength + 3;
//        srand(time(NULL));
//        ifs.close();
//        //Generate a random number that is between 0 and the fileLength.
//        int bitToFlip = rand() % (allCharactersInFrame * 8);//Each char is made up of 8 1's and 0's.
//        //Generate the file of 1's and 0's.
//        //CommandT(file1, file2, bitToFlip);
//    }
//    else
//        throw 3;
}

void ApplicationLayer::CommandTHam(string hostname, string fileToReadFrom, bool ham, bool clientTransmitting)
{
    CommandT(hostname, fileToReadFrom, -1, ham, clientTransmitting);
}

void ApplicationLayer::CommandRHam(string hostname, string fileToWriteTo, bool ham, bool clientTransmitting)
{
    CommandR(hostname, fileToWriteTo, ham, clientTransmitting);
}

void ApplicationLayer::CommandTCrc(string hostname, string fileToReadFrom, bool ham, bool clientTransmitting)
{
    int bitToFlip = -1;
    DataLinkLayer dl;
    ifstream ifsLeng(fileToReadFrom, ios::in | ios::ate);
    int fileLength = ifsLeng.tellg();
    ifsLeng.close();

    //Open the file and get the data length of the extra frame's.
    ifstream ifs (fileToReadFrom, ios::in | ios::binary);
    if (ifs.good())
    {
        char character;
        //We will have 64 chars in the frame, get the data for 2 - 65.
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

        dl.Framing(chars, hostname, allCharactersInFrame, fullFrames, extraFrameDataLength, bitToFlip, ham, clientTransmitting);

        ifs.close();
    }
    else
        throw 3;
}

void ApplicationLayer::CommandRCrc(string hostname, string fileToWriteTo, bool crc, bool clientTransmitting)
{
    DataLinkLayer dl;
    unsigned char *values;
    //values = dl.Deframing(crc, clientTransmitting, hostname);
    values = dl.DeframingCRC(clientTransmitting, hostname);
    ofstream ofs(fileToWriteTo, ios::out | ios::trunc);
    if (ofs.good())
    {
        unsigned char character;
        int charToGet = 0;
        //Keep doing this until we see a NULL character.
        while (values[charToGet] != '\0')
        {
            character = values[charToGet];
            ofs.put(character);
            charToGet++;
        }

        ofs.flush();
        ofs.close();
    }
    else
        throw 3;
}




