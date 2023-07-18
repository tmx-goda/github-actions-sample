#include <stdint.h>

#define MAX_ATTEMPTS 5
#define SENSORS 0
#define ACTUATORS 1
#define CATEGORIES 2
#define HANDLE_NUM 3
#define COMPENSATION 2

enum SENSOR_STATUS {SENSOR_READ_OK=0, SENSOR_INIT_ERROR=1, SENSOR_READ_FAILED=2};

typedef enum SENSOR_STATUS sensor_stat;
typedef int32_t * sensor_handle;

int32_t needCompensation(void);
int32_t calcCompensation(int32_t temp);
enum SENSOR_STATUS readSensor(sensor_handle, int32_t * measure);
void finalizeSensor(sensor_handle handle);
sensor_handle initializeSensor(unsigned id);
void log_error();

