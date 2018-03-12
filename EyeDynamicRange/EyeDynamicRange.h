#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EyeDynamicRange.h"
#include "ETSTobii.h"
#include "DrawAreaEDR.h"

class EyeDynamicRange : public QMainWindow
{
    Q_OBJECT

private:

	ETSTobii * tobii;
	DrawAreaEDR * drawArea;
	int timerId;

public:

	// Options.
	int optCalibrationHoriz;
	int optCalibrationVert;

private:
    Ui::EyeDynamicRangeClass ui;

public:
    EyeDynamicRange(QWidget *parent = Q_NULLPTR);

	void reconnectToTobii();
	void timerEvent(QTimerEvent * event) override;
	static void onGazePointReceived(float alpha, float beta, void * context);

public slots:

	// General.
	void onTobiiReconnectClicked();
	void onCalibrationHorizChanged(int newValue);
	void onCalibrationVertChanged(int newValue);
	void onFullscreen(bool newValue);
	void onShowControls(bool newValue);

};
