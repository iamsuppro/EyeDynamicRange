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

/**
 * A tone mapper in which a dynamic range above and below the target
 * exposure is specified. Values outside the dynamic range are either
 * full black or full white. This class gamma corrects the target
 * exposure 
 */
class EDRToneMapper_DR : public EDRToneMapper
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

	virtual void toneMap(size_t x, size_t y, float dt) override;
	virtual void toneMap(float linExposure, float dt) override;
	virtual EDRStandardPixel getPixel(size_t x, size_t y) override;

	virtual unsigned char mapOneChannel(float in) const;

	virtual EDRDynamicRange getDynamicRange() const;
};