/*
* Created by Jack Boffa on 03/10/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRImageIO_EXR.h"
#include "ImfImageIO.h"
#include "ImfRgbaFile.h"
#include "ImfRgba.h"
#include "ImathBox.h"

using namespace Imf_2_2;

EDRImageIO_EXR::EDRImageIO_EXR(char * filename)
	: EDRImageIO(filename)
{
}

EDRImageIO_EXR::~EDRImageIO_EXR()
{
}

EDRImage * EDRImageIO_EXR::loadFromFile()
{
	// Load the EXR file.
	RgbaInputFile file(filename);
	Imath_2_2::Box2i dw = file.dataWindow();
	size_t width = dw.max.x - dw.min.x + 1;
	size_t height = dw.max.y - dw.min.y + 1;

	// Create an empty EDRImage.
	EDRImage * img = new EDRImage();
	img->createBlankImage(width, height);
	
	// Create a temporary buffer for converting to EDRImagePixels.
	Rgba * stager = (Rgba *) malloc(sizeof(Rgba) * width * height);
	file.setFrameBuffer(stager, 1, width);
	file.readPixels(dw.min.y, dw.max.y);

	// Read a horizontal line from the EXR into the buffer.
	for (unsigned int i = 0; i < width * height; i++)
	{
		EDRImagePixel * impix = img->getRawData() + i;
		impix->r = (float)stager[i].r;
		impix->g = (float)stager[i].g;
		impix->b = (float)stager[i].b;
	}

	free(stager);
	
	return img;
}
