# vixen_arduino_ws2812

## setup in Vixen
1. Add a generic serial controller

![image](https://user-images.githubusercontent.com/590535/121105439-1daf0100-c7d2-11eb-9a81-21ec114c6cae.png)

2. Give it a number of outputs equal to the number of strings (4) x leds per string (300) x number of colors (3) = 3600

![image](https://user-images.githubusercontent.com/590535/121105588-6070d900-c7d2-11eb-8fae-b95af3a815a5.png)

3. Assign a COM port and give it the baud rate 921600

![image](https://user-images.githubusercontent.com/590535/121105645-7bdbe400-c7d2-11eb-9a36-a5818b025d16.png)

4. The text header is a single right ankle

![image](https://user-images.githubusercontent.com/590535/121105682-8c8c5a00-c7d2-11eb-8ac7-71b8a33add16.png)

5. Patch the correct number of strings by checking that the output counts match

![image](https://user-images.githubusercontent.com/590535/121105803-ca897e00-c7d2-11eb-9ded-807ec2bd4024.png)

## MCU programming
* Designed for Sparkfun SAMD21 mini breakout
* Ring buffer size increased to 1024
* Use the boards manager to install Sparkfn SAMD 1.6.1 and Arduino SAMD 16.19
* the controller will do a 5x fast blink initializtion during bootup and the blue LED should do dark.
* When talking to Vixen the blue LED is rapid blinking
