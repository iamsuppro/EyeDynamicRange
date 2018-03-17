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
	, exposure(1.f)
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
		exposure = img->getPixelExposure(x, y);
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

EDRImage * EDREye::getEDRImage() const
{
	return img;
}

void EDREye::setEDRImage(EDRImage * img)
{
	this->img = img;
}

EDRToneMapper * EDREye::getToneMapper() const
{
	return mapper;
}

void EDREye::setToneMapper(EDRToneMapper * mapper)
{
	this->mapper = mapper;
}

EDRToneBuffer * EDREye::getBuffer() const
{
	return buffer;
}

void EDREye::setBuffer(EDRToneBuffer * buffer)
{
	this->buffer = buffer;
}
