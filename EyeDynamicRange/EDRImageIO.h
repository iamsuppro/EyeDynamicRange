/*
* Created by Jack Boffa on 03/08/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"
#include "EDRImage.h"

class EDRImageIO : public EDRObject
{

protected:

	char * filename;
	
public:

	EDRImageIO(char * filename);
	~EDRImageIO();

	virtual EDRImage * loadFromFile();
	virtual bool saveToFile(EDRImage * img);
};