# Device Driver for a SSD1306 OLED LCD on BeagleBone Black board

# Testing video:
https://www.youtube.com/watch?v=1O1K57AnjL8

# How to use:
- Include the ssd1306_lcd.dtsi into am335x-boneblack.dts
- Rebuild & copy new dtb file to the device.
- Compile the driver: make driver
- Compile the test app: make user_app
- Load the driver then load the user_app to control the LCD