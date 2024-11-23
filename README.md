# Simple Calculator

## Introduction
This project implements a simple calculator on an ATmega32 microcontroller using a character LCD (CLCD) and three push buttons. The calculator allows the user to perform basic arithmetic operations (`+`, `-`, `*`, `/`) between two single-digit numbers. The result is displayed on the LCD.

---

## Features
- Supports basic arithmetic operations:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`)
- User-friendly interface with a **Character LCD (CLCD)** and **push buttons**.
- Error handling for division by zero.
- Clean and modular code for easy readability and reusability.

---

## Components
### Hardware
1. **Microcontroller**: ATmega32
2. **Display**: 16x2 Character LCD (CLCD)
3. **Input Devices**: 3 Push Buttons
4. **Power Source**: 5V DC power supply

### Software
- Code is written in C and uses:
  - **AVR-GCC**: For compiling the code.
- Standard AVR utility libraries:
  - `<util/delay.h>` for implementing delays.

---

## Circuit Design
### Pin Configuration
- **LCD Connections**:
  - Data Pins: Connected to `PORTA`
  - Control Pins (RS, RW, EN): Connected to `PORTC` (pins 0, 1, 2 respectively)
- **Push Buttons**:
  - **Button 1**: Increases the current number (connected to `PORTD, PIN2`).
  - **Button 2**: Decreases the current number (connected to `PORTD, PIN3`).
  - **Button 3**: Confirms the current step:
    1. Finalizes the input of the first number and moves to the operation selection.
    2. Finalizes the operation selection and moves to the second number.
    3. Finalizes the second number and calculates the result.

---

## How It Works
### Input Workflow
1. **Start**:
   - The LCD initializes and displays:
     ```
     1 + 1
     ```
   - By default, the first number is `1`, the operator is `+`, and the second number is `1`.

2. **Input the First Number**:
   - Use **Button 1** to increase the first number (cycles between 0-9).
   - Use **Button 2** to decrease the first number (cycles between 0-9).
   - Press **Button 3** to confirm the first number and move to the operation selection.

3. **Select the Operation**:
   - Use **Button 1** to cycle through operations (`+`, `-`, `*`, `/`).
   - Use **Button 2** to cycle backward through operations.
   - Press **Button 3** to confirm the operation and move to the second number.

4. **Input the Second Number**:
   - Use **Button 1** to increase the second number (cycles between 0-9).
   - Use **Button 2** to decrease the second number (cycles between 0-9).
   - Press **Button 3** to confirm the second number and calculate the result.

5. **Display the Result**:
   - The LCD displays the result of the operation.
   - If dividing by zero, the LCD shows `"Err"`.
