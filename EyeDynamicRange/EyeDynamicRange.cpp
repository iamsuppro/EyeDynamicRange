/*
* Created by Jack Boffa on 03/11/2018.
* Copyright (c) 2018. All rights reserved.
*/

#include "EyeDynamicRange.h"
#include <QApplication>
#include <QDesktopWidget>

EyeDynamicRange::EyeDynamicRange(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	drawArea = (DrawAreaEDR *)ui.mainDrawArea;

	// Initialize the Tobii bridge.
	tobii = new ETSTobii();
	tobii->init();
	reconnectToTobii();

	// Start framerate timer.
	timerId = startTimer(100);
}

void EyeDynamicRange::reconnectToTobii()
{
	tobii->disconnectDevice();

	// Connect to a device and setup a callback.
	if (tobii->connectDevice())
	{
		tobii->registerGazePointCallback(onGazePointReceived, this);
		ui.tobiiLabel->setText(QString("<font color='green'>Connected</font>"));
	}
	else
	{
		ui.tobiiLabel->setText(QString("<font color='red'>Disconnected</font>"));
	}
}

void EyeDynamicRange::timerEvent(QTimerEvent * event)
{
	// Process eye data (thereby calling our callback).
	if (tobii->isConnected())
	{
		if (!tobii->processEyeData(false))
		{
			if (tobii->mError == TOBII_ERROR_CONNECTION_FAILED)
			{
				tobii->disconnectDevice();
				ui.tobiiLabel->setText(QString("<font color='red'>Disconnected</font>"));
			}
		}
	}

	// If no Tobii is connected, draw the scotoma in the center.
	else
	{
		drawArea->setGazeLocalPosition(QPoint(drawArea->img.width() / 2, drawArea->img.height() / 2));
		drawArea->repaintDrawArea(this);
	}
}

void EyeDynamicRange::onGazePointReceived(float alpha, float beta, void * context)
{
	EyeDynamicRange * edr = (EyeDynamicRange *)context;

	// Tobii gives us barycentric (0-1) coords, so we need to convert to screen coords.
	QRect screenRect = QApplication::desktop()->screenGeometry();
	QPoint screenPoint(screenRect.width() * alpha, screenRect.height() * beta);

	// Send that on to the draw area, and tell it to redraw.
	edr->drawArea->setGazeScreenPosition(screenPoint);
	edr->drawArea->repaintDrawArea(edr);
}

void EyeDynamicRange::onTobiiReconnectClicked()
{
	reconnectToTobii();
}

void EyeDynamicRange::onCalibrationHorizChanged(int newValue)
{
	optCalibrationHoriz = newValue;
}

void EyeDynamicRange::onCalibrationVertChanged(int newValue)
{
	optCalibrationVert = newValue;
}

void EyeDynamicRange::onFullscreen(bool newValue)
{
	if (newValue)
		showFullScreen();
	else
		showNormal();
}

void EyeDynamicRange::onShowControls(bool newValue)
{
	ui.tabWidget->setHidden(!newValue);
}
