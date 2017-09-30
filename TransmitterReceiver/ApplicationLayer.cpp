//
// Created by kristopher on 9/30/17.
//

#include "ApplicationLayer.h"
#include "PhysicalLayer.h"

#include <iostream>
#include <string>
#include <fstream>

ApplicationLayer::ApplicationLayer()
{

}

ApplicationLayer::~ApplicationLayer()
{

}

void ApplicationLayer::CommandT(string file1, string file2)
{
    ifstream ifs(file1, ios::in | ios::binary);
    if (ifs.good())
    {
        char character;
        while (ifs.get(character));

    }
    //ofstream ofs(file2, ios::out)
}

void ApplicationLayer::CommandR(string file1, string file2)
{

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

