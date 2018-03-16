/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneBuffer.h"

/**
 * Abstract superclass for a buffer that stores a number of 
 * images at target exposures specified by a gamma value. The
 * exposure steps are chosen within the range of the minimum
 * to the maximum brightness pixel in the EDRImage, and are
 * exponential to allow similar perceptual qualities throughout
 * the range. Target exposures in between stored exposure levels
 * can be interpolated from the nearest available levels.
 */
class EDRToneBuffer_GammaLerp : public EDRToneBuffer
{
protected:

	// Instance parameters.
	const unsigned int nImages;
	const float bufferGamma;
	bool interpEnabled;

	// Min and max exposures found in the image.
	float minExposure;
	float maxExposure;

	// Arrays containing nImages standard images and target exposures.
	void ** images;
	float * imageExposures;

public:

	EDRToneBuffer_GammaLerp(unsigned int nImages, float gamma, bool interp = true);
	virtual ~EDRToneBuffer_GammaLerp();

	virtual void compute(class EDRToneMapper * toneMapper) override;
	virtual void * getStandardImage(float targetExposure) override;

	bool isInterpEnabled() const;
	void setInterpEnabled(bool enabled);

protected:

	/**
	 * Override to specify how a buffered image is created. Returns a
	 * pointer to an image of the specified width and height.
	 */
	virtual void * createBufferedImage(size_t width, size_t height) const = 0;

	/**
	 * Override to specify how a pixel is set within an allocated buffer
	 * image. This should set the pixel at (x, y) to the values in value.
	 */
	virtual void setBufferedImagePixel(void * image, size_t x, size_t y, EDRStandardPixel value) = 0;

	/**
	 * Override to specify how an image is interpolated from two neighboring
	 * exposure levels. Here we are given the images for the stored exposures
	 * directly above and below the target, as well as the normalized linear
	 * alpha value of where the target is between the images.
	 */
	virtual void * interpImage(void * imageBelow, void * imageAbove, float alpha) = 0;
};