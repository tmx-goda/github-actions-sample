#include <stdio.h>
#include <stdint.h>

static int32_t i = 10;
static int32_t* x;

static int32_t helper1(char b) {
    if (b)
        return 0;
    return *x;
}

static int32_t helper2() {
    return *x;
}

static int32_t noFalseViolation1(int32_t level) {
    x = 0;
    if (level > 0)
        x = &i;
    if (level > 4)
        return *x;
    return 0;
}

static int32_t noFalseViolation2(char b) {
    x = 0;
    if (b)
        x = &i;
    if (b)
        return *x;
    return 0;
}

static int32_t noFalseViolation3(char b) {
    int32_t* y = 0;
    if (x != 0)
        y = &i;
    if (y != 0)
        return *x + *y;
    else
        return 0;
}

static int32_t trueViolation(char b) {
    int32_t* y = 0;
    if (x != 0)
        y = &i;
    if (y != 0)
        return *x + *y;
    else
        return *x;
}

static int32_t functionCall_noFalseViolation1(char b) {
    x = 0;
    if (!b)
        x = &i;
    return helper1(b);
}


static int32_t functionCall_noFalseViolation2(int32_t* x) {
    if (x == 0) /* checking parameter (not the global variable) for null */
        printf("x is null");
    return helper2();
}

static int32_t functionCall_trueViolation1(char b) {
    x = 0;
    if (b)
        x = &i;
    return helper1(b);
}

static int32_t functionCall_trueViolation2() {
    x = 0;
    return helper2();
}

