/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneMapper.h"

typedef struct
{
	float black;
	float white;
} EDRDynamicRange;

class EDRToneMapper_Basic : public EDRToneMapper
{

private:

	float exposure;
	EDRDynamicRange range;
	float gamma;

public:

	static const unsigned int DRANGE_EV_ABOVE;
	static const unsigned int DRANGE_EV_BELOW;

public:

	EDRToneMapper_Basic(EDRImage * img);
	~EDRToneMapper_Basic();

	virtual void toneMap(float linExposure, float dt) override;
	virtual EDRStandardPixel getPixel(size_t x, size_t y) override;

	virtual unsigned char mapOneChannel(float in) const;

	virtual EDRDynamicRange getDynamicRange() const;
};