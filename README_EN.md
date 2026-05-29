# 1.28" 240×240 TFT SPI module (GC9A01) — documentation & samples

**简体中文：** [`README.md`](README.md)

---

> This repository provides an **ESP-IDF sample project**. Datasheets and specifications will be added to `docs/` when available.

## Product overview

| Item | Description |
|:--|:--|
| Module | 1.28-inch **TFT** (round), **240×240** resolution |
| Interface | **SPI** |
| Driver IC | **GC9A01** |
| Spec ID | **`1.28-tft-240x240-spi-gc9a01`** is the common product designation in documentation |

---

## Repository layout

### Top-level

| Path | Contents |
|:--|:--|
| `assets/` | Demo screenshots for sample projects (when available) |
| `docs/` | Datasheets and specifications (**to be added**) |
| `examples/` | **Sample projects** |

### `examples/` layout

| Location | Description |
|:--|:--|
| `examples/` root | ESP32-S3 + IDF5: GC9A01 SPI + LVGL9 (round display UI animation demo) |

### Sample project paths

| Description | Path |
|:--|:--|
| GC9A01 SPI bringup (LVGL9) | `examples/esp32s3-1.28-tft-240x240-spi-gc9a01-bringup/` |
