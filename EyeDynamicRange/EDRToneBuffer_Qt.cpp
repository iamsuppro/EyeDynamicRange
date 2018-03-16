/*
* Created by Jack Boffa on 03/15/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EDRToneBuffer_Qt.h"
#include <QPainter>

EDRToneBuffer_Qt::EDRToneBuffer_Qt(unsigned int nImages, float gamma, bool interp)
	: EDRToneBuffer_GammaLerp(nImages, gamma, interp)
{
}

EDRToneBuffer_Qt::~EDRToneBuffer_Qt()
{
}

void * EDRToneBuffer_Qt::createBufferedImage(size_t width, size_t height) const
{
	return new QImage(width, height, QImage::Format::Format_RGB32);
}

void EDRToneBuffer_Qt::setBufferedImagePixel(void * image, size_t x, size_t y, EDRStandardPixel value)
{
	((QImage *)image)->setPixelColor(x, y, QColor(value.r, value.g, value.b));
}

void * EDRToneBuffer_Qt::interpImage(void * imageBelow, void * imageAbove, float alpha)
{
	interpImg = QImage(*(QImage *)imageBelow);

	QPainter painter(&interpImg);
	//painter.setCompositionMode(QPainter::CompositionMode::)
	painter.setOpacity(alpha);
	painter.drawImage(0, 0, *(QImage *)imageAbove);
	painter.end();

	return &interpImg;
}
