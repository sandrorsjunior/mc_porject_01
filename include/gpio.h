/*
 * gpio.h
 * Biblioteca simples para controle de GPIO em AVR
 */ 

#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

// Definições para facilitar a leitura
typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1
} GpioDirection;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} GpioState;

/**
 * Configura a direção do pino (Input ou Output)
 * @param ddr_reg: Ponteiro para o registrador de direção (ex: &DDRB)
 * @param pin: Número do pino (ex: PB1)
 * @param direction: GPIO_INPUT ou GPIO_OUTPUT
 */
void gpio_config(volatile uint8_t *ddr_reg, uint8_t pin, GpioDirection direction);

/**
 * Escreve HIGH ou LOW em um pino configurado como saída
 * @param port_reg: Ponteiro para o registrador de porta (ex: &PORTC)
 * @param pin: Número do pino (ex: PC5)
 * @param state: GPIO_HIGH ou GPIO_LOW
 */
void gpio_write(volatile uint8_t *port_reg, uint8_t pin, GpioState state);

/**
 * Lê o estado atual de um pino
 * @param pin_reg: Ponteiro para o registrador de entrada (ex: &PINB)
 * @param pin: Número do pino (ex: PB1)
 * @return: true se HIGH, false se LOW
 */
bool gpio_read(volatile uint8_t *pin_reg, uint8_t pin);

#endif