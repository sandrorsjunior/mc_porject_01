/*
 * gpio.c
 * Implementação das funções de controle de GPIO
 */

#include "../include/gpio.h"

void gpio_config(volatile uint8_t *ddr_reg, uint8_t pin, GpioDirection direction) {
    if (direction == GPIO_OUTPUT) {
        *ddr_reg |= (1 << pin);  // Seta o bit para 1 (Output)
    } else {
        *ddr_reg &= ~(1 << pin); // Seta o bit para 0 (Input)
    }
}

void gpio_write(volatile uint8_t *port_reg, uint8_t pin, GpioState state) {
    if (state == GPIO_HIGH) {
        *port_reg |= (1 << pin);  // Nível lógico alto
    } else {
        *port_reg &= ~(1 << pin); // Nível lógico baixo
    }
}

bool gpio_read(volatile uint8_t *pin_reg, uint8_t pin) {
    // Verifica se o bit específico está setado
    if (*pin_reg & (1 << pin)) {
        return true; // Está HIGH
    }
    return false;    // Está LOW
}