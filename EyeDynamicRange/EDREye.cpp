/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDREye.h"
#include <cmath>

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
		int windowSize = 20;
		int n = 0;
		float exposureTotal = 0.f;

		for (unsigned int i = fmax(0, x - windowSize); i < fmin(x + windowSize, img->getWidth()); i++)
		{
			for (unsigned int j = fmax(0, y - windowSize); j < fmin(y + windowSize, img->getHeight()); j++)
			{
				exposureTotal += img->getPixelExposure(i, j);
				n++;
			}
		}

		exposure = exposureTotal / n;
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
