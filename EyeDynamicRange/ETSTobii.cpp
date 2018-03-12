#include "ETSTobii.h"

#include <cstdlib>
#include <cstring>

ETSTobii::ETSTobii()
{
	// Initialize everything to null/0.
	mApi = nullptr;
	mDevice = nullptr;
	mError = TOBII_ERROR_NO_ERROR;
	memset(mUrl, 0, 256);
}

ETSTobii::~ETSTobii()
{
}

bool ETSTobii::init()
{
	mError = tobii_api_create(&mApi, nullptr, nullptr);
	return mError == TOBII_ERROR_NO_ERROR;
}

bool ETSTobii::shutdown()
{
	mError = tobii_api_destroy(mApi);
	mApi = nullptr;
	return mError == TOBII_ERROR_NO_ERROR;
}

bool ETSTobii::connectDevice()
{
	// Enumerate devices.
	mError = tobii_enumerate_local_device_urls(mApi, onEnumDevice, this);

	// We assume the final device enumerated had a valid URL. Now connect to that.
	if (mError == TOBII_ERROR_NO_ERROR && strlen(mUrl) > 0)
	{
		mError = tobii_device_create(mApi, mUrl, &mDevice);
		return mError == TOBII_ERROR_NO_ERROR;
	}

	return false;
}

bool ETSTobii::disconnectDevice()
{
	if (mDevice)
	{
		mError = tobii_device_destroy(mDevice);
		mDevice = nullptr;
		return mError == TOBII_ERROR_NO_ERROR;
	}
	return true;
}

bool ETSTobii::isConnected()
{
	return mApi && mDevice;
}

bool ETSTobii::processEyeData(bool waitUntilData)
{
	if (!mDevice)
		return false;

	// Call this function. If waitUntilData is true, we want to keep calling it
	// until it doesn't time out.
	do
	{
		mError = tobii_wait_for_callbacks(nullptr, 1, &mDevice);
	} while (waitUntilData && mError == TOBII_ERROR_TIMED_OUT);

	if (mError != TOBII_ERROR_NO_ERROR)
	{
		return false;
	}

	mError = tobii_device_process_callbacks(mDevice);
	return mError == TOBII_ERROR_NO_ERROR;
}

bool ETSTobii::registerGazePointCallback(ETSTobiiCallback callback, void * context)
{
	// Remember the callback they want to register so our callback can call it.
	mCallbackInfo.callback = callback;
	mCallbackInfo.context = context;

	mError = tobii_gaze_point_subscribe(mDevice, gazePointCallbackInternal, this);
	return mError == TOBII_ERROR_NO_ERROR;
}

bool ETSTobii::unregisterGazePointCallback()
{
	mError = tobii_gaze_point_unsubscribe(mDevice);
	return mError == TOBII_ERROR_NO_ERROR;
}



void ETSTobii::onEnumDevice(char const * url, void * user_data)
{
	ETSTobii *tobii = (ETSTobii *)user_data;

	// Read this url into the mUrl buffer.
	strcpy(tobii->mUrl, url);
}

void ETSTobii::gazePointCallbackInternal(tobii_gaze_point_t const * gaze_point, void * user_data)
{
	ETSTobii *tobii = (ETSTobii *)user_data;
	tobii->mCallbackInfo.callback(gaze_point->position_xy[0], gaze_point->position_xy[1], tobii->mCallbackInfo.context);
}
