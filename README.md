# I2C_Driver
Lightweight I²C Master Mode driver for Microchip PIC16F87XA microcontrollers using MPLAB XC8.
# I²C Bus Master Mode Driver Documentation

**Version:** 1.0.0
**Author:** **WilfriedEngineering**

---

## Design Philosophy

The **I²C Bus Driver** is designed according to the following software engineering principles:

* Modular architecture
* Hardware portability
* Code reusability
* Ease of maintenance
* Clear hardware abstraction layers
* Low memory footprint for embedded systems

**Programming Language:** C (MPLAB XC8)
**Target MCU:** Microchip PIC16F87XA Family (PIC16F873A, PIC16F874A, PIC16F876A, and PIC16F877A)
**Communication Interface:** I²C Standard Mode (100 kHz) and Fast Mode (400 kHz)

---

## 1. Driver Overview

The **I²C Bus Driver (Master Mode)** is a reusable embedded software library that provides a complete software interface for the **Microchip PIC16F87XA Family**, including the PIC16F873A, PIC16F874A, PIC16F876A, and PIC16F877A microcontrollers.

The driver supports the following operations:

* Bus initialization
* Start condition
* Repeated Start condition
* Data transmission
* Data reception
* Stop condition

The driver is designed to provide a simple, portable, and hardware-independent interface for applications requiring data exchange between an **I²C master (PIC16F87XA)** and one or more **I²C slave devices**.

---

## 2. Software Requirements

The following software tools and components are required to use and develop applications with this driver:

* **MPLAB X IDE**
* **MPLAB XC8 Compiler**
* **PIC16F87XA microcontroller**
* **I²C Bus Driver library**

---

## 3. Hardware Requirements

The following hardware components are required:

* PIC16F87XA microcontroller
* Pull-up resistors (typically **1–10 kΩ**) on the SDA and SCL lines
* Appropriate power supply for the I²C bus and connected slave devices

> **Note:** The appropriate pull-up resistor value depends on the bus capacitance, operating voltage, bus speed, and the number of connected devices.

---

## 4. Driver Architecture

```text
+----------------------+
|      Application     |
+----------------------+
           |
           v
+----------------------+
|      I²C Driver      |
+----------------------+
           |
           v
+----------------------+
|   PIC16F87XA I²C     |
|   Hardware Peripheral|
+----------------------+
```

The **I²C Bus Driver** provides a clean abstraction layer between the application software and the underlying hardware peripheral.

This modular architecture simplifies maintenance and allows the driver to be reused across different projects with minimal modifications.

---

## 5. Public API

### Data Structure

#### `BUS_I2C`

The `BUS_I2C` structure contains pointers to all public driver functions. Each function operates through the `BUS_I2C` interface.

The function names follow the following naming convention:

```text
BUS_I2C_<FunctionName>
```

---

### Function Descriptions

#### `Init`

```c
void (*Init)(unsigned long f_osc, const unsigned long f_bus);
```

Initializes and configures the I²C bus.

**Parameters:**

* `f_osc` — Microcontroller oscillator frequency, expressed in Hertz (Hz).
* `f_bus` — Desired I²C bus frequency, expressed in Hertz (Hz):

  * **100 kHz** for Standard Mode
  * **400 kHz** for Fast Mode

---

#### `Start`

```c
void (*Start)(void);
```

Generates an I²C **Start condition** and initiates communication with a slave device.

---

#### `Repeated_Start`

```c
void (*Repeated_Start)(void);
```

Generates an I²C **Repeated Start condition** without releasing the bus.

---

#### `Write`

```c
char (*Write)(char x_data);
```

Transmits one byte of data on the I²C bus.

**Parameters:**

* `x_data` — Byte of data to transmit.

**Return value:**

Returns a status value indicating the result of the transmission.

---

#### `Read`

```c
char (*Read)(char ack_val);
```

Reads one byte of data from the I²C bus.

**Parameters:**

* `ack_val = 0` — Reads the **last byte**. The master sends a **NACK** after receiving the byte, indicating that no more data is requested.
* `ack_val = 1` — Reads a byte and sends an **ACK**, indicating that the master wants to receive another byte.

**Return value:**

Returns the received byte.

##### `ack_val` Behavior

| `ack_val` | Operation                        | I²C Response |
| :-------: | -------------------------------- | ------------ |
|    `0`    | Read the last byte               | NACK         |
|    `1`    | Read a byte and continue reading | ACK          |

Example:

```c
data1 = BUS_I2C_Read(1);  // Read byte 1 and send ACK
data2 = BUS_I2C_Read(1);  // Read byte 2 and send ACK
data3 = BUS_I2C_Read(0);  // Read byte 3 and send NACK
```

The last byte of a read sequence should be read with `ack_val = 0`.

---

#### `Stop`

```c
void (*Stop)(void);
```

Generates an I²C **Stop condition** and terminates the current communication.

---

## 6. Driver Function Prototypes

The following public functions are provided by the driver:

```c
void BUS_I2C_Init(unsigned long f_osc, const unsigned long f_bus);

void BUS_I2C_Start(void);

void BUS_I2C_Repeated_Start(void);

char BUS_I2C_Write(char x_data);

char BUS_I2C_Read(char ack_val);

void BUS_I2C_Stop(void);
```

---

## 7. Important Notes

Before using the driver, ensure that the following conditions are satisfied:

* The I²C bus is properly initialized before calling any other driver function.
* The selected I²C bus frequency is supported by all devices connected to the bus.
* Appropriate pull-up resistors are connected to the SDA and SCL lines.
* The electrical characteristics of the bus are compatible with the connected devices.
* This driver supports **single-master I²C bus configurations only**.
* **Multi-master operation is not supported** by this library.
* I²C Slave Mode is not supported by this driver.

---

## 8. Driver Test / Demo

A demonstration project is available in the **`demo`** folder.

The demo provides an example of how to initialize and use the I²C driver in an application.

Typical operations demonstrated include:

1. Initializing the I²C bus
2. Starting communication
3. Sending data to a slave device
4. Receiving data from a slave device
5. Generating a Stop condition

### Demo Directory Guide

```text
demo/
│
├── BUS_I2C_Test.c
├── I2C_BUS_Test.X.production.hex
├── I2C_BUS_Test.pdsprj
├── I2C_BUS_Test.PDF
├── I2C_BUS_Test.mp4

```

### Files

* `BUS_I2C_Test.c` — Test source code
* `I2C_BUS_Test.X.production.hex` — Compiled firmware
* `I2C_BUS_Test.pdsprj` — Proteus simulation project
* `I2C_BUS_Test.PDF` — Test schematic
* `I2C_BUS_Test.mp4` — Test demonstration video


Refer to the source files in the `demo` folder for a practical example of driver usage.

---

## 9. References

For detailed information about the microcontroller hardware and I²C peripheral, refer to the following documentation:

* **Microchip PIC16F87XA Family Data Sheet**
* **MPLAB XC8 Compiler Documentation**
* **Microchip MPLAB X IDE Documentation**

---

## License

This project is licensed under the **MIT License**.

See the [`LICENSE`](LICENSE) file for the complete license text.

---

## Author

**WilfriedEngineering**

Embedded software and hardware development focused on microcontroller-based systems.
