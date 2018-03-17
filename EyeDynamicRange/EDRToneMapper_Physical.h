/*
* Created by Jack Boffa on 03/12/2018.
* Copyright (c) 2018. All rights reserved.
*/

#pragma once
#include "EDRToneMapper_DR.h"

class EDRToneMapper_Physical : public EDRToneMapper_DR
{

protected:

	class EDREye_Physical * eye;

public:

	EDRToneMapper_Physical(EDRImage * img);
	virtual ~EDRToneMapper_Physical();

	virtual void attachPhysicalEye(class EDREye_Physical * eye);
	class EDREye_Physical * getPhysicalEye() const;

protected:

	virtual float calcGamma(float exposureNorm) const override;

};