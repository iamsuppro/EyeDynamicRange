/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRObject.h"
#include "EDRImage.h"

class EDRToneMapper : public EDRObject
{

private:

	EDRImage * img;

public:

	EDRToneMapper(EDRImage * img);
	~EDRToneMapper();

	/**
	 * Configure the tone mapper for a specified eye position on the image.
	 * (x, y) is the eye position, dt is the time in seconds since toneMap()
	 * was last called.
	 */
	void toneMap(size_t x, size_t y, float dt);

	/**
	* Configure the tone mapper for a specified eye position on the image.
	* (x, y) is the eye position, dt is the time in seconds since toneMap()
	* was last called.
	*/
	void toneMap(float linExposure, float dt);
};