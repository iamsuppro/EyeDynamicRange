/*
* Created by Jack Boffa on 03/08/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRImageIO.h"

class EDRImageIO_EXR : public EDRImageIO
{

public:

	virtual EDRImage * loadFromFile() override;

};