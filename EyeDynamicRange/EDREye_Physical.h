/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDREye.h"

/**
 * A 
 */
typedef struct EDRLuminanceDataPoint_t
{
	char * name;				// Friendly name (e.g. "clear sky")
	float luminanceCdm2;		// Luminance in candelas per m^2
	float standardImageNorm;	// Normalized (0-1) value of the desired brightness
								//		in a standard image
	float adaptUpSeconds;		// Time it takes the eye to adapt up to this luminance
								//		from a very dark environment
	float adaptDownSeconds;		// Time to adapt down from a very bright environment

	struct EDRLuminanceDataPoint_t() {}

	struct EDRLuminanceDataPoint_t(char * name, float luminance, float standardImgNorm, float adaptUp, float adaptDown)
		: name(name)
		, luminanceCdm2(luminance)
		, standardImageNorm(standardImgNorm)
		, adaptUpSeconds(adaptUp)
		, adaptDownSeconds(adaptDown)
	{}

} EDRLuminanceDataPoint;

typedef struct
{
	float shiftX, shiftY;
	float scaleX, scaleY;
	float gamma;
	bool flip;
} EDRExponentialFit;

/**
 * A more advanced eye implementation that accounts for physical and temporal
 * characteristics of the human eye.
 */
class EDREye_Physical : public EDREye
{

protected:

	float scalingFactor;
	EDRLuminanceDataPoint lumData[3];

	EDRExponentialFit fitStandardImageNorm;
	EDRExponentialFit fitAdaptUp;
	EDRExponentialFit fitAdaptDown;

	float goalExposure;

	unsigned int gazeAreaSize;

public:

	EDREye_Physical(EDRImage * img, EDRToneMapper * mapper, EDRToneBuffer * buffer = nullptr);
	virtual ~EDREye_Physical();

	/**
	 * Tethers values from the EDRImage (which may not have values consistent
	 * with other EDRImages) to real world values. Given that values in the
	 * image are linear, all we need to know is a value from the image and a
	 * corresponding real world value, and we can calculate a scaling factor.
	 */
	virtual void calibrate(float imageLuminanceValue, float actualLuminanceValue);

	/**
	 * Sets the scaling factor directly.
	 */
	virtual void calibrate(float scalingFactor);

	float getLuminanceScalingFactor() const;

	virtual void adapt(size_t x, size_t y, float dt) override;

	/**
	 * Creates an EDRLuminanceDataPoint containing standard image values and
	 * adaptation times for the specified luminance level. This extrapolates
	 * from known luminance data points.
	 */
	virtual EDRLuminanceDataPoint calcDataPointForLuminance(float lumCdm2) const;

	unsigned int getGazeAreaSize() const;
	void setGazeAreaSize(unsigned int newSize);

public:

	/**
	 * Helper function that calculates gamma values for standard image normalized
	 * exposure and adaptation up/down times. Ideally we would have these values
	 * for every luminance level, but this allows us to have values for just 3.
	 */
	static EDRExponentialFit calcExponentialFitInfo(float xlow, float ylow, float xmid, float ymid, float xhigh, float yhigh, bool flip);

	static float doExponentialFit(EDRExponentialFit fit, float x);

};