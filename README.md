UART Echo Using Interrupts (Bare-Metal, STM32F401RE)
This project demonstrates how to implement UART echo using interrupt-driven communication on the STM32 Nucleo-F401RE board, configured with CMSIS and pure register-level programming — no HAL, no CubeMX.Instead of continuously polling the RX register, this setup uses the USART2 interrupt (RXNE) to receive characters and immediately echo them back via TX.

What It Does:
- Initializes USART2 on PA2 (TX) and PA3 (RX) at 9600 baud
- Enables RX interrupt using RXNEIE
- Triggers an interrupt when a character is received
- Echoes the character back in the interrupt context (non-blocking main loop)

Why Use Interrupts?
- Frees up the CPU from blocking RX loops
- Allows multitasking and better efficiency
- Scalable for command parsing and multitasking systems

Hardware:
- Board: STM32 Nucleo-F401RE
- TX Pin: PA2 (USART2_TX)
- RX Pin: PA3 (USART2_RX)
- Interface: ST-Link VCP (USB)
- Terminal: Arduino Serial Monitor / PuTTY / Tera Term

Baud Rate:- 9600 bps (BRR = 0x0683 for 16 MHz system clock)

Tools Used:
- Language: C (Bare-Metal CMSIS)
- IDE: Keil uVision5 / STM32CubeIDE
- Debugger: ST-Link (onboard)
- Terminal: Arduino Serial Monitor

How to Run:
1. Flash the code to STM32 Nucleo-F401RE
2. Connect to serial terminal at 9600 baud
3. Type any character — it will be echoed back instantly

Key Concepts Implemented:
1. CMSIS-level USART2 configuration
2. GPIO Alternate Function setup (AF7 for PA2/PA3)
3. Baud rate configuration via BRR register
4. RXNE interrupt handling (USART2_IRQHandler)
5. Non-blocking main loop (interrupt-driven design)
