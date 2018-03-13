/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "DrawAreaEDR.h"

#include <QImageReader>
#include <QImage>
#include <QPainter>
#include "EDRToneMapper_Basic.h"
#include "EDRToneMapper_QtBuffer.h"
#include "EyeDynamicRange.h"

DrawAreaEDR::DrawAreaEDR(QWidget *parent)
	: QLabel(parent)
	, resizeTimerId(-1)
	, hdrImg(nullptr)
{
	EDRToneMapper * wrappedMapper = new EDRToneMapper_Basic(hdrImg);
	toneMapper = new EDRToneMapper_QtBuffer(wrappedMapper);
}

DrawAreaEDR::~DrawAreaEDR()
{
}

void DrawAreaEDR::initializeForImage(EDRImage * hdrImg)
{
	this->hdrImg = hdrImg;
	toneMapper->setImage(hdrImg);
	((EDRToneMapper_QtBuffer *)toneMapper)->precomputeQImages();
}

void DrawAreaEDR::repaintDrawArea(EyeDynamicRange * ets)
{
	if (!hdrImg) return;

	// Initialize drawing.
	//img = QImage((int)hdrImg->getWidth(), (int)hdrImg->getHeight(), QImage::Format::Format_ARGB32);

	QPoint finalEyePos = QPoint(qMax(0, qMin(gazeLocalPos.x() + ets->optCalibrationHoriz,
		img.width())), qMax(0, qMin(gazeLocalPos.y() + ets->optCalibrationVert, img.height())));

	// Tone map to gaze position.
	toneMapper->toneMap(finalEyePos.x(), finalEyePos.y(), 0);
	img = ((EDRToneMapper_QtBuffer *)toneMapper)->getToneMappedImage();

	QPainter painter(&img);

	// Pull pixels.
	/*for (unsigned int i = 0; i < img.width(); i++)
	{
		for (unsigned int j = 0; j < img.height(); j++)
		{
			EDRStandardPixel pix = toneMapper->getPixel(i, j);
			img.setPixelColor((signed)i, (signed)j, QColor(pix.r, pix.g, pix.b));
		}
	}*/

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
