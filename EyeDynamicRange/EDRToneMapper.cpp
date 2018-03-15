/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRToneMapper.h"

EDRToneMapper::EDRToneMapper(EDRImage * img)
{
	this->img = img;
}

EDRToneMapper::~EDRToneMapper()
{
}

EDRImage * EDRToneMapper::getImage()
{
	return img;
}

void EDRToneMapper::setImage(EDRImage * newImg)
{
	img = newImg;
}
