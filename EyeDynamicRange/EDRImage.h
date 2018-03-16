/* 
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"

/**
 * Defines an image pixel.
 */
typedef struct
{
	float r;
	float g;
	float b;
} EDRImagePixel;

/**
 * Supported formats of HDR images.
 */
enum EDRImageFormat
{
	Format_EDR,
	Format_HDR
};

/**
 * Represents an HDR image, before tone mapping.
 */
class EDRImage : public EDRObject
{

private:

	EDRImagePixel * img;
	size_t width;
	size_t height;

public:

	EDRImage();
	virtual ~EDRImage();

	void createBlankImage(size_t width, size_t height);

	EDRImagePixel * getRawData() const;
	size_t getWidth() const;
	size_t getHeight() const;

	void setPixel(size_t x, size_t y, EDRImagePixel value);
	EDRImagePixel getPixel(size_t x, size_t y) const;
	EDRImagePixel * getPixRef(size_t x, size_t y) const;

	float getPixelExposure(size_t x, size_t y) const;
	float getPixelExposure(EDRImagePixel pix) const;
};