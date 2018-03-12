#pragma once
#include "tobii.h"
#include "tobii_streams.h"

typedef void(*ETSTobiiCallback)(float alpha, float beta, void * context);

typedef struct
{
	ETSTobiiCallback callback;
	void * context;
} ETSTobiiCallbackInfo;

class ETSTobii
{

public:

	tobii_error_t mError;

private:

	tobii_api_t * mApi;
	tobii_device_t * mDevice;
	char mUrl [256];
	ETSTobiiCallbackInfo mCallbackInfo;

public:

	ETSTobii();
	~ETSTobii();

	/**
	 * Initialize this object for use. connectDevice() will be ready
	 * to call after this. Returns true if no errors.
	 */
	bool init();

	/**
	 * Destroy this object at the end of the application.
	 */
	bool shutdown();

	/**
	 * Finds the Tobii and connects to it. Returns true if no errors.
	 */
	bool connectDevice();

	/**
	 * Disconnects the currently connected Tobii.
	 */
	bool disconnectDevice();

	bool isConnected();

	/**
	 * Process data and call any registered callbacks. Calling this every
	 * frame will drive a callback engine.
	 */
	bool processEyeData(bool waitUntilData);

	bool registerGazePointCallback(ETSTobiiCallback callback, void * context);

	bool unregisterGazePointCallback();

protected:

	static void onEnumDevice(char const* url, void* user_data);

	static void gazePointCallbackInternal(tobii_gaze_point_t const* gaze_point, void* user_data);
};