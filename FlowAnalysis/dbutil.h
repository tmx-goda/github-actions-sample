#include <stdint.h>

typedef struct Person {
    char* name;
    int32_t personalId;
    char* reference;
    int32_t salary;
    int32_t daysWorkedInPassedMonth;
} Person;

Person* retrievePersonFromDB(int32_t id);
