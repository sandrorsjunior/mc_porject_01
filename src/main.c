#include "../include/gpio.h" // Incluímos nossa nova lib

typedef enum {
    STATE_CONFIG,
    STATE_CLOSED,
    STATE_OPEN
} MachineState;

int main(void)
{
    MachineState currentState = STATE_CONFIG;

    while (1)
    {
        switch (currentState)
        {
        case STATE_CONFIG:
            // Configura B1 como Input (Botão)
            gpio_config(&DDRB, DDB1, GPIO_INPUT);
            
            // Habilita o resistor de Pull-up interno em B1 (Escrevendo HIGH na entrada)
            gpio_write(&PORTB, PORTB1, GPIO_HIGH);
            
            // Configura C5 como Output (LED/Relé)
            gpio_config(&DDRC, DDC5, GPIO_OUTPUT);

            currentState = STATE_CLOSED;
            break;

        case STATE_CLOSED:
            // Desliga a saída C5
            gpio_write(&PORTC, PORTC5, GPIO_LOW);

            // Se a leitura de B1 for LOW (botão pressionado no GND)
            if (gpio_read(&PINB, PINB1) == false) {
                currentState = STATE_OPEN;
            }
            break;

        case STATE_OPEN:
            // Liga a saída C5
            gpio_write(&PORTC, PORTC5, GPIO_HIGH);

            // Se a leitura de B1 for HIGH (botão solto)
            // Nota: Isso assume que há um resistor de pull-up externo ou interno
            if (gpio_read(&PINB, PINB1) == true) { 
                currentState = STATE_CLOSED;
            }
            break;
        }
        
        // Pequeno delay para evitar leitura de ruído (Debounce simples)
        _delay_ms(10);
    }
}