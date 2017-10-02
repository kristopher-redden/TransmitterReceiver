//
// Created by kristopher on 9/30/17.
//

#include "PhysicalLayer.h"
#include <iostream>

PhysicalLayer::PhysicalLayer()
{

}
PhysicalLayer::~PhysicalLayer()
{

}
void PhysicalLayer::Encode(string dataField, string outputFile)
{
    //Works for extended ASCII table.
    string dataFieldInBinary;
    bool fullChars = false;
    for (int i = 0; i < dataField.length(); i++)
    {
        char tempCharacter = dataField.at(i);
        //ASCII of 0 is 0110000
        //Stored in a byte: 00110000
        //Or with parity to store value.
        int value;
        //Generate the 56 bits that are needed for transmission.
        for (int pos = 7; pos >= 0; pos--)//8 times
        {
            value = (int) (tempCharacter >> pos) & 1;
            if (value == 1)
                dataFieldInBinary += "1";
            else dataFieldInBinary += "0";
        }
    }
    //Append parity bits to the correct locations.
    int parityCount = 0;
    string dataFieldWithParity;
    for (int offset = 1, letter = 6, numOfRuns = 0; numOfRuns < dataFieldInBinary.length() / 7;offset++, letter--, numOfRuns++)
    {
        //If buffer isn't zero, do this. Otherwise we don't have a set of 7 numbers.
        //Implement this still.
        //Iterate through this letter "count" number of times.
        for (int count = letter, end = 1; count >= 0; count--, end++)
        {
            int bitToComp = dataFieldInBinary.at(offset * 8 - end);
            //49 is the ASCII value of "1".
            if (bitToComp == 49)
                parityCount++;
            dataFieldWithParity += bitToComp;
        }

        //Add the parity bit and then reset the count.
        if (parityCount % 2 == 0)
            dataFieldWithParity += "1";
        else
            dataFieldWithParity += "0";
        parityCount = 0;

        //Tack on the rest of the current letter. At most we have 7 letters.
        if (offset < 8)
        {
            for (int leftOver = offset; leftOver > 0; leftOver--)
            {
                int restOfBits = dataFieldInBinary.at((offset - 1) * 8 + leftOver - 1);
                if (restOfBits == 49)
                    parityCount++;
                dataFieldWithParity += restOfBits;
            }
        }
    }
    //We've copied over the last char, pad (if needed) check the parity of the last item.
    int padding = dataFieldWithParity.length() % 8;
    //If we had 7 chars, then we filled the data field completly already.
    if (padding != 0)
    {
        //There is a need to pad if we didn't have 7 chars.
        int padWith = 7 - padding ;
        for (int pad = 0; pad < padWith; pad++)
            dataFieldWithParity += "0";
        if (parityCount % 2 == 0)
            dataFieldWithParity += "1";
        else
            dataFieldWithParity += "0";
    }
    cout << "Data field with pairty: " + dataFieldWithParity << endl;
}
void PhysicalLayer::Decode(char character)
{

}