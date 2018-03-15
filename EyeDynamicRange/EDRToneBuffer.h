/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"

/**
* Abstract super-class for a buffer to store multiple pre-computed
* exposure levels. This interacts with an EDRToneMapper and saves
* entire images, which can then be retrieved as a whole rather than
* requiring pixel-by-pixel calculation.
*/
class EDRToneBuffer : public EDRObject
{

protected:

	EDRToneBuffer();
	~EDRToneBuffer();

public:

	/**
	 * Pre-compute exposure levels by querying a tone mapper. This
	 * method should be expected to take several minutes before it
	 * returns.
	 */
	virtual void compute(class EDRToneMapper * toneMapper) = 0;

	/**
	 * Gets a pointer to an image targeted at the specified exposure
	 * level. This can return any abstract form of image, so the caller
	 * should know what to do with it. The address points to internal
	 * memory of this EDRToneMapper and should not be modified or freed.
	 */
	virtual void * getStandardImage(float targetExposure) = 0;
};