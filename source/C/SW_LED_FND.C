#include <stdint.h>

#define GPO_OUT_REG    (*(volatile uint32_t *)0x20001000)
#define GPI_IN_REG     (*(volatile uint32_t *)0x20001004)
#define GPIO_REG       (*(volatile uint32_t *)0x20002000)
#define FND_REG        (*(volatile uint32_t *)0x20003004)

int main(void) {
    uint32_t sw_left, sw_right, total_val;

    while (1) {
        sw_left  = GPI_IN_REG & 0xFF; 
        sw_right = GPIO_REG & 0xFF; 

        
        total_val = (sw_left << 8) | sw_right;

       
        GPO_OUT_REG = sw_left; 
        GPIO_REG = (sw_right << 8); 

     
        FND_REG = total_val; 
    }
    return 0;
}