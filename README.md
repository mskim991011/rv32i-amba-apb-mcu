#  RISC-V RV32I Multi-Cycle SoC with AMBA APB Protocol

##  Project Overview
This project implements a **full-stack System-on-Chip (SoC) integrating Hardware and Software**. It features a custom-designed **32-bit RISC-V (RV32I) Multi-Cycle processor** and an **AMBA APB (Advanced Peripheral Bus)** protocol to interface with various peripheral IPs. The entire system was designed at the RTL level (Verilog/SystemVerilog), verified via simulation, and successfully validated on a **Xilinx Basys 3 FPGA board** using C programming for Hardware/Software Co-design.

##  Key Features
* **RV32I Multi-Cycle Core:** Designed a 5-stage instruction execution cycle (Fetch, Decode, Execute, Memory, Write-back) using an FSM-based Control Unit. This resolves the critical path delay issues found in single-cycle architectures, allowing for a higher and more stable clock frequency.
* **AMBA APB Protocol Integration:** Designed a standard APB Master and Slave interface (Setup and Access phases) to resolve the speed gap between the high-speed CPU and slow I/O devices.
* **Custom Peripheral IPs:** Designed RTL modules for RAM, GPO, GPI, GPIO (with tri-state buffers), 7-Segment (FND) Controller, and UART.
* **HW/SW Co-Design:** Handled peripherals using Memory-Mapped I/O (MMIO) and developed bare-metal C software to control hardware behavior dynamically.
* **FPGA Validation:** Synthesized and tested on a Digilent Basys 3 FPGA, successfully interacting with switches, LEDs, 7-Segment displays, and PC serial terminals.

---

##  System Architecture

### 1. Multi-Cycle RISC-V Processor
Unlike a single-cycle CPU that performs address decoding, data transfer, and writing in one clock, this architecture separates the workload into distinct cycles using registers between stages.
* **Control Unit (FSM):** Implemented a Finite State Machine (FSM) with 9 states to systematically sequence instructions based on their Opcode.

### 2. AMBA APB Bus Architecture
The APB Master controls the bus transactions (Read/Write) issued by the RISC-V CPU.
* **Address Decoder:** Routes the CPU's address to the corresponding APB Slave (RAM, GPIO, UART, etc.) via the `PSELx` signal.
* **Multiplexer (MUX):** Selects the `PRDATA` and `PREADY` signals from the active slave and passes them back to the CPU.

---

##  Memory Map
The SoC utilizes Memory-Mapped I/O (MMIO) to access memory and peripherals.

| Base Address | Size | Description (Peripheral) |
| :--- | :--- | :--- |
| `0x0000_0000` | 4KB | **ROM** (Instruction Memory) |
| `0x1000_0000` | 4KB | **RAM** (Data Memory) |
| `0x2000_0000` | 4KB | **GPO** (General Purpose Output / LEDs) |
| `0x2000_1000` | 4KB | **GPI** (General Purpose Input / Switches) |
| `0x2000_2000` | 4KB | **GPIO** (In/Out with tri-state buffer) |
| `0x2000_3000` | 4KB | **FND** (4-Digit 7-Segment Display Controller) |
| `0x2000_4000` | 4KB | **UART** (Serial Communication) |

---

##  Software Implementation (C Code)
The software layer is written in C and directly interacts with the hardware registers defined in the memory map.
* **Switch & LED Control:** Reads the 16-bit input from the Basys 3 switches (GPI) and outputs the corresponding values to the LEDs (GPO).
* **7-Segment Display:** Combines upper and lower 8-bit switch inputs into a 16-bit value and sends it to the FND controller to display hexadecimal values.
* **UART Polling:** Evaluates the `UART_STATUS` register via polling to check the `TX_READY` flag, ensuring data synchronization between the fast CPU and the slow 9600 bps UART transmission.

---

##  Limitations & Future Work
1. **Interrupt Controller (IRQ):** The current UART and switch monitoring rely heavily on infinite polling loops, which consumes significant CPU resources. Future designs will implement an Interrupt Controller to achieve an event-driven architecture, increasing overall system efficiency.
2. **Bus Expansion:** To support higher bandwidth peripherals (e.g., Video, DMA), the bus architecture will be extended to include AMBA AHB or AXI protocols.
