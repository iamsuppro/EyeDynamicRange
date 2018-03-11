#include "EDRImageIO_EXR.h"
#include "ImfImageIO.h"
#include "ImfRgbaFile.h"
#include "ImfRgba.h"
#include "ImathBox.h"

using namespace Imf_2_2;

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
	
	// Create a temporary buffer for converting to EDRImagePixels, one scanline at a time.
	Rgba * stager = (Rgba *) malloc(sizeof(Rgba) * width);
	file.setFrameBuffer(stager, 1, width);

	// Read a horizontal line from the EXR into the buffer.
	for (unsigned int j = 0; j < height; j++)
	{
		file.readPixels((signed)j);

		// Copy and convert the buffer pixels to EDRImagePixels.
		for (unsigned int i = 0; i < width; i++)
		{
			EDRImagePixel pix = { (float)stager[i].r, (float)stager[i].g, (float)stager[i].b };
			img->setPixel(i, j, pix);
		}
	}
	
	return img;
}
