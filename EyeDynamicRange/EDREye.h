/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"
#include "EDRImage.h"
#include "EDRToneMapper.h"
#include "EDRToneBuffer.h"

/**
* Point of interaction that invokes a tone mapper, performs buffering,
* and accounts for physical characteristics of the human eye (e.g.
* adaptation over time). An eye takes a position of gaze in an HDR image
* and outputs a full standard image.
*/
class EDREye : public EDRObject
{
	
protected:

	EDRImage * img;
	EDRToneMapper * mapper;
	EDRToneBuffer * buffer;

	float exposure;

public:

	EDREye(EDRImage * img, EDRToneMapper * mapper, EDRToneBuffer * buffer = nullptr);
	virtual ~EDREye();

	/**
	 * Performs computation that can be done before usage begins. If
	 * this eye uses a buffer, this will call compute() on the buffer
	 * to pre-calculate various exposure levels.
	 */
	virtual void precomputeExposures();

	/**
	 * Adapts the eye to the given location in the image. This should
	 * be called before getStandardImage(). (x, y) is the pixel of the
	 * EDRImage that is the center of the gaze, and dt is how much time
	 * has passed (in seconds) since adapt() was last called.
	 */
	virtual void adapt(size_t x, size_t y, float dt);

	/**
	 * Gets the current standard (tone-mapped) image. This can return any
	 * abstract form of image, so the caller should know what to do with it.
	 * The address points to internal memory of this EDREye and should not be
	 * modified or freed.
	 */
	virtual void * getStandardImage();

	/**
	 * Gets the current target exposure level of the eye.
	 */
	float getTargetExposure() const;

	EDRImage * getEDRImage() const;
	void setEDRImage(EDRImage * img);
	EDRToneMapper * getToneMapper() const;
	void setToneMapper(EDRToneMapper * mapper);
	EDRToneBuffer * getBuffer() const;
	void setBuffer(EDRToneBuffer * buffer);
};