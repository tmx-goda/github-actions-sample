#include "sensor.h"

int32_t addSignals(int32_t signalA, int32_t signalB, int32_t temp) {
	int32_t result = 0;
	if (needCompensation() != 0) {
		result = signalA + signalB + calcCompensation(temp);
	} else {
		result = signalA + signalB;
	}
	return result;
}

int32_t getTemperature(int32_t * result) {
	int32_t attempts = 0;

	sensor_handle sh = initializeSensor(SENSORS);
	if(!sh) {
		log_error();
		return SENSOR_INIT_ERROR;
	}

	while (attempts < MAX_ATTEMPTS && readSensor(sh, result) != SENSOR_READ_OK) {
		log_error();
		++attempts;
	}
	if (attempts == MAX_ATTEMPTS) {
		finalizeSensor(sh);   // NG:test_case_getTemperature_StubParamCheck
		//finalizeSensor(0);  // OK:test_case_getTemperature_StubParamCheck
		return SENSOR_READ_FAILED;
	}
	finalizeSensor(sh);
	return SENSOR_READ_OK;
}

sensor_handle initializeSensor(unsigned id)
{
	static int32_t handles[CATEGORIES][HANDLE_NUM] = {{0,0,0}, {0,0,0}};
	sensor_handle handle = 0;
	int32_t i = 0;

	if (id < 0 || id >= CATEGORIES) {
		return handle;
	}
    for (i = 0; i < HANDLE_NUM; ++i) {
    	if (handles[id][i] == 0) {
    		handles[id][i] = 1;
    		handle = &handles[id][i];
    		break;
    	}
    }
    return handle;
}
