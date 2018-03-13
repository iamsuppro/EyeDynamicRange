/*
* Created by Jack Boffa on 03/10/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRImageIO.h"

class EDRImageIO_EXR : public EDRImageIO
{

public:

	EDRImageIO_EXR(char * filename);
	~EDRImageIO_EXR();

	virtual EDRImage * loadFromFile() override;


};