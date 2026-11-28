## Related Project

A more comprehensive Python-based implementation of IEEE 802.11bc, covering the complete end-to-end communication workflow, is available in a separate repository.

See [IEEE 802.11bc Python Implementation](https://github.com/ichenglin/80211bc-ebcs).

## Prerequisites

- ESP32 board with [Wi-Fi capability](#tested-boards) and USB cable
- [ESP-IDF and Tools](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#installation)
- [ESP-IDF Extension for VSCode](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/index.html) (Optional)

> [!NOTE]
> This project was developed and tested with **ESP-IDF v6.1.1**.
> Using this version is recommended to ensure compatibility.

## Setup Environment

Configure the target device and flashing settings. For example:

- Device Target: `esp32c5`
- Serial Port: `/dev/ttyUSB0`
- Flash Method: `UART`

Next, open the SDK Configuration Editor (menuconfig) and configure the following parameters.
The values shown are for reference and should be adjusted as needed:

- Board Role: `Device`
- Board Wi-Fi Channel: `1`
- Device Button GPIO: `0` *(Device Only)*

Once the configuration is complete, the project is ready to be built and flashed onto the device.

## Tested Boards

The implementation is expected to work on all ESP32 SoCs equipped with Wi-Fi connectivity.
ESP32-H and ESP32-P series are excluded, as they do not include Wi-Fi support.

The following table lists the boards tested so far:

| SoC      | Module           | Board                               | Wi-Fi       | Status |
|----------|------------------|-------------------------------------|-------------|--------|
| ESP32    | ESP32-WROOM-32   | (Generic) ESP32 DevKit V1           | 2.4     GHz | Tested |
| ESP32-S3 | ESP32-S3N8       | Heltec WiFi LoRa 32          (V3)   | 2.4     GHz | Tested |
| ESP32-C5 | ESP32-C5-WROOM-1 | Espressif ESP32-C5-DevKitC-1 (V1.2) | 2.4 / 5 GHz | Tested |
