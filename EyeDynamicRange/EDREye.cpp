/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDREye.h"

EDREye::EDREye(EDRImage * img, EDRToneMapper * mapper, EDRToneBuffer * buffer)
	: img(img)
	, mapper(mapper)
	, buffer(buffer)
{
}

EDREye::~EDREye()
{
}

void EDREye::precomputeExposures()
{
	// If we're using a buffer, tell it to do some computation.
	if (mapper && buffer)
	{
		buffer->compute(mapper);
	}
}

void EDREye::adapt(size_t x, size_t y, float dt)
{
	if (img)
	{
		// Basic implementation that sets the target exposure to exactly
		// the level of the given pixel.
		EDRImagePixel pix = img->getPixel(x, y);
		exposure = (pix.r + pix.g + pix.b) / 3.f;
	}
}

void * EDREye::getStandardImage()
{
	// This EDREye base class only returns anything if a buffer is attached.
	if (buffer)
	{
		return buffer->getStandardImage(exposure);
	}

	return nullptr;
}

float EDREye::getTargetExposure() const
{
	return exposure;
}
