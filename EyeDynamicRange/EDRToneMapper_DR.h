/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneMapper.h"

/**
 * Dynamic range values.
 */
typedef struct EDRDynamicRange_t
{
	float black;
	float white;

	struct EDRDynamicRange_t()
		: black(0.f)
		, white(0.f)
	{
	}

	struct EDRDynamicRange_t(float black, float white)
		: black(black)
		, white(white)
	{
	}

} EDRDynamicRange;

/**
 * A tone mapper that specifies a dynamic range and performs gamma
 * correction within that range. Values outside the dynamic range
 * become full black or full white.
 */
class EDRToneMapper_DR : public EDRToneMapper
{

protected:

	float exposure;

	EDRDynamicRange currentRangeLin;
	EDRDynamicRange eyeRangeStops;

	float gamma;

public:

	EDRToneMapper_DR(EDRImage * img);
	virtual ~EDRToneMapper_DR();

	virtual void toneMap(float linExposure) override;
	virtual EDRStandardPixel getPixel(size_t x, size_t y) override;

	float getTargetExposure() const;
	EDRDynamicRange getCurrentRangeLin() const;
	EDRDynamicRange getEyeRangeFStops() const;
	void setEyeRangeFStops(float fStopsBelow, float fStopsAbove);
	float getGamma() const;

protected:

	/**
	 * Tone map a single RGB channel, after DR and gamma have been
	 * configured with a call to toneMap(). This method is called by
	 * getPixel() and determines each R/G/B value.
	 */
	virtual unsigned char mapOneChannel(float in) const;

	/**
	 * Assuming exposure is set properly, calculate the linear edges
	 * of the dynamic range using the values of eyeRangeStops.
	 */
	virtual EDRDynamicRange calcDynamicRangeLin() const;

	/**
	 * Calculate a new value for gamma, given a normalized (0-1) value
	 * of where the target exposure linearly falls within the dynamic
	 * range.
	 */
	virtual float calcGamma(float exposureNorm) const;
};