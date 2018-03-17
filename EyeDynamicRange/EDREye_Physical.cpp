#include "EDREye_Physical.h"
#include <cmath>

EDREye_Physical::EDREye_Physical(EDRImage * img, EDRToneMapper * mapper, EDRToneBuffer * buffer)
	: EDREye(img, mapper, buffer)
{
	lumData[0] = EDRLuminanceDataPoint("Moonlit Ground", 1.4e-3f, 0.09f, 0.1f, 300.f);
	lumData[1] = EDRLuminanceDataPoint("Shaded Grass", 2000.f, 0.4f, 10.f, 5.f);
	lumData[2] = EDRLuminanceDataPoint("Clear Sky", 8000.f, 0.6575f, 30.f, 0.5f);

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

EDRExponentialFit EDREye_Physical::calcExponentialFitInfo(float xlow, float ylow, float xmid, float ymid, float xhigh, float yhigh, bool flip) const
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

float EDREye_Physical::doExponentialFit(EDRExponentialFit fit, float x) const
{
	float xnorm = (x - fit.shiftX) / fit.scaleX;
	float ynorm = powf(xnorm, fit.gamma);
	if (fit.flip) ynorm = 1.f - ynorm;
	return (ynorm * fit.scaleY) + fit.shiftY;
}
