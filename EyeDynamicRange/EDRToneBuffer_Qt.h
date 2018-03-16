/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneBuffer_GammaLerp.h"
#include <QImage>

class EDRToneBuffer_Qt : public EDRToneBuffer_GammaLerp
{

private:

	QImage interpImg;

public:

	EDRToneBuffer_Qt(unsigned int nImages, float gamma, bool interp = true);
	~EDRToneBuffer_Qt();

	virtual void * createBufferedImage(size_t width, size_t height) const override;
	virtual void setBufferedImagePixel(void * image, size_t x, size_t y, EDRStandardPixel value) override;
	virtual void * interpImage(void * imageBelow, void * imageAbove, float alpha) override;
};