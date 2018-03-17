#include "EDRToneMapper_Physical.h"
#include "EDREye_Physical.h"
#include <cmath>

EDRToneMapper_Physical::EDRToneMapper_Physical(EDRImage * img)
	: EDRToneMapper_DR(img)
	, eye(nullptr)
{
}

EDRToneMapper_Physical::~EDRToneMapper_Physical()
{
}

void EDRToneMapper_Physical::attachPhysicalEye(EDREye_Physical * eye)
{
	this->eye = eye;
}

EDREye_Physical * EDRToneMapper_Physical::getPhysicalEye() const
{
	return eye;
}

float EDRToneMapper_Physical::calcGamma(float exposureNorm) const
{
	float goal = 0.5f;

	// Instead of always gamma correcting the exposed value to 0.5, try
	// to use perceptually accurate values.
	if (eye)
	{
		EDRLuminanceDataPoint l = eye->calcDataPointForLuminance(exposure * eye->getLuminanceScalingFactor());
		goal = l.standardImageNorm;
	}

	return log(goal) / log(exposureNorm);
}
