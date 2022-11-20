# 此文件夹是STM32在ST7735上移植LVGL，pdf有教程。
## ST7735用stm32f103zet6的SPI1。片选脚CS用软件管脚。cubemx设置SPI1选仅主机发送模式，只需要SPI1_MOSI (SDA),不需要SPI_MISO.因为显示屏只接受单片机发来的数据，不向单片机发送数据。
    DC-->B10
    RST-->B12
    CS-->B11
