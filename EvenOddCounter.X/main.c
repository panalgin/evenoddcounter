// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 4000000

#define oddPin PORTAbits.RA0
#define evenPin PORTAbits.RA1
#define tripletPin PORTAbits.RA2

unsigned char digits[] = {
    /*0b00111111, 0*/ 0b11000000,
    /*0b00000110, 1*/ 0b11111001,
    /*0b01011011, 2*/ 0b10100100,
    /*0b01001111, 3*/ 0b10110000,
    /*0b01100110, 4*/ 0b10011001,
    /*0b01101101, 5*/ 0b10010010,
    /*0b01111101, 6*/ 0b10000010,
    /*0b00000111, 7*/ 0b11111000,
    /*0b01111111, 8*/ 0b10000000,
    /*0b01101111, 9*/ 0b10010000,
};

void nextOdd();
void nextEven();
void nextTriplet();
void printNumber();

unsigned char currentNumber = 0;

void main(void) {
    CMCON = 0x07;
    PCONbits.OSCF = 1; //Use 4mhz internal osc

    TRISA = 0b00000111;
    TRISB = 0x00;

    PORTA = 0x00;
    PORTB = 0x00;

    while (1) {
        if (oddPin == 0) {
            __delay_ms(10);
            
            if (oddPin == 0) {
                nextOdd();
                
                __delay_ms(300);
            }
        }
        else if (evenPin == 0) {
            __delay_ms(10);
            
            if (evenPin == 0) {
                nextEven();
                
                __delay_ms(300);
            }
        }
        else if (tripletPin == 0) {
            __delay_ms(10);
            
            if (tripletPin == 0) {
                nextTriplet();
                
                __delay_ms(300);
            }
        }
        
        printNumber();
    }

    return;
}

void nextOdd() {
    if (currentNumber % 2 != 1)
        currentNumber++;
    else
        currentNumber += 2;
    
    currentNumber %= 10;
}

void nextEven() {    
    if (currentNumber % 2 != 0)
        currentNumber++;
    else
        currentNumber += 2;
    
    currentNumber %= 10;
}

void nextTriplet() {
    currentNumber += 3;
    currentNumber %= 10;
}

void printNumber() {
    PORTB = digits[currentNumber];
}
