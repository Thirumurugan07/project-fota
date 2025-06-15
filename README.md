# 🔐 OPTIGA™ Trust M – STM32 Data Transfer Example

This repository provides an integration example between **Infineon’s OPTIGA™ Trust M** and an **STM32F4 microcontroller**, enabling secure data read/write operations over I2C.

It demonstrates the use of OPTIGA Trust M middleware layers (communication, PAL, utility, crypto) with STM32 HAL, featuring full build support, modular organization, and debugging compatibility.

---

## ✅ Features Implemented

- [x] Initialized OPTIGA™ Trust M in unprotected mode
- [x] Wrote trust anchor and metadata to OID `0xE0E8`
- [x] Read certificate and metadata from OID `0xE0E0`
- [x] Used UART (via PicoCOM) for real-time debug output
- [x] Modularized code with `optiga_util_*` APIs
- [x] Integrated middleware: `pal`, `optiga`, `hal`

---

## 🔧 Prerequisites

### Hardware
- STM32F4 series board (e.g., STM32F401RE)
- OPTIGA™ Trust M Shield or breakout board
- UART-USB converter (or onboard ST-Link VCOM)
- Breadboard and jumper wires

### Software
- STM32CubeIDE
- Infineon OPTIGA™ Trust M middleware
- PicoCOM / PuTTY / TeraTerm (for UART logs)
- Git (for version control)

---
## 🧱 Project Structure

```bash
.
├── Core/
│   ├── Inc/                        # Header files (main.h, HAL config, interrupt handlers)
│   ├── Src/                        # Application logic and middleware calls
│   └── Startup/                   # Startup assembly and system init
├── Drivers/                        # CMSIS and STM32 HAL drivers
├── optiga/
│   ├── comms/                      # I2C communication layers for Trust M
│   ├── common/                     # Common utility and support files
│   ├── crypt/                      # Cryptographic interface to Trust M
│   ├── util/                       # OPTIGA Util API (read/write/data mgmt.)
│   └── include/                    # API headers for integration
├── pal/
│   └── stm32_hal/                  # Platform abstraction for STM32 HAL
├── Debug/                          # IDE-generated build output
├── README.md                       # Project documentation
└── ...          

