//
// Created by kristopher on 9/30/17.
//

#include "PhysicalLayer.h"
#include <iostream>
#include <fstream>

PhysicalLayer::PhysicalLayer()
{

}
PhysicalLayer::~PhysicalLayer()
{

}
void PhysicalLayer::Encode(string dataField, string outputFile)
{
    //datafield contains: syn, syn, length, and the data.
    //Works for extended ASCII table.
    string dataFieldInBinary;
    for (int i = 0; i < dataField.length(); i++)
    {
        char tempCharacter = dataField.at(i);
        //ASCII of 0 is 0110000
        //Stored in a byte: 00110000
        //Or with parity to store value.
        int parityCount = 0;
        int value;
        for (int pos = 0; pos < 7; ++pos)//7 times
        {
            value = (int) (tempCharacter >> pos) & 1;
            if (value == 1)
                dataFieldInBinary += "1";
            else dataFieldInBinary += "0";

            if (value == 1)
                parityCount++;
        }
        //Make this odd parity.
        if (parityCount % 2 == 0)
            dataFieldInBinary += "1";
        else
            dataFieldInBinary += "0";
        cout << dataFieldInBinary << endl;
    }

    //Now that we have the entire binary number with parity bits included, write these values to a file.
    ofstream ofs(outputFile, ios::out | ios::app);
    for (int loc = 0; loc < dataFieldInBinary.length(); loc++)
    {
        unsigned char character = (unsigned char) dataFieldInBinary.at(loc);
        ofs.put(character);
    }

}
void PhysicalLayer::Decode(string frame, string outputFile)
{
    string theChar;
    int parityValue;
    int onesCount;
    for (int count = 1; count <= frame.length() / 8; count++)
    {
        //The first bit is 0 since we are only doing ASCII.
        theChar = "0";
        parityValue = frame.at(count * 8 - 1);//This is the last bit of the char.
        for (int position = count * 8 - 2; position >= (count - 1) * 8; position--)
        {
            char tempCharacter = frame.at(position);
            if (tempCharacter == 49)
                onesCount++;
            theChar += tempCharacter;
        }
        //When we find an error..?
        int onesModded = onesCount % 2;
        //We had an odd number of 1's.
        if (parityValue == 0)
        {
            //This is an error.
            if (onesModded == 0)
            {

            }
            else
            {
                //Good.
            }
        }
            //We had an even number of 1's.
        else
        {
            if (onesModded == 0)
            {

            }
            else
            {

            }
        }

    }

}