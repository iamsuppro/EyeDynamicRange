#include "EDRToneMapper_Basic.h"
#include <cmath>

const unsigned int EDRToneMapper_Basic::DRANGE_EV_ABOVE = 6;
const unsigned int EDRToneMapper_Basic::DRANGE_EV_BELOW = 6;

EDRToneMapper_Basic::EDRToneMapper_Basic(EDRImage * img)
	: EDRToneMapper(img)
{
}

EDRToneMapper_Basic::~EDRToneMapper_Basic()
{
}

void EDRToneMapper_Basic::toneMap(size_t x, size_t y, float dt)
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

void EDRToneMapper_Basic::toneMap(float linExposure, float dt)
{
	// Set the linear values for target exposure and dynamic range edges.
	exposure = linExposure;
	range = getDynamicRange();

	// Normalize (0-1) the target exposure value within the dynamic range.
	float exposureNorm = (exposure - range.black) / range.white;

	// Calculate gamma. We want to put the target exposure value halfway in
	// the range. That is, we want the pixel the user is looking at to end
	// up with values around 0.5. Base our gamma correction on the value
	// that does that.

	// exposureNorm ^ gamma = 0.5
	// gamma = log base exposureNorm of 0.5

	gamma = log(0.5) / log(exposureNorm);
}

EDRStandardPixel EDRToneMapper_Basic::getPixel(size_t x, size_t y)
{
	// Set up image pixel and standard (output) pixel.
	EDRImagePixel pIn = img->getPixel(x, y);
	EDRStandardPixel pOut;

	// Tone map each of the three channels independently.
	pOut.r = mapOneChannel(pIn.r);
	pOut.g = mapOneChannel(pIn.g);
	pOut.b = mapOneChannel(pIn.b);

	return pOut;
}

unsigned char EDRToneMapper_Basic::mapOneChannel(float in) const
{
	// Normalize and clamp the input exposure to a value between 0 and 1
	// that represents where that value is (linearly) in the dynamic range.
	float inNorm = (in - range.black) / range.white;
	inNorm = fmin(fmax(0.f, inNorm), 1.f);

	// Gamma correct using the pre-computed gamma value.
	float out = powf(inNorm, gamma);

	return (unsigned char)(out * 255.f);
}

EDRDynamicRange EDRToneMapper_Basic::getDynamicRange() const
{
	EDRDynamicRange r;
	r.white = exposure * (float)(1 << DRANGE_EV_ABOVE);
	r.black = exposure / (float)(1 << DRANGE_EV_BELOW);
	return r;
}
