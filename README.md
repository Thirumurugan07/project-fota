# 🔐 OPTIGA™ Trust M – Data Transfer with STM32 (Unprotected Mode)

This project demonstrates communication between an STM32F4 microcontroller and the **Infineon OPTIGA™ Trust M** security chip using I²C in **unprotected mode**. It focuses on writing and reading data and metadata to/from specific data objects on the Trust M using the OPTIGA™ Util APIs.

## 🧾 Description

This `main` branch represents the **first milestone** in our development journey:

- ✅ Successful hardware communication with OPTIGA Trust M over I²C.
- ✅ Data write and metadata operations to secure element (OID `0xE0E8`).
- ✅ Verified data and metadata reads.
- ❌ Secure communication (e.g., Shielded/Protected) is **not enabled** in this branch.
- ❌ Cryptographic functions are not part of this baseline (to be implemented in later branches).

We use the STM32 HAL-based Pico COM board, and STM32CubeIDE as the toolchain.

---

## 🧱 Project Structure

```bash
.
├── Core/                          # STM32 Application Code
│   ├── Inc/                      # Header files
│   ├── Src/                      # Source files (main.c, pal, i2c, etc.)
│   └── Startup/                  # Startup and linker files
├── Drivers/                      # CMSIS and STM32 HAL drivers
├── optiga/                       # OPTIGA Trust M integration
│   ├── comms/                    # I2C transport stack
│   ├── common/                   # Shared definitions/utilities
│   ├── crypt/                    # Placeholder for future ECC support
│   ├── util/                     # OPTIGA Util APIs (read/write)
│   └── include/                  # Header definitions for all layers
├── pal/
│   └── stm32_hal/                # Platform abstraction for STM32 HAL
├── Debug/                        # Build output
│   └── ...                       # IDE-generated debug folders
├── README.md                     # This file
