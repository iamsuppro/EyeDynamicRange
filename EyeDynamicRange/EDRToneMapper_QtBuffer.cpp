/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRToneMapper_QtBuffer.h"

EDRToneMapper_QtBuffer::EDRToneMapper_QtBuffer(EDRToneMapper * mapper)
	: EDRToneMapper(mapper->getImage())
	, mapper(mapper)
	, gamma(0.5)
	, useGammaMap(true)
{
}

EDRToneMapper_QtBuffer::~EDRToneMapper_QtBuffer()
{
}

void EDRToneMapper_QtBuffer::precomputeQImages()
{
	if (!mapper) return;

	minExposure = 100000000.f, maxExposure = 0.f;

	// Figure out min and max possible exposure values.
	for (unsigned int i = 0; i < img->getWidth(); i++)
	{
		for (unsigned int j = 0; j < img->getHeight(); j++)
		{
			EDRImagePixel pix = img->getPixel(i, j);
			float pixExp = (pix.r + pix.g + pix.b) / 3.f;

			if (pixExp < minExposure) minExposure = pixExp;
			if (pixExp > maxExposure) maxExposure = pixExp;
		}
	}

	// Split the exposure range into QTBUFFER_NUM_IMAGES different steps.
	for (unsigned int k = 0; k < QTBUFFER_NUM_IMAGES; k++)
	{
		float targetExposure;

		if (useGammaMap)
		{
			targetExposure = minExposure + (maxExposure - minExposure) * pow((1.f / (QTBUFFER_NUM_IMAGES - 1)) * k, gamma);
		}
		else
		{
			targetExposure = minExposure + ((maxExposure - minExposure) / (QTBUFFER_NUM_IMAGES - 1)) * k;
		}

		// Tone map to this exposure. Can't do anything time-based.
		mapper->toneMap(targetExposure, 0.f);

		// Create a QImage from the result.
		images[k] = QImage(img->getWidth(), img->getHeight(), QImage::Format::Format_ARGB32);
		for (unsigned int i = 0; i < img->getWidth(); i++)
		{
			for (unsigned int j = 0; j < img->getHeight(); j++)
			{
				EDRStandardPixel pixOut = mapper->getPixel(i, j);
				images[k].setPixelColor(i, j, QColor(pixOut.r, pixOut.g, pixOut.b));
			}
		}
	}
}

void EDRToneMapper_QtBuffer::toneMap(size_t x, size_t y, float dt)
{
	int windowSize = 10;
	int n = 0;
	float exposureTotal = 0.f;

	for (unsigned int i = fmax(0, x - windowSize); i < fmin(x + windowSize, img->getWidth()); i++)
	{
		for (unsigned int j = fmax(0, y - windowSize); j < fmin(y + windowSize, img->getHeight()); j++)
		{
			EDRImagePixel pix = img->getPixel(x, y);
			exposureTotal += (pix.r + pix.g + pix.b) / 3.f;
			n++;
		}
	}

	exposure = exposureTotal / n;
	toneMap(exposure, dt);
}

void EDRToneMapper_QtBuffer::toneMap(float linExposure, float dt)
{
	// Figure out where between the lowest and highest exposure we are, normalized.
	float minmaxrange = (exposure - minExposure) / maxExposure;
	minmaxrange = fmin(fmax(0.f, minmaxrange), 1.f);

	if (useGammaMap) minmaxrange = pow(minmaxrange, gamma);

	unsigned int bucket = (unsigned int)(minmaxrange * (QTBUFFER_NUM_IMAGES - 1));
	imageOut = images[bucket];
}

EDRStandardPixel EDRToneMapper_QtBuffer::getPixel(size_t x, size_t y)
{
	return EDRStandardPixel();
}

EDRToneMapper * EDRToneMapper_QtBuffer::getWrappedMapper() const
{
	return mapper;
}

void EDRToneMapper_QtBuffer::setWrappedMapper(EDRToneMapper * mapper)
{
	this->mapper = mapper;
}

void EDRToneMapper_QtBuffer::setImage(EDRImage * newImg)
{
	EDRToneMapper::setImage(newImg);
	mapper->setImage(newImg);
}

QImage EDRToneMapper_QtBuffer::getToneMappedImage() const
{
	return imageOut;
}
