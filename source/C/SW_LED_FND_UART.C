#include <stdint.h>

#define GPO_OUT_REG      (*(volatile uint32_t *)0x20001000)
#define GPI_IN_REG       (*(volatile uint32_t *)0x20001004)
#define GPIO_REG         (*(volatile uint32_t *)0x20002000)
#define FND_REG          (*(volatile uint32_t *)0x20003004)
#define UART_STATUS_REG  (*(volatile uint32_t *)0x20004008)
#define UART_TX_DATA_REG (*(volatile uint32_t *)0x2000400C) 


void uart_putc(char c) {
    while ((UART_STATUS_REG & 0x01) == 0); 
    UART_TX_DATA_REG = c;
}


void uart_print_hex(uint16_t val) {
    char hex[] = "0123456789ABCDEF";
    uart_putc('V'); uart_putc(':'); uart_putc(' ');
    uart_putc(hex[(val >> 12) & 0xF]); 
    uart_putc(hex[(val >> 8) & 0xF]);  
    uart_putc(hex[(val >> 4) & 0xF]);  
    uart_putc(hex[val & 0xF]);        
    uart_putc('\r'); uart_putc('\n');
}

int main(void) {
    uint32_t sw_left, sw_right, total_val;
    uint32_t last_val = 0xFFFF; 

    while (1) {
        sw_left  = GPI_IN_REG & 0xFF;
        sw_right = GPIO_REG & 0xFF;
        total_val = (sw_left << 8) | sw_right;

     
        GPO_OUT_REG = sw_left;
        GPIO_REG = (sw_right << 8);
        FND_REG = total_val;

  
        if (total_val != last_val) {
            uart_print_hex(total_val);
            last_val = total_val; 
        }
    }
    return 0;
}