/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "DrawAreaEDR.h"

#include <QImageReader>
#include <QImage>
#include <QPainter>
#include "EDRToneMapper_Basic.h"
#include "EyeDynamicRange.h"

DrawAreaEDR::DrawAreaEDR(QWidget *parent)
	: QLabel(parent)
	, resizeTimerId(-1)
	, hdrImg(nullptr)
{
	toneMapper = new EDRToneMapper_Basic(hdrImg);
}

DrawAreaEDR::~DrawAreaEDR()
{
}

void DrawAreaEDR::initializeForImage(EDRImage * hdrImg)
{
	this->hdrImg = hdrImg;
	this->toneMapper->setImage(hdrImg);
}

void DrawAreaEDR::repaintDrawArea(EyeDynamicRange * ets)
{
	if (!hdrImg) return;

	// Initialize drawing.
	img = QImage((int)hdrImg->getWidth(), (int)hdrImg->getHeight(), QImage::Format::Format_ARGB32);

	// Tone map to gaze position.
	toneMapper->toneMap(gazeLocalPos.x() + ets->optCalibrationHoriz, gazeLocalPos.y() + ets->optCalibrationVert, 0);

	// Pull pixels.
	for (unsigned int i = 0; i < img.width(); i++)
	{
		for (unsigned int j = 0; j < img.height(); j++)
		{
			EDRStandardPixel pix = toneMapper->getPixel(i, j);
			img.setPixelColor((signed)i, (signed)j, QColor(pix.r, pix.g, pix.b));
		}
	}

	// Dump the image buffer to the label's pixmap.
	setPixmap(QPixmap::fromImage(img));
	repaint();
}

void DrawAreaEDR::setGazeLocalPosition(QPoint pos)
{
	gazeLocalPos = pos;
}

void DrawAreaEDR::setGazeScreenPosition(QPoint pos)
{
	// We were given a screen position of the user's gaze. Save the position
	// relative to the widget.
	gazeLocalPos = mapFromGlobal(pos);
	gazeLocalPos.setY(gazeLocalPos.y() - 50);
}

void DrawAreaEDR::resizeEvent(QResizeEvent * event)
{
	// This resize event will fire consistently while the user is resizing
	// the window. In order to prevent lots of expensive operations, we only
	// handle resizes after no resize events have fired for a set period of time.
	if (resizeTimerId >= 0)
		killTimer(resizeTimerId);
	resizeTimerId = startTimer(200);
}

void DrawAreaEDR::timerEvent(QTimerEvent * event)
{
	// Prevent the timer from firing repeatedly.
	killTimer(event->timerId());
	resizeTimerId = -1;
}
