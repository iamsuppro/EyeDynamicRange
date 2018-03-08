/*
* Created by Jack Boffa on 03/08/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRImageIO.h"

EDRImageIO::EDRImageIO(char * filename)
{
	this->filename = filename;
}

EDRImageIO::~EDRImageIO()
{
}

EDRImage * EDRImageIO::loadFromFile()
{
	return nullptr;
}

bool EDRImageIO::saveToFile(EDRImage * img)
{
	return false;
}
