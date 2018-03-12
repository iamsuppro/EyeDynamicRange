/*
* Created by Jack Boffa on 03/07/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "DrawAreaEDR.h"

#include <QImageReader>
#include <QImage>
#include <QPainter>

DrawAreaEDR::DrawAreaEDR(QWidget *parent)
	: QLabel(parent)
	, resizeTimerId(-1)
{
}

DrawAreaEDR::~DrawAreaEDR()
{
}

void DrawAreaEDR::repaintDrawArea(EyeDynamicRange * ets)
{
	// Initialize drawing.
	QPainter painter(&img);
	painter.setBrush(Qt::black);

	painter.end();

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
