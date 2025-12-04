# 🔧 STM32 RTOS with Cooperative Multitasking and Semaphores

This project implements a basic Real-Time Operating System (RTOS) kernel on an STM32F103 microcontroller. It features cooperative multitasking using semaphores for task synchronization. UART is used for debugging and motor control status messages.

---

## 📌 Features

- Cooperative multitasking (manual context switching)
- Two concurrent tasks: `Task0` (Motor Run) and `Task1` (Motor Stop)
- Binary semaphore-based synchronization
- UART communication for runtime feedback
- Configurable time quanta

---

## 🛠 System Requirements

- **MCU**: STM32F103C8T6 (Blue Pill)
- **Toolchain**: `arm-none-eabi-gcc`, ST-Link, or Keil MDK
- **Peripherals**:
  - UART1 (for messages)
  - GPIO (optional for motor control)

---

## 🚀 How It Works

1. `osKernelInit()` initializes the RTOS.
2. Two threads are added: `Task0` and `Task1`.
3. Two semaphores are initialized:
   - `semaphore1` starts at `1` to allow `Task0` to run first.
   - `semaphore2` starts at `0` to block `Task1`.
4. `Task0` runs, simulates a motor run, then gives `semaphore2`.
5. `Task1` stops the motor and gives `semaphore1`.
6. The loop continues with coordinated hand-off using semaphores.

---

## 📁 File Structure

| File        | Description                            |
|-------------|----------------------------------------|
| `main.c`    | Application code with tasks and semaphores |
| `osKernel.c/.h` | RTOS core: thread stack, scheduler, semaphores |
| `uart.c/.h` | UART1 driver for debugging output      |
| `startup.s` | Startup assembly for Cortex-M3         |
| `stm32f103.ld` | Linker script (if using GCC)         |

---




