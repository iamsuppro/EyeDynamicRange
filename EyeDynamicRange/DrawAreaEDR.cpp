/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "DrawAreaEDR.h"

#include "EyeDynamicRange.h"
#include <QImageReader>
#include <QImage>
#include <QPainter>
#include "EDRToneMapper_DR.h"
#include "EDRToneBuffer_Qt.h"
#include "EDREye_Physical.h"

DrawAreaEDR::DrawAreaEDR(QWidget *parent)
	: QLabel(parent)
	, resizeTimerId(-1)
	, hdrImg(nullptr)
	, mapper(nullptr)
	, buffer(nullptr)
	, eye(nullptr)
{
}

DrawAreaEDR::~DrawAreaEDR()
{
}

void DrawAreaEDR::initializeForImage(EDRImage * hdrImg)
{
	if (this->hdrImg)
	{
		delete this->hdrImg;
		delete this->mapper;
		delete this->buffer;
		delete this->eye;
	}

	this->hdrImg = hdrImg;

	mapper = new EDRToneMapper_DR(hdrImg);
	buffer = new EDRToneBuffer_Qt(32, 2.f);
	eye = new EDREye_Physical(hdrImg, mapper, buffer);

	((EDREye_Physical *)eye)->calibrate(1.3f, 8000.f);
	eye->precomputeExposures();
}

void DrawAreaEDR::repaintDrawArea(EyeDynamicRange * ets)
{
	if (!hdrImg) return;

	// Initialize drawing.
	//img = QImage((int)hdrImg->getWidth(), (int)hdrImg->getHeight(), QImage::Format::Format_ARGB32);

	QPoint finalEyePos = QPoint(qMax(0, qMin(gazeLocalPos.x() + ets->optCalibrationHoriz,
		img.width())), qMax(0, qMin(gazeLocalPos.y() + ets->optCalibrationVert, img.height())));

	// Tone map to gaze position.
	eye->adapt(finalEyePos.x(), finalEyePos.y(), 1.f / ets->optFPS);
	img = QImage(*(QImage *)eye->getStandardImage());

	QPainter painter(&img);

	// Draw gaze position.	
	if (ets->optCalibrationShowGaze)
	{
		painter.setBrush(Qt::black);
		painter.fillRect(finalEyePos.x() - 5, finalEyePos.y() - 5, 10, 10, Qt::BrushStyle::SolidPattern);
	}

	// Dump the image buffer to the label's pixmap.
	painter.end();
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
