/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneMapper.h"
#include <QImage>

#define QTBUFFER_NUM_IMAGES 32

class EDRToneMapper_QtBuffer : public EDRToneMapper
{

protected:

	EDRToneMapper * mapper;
	QImage images [QTBUFFER_NUM_IMAGES];
	QImage imageOut;

	bool useGammaMap;
	float minExposure, maxExposure;
	float gamma;
	float exposure;

public:

	EDRToneMapper_QtBuffer(EDRToneMapper * mapper);
	~EDRToneMapper_QtBuffer();

	virtual void precomputeQImages();

	virtual void toneMap(size_t x, size_t y, float dt) override;
	virtual void toneMap(float linExposure, float dt) override;
	virtual EDRStandardPixel getPixel(size_t x, size_t y) override;

	EDRToneMapper * getWrappedMapper() const;
	void setWrappedMapper(EDRToneMapper * mapper);

	virtual void setImage(EDRImage * newImg) override;

	virtual QImage getToneMappedImage() const;
};