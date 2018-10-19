/*
--------------------------------------
RPI 1/2/3
--------------------------------------
+3V3                1       2   +5V0
GPIO2 / I2C 1 SDA   3       4   +5v0
GPIO3 / I2C 1 SCL   5       6   GND
GPIO4               7       8   GPIO14 / UART TX
GND                 9       10  GPIO15 / UART RX
GPIO17              11      12  GPIO18
GPIO27              13      14  GND
GPIO22              15      16  GPIO23
+3V3                17      18  GPIO24
GPIO10 / SPI 0 MOSI 19      20  GND
GPIO9 / SPI 0 MISO  21      22  GPIO25
GPIO11 / SPI 0 SCLK 23      24  GPIO8 / SPI 0 CS0
GND                 25      26  GPIO7 / SPI 0 CS1
--------------------------------------
RPI 2/3
--------------------------------------
RESVD               27      28  RESVD
GPIO5               29      30  GND
GPIO6               31      32  GPIO12
GPIO13              33      34  GND
GPIO19 / SPI 1 MISO 35      36  GPIO16 / SPI 1 CS0
GPIO26              37      38  GPIO20 / SPI 1 MOSI
GND                 39      40  GPIO21 / SPI 1 SCLK
*/

#define US_INPUT    16  // Ultrasonic signal from Arduino

#ifdef _HAS_SERIAL
#define HOST_PORT "/dev/ttyS4"
#endif
