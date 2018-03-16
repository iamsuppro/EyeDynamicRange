/*
* Created by Jack Boffa on 03/11/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once

#include <QLabel>
#include "EDRImage.h"

class DrawAreaEDR : public QLabel
{
	Q_OBJECT

private:
	
	QPoint gazeLocalPos;
	int resizeTimerId;

	EDRImage * hdrImg;
	class EDRToneMapper * mapper;
	class EDRToneBuffer * buffer;
	class EDREye * eye;

public:

	QImage img;

public:
	DrawAreaEDR(QWidget *parent);
	~DrawAreaEDR();

	void initializeForImage(EDRImage * hdrImg);

	void repaintDrawArea(class EyeDynamicRange * ets);

	void setGazeLocalPosition(QPoint pos);
	void setGazeScreenPosition(QPoint pos);

protected:

	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void timerEvent(QTimerEvent *event) override;
	

};
