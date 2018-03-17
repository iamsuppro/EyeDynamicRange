#include "EDREye_Physical.h"
#include <cmath>

EDREye_Physical::EDREye_Physical(EDRImage * img, EDRToneMapper * mapper, EDRToneBuffer * buffer)
	: EDREye(img, mapper, buffer)
	, gazeAreaSize(20)
{
	lumData[0] = EDRLuminanceDataPoint("Moonlit Ground", 1.4e-3f, 0.09f, 0.1f, 300.f);
	lumData[1] = EDRLuminanceDataPoint("Shaded Grass", 2000.f, 0.4f, 5.f, 10.f);
	lumData[2] = EDRLuminanceDataPoint("Clear Sky", 8000.f, 0.6575f, 6.f, 0.5f);

	fitStandardImageNorm = calcExponentialFitInfo(
		lumData[0].luminanceCdm2, lumData[0].standardImageNorm,
		lumData[1].luminanceCdm2, lumData[1].standardImageNorm,
		lumData[2].luminanceCdm2, lumData[2].standardImageNorm, false);
	fitAdaptUp = calcExponentialFitInfo(
		lumData[0].luminanceCdm2, lumData[0].adaptUpSeconds,
		lumData[1].luminanceCdm2, lumData[1].adaptUpSeconds,
		lumData[2].luminanceCdm2, lumData[2].adaptUpSeconds, false);
	fitAdaptDown = calcExponentialFitInfo(
		lumData[0].luminanceCdm2, lumData[0].adaptDownSeconds,
		lumData[1].luminanceCdm2, lumData[1].adaptDownSeconds,
		lumData[2].luminanceCdm2, lumData[2].adaptDownSeconds, true);
}

EDREye_Physical::~EDREye_Physical()
{
}

void EDREye_Physical::calibrate(float imageLuminanceValue, float actualLuminanceValue)
{
	calibrate(actualLuminanceValue / imageLuminanceValue);
}

void EDREye_Physical::calibrate(float scalingFactor)
{
	this->scalingFactor = scalingFactor;
}

float EDREye_Physical::getLuminanceScalingFactor() const
{
	return scalingFactor;
}

void EDREye_Physical::adapt(size_t x, size_t y, float dt)
{
	if (!img) return;

	int n = 0;
	float exposureTotal = 0.f;

	// Average the exposure value over the gaze area.
	for (unsigned int i = fmax(0, x - gazeAreaSize); i < fmin(x + gazeAreaSize, img->getWidth()); i++)
	{
		for (unsigned int j = fmax(0, y - gazeAreaSize); j < fmin(y + gazeAreaSize, img->getHeight()); j++)
		{
			exposureTotal += img->getPixelExposure(i, j);
			n++;
		}
	}

	// Set the goal exposure value.
	goalExposure = exposureTotal / n;

	// Calculate luminance data for the current and goal exposures.
	EDRLuminanceDataPoint ldCurrent = calcDataPointForLuminance(exposure * scalingFactor);
	EDRLuminanceDataPoint ldGoal = calcDataPointForLuminance(goalExposure * scalingFactor);

	float adaptSeconds;

	// Figure out how long it should take to fully adapt to the goal exposure.
	if (exposure < goalExposure) {
		adaptSeconds = ldGoal.adaptUpSeconds - ldCurrent.adaptUpSeconds;
	}
	else {
		adaptSeconds = ldCurrent.adaptDownSeconds - ldGoal.adaptDownSeconds;
	}

	// Move the actual exposure value towards the goal exposure.
	if (adaptSeconds <= dt) {
		exposure = goalExposure;
	}
	else {
		exposure += (goalExposure - exposure) * (dt / adaptSeconds);
	}
}

EDRLuminanceDataPoint EDREye_Physical::calcDataPointForLuminance(float lumCdm2) const
{
	EDRLuminanceDataPoint l;
	l.luminanceCdm2 = lumCdm2;
	l.standardImageNorm = doExponentialFit(fitStandardImageNorm, lumCdm2);
	l.adaptUpSeconds = doExponentialFit(fitAdaptUp, lumCdm2);
	l.adaptDownSeconds = doExponentialFit(fitAdaptDown, lumCdm2);
	return l;
}

unsigned int EDREye_Physical::getGazeAreaSize() const
{
	return gazeAreaSize;
}

void EDREye_Physical::setGazeAreaSize(unsigned int newSize)
{
	gazeAreaSize = newSize;
}

EDRExponentialFit EDREye_Physical::calcExponentialFitInfo(float xlow, float ylow, float xmid, float ymid, float xhigh, float yhigh, bool flip)
{
	EDRExponentialFit fit;
	fit.flip = flip;
	fit.shiftX = xlow;
	fit.scaleX = xhigh - xlow;
	fit.shiftY = flip ? yhigh : ylow;
	fit.scaleY = (flip ? -1.f : 1.f) * (yhigh - ylow);

	float xmidnorm = (xmid - fit.shiftX) / fit.scaleX;
	float ymidnorm = (ymid - fit.shiftY) / fit.scaleY;
	if (flip) ymidnorm = 1.f - ymidnorm;

	fit.gamma = log(ymidnorm) / log(xmidnorm);

	return fit;
}

float EDREye_Physical::doExponentialFit(EDRExponentialFit fit, float x)
{
	float xnorm = (x - fit.shiftX) / fit.scaleX;
	float ynorm = powf(xnorm, fit.gamma);
	if (fit.flip) ynorm = 1.f - ynorm;
	return (ynorm * fit.scaleY) + fit.shiftY;
}
