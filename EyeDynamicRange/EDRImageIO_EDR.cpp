/*
* Created by Jack Boffa on 03/08/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRImageIO_EDR.h"
#include <cstdio>
#include <string>

EDRImage * EDRImageIO_EDR::loadFromFile()
{
	int result;

	// Load the file.
	FILE * fp = fopen(filename, "r");

	if (!fp)
	{
		return nullptr;
	}

	// Load the "EDR" string that should be at the beginning, and the size.
	char edr_check[4];
	unsigned int width, height;
	result = fscanf(fp, "%s %u%u", edr_check, &width, &height);

	// Make sure we're reading the right type of file.
	if (result == 3 && strcmp(edr_check, "EDR") != 0)
	{
		fclose(fp);
		return nullptr;
	}
	
	// Create an empty image.
	EDRImage * img = new EDRImage();
	img->createBlankImage(width, height);

	// Read into the image buffer.
	result = fread(img->getRawData(), sizeof(EDRImagePixel), width * height, fp);

	fclose(fp);
	return img;
}

bool EDRImageIO_EDR::saveToFile(EDRImage * img)
{
	int result;

	// Create the file.
	FILE * fp = fopen(filename, "w");

	if (!fp)
	{
		return false;
	}

	unsigned int width = img->getWidth();
	unsigned int height = img->getHeight();

	// Write the EDR string and the size.
	result = fwrite("EDR ", sizeof(char), 4, fp);
	result += fwrite(&width, sizeof(size_t), 1, fp);
	result += fwrite(&height, sizeof(size_t), 1, fp);

	if (result < 6)
	{
		fclose(fp);
		return false;
	}

	// Write the buffer.
	result = fwrite(img->getRawData(), sizeof(EDRImagePixel), img->getWidth() * img->getHeight(), fp);

	fclose(fp);
	return result == img->getWidth() * img->getHeight();
}
