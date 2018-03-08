/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRImageIO.h"

class EDRImageIO_EDR : public EDRImageIO
{

public:

	virtual EDRImage * loadFromFile() override;
	virtual bool saveToFile(EDRImage * img) override;

};