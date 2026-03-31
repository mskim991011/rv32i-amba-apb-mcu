#include <stdint.h>

#define GPO_OUT_REG    (*(volatile uint32_t *)0x20001000) // LED[15~8]
#define GPI_IN_REG     (*(volatile uint32_t *)0x20001004) // SW[15~8] 
#define GPIO_ODATA_REG (*(volatile uint32_t *)0x20002004) //  LED[7~0]
#define GPIO_IDATA_REG (*(volatile uint32_t *)0x20002008) //  SW[7~0] 

int main(void) {
    uint32_t sw_left, sw_right;

    while (1) {
     
        sw_left  = GPI_IN_REG & 0xFF;  
        sw_right = GPIO_IDATA_REG & 0xFF;

      
        GPO_OUT_REG = sw_left; 
        
   
        GPIO_ODATA_REG = (sw_right << 8); 
    }
    return 0;
}