#include "stm32f1xx_hal.h"
#include "Defines.h"

uint32_t MAP(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax,
		uint32_t au32_OUTmin, uint32_t au32_OUTmax);

int constrain(int x, int a, int b);

void btnMachine(button* btns);
