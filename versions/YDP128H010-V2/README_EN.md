<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 1.28″ TFT 240×240 (GC9A01 · SPI)</h1>

<p align="center"><b>Round TFT module · SPI · GC9A01</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English · <a href="../../README_EN.md">Family index</a></p>

<p align="center">
  <img alt="Size: 1.28 inch" src="https://img.shields.io/badge/Size-1.28%22-3498DB?style=flat-square" />
  <img alt="Resolution: 240x240" src="https://img.shields.io/badge/Resolution-240%C3%97240-8E44AD?style=flat-square" />
  <img alt="Interface: SPI" src="https://img.shields.io/badge/Interface-SPI-27AE60?style=flat-square" />
  <img alt="Driver: GC9A01" src="https://img.shields.io/badge/Driver-GC9A01-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 1.28&quot; 240×240 TFT SPI module (GC9A01) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **1.28″ 240×240 TFT** is a round **SPI** color display module driven by **GC9A01**. Suited to wearables, round gauges, and compact circular HMI.

Spec ID (repository name): `tft-1.28-240x240-spi-gc9a01`

Current panel version: **YDP128H010-V2**. Electrical and mechanical details follow [`docs/YDP128H010-V2.pdf`](./docs/YDP128H010-V2.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 1.28 inch |
| Type | TFT (color, round) |
| Resolution | 240×240 |
| Interface | SPI |
| Driver IC | GC9A01 |

> Full outline, FPC definition, power, and timing follow the screen datasheet / mechanical drawing / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-S3 · GC9A01 SPI + LVGL9 (circular UI demo) | [`examples/esp32s3-tft-1.28-240x240-spi-gc9a01-bringup/`](./examples/esp32s3-tft-1.28-240x240-spi-gc9a01-bringup/) |

## Repository layout

```text
tft-1.28-240x240-spi-gc9a01/                                # repo root (nav: ../../README_EN.md)
└── versions/
    └── YDP128H010-V2/                                # full materials for this part number
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Screen datasheet (YDP128H010-V2) | [`docs/YDP128H010-V2.pdf`](./docs/YDP128H010-V2.pdf) |
| Driver IC datasheet (GC9A01) | [`docs/LCD_DST_3015_GC_9_A01_Data_Sheet_V1_0_Preliminary_2_35d4b172aa.pdf`](./docs/LCD_DST_3015_GC_9_A01_Data_Sheet_V1_0_Preliminary_2_35d4b172aa.pdf) |
| Init sequence (text) | [`docs/HSD1.28+GC9A01 initial code 20191231 优美K15.txt`](./docs/HSD1.28+GC9A01%20initial%20code%2020191231%20%E4%BC%98%E7%BE%8EK15.txt) |

### Samples

- [ESP32-S3 GC9A01 SPI + LVGL9](./examples/esp32s3-tft-1.28-240x240-spi-gc9a01-bringup/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group (China): **985881096**
- Website: <https://osptek.com/>
- Feel free to open an Issue in this repository if you have any questions

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
