#include "EDRToneMapper_DR.h"
#include <cmath>

EDRToneMapper_DR::EDRToneMapper_DR(EDRImage * img)
	: EDRToneMapper(img)
	, exposure(0.f)
	, gamma(0.f)
	, currentRangeLin(0.f, 0.f)
	, eyeRangeStops(4.f, 4.f)
{
}

EDRToneMapper_DR::~EDRToneMapper_DR()
{
}

void EDRToneMapper_DR::toneMap(float linExposure)
{
	// Set the linear values for target exposure and dynamic range edges.
	exposure = linExposure;
	currentRangeLin = calcDynamicRangeLin();

	// Normalize (0-1) the target exposure value within the dynamic range.
	float exposureNorm = (exposure - currentRangeLin.black) / (currentRangeLin.white - currentRangeLin.black);

	// Calculate the value used for gamma correction.
	gamma = calcGamma(exposureNorm);
}

EDRStandardPixel EDRToneMapper_DR::getPixel(size_t x, size_t y)
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

float EDRToneMapper_DR::getTargetExposure() const
{
	return exposure;
}

EDRDynamicRange EDRToneMapper_DR::getCurrentRangeLin() const
{
	return currentRangeLin;
}

EDRDynamicRange EDRToneMapper_DR::getEyeRangeFStops() const
{
	return eyeRangeStops;
}

void EDRToneMapper_DR::setEyeRangeFStops(float fStopsBelow, float fStopsAbove)
{
	eyeRangeStops.black = fStopsBelow;
	eyeRangeStops.white = fStopsAbove;
}

float EDRToneMapper_DR::getGamma() const
{
	return gamma;
}

unsigned char EDRToneMapper_DR::mapOneChannel(float in) const
{
	// Normalize and clamp the input exposure to a value between 0 and 1
	// that represents where that value is (linearly) in the dynamic range.
	float inNorm = (in - currentRangeLin.black) / (currentRangeLin.white - currentRangeLin.black);
	inNorm = fmin(fmax(0.f, inNorm), 1.f);

	// Gamma correct using the pre-computed gamma value.
	float out = powf(inNorm, gamma);

	return (unsigned char)(out * 255.f);
}

EDRDynamicRange EDRToneMapper_DR::calcDynamicRangeLin() const
{
	EDRDynamicRange r;
	r.white = exposure * pow(2.f, eyeRangeStops.white);
	r.black = exposure / pow(2.f, eyeRangeStops.black);
	return r;
}

float EDRToneMapper_DR::calcGamma(float exposureNorm) const
{
	// Calculate gamma. We want to put the target exposure value halfway in
	// the range. That is, we want the pixel the user is looking at to end
	// up with values around 0.5. Base our gamma correction on the value
	// that does that.

	// exposureNorm ^ gamma = 0.5
	// gamma = log base exposureNorm of 0.5

	return log(0.5) / log(exposureNorm);
}