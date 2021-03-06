/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"
#include "EDRImage.h"

/**
 * Stores an RGB pixel with values from 0-255.
 */
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} EDRStandardPixel;


/**
 * Abstract super-class for an object that performs tone-mapping from a high
 * dynamic range EDRImage to standard dynamic range values.
 */
class EDRToneMapper : public EDRObject
{

protected:

	EDRImage * img;

protected:

	EDRToneMapper(EDRImage * img);

public:

	virtual ~EDRToneMapper();

	/**
	 * Configure the tone mapper for a specified exposure value. This value is
	 * linear and corresponds to the pixel brightness level of the EDRImage that
	 * should be perfectly exposed.
	 */
	virtual void toneMap(float linExposure) = 0;

	/**
	 * Get a tone-mapped pixel at the specified position.
	 */
	virtual EDRStandardPixel getPixel(size_t x, size_t y) = 0;

	virtual EDRImage * getImage();
	virtual void setImage(EDRImage * newImg);
};