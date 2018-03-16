#include "EDRToneBuffer_GammaLerp.h"

#include <cstdlib>
#include <cmath>

EDRToneBuffer_GammaLerp::EDRToneBuffer_GammaLerp(unsigned int nImages, float gamma, bool interp)
	: nImages(nImages)
	, bufferGamma(gamma)
	, interpEnabled(interp)
{
	images = (void **)malloc(sizeof(void *) * nImages);
	imageExposures = (float *)malloc(sizeof(float) * nImages);
}

EDRToneBuffer_GammaLerp::~EDRToneBuffer_GammaLerp()
{
	free(images);
	free((void *)imageExposures);
}

void EDRToneBuffer_GammaLerp::compute(EDRToneMapper * toneMapper)
{
	if (!toneMapper || !(toneMapper->getImage())) return;

	EDRImage * img = toneMapper->getImage();

	minExposure = 100000000.f, maxExposure = 0.f;

	// Figure out min and max possible exposure values.
	for (unsigned int i = 0; i < img->getWidth(); i++)
	{
		for (unsigned int j = 0; j < img->getHeight(); j++)
		{
			float pixExp = img->getPixelExposure(i, j);

			if (pixExp < minExposure) minExposure = pixExp;
			if (pixExp > maxExposure) maxExposure = pixExp;
		}
	}

	// Split the exposure range into nImages different steps.
	for (unsigned int k = 0; k < nImages; k++)
	{
		// Calculate and store this intermediate level based on gamma.
		float targetExposure = minExposure + (maxExposure - minExposure) * pow((1.f / (nImages - 1)) * k, bufferGamma);
		imageExposures[k] = targetExposure;

		// Tone map to this exposure.
		toneMapper->toneMap(targetExposure);

		// Create an image from the result.
		images[k] = createBufferedImage(img->getWidth(), img->getHeight());
		for (unsigned int i = 0; i < img->getWidth(); i++)
		{
			for (unsigned int j = 0; j < img->getHeight(); j++)
			{
				EDRStandardPixel pixOut = toneMapper->getPixel(i, j);
				setBufferedImagePixel(images[k], i, j, pixOut);
			}
		}
	}
}

void * EDRToneBuffer_GammaLerp::getStandardImage(float targetExposure)
{
	for (unsigned int i = 0; i < nImages; i++)
	{
		if (imageExposures[i] > targetExposure)
		{
			if (i == 0 || !interpEnabled) return images[i];
			
			float alpha = (targetExposure - imageExposures[i - 1]) / (imageExposures[i] - imageExposures[i - 1]);
			return interpImage(images[i - 1], images[i], alpha);
		}
	}

	return images[nImages - 1];
}

bool EDRToneBuffer_GammaLerp::isInterpEnabled() const
{
	return interpEnabled;
}

void EDRToneBuffer_GammaLerp::setInterpEnabled(bool enabled)
{
	interpEnabled = enabled;
}
