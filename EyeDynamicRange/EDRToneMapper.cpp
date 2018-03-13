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

void EDRToneMapper::toneMap(size_t x, size_t y, float dt)
{
	// Get the pixel at the specified position and calculate desired
	// exposure as the average of the 3 color channels.
	EDRImagePixel pix = img->getPixel(x, y);
	float exposure = (pix.r + pix.g + pix.b) / 3.f;

	// Tone map to this exposure level.
	toneMap(exposure, dt);
}

EDRImage * EDRToneMapper::getImage()
{
	return img;
}

void EDRToneMapper::setImage(EDRImage * newImg)
{
	img = newImg;
}
