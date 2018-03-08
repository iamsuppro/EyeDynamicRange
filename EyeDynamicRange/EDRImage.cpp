/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRImage.h"
#include <cstdlib>

EDRImage::EDRImage()
	: img(nullptr)
	, width(0)
	, height(0)
{
}

EDRImage::~EDRImage()
{
	if (img)
		free(img);
}

void EDRImage::createBlankImage(size_t width, size_t height)
{
	// Delete the old image.
	if (img)
		free(img);

	// Create a new empty image with width*height pixels.
	img = (EDRImagePixel *) malloc(width * height * sizeof(EDRImagePixel));
	this->width = width;
	this->height = height;
}

EDRImagePixel * EDRImage::getRawData() const
{
	return img;
}

size_t EDRImage::getWidth() const
{
	return width;
}

size_t EDRImage::getHeight() const
{
	return height;
}

void EDRImage::setPixel(size_t x, size_t y, EDRImagePixel value)
{
	*getPixRef(x, y) = value;
}

EDRImagePixel EDRImage::getPixel(size_t x, size_t y) const
{
	return *(img + (width * y) + x);
}

EDRImagePixel * EDRImage::getPixRef(size_t x, size_t y) const
{
	return img + (width * y) + x;
}
