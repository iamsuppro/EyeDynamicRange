/*
* Created by Jack Boffa on 03/11/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once

#include <QLabel>

class DrawAreaEDR : public QLabel
{
	Q_OBJECT

private:
	
	QPoint gazeLocalPos;
	int resizeTimerId;

public:

	QImage img;

public:
	DrawAreaEDR(QWidget *parent);
	~DrawAreaEDR();

	void repaintDrawArea(class EyeDynamicRange * ets);

	void setGazeLocalPosition(QPoint pos);
	void setGazeScreenPosition(QPoint pos);

protected:

	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void timerEvent(QTimerEvent *event) override;
	

};
