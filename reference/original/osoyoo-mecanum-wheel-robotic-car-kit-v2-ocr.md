## OSOYOO Mecanum Wheel Robotic Car Kit V2 for Arduino

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970230.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=nyZxhCg5TWCqsSdgIbOrWnspfNQ%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

# INTRODUCTION

</div>

Mecanum wheels, also known as omni wheels or Ilon wheels, consist of a hub with rollers oriented $ 4 5^{\circ} $ to the axis of rotation. The mecanum wheels are wheel hubs fitted with integrated rollers that move passively and independently.

Depending on which wheels rotate in which direction, the platform will move forward, backward, sideways, diagonally, or spin in place. This range of maneuverability enables the omni platform to efficiently navigate any space, particularly around tight corners, narrow lanes, and complex pathways.

This Arduino omini direction robot car learning kit is developed our Japan and Canada engineer team. It has all features a traditional Arduino Robot car should have, including remote control by bluetooth, IoT through wifi, line tracking, obstacle avoidance auto driving and object follow. With the help of powerful mecanum wheels, the car can make much more complicated movement such as sideway shifting and diagonally movement controlled by cell phone APP.

The kit comes with OSOYOO Mega2560 board (fully compatible with Arduino Mega2560) and OSOYOO ESP8266 WiFi shield. Besides, we have designed five step by step lessons which help students to learn Arduino robot programming from scratch. If you are an experience DIY player or Arduino programmer, you can also get a lot of knowledge from this kit's open source code and hardware to make interesting DIY project of your own.

Download PDF Tutorial: https://osoyoo.com/manual/2021006600-2026.pdf

OSOYOO Robot car installation video: https://osoyoo.com/manual/2021006600.html

## AUTHORIZED ONLINE RETAILERS

<table border="1"><tr><td>Buy from US</td><td>Buy from UK</td><td>Buy from DE</td><td>Buy from IT</td><td>Buy from FR</td><td>Buy from ES</td><td>Buy from JP</td></tr><tr><td>BUY NOW</td><td>BUY NOW</td><td>BUY NOW</td><td>BUY NOW</td><td>BUY NOW</td><td>BUY NOW</td><td>BUY NOW</td></tr></table>

## CONTENTS

Lesson 1 Basic Robot Car Assembly...4

Lesson 2 Obstacle Avoidance Robot Car...26

Lesson 3 Tracking Line Robot Car...34

Lesson 4 Object Follow Robot Car...39

Lesson 5-Imitation Driving With Bluetooth...44

Lesson 6 Wifi Iot Controlled Robot Car...52

<div align="center">

# Lesson 1 Basic Robot Car Assembly

</div>

## INTRODUCTION

Mecanum omni direction wheel is a very interesting wheel which allows robot car make omni-directional movement ( e.g. parallel shift to left and right).

In this project, we will show how to use Arduino to control an osoyoo brand mecanum wheel robot car to make some basic movement including go forward, backward, left turn, right turn, parallel left shift, parallel right shift etc.

This lesson also shows you how to install the chassis of this car and connect Arduino control signal wires to model Y board. This installation will be the start point of our other lessons.

<table><tr><td>OSOYOO Mecanum wheels robotic car chassis x1</td></tr><tr><td>OSOYOO Wheels and motors x4 (left-wheels x2/right-wheels x2)</td></tr><tr><td>OSOYOO Mega2560 board fully compatible with Arduino UNO/Mega2560 x1</td></tr><tr><td>OSOYOO Uart Wifi shield x1</td></tr><tr><td>OSOYOO Model Y Motor driver board</td></tr><tr><td>OSOYOO Voltage meter x1</td></tr><tr><td>OSOYOO Battery box x1</td></tr><tr><td>OSOYOO 6pin male to female jumper wire x2</td></tr><tr><td>OSOYOO 3pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 2 pin PnP female to female x1</td></tr><tr><td>18650 Batteries(3.7V) x2</td></tr><tr><td>Battery charger x1</td></tr></table>

<div align="center">

Step1. Please install the white coupling onto the yellow motor according to the steps shown in the image, ensuring that the coupling is inserted all the way to the base.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970283.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=nXl8Dc0JLILXmTZdH1pX8Tet69g%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970309.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=0rXHSC7Nyk9MvnjAE9owmrM%2BNfs%3D&Expires=1789692770' alt='OCR图片'/></div>

Step2. Attach the 4 motors using the metal motor holders as shown. (Please ensure the motor orientation is correct before installing the metal motor holders.)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970313.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=yvMlFHCntzT7af%2Fl42o%2BMvn5MPI%3D&Expires=1789692770' alt='OCR图片'/></div>

Step3. Secure the 4 motors to the lower car chassis using M3*10 hex screws and a hex screwdriver, as shown in the image. (The screws required for this step are included in the metal motor holder package.)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970326.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=knsYg5WNpiXwahaOtrvJnykhJFE%3D&Expires=1789692770' alt='OCR图片'/></div>

Step4. Mount the OSOYOO Model Y driver board onto the lower car chassis using 4 M3 plastic screws, plastic pillars, and plastic nuts (It is recommended to install the plastic pillar with the male end facing downward.) . Connect the 4 motors to the K1 and K3 sockets on the Model Y motor driver board, as shown in the diagram. There are two installation modes for plastic pillars: A. The male end of the plastic pillar faces downward. B. The male end of the plastic pillar faces upward.

About Model Y V2.0 H-Bridge 4-Channel Motor Driver: https://osoyoo.com/?p=46344

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970332.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=M58VybYnryRiyq6EyhcocKSNPtI%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970340.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=BLabIU7bvRYkyTs8HnR6Bl5eqbY%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970350.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=4rRgfjuw0plcXjUKLbCGUs%2F2lgY%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970357.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=qdUzMdnd0WDL4dBi7uXM1AizAEU%3D&Expires=1789692770' alt='OCR图片'/></div>

<table border="1"><tr><td>Wheel Motor</td><td>Model Y board</td></tr><tr><td>Front-right wheel motor</td><td>BK1</td></tr><tr><td>Front-left wheel motor</td><td>BK3</td></tr><tr><td>Rear-right wheel motor</td><td>AK1</td></tr><tr><td>Rear-left wheel motor</td><td>AK3</td></tr></table>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_4_1789087970367.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=GNw05JaRJfo05mKa2xW6kU6Wsf0%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step5. Attach the tracking sensor module to the lower chassis using two M3 plastic screws, two M3 plastic pillars, and two M3 plastic nuts (It is recommended to install the plastic pillar with the male end facing upward). Ensure the sensor is securely fixed and properly aligned for accurate functionality.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970372.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=2dc%2FsIm9C20clW4NPAlMLYnSzS0%3D&Expires=1789692770' alt='OCR图片'/></div>

Step6. Attach six M3*40 copper pillars to the lower chassis using six M3*10 screws and six M3 washers. Ensure the pillars are firmly fixed to provide stable support for the upper chassis.

Slide the washer onto the screw, a washer distributes screw pressure and improves stability when securing screws into metal pillars.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970378.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=0xCMgiMHDhsYPX3gT42XP0NyqFU%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step7. Use M3*10 screws and M3 nuts to attach the battery box to the designated markings on the upper chassis.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970391.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=Pks6VqjZG3my1sQWS0bA0WvQtug%3D&Expires=1789692770' alt='OCR图片'/></div>

Step8. Attach the voltage meter to the designated markings on the lower chassis using two M3 plastic screws, two M3 plastic pillars, and two M3 plastic nuts. (It is recommended to install the plastic pillar with the male end facing upward.)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970405.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=4HjluMwRFmo%2FpX1wCNeIVz%2FawOU%3D&Expires=1789692770' alt='OCR图片'/></div>

Step9. Fix OSOYOO Mega2560 board on upper car chassis with 6pcs M3 plastic screws, 6pcs plastic pillars and 2pcs plastic nuts. (Please install mega2560 board at the side with printing.)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970414.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=Bvmfl03UrLHkgoLZuv6TY7prsv4%3D&Expires=1789692770' alt='OCR图片'/></div>

Insert the OSOYOO UART WiFi Shield into the Mega2560 board. Ensure it is properly aligned and securely connected to establish a stable communication interface

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970422.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=bAc5kgV%2FVmNNF2jMfTqnC82AiW4%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step10. Using two M2.2*8 self-tapping screws, mount the servo motor at the front of the upper chassis.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970428.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=GWPDAtEUioLG8a2DgtV0YmG80GY%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step11. Attach two IR distance sensors to the front of the upper chassis using two M3 plastic screws, M3 plastic pillars, and M3 plastic nuts. To secure the sensors tightly, It is recommended to install the plastic pillar with the male end facing upward.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970433.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=4UUBPr7oHbgPxgQQpFFrniSEEao%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step12. Mount two LED lights onto the front barrier plate as shown in the diagram.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970439.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=g2Yn53ILeYRv4TmDrmEz4XKfFcA%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step13. Ensure all necessary circuit connections are completed before assembling the upper and lower chassis.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970443.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=PPeCKk1VFiUNFv4SEYgAKL5gmEA%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step14. Connect the OSOYOO Model Y Board to the UART WiFi board.

</div>

Use two 6-pin male-to-female jumper wires to connect the OSOYOO Model Y board to the UART WiFi shield as shown in the diagram:

Route the 6-pin wires in Area M_B through the hole near the SG90 servo. Route the 6-pin wires in Area M_A through the hole near the voltage meter.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970449.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=TfIy%2BndxuVtHRmApub12UAnJDr0%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970461.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=MxL%2BO1F2U1yuNldgvukDnA7SG%2B0%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970467.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=dqeHVoNuDJDfgdQrClLRfYDBPe8%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

2pcs 6pin male to female wires

</div>

<table border="1"><tr><td>Model Y board</td><td>Uart Wifi Shield</td></tr><tr><td>M_A ENA</td><td>D11</td></tr><tr><td>M_A IN1</td><td>D5</td></tr><tr><td>M_A IN2</td><td>D6</td></tr><tr><td>M_A IN3</td><td>D7</td></tr><tr><td>M_A IN4</td><td>D8</td></tr><tr><td>M_A ENB</td><td>D12</td></tr></table>

<table border="1"><tr><td>Model Y board</td><td>Uart Wifi Shield</td><td>Mega2560 board</td></tr><tr><td>M_B ENA</td><td>D9</td><td>/</td></tr><tr><td>M_B IN1</td><td>/</td><td>D22</td></tr><tr><td>M_B IN2</td><td>/</td><td>D24</td></tr><tr><td>M_B IN3</td><td>/</td><td>D26</td></tr><tr><td>M_B IN4</td><td>/</td><td>D28</td></tr><tr><td>M_B ENB</td><td>D10</td><td>/</td></tr></table>

## Caution:

When insert/remove this 6-pin plug into Model Y 6-pin male socket, please hold the plastic pin-holder to do operation. Never drag the wires to pull the plug out of the socket, otherwise it will damage the wires.

Step15. Connect the voltage meter to the OSOYOO Model Y board using a 3-pin female-to-female jumper wire as shown in the connection diagram.

Connect the battery box to the VIN socket of the OSOYOO Model Y board according to the diagram.

Connect the VOUT socket of the OSOYOO Model Y board to the VIN socket of the WiFi shield using a 2-pin PnP cable as illustrated.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970472.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=HXKziyvkyN8lXjnIrLW0kkPrnh0%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970482.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=C6sodGZF3NjjmZNdSBZLWPyNr8w%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step16. Mount 2 LED lights on the front transverse diaphragm. Connect the red wires (VCC) of the LED lights to the 3V or 5V pins, and the black wires (GND) to the GND pins on the UART WiFi shield.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970490.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=Gdk4pCaMxMpaGQXfsSNoUZYtHPc%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970496.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=tkDuFduIniBzmEBXvA6wr1kRxu4%3D&Expires=1789692770' alt='OCR图片'/></div>

## Note:

If the wire of the LED light you receive has a male connector end, you can plug it into the female connector end of the Wi-Fi board;

If the wire of the LED light you receive has a female connector end, you can plug it into the male connector end of the Wi-Fi board.

Additionally, this LED light can use the 3.3V port, and it can also use the 5V port. This just results in different brightness levels of the LED.

<div align="center">

Step17. Connect the servo motor's orange wire (PWM) to S, red wire (VCC) to 5V, and brown wire (GND) to GND on the Model Y board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970509.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=XkLhE%2BHKUE9cvwj8WEMnG1YmKSM%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970514.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=k%2FWICLamexAtr9wMyQw1f5akHxk%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step18. Connect GND-VCC pin of tracking sensor module to GND-5V of OSOYOO Uart WiFi shield V1.3; connect IR1, IR2, IR3, IR4, IR5 pins to A4, A3, A2, A3, A1 with 7pin 25cm female to female cable as the following photo shows.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970520.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=QHG2NqL%2BEGFKZWnti8Q4NgS0h1g%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step19. Fix upper chassis to lower chassis with 6pcs M3*10 hex screws.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970530.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=dXQnTao4aKzyo7uXKWkJ2xGvrX0%3D&Expires=1789692770' alt='OCR图片'/></div>

Step20. Install 4 wheels onto the motors with 4pcs M2.5X20 or M2.6×20 Self-tapping screws.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970536.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=CSBBwM2kQOyBNGwa7v4euYyp84E%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970541.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=JzdWh6JLvj6XXaU8kHvsKarYmvE%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970547.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=BKvhJBOvuMP4rHqnakD6qx%2FY5eQ%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970566.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=cYU6KscSPtTSJmOsfc4wMICyimQ%3D&Expires=1789692770' alt='OCR图片'/></div>

Note: there are two types and to arrange them so the rollers point toward center of car when viewed from above.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970578.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=lAxHrP6mpi0MzqrqalsI0pq9SaA%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970582.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=p8xPMJRnL9UkaiVyg%2FdenSGEKro%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970586.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=pf0Bx5XdtKmz1%2FMMG5gw3L1ZfGE%3D&Expires=1789692770' alt='OCR图片'/></div>

<table border="1"><tr><td>Direction of Movement</td><td>Wheel Actuation</td></tr><tr><td>Forward</td><td>All wheels forward same speed</td></tr><tr><td>Reverse</td><td>All wheels backward same speed</td></tr><tr><td>Right Shift</td><td>Wheels 1,4 forward;2,3 backward</td></tr><tr><td>Left Shift</td><td>Wheels 2,3 forward;1,4 backward</td></tr><tr><td>CW Turn</td><td>Wheels 1,3 forward;2,4 backward</td></tr><tr><td>CCW Turn</td><td>Wheels 2,4 forward;1,3 backward</td></tr></table>

To the right: This is a top view looking down on the drive platform. Wheels in Positions 1,4 should make X- pattern with Wheels 2,3. If not set up like shown, wheels will not operate correctly.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_4_1789087970596.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=LBN4ltH8HFIpgXlQS5HeJf4KZug%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970601.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=4yBT78IZViE2GYEHMNuP5EBHfac%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Now hardware installation is almost down. Before we install 18650 batteries into the box, we need burn the sample code into Arduino First.

</div>

## SOFTWARE INSTALLATION

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Infinite symbol</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlang=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>7 ZIP</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en , then install the software.

Step 2: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson1.zip, unzip the download zip file mc-lesson1.zip, you will see a folder called mc-lesson1.zip.

Step 3: Connect Mega2560 board to PC with USB cable, Open Arduino IDE -> click file -> click Open -> choose code "mc-lesson1.ino" in lesson1 folder, load the code into arduino.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970607.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=hm3k9aWvgY40%2BM0JOyB%2B%2Fijo4JM%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Choose corresponding board/port for your project,upload the sketch to the board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970614.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=LtpujX46lrjWUHXmdsA%2FGj8qGH4%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970620.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=S%2Fg8GSxrL29Z3XJ4fozUVqnqzqg%3D&Expires=1789692770' alt='OCR图片'/></div>

## Note:

If the car runs properly when powered via USB (e.g., the wheels spin when lifted off the ground) but does not work when the USB is disconnected and the batteries are correctly inserted, check the switch on the double-driver Y board. It may have been accidentally toggled upward. Use a screwdriver to push it down without disassembling the car.

## HOW TO PLAY

Disconnect the Arduino from the PC and insert batteries into the battery box. Place the car on the ground and turn on the switches on both the OSOYOO UART WiFi Shield V1.3 and the 18650 battery box (if installed).

The car should perform the following sequence:

Forward → Backward → Left Turn → Right Turn →

Right Parallel Shift $ \rightarrow $ Left Parallel Shift $ \rightarrow $

Down Left Diagonal $ \rightarrow $ Up Right Diagonal $ \rightarrow $

Up Left Diagonal $ \rightarrow $ Down Right Diagonal, and then stop.

If, after running the Lesson 1 code, you notice that one side wheels are not turning, or one side wheels can only move forward but not backward, or only backward but not forward, the issue is likely a loose or broken wire in the 6-pin cable connecting to the Model Y board.

Here is the solution:

Step 1: Disconnect the 6-pin cable that connects the Model Y board and the Arduino board.

Step 2: Locate six (6) single spare Female-to-Male jumper wires from your kit (any color is fine).

Step 3: Use these six single jumper wires to manually reconnect the Model Y pins (ENA, IN1, IN2, IN3, IN4, ENB) to the corresponding pins on the Arduino as per previous model Y wire map

Step 4: Retest the Lesson 1 code to see if the issue is resolved. If the problem still exists, you can send your problem detail to support@osoyoo.info and our tech support team will help you.

<div align="center">

# Lesson 2 Obstacle Avoidance Robot Car

</div>

## INTRODUCTION

In this lesson, we will do an obstacle avoidance auto-driving project. We use an ultrasonic module to "see" the obstacle, and the car will turn around from the obstacle automatically.

You must complete lesson 1 before you continue on with this lesson.

## PARTS & DEVICES

<table><tr><td>OSOYOO Mecanum wheels robotic car chassis x1</td></tr><tr><td>OSOYOO Wheels and motors x4 (left-wheels x2/right-wheels x2)</td></tr><tr><td>OSOYOO Mega2560 board fully compatible with Arduino UNO/Mega2560 x1</td></tr><tr><td>OSOYOO Uart Wifi shield x1</td></tr><tr><td>OSOYOO Model Y driver board x1</td></tr><tr><td>OSOYOO Voltage meter x1</td></tr><tr><td>OSOYOO MG90 servo motor x1</td></tr><tr><td>OSOYOO Ultrasonic sensor module x1</td></tr><tr><td>OSOYOO Mount holder x1</td></tr><tr><td>OSOYOO Battery box x1</td></tr><tr><td>OSOYOO 3pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 6pin male to female jumper wire x2</td></tr><tr><td>OSOYOO 10pin male to female jumper wire x1</td></tr><tr><td>OSOYOO 2 pin XH.25 female to female x1</td></tr><tr><td>18650 Batteries(3.7V) x2</td></tr><tr><td>Battery charger x1</td></tr></table>

<div align="center">

Step1. Attach the ultrasonic module to the mounting holder using 4 M1.5*8 screws and M1.5 nuts.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970627.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=kaLmqzceMbl1yZul7%2FhZCfLZX5I%3D&Expires=1789692770' alt='OCR图片'/></div>

Step2. Secure the ultrasonic module's mounting holder onto the servo motor with M2*4 self-tapping screws Or the screws from the SG90 servo screw kit.

When placing the ultrasonic underneath, as the self-tapping screws easily strip.

A. Support the motor from underneath, as the self-tapping screws easily strip.

B. Do not insert the screw until after the alignment process.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970636.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=JvFqwja5nboSY%2B92afccVstEWbc%3D&Expires=1789692770' alt='OCR图片'/></div>

Step3. Keep all connections from Lesson 1 unchanged. Before connecting additional wires, ensure that the SG90 servo motor is properly connected to both the Model Y board and the

OSOYOO UART Wi-Fi Shield as shown in the diagram.

( Note: You will need to split one male-to-female jumper wire from the provided 10-piece jumper wire bundle. Any color can be used. The remaining wires are spare parts in case of damage or failure.)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970648.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=qexwNc8RRpEwCSML%2BPYexX6Kscs%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970659.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=bUNiolAaR4XTGMT%2FtjaJgQYKnaU%3D&Expires=1789692770' alt='OCR图片'/></div>

Step4: Connect the ultrasonic module to the OSOYOO UART Wi-Fi Shield as shown in the diagram.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970672.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=RYyb%2BZfOJp4e6fm%2BubmKMAHyfF8%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

SOFTWARE INSTALLATION

</div>

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Infinite symbol</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlanguage=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>7 ZIP</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en, then install the software.

<div align="center">

Step 2: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson2.zip, unzip the download zip file mc-lesson2.zip, you will see a folder called mc-lesson2.zip.

</div>

<div align="center">

Step 3: Connect Mega2560 board to PC with USB cable, Open Arduino IDE $ \rightarrow $ click file $ \rightarrow $ click Open $ \rightarrow $ choose code "lesson2.ino" in lesson1 folder, load the code into Arduino.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970678.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=CdgGQURLyMYy4SPTl33Ek5Dmh4w%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Choose MEGA2560 board as the board type and correct port for your project as following picture, upload the sketch to the board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970683.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=lEmKNt0zg0INJgxY4MukhnqL%2B1U%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970690.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=5d982qOQeGjCUnEeZSbTWPrxTvk%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

HOW TO PLAY

</div>

<div align="center">

Ultrasonic sensor servo initial direction alignment

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970696.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=%2BKiViZfKfkINTSdyxlnHKaelxO0%3D&Expires=1789692770' alt='OCR图片'/></div>

After turning on the battery, the servo will make some movement and finally stops at front direction for 3 seconds.

If the ultrasonic sensor does not face the front during this first 3 seconds, you should turn off battery immediately and remove the sensor from the servo, reinstall it and make it facing straight forward direction as following picture. Otherwise, the obstacle avoidance program will not work properly.

After adjusting sensor direction, turn on battery again, the sensor should face front same as following picture. If its direction is not straight forward, turn off battery and do direction alignment again.

## Final Testing :

After turning on the battery switch on the battery box, if the ultrasonic module turn to front view position, that means you don't need to adjust sensor position anymore. Just wait 3 seconds. If no obstacle is detected, the car will go forward. If any obstacles are detected, the car will stop, the ultrasonic module will turn from right to left to detect surrounding obstacles. The robot car will decide to make left turn, right turn or backward according to obstacle sensor data and our obstacle avoidance algorithm.

Sometimes your car might have collision and make your Ultrasonic sensor position

change, you must remember to do sensor direction alignment again as per link Ultrasonic sensor servo initial direction alignment.

## Trouble Shooting

Sometimes when you run the lesson 2 sketch code, you might see that the car moves backward even if there is no obstacle in front. This normally means the ultrasonic sensor installation or wire connection has a problem.

To solve the problem, please check hardware installation step 4.

Use 4 new jumper wires to connect sensor to Arduino Wi-Fi board,

make sure:

Ultrasonic Sensor VCC connects to Wi-Fi board 5V

Ultrasonic Sensor TRIG connects to Wi-Fi board D30

Ultrasonic Sensor ECHO connects to Wi-Fi board D31

Ultrasonic Sensor GND connects to Wi-Fi board GND

After sensor wires are properly connected based on above instruction, you can make a test of the sensor.

Please download distance sensor test code from

https://osoyoo.com/download/code/distance.zip, keep your Arduino and PC connected with blue cable and then run the distance.ino code.

Now open your Arduino IDE Serial monitor, put your hand in front of the sensor,

You should see a distance value in serial monitor. That value is the distance between your hand and sensor.

If you can only see 0 value in Serial monitor, it means your sensor wire connection is wrong or wire might be broken or sensor is defective. You might need to change 4 new wires or contact OSOYOO support for sensor replacement.

<div align="center">

# Lesson 3 Tracking Line Robot Car

</div>

## INTRODUCTION

In this lesson, we will do a line-tracking auto-driving project. We will add a 5-Point tracking sensor module to the robotic car built in Lesson 1. The software in this lesson will read data from the 5-Point Tracking sensor module and automatically guide the smart car to move along the black track line in the white ground.

<table><tr><td>OSOYOO Mecanum wheels robotic car chassis x1</td></tr><tr><td>OSOYOO Wheels and motors x4 (left-wheels x2/right-wheels x2)</td></tr><tr><td>OSOYOO Mega2560 board fully compatible with Arduino UNO/Mega2560 x1</td></tr><tr><td>OSOYOO Uart Wifi shield x1</td></tr><tr><td>OSOYOO Model Y driver board x1</td></tr><tr><td>OSOYOO Voltage meter x1</td></tr><tr><td>OSOYOO 5-point tracking sensor module x1</td></tr><tr><td>OSOYOO Battery box x1</td></tr><tr><td>OSOYOO 3pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 6pin male to female jumper wire x2</td></tr><tr><td>OSOYOO 7pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 2 pin XH.25 female to female x1</td></tr><tr><td>18650 Batteries(3.7V) x2</td></tr><tr><td>Battery charger x1</td></tr></table>

<div align="center">

Step1. Please keep all lesson 1 connections same as it is. (Remember: DO NOT remove any existing wires installed in Lesson 1 ).

</div>

Step2. Connect GND-VCC pin of tracking sensor module to GND-5V of OSOYOO Uart WiFi shield V1.3; connect IR1, IR2, IR3, IR4, IR5 pins to A4, A3, A2, A2, A1 with 7pin 25cm female to female cable as the following photo shows.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970702.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=%2FBYj2sJ%2Fchq3rAreKHXc4I0BX84%3D&Expires=1789692770' alt='OCR图片'/></div>

SOFTWARE INSTALLATION

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Infinite symbol</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlanguage=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>7 ZIP</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en, then install the software.

<div align="center">

Step 2: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson3.zip unzip the download zip file mc-lesson3.zip, you will see a folder called mc-lesson3.zip.

</div>

<div align="center">

Step 3: Connect Mega2560 board to PC with USB cable, Open Arduino IDE $ \rightarrow $ click file $ \rightarrow $ click Open $ \rightarrow $ choose code "lesson3.ino" in lesson3 folder, load the code into Arduino.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970716.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=gmpF7QBosEyE8hoT%2Fdmd0YD93eQ%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Choose corresponding board/port for your project, upload the sketch to the board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970730.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=z74ClZmq%2FqyDs31%2FbBa6Dj%2FykUY%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970736.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=BmdXuhuTq0MpQU0LxIUOZIed%2BIE%3D&Expires=1789692770' alt='OCR图片'/></div>

Adjusting the Sensitivity of Tracking Sensor Modules.

Turn on the car and hold it in place. Use a Phillips screwdriver to adjust the potentiometer on the tracking sensor module. Fine-tune it until you achieve optimal sensitivity:

The signal indicator LED should turn on when the sensor is positioned over a black track. The signal indicator LED should turn off when the sensor is positioned over a white surface.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970741.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=Bh%2BC6qnA5wvLUnTdtMx0V%2FUcGCw%3D&Expires=1789692770' alt='OCR图片'/></div>

## Final Testing:

Prepare a black track (the width of the black track is more than 20mm and less than 30mm) in white ground. Please note, the turning angle of track can't be too sharp, otherwise the car will move out of the track.

Turn on the car and put the middle of tracking sensor module facing over black track, and then the car will move along the black track.

## Lesson 4 Object follow Robot car

In this lesson, we will install 2pcs IR distance sensors on a robot car and program the car to follow object movements. The car receives the signal from the IR distance sensors, and then the program will drive the car to take actions.

<table><tr><td>OSOYOO Mecanum wheels robotic car chassis x1</td></tr><tr><td>OSOYOO Wheels and motors x4 (left-wheels x2/right-wheels x2)</td></tr><tr><td>OSOYOO Mega2560 board fully compatible with Arduino UNO/Mega2560 x1</td></tr><tr><td>OSOYOO Uart Wifi shield x1</td></tr><tr><td>OSOYOO Model Y driver board x1</td></tr><tr><td>OSOYOO Voltage meter x1</td></tr><tr><td>OSOYOO IR distance sensors x2</td></tr><tr><td>OSOYOO Battery box x1</td></tr><tr><td>OSOYOO 3pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 6pin male to female jumper wire x2</td></tr><tr><td>OSOYOO 10pin male to female jumper wire x1</td></tr><tr><td>OSOYOO 2 pin XH.25 female to female x1</td></tr><tr><td>18650 Batteries(3.7V) x2</td></tr><tr><td>Battery charger x1</td></tr></table>

<div align="center">

Step 1: Install the smart car basic framework as per Smart Car Lesson 1. If you have already completed installation in Lesson 1, just keep it as is.

</div>

<div align="center">

Step 2: Connect 2pcs IR distance sensors modules as below connection diagram. (Remember: DO NOT remove any existing wires installed in Lesson

</div>

<table border="1"><tr><td>Uart Wifi Board</td><td>IR Obstacle Sensor</td></tr><tr><td>5V</td><td>VCC(Left)</td></tr><tr><td>GND</td><td>GND(Left)</td></tr><tr><td>D3</td><td>OUT(Left)</td></tr><tr><td>5V</td><td>VCC(Right)</td></tr><tr><td>GND</td><td>GND(Right)</td></tr><tr><td>D2</td><td>OUT(Right)</td></tr></table>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970747.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=vNWMCBD7ZjVjZY2wAUr1zVHYOCQ%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970752.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=FX2LAb4h7OeCytSEdmX4zh%2F8Bec%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970763.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=AieAwNodO5qsIW0%2Fz7nENlT3KyE%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

SOFTWARE INSTALLATION

</div>

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Infinite symbol</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlanguage=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>7 ZIP</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en, then install the software.

Step 2: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson4.zip, unzip the download zip file mc-lesson4.zip, you will see a folder called mc-lesson4.zip.

Step 3: Connect Mega2560 board to PC with USB cable, Open Arduino IDE $ \rightarrow $ click file $ \rightarrow $ click Open $ \rightarrow $ choose code "lesson4.ino" in lesson4 folder, load the code into Arduino.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970778.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=nRHiPPFZWvscoGb1wxQbVHNEAhc%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Choose corresponding board/port for your project, upload the sketch to the board.

</div>

<table><tr><td>Auto Format</td><td>Ctrl+T</td></tr><tr><td>Archive Sketch</td><td></td></tr><tr><td>Fix Encoding &amp; Reload</td><td></td></tr><tr><td>Manage Libraries...</td><td>Ctrl+Shift+I</td></tr><tr><td>Serial Monitor</td><td>Ctrl+Shift+M</td></tr><tr><td>Serial Plotter</td><td>Ctrl+Shift+L</td></tr><tr><td colspan="2">WiFi101 / WiFiNINA Firmware Updater</td></tr><tr><td colspan="2">Board: "Arduino Mega or Mega 2560"</td></tr><tr><td colspan="2">Processor: ATmega2560 (Mega 2560)"</td></tr><tr><td colspan="2">Port: "COM260 (Arduino Mega or Mega 2560)</td></tr><tr><td colspan="2">Get Board Info</td></tr><tr><td colspan="2">Programmer: "AVRISP mkII"</td></tr><tr><td colspan="2">Burn Bootloader</td></tr></table>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970782.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=2uq8pIw2XczTugVLlkbzSpseYM4%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 5: Turn on the car, put object about 10 cm ahead of each IR distance sensors and adjust potentiometer on IR distance sensors to detect object or your hand.

</div>

Note: When these IR modules detect objects, both the power indicator and signal indicator are on. When No object is detected, only power indicator is on, signal indicator is off. If the signal indicator is always on even though there is no obstacle in front of the sensor, you need to adjust the potentiometer.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970789.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=WWNeIeTCzW55PD83lHDkGVLWlPw%3D&Expires=1789692770' alt='OCR图片'/></div>

Turn on the car, place your hand ahead of the car, then the car will move towards your hand as if you pull it. It goes forward when both IR Obstacle Avoidance modules detect your hand; it turns right if only the right IR Obstacle Avoidance module detects object; it turns left if only the left IR distance sensor detects object.

When your hand is over 10 cm ahead, it will stop.

<div align="center">

# Lesson 5-Imitation Driving with Bluetooth

</div>

## INTRODUCTION

In this lesson, we will use a mobile APP to control our robot car and make an imitation driving. Since it is a mock driving, we will use a virtual steering wheel and gear in our APP to imitate their counterparts in the real car.

## PARTS & DEVICES

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970801.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=vmDiHwKQTlSUU76tg6%2B%2B%2B71eQbE%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 1: You must complete lesson 1 (assembling the car) before you continue on with this lesson.

</div>

Step 2: Connect Bluetooth TX/RX ports to D19,D18 with jumper wires.

(Note: You need to split 2 pcs of male-to-female jumper wires from our 10-pc jumper wire bundle. Any color from the bundle will be ok. The rest of 8 pcs wires are as spare parts for potential broken or damaged wires.)

<table border="1"><tr><td>Uart Wifi Board</td><td>Arduino mega2560</td></tr><tr><td>B_TX</td><td>D19</td></tr><tr><td>B_RX</td><td>D18</td></tr></table>

<div align="center">

2pin male to female wire

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970808.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=zeZfO%2FOZpDw4jNDwH3s8dbi6JEo%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970813.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=WExY6skDLyZBjfr4lXLaUtBhxCE%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 3: Bluetooth Module should be inserted into Bluetooth 6-pin slot in OSOYOO Wi-Fi Board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_3_1789087970823.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=RvtKupSn%2F0hnQq9wsWGWJAJCGHM%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Mobile APP:

</div>

Go to your Google Play or Apple APP store and search APP name "OSOYOO imitation driving", Download the APP as following and install it in your smartphone.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970846.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=%2FX8qxTv8iYnGTj5nQJGhXUrhnKs%3D&Expires=1789692770' alt='OCR图片'/></div>

- Connect HC-02 Bluetooth in Android phone. There is a BT Search button in Android APP: When click this button, you will see a Bluetooth device list which has been paired with your APP. Select HC-02 device to connect the car. Once HC-02 is connected, Bluetooth Status will change from Disconnected to Connected. You can only control your car when Bluetooth is connected.

- Connect HC-02 Bluetooth in iPhone/iPad, simply click Connect button, a HC-02 device will show up in a pop-up list. Click that HC-02 device to connect Bluetooth module to your iPhone. Then the Connect button will change name to Disconnect.

## Control Interface

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970854.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=LIXPzsw5OHm21qMLk%2B1HMfOuxXw%3D&Expires=1789692770' alt='OCR图片'/></div>

- Engine toggle : When Engine toggle is set to OFF (white), the car will stop and all buttons in the APP will be disabled. When Engine toggle is set to ON (red), the car will start to move. All other movement control buttons will activate.

- Forward/Backward gear switch: This gear switch can control the car is moving ahead or reverse like real car gear.

- F1,F2,F3,F4,F5 customized button. In this lesson, we only use the F3 key which pauses the car movement. The difference between F3 and Engine OFF button is that Engine OFF button when touched, all other buttons will be disabled. You should toggle Engine button again to enable other button. On the other hand, when F3 is clicked, the car will stop, but all other buttons are still active. Press F1 to Shift to left way, F2 to up left diagonal, F3 to pause, F4 to up right diagonal, F5 to shift to right way.

- Direction Steering Wheel: When you rotate your mobile phone angle, the steering wheel will change angle as per your mobile phone rotation angle. This will make your car change direction. For example, when the steering wheel makes clockwise rotation, the car will move to the left. Remember, the steering and Forward/Backward gear should work together same as you are driving a real car. For example, when you want to back your car to a right side parking lot, you need to set Gear to R position and rotate your steer to count-clockwise direction.

- Speed+: Make the robot car speed up

- Speed-: Make the robot car slow down

<div align="center">

SOFTWARE INSTALLATION

</div>

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Infinite symbol</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlang=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>7 ZIP</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en, then install the software.

Step 2: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson5.zip, unzip the download zip file mc-lesson5.zip, you will see a folder called mc-lesson5.zip.

<div align="center">

Step 3: Connect Mega2560 board to PC with USB cable, Open Arduino IDE $ \rightarrow $ click file $ \rightarrow $ click Open $ \rightarrow $ choose code "lesson5.ino" in lesson5 folder, load the code into Arduino.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970859.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=runr7yfMjG2ecvCGS9SL3xDqs9I%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 4: Choose corresponding board/port for your project, upload the sketch to the board.

</div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970863.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=u987dMbguqHEhflCmjPjPi7aRKk%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970873.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=aXaCNJdgEOggoWeRAq%2FYfB4uJTg%3D&Expires=1789692770' alt='OCR图片'/></div>

HOW TO PLAY

Now you have installed your hardware and software for this lesson, let's drive our car!

Step1) Put your robot car onto the ground and turn on the switch.

Step 2) Go to your mobile phone $ \rightarrow $ Setting $ \rightarrow $ Bluetooth setting and search a Bluetooth device called HC-02, pair it with code 1234.

Connect with Android device:

If you use an Android device and have not paired the Bluetooth module with your cell phone, please pair the Bluetooth module first before open the APP. In your cell phone Setting $ \rightarrow $ Bluetooth, find a Bluetooth device called HC02, pair it with password 1234. After the Bluetooth HC02 device is paired, open the APP. Click BT Search Button to connect APP to HC02 device.

Connect with iOS device:

If you use iOS device, simply open the APP, click Connect button, you will see a Bluetooth list, select the HC02 device.

Step 3) Open OSOYOO imitation driving Robot APP, Click BT Search button and find the

Bluetooth you have paired

Step 4) Turn on Engine toggle, click Speed+ to make the robot speed up, as the robot car is very slow at first. When you rotate your mobile phone angle, your car will change direction.

Step 5) click Gear button to change gear to Forward or Backward direction.

Step 6) press F1 to Shift to left way, F5 to shift to right way, F2 to up left diagonal, F4 to up right diagonal, F3 to pause.

## NOTICE

Motor Speed Tuning for better performance

To get better running performance result, motor power (speed) value should be adjusted properly as per battery level. If motor power (speed) value is too high, your car might run too fast and easy to out of control. If motor power (speed) is too low, the car might not even move.

To adjust the motor power value, you need to change the 3 constants line 27,28,29 in mecanum-2560-lesson4.ino sketch file:

#define MIN_SPEED 50

#define TURN_SPEED 70

#define SLOW_TURN_SPEED 50

#define BACK_SPEED 60

MIN_SPEED is the minimum power required to start the car. If when APP engine toggle is switched to RED, but your car does not move, you need to increase this value, if the car runs too fast at engine start moment, you need to reduce this value.

TURN_SPEED AND, SLOW_TURN_SPEED value determines the turning speed of your car. If your car turning too fast, you need to reduce these two values, if turning too slow or not turning, increase these two values. Always make SLOW_TURN_SPEED about 20 to 30 lower than TURN_SPEED value.

BACK_SPEED value determines the reverse back running speed.

After batteries are running low, you might need to increase the value of these 3 constants. You can gradually add or reduce 10 each time on these values and compare which values have best tracking performance.

Trouble Shooting:

We have a group of students, all our robot cars are using same bluetooth name "HC-02" which might conflict with each other in the same room. How to change the HC-02 name to other bluetooth name?

1) Wire Connection

HC-02 TX Arduino D4 (SoftwareSerial RX)

HC-02 RX Arduino D5 (SoftwareSerial TX)

HC-02 VCC 5V

HC-02 GND GND

HC-02 KEY / EN / STATE (depending on your module) $ \rightarrow $ HIGH (3.3V or 5V)

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970891.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=iEpdnLxGyYsE%2BZAcRaELg%2BIfMRY%3D&Expires=1789692770' alt='OCR图片'/></div>

2) Download Arduino AT command sketch from following link:

https://osoyoo.com/driver/2wd/hc02.zip

unzip above file , you will see a folder "hc02" , enter that folder and double click hc02.ino file to open it in Arduino IDE.

3) Test AT command in Serial Monitor

After you upload the hc02.ino code to Arduino, open your Arduino IDE Serial monitor, set baud rate to 9600, set line mode to No Line Ending as following:

<div align="center">

# Lesson 6 WiFi IoT Controlled Robot Car

</div>

## INTRODUCTION

In this project, we will connect the Robot Car to Wi-Fi and Use an APP to control the car through Wi-Fi. This is a typical Internet of Things (IoT) Application. Lesson 1, Lesson 2, Lesson 3 must be completed before doing this lesson.

## PARTS & DEVICES

<table border="1"><tr><td>OSOYOO Mecanum wheels robotic car chassis x1</td></tr><tr><td>OSOYOO Wheels and motors x4(left-wheels x2/right-wheels x2)</td></tr><tr><td>OSOYOO Mega2560 board fully compatible with Arduino UNO/Mega2560 x1</td></tr><tr><td>OSOYOO Uart Wifi shield x1</td></tr><tr><td>OSOYOO Model Y driver board x1</td></tr><tr><td>OSOYOO Voltage meter x1</td></tr><tr><td>OSOYOO Battery box x1</td></tr><tr><td>OSOYOO 3pin female to female jumper wire x1</td></tr><tr><td>OSOYOO 6pin male to female jumper wire x2</td></tr><tr><td>OSOYOO 10pin male to female jumper wire x1</td></tr><tr><td>OSOYOO 2 pin XH.25 female to female x1</td></tr><tr><td>18650 Batteries(3.7V)x2</td></tr><tr><td>Battery charger x1</td></tr></table>

## HARDWARE INSTALLATION

If you just finish all lesson 1-3 and lesson 5 (Bluetooth imitation driver), please keep all lesson connections same as is. Then unplug Bluetooth from Wi-Fi Shield.

Step 1. Remove the connection B_TX to D18 and B_RX to D19.

Step 2. Connect E_RX to D18(TX1) and E_TX to D19(RX1).

Only the B_ends need to be unplugged. The TX and RX pin order is reversed from Bluetooth.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970896.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=ygHFDaP3OcQTghU9Ushugk%2FPS1g%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970902.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=gR77rCNo1nvtWZsvi4psV1eOWQM%3D&Expires=1789692770' alt='OCR图片'/></div>

2pin 20cm male to female wire

<div align="center">

SOFTWARE INSTALLATION

</div>

<table border="1"><tr><td>Open-source Arduino Software(IDE)</td><td>Download Arduino IDE here:https://www.arduino.cc/en/Main/Software?setlang=en</td></tr><tr><td>7 zip is a free zip utility that un-zips zip files</td><td>Download 7zip here for freehttps://www.7-zip.org/</td></tr></table>

Step 1: Install latest Arduino IDE (If you have Arduino IDE version after 1.1.16, please skip this step). Download Arduino IDE from

https://www.arduino.cc/en/Main/Software?setlang=en, then install the software.

Step 2:Please download the library zip file from WiFiEsp-master.zip. Open Arduino IDE click Sketch $ \rightarrow $ Include Library $ \rightarrow $ Add .ZIP library, then load above zip file into Arduino.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970906.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=ZGsMBtnKxJPX1heTHWV8xWbfLs8%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 3: Download https://osoyoo.com/driver/mecanum_acrylic_chassis_v2/mc-lesson6.zip unzip the download zip file mc-lesson6.zip, you will see a folder called mc-lesson6.

</div>

Step 4: search "Osoyoo IoT UDP Robot APP"in Google Play or Apple Store(If you can not find this APP in Google Play,

If you can not find OSOYOO IoT UDP Robot APP from Google Play Store, you can directly download the APP from following link: https://osoyoo.com/driver/udp-app.apk)

## Android Phone

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970913.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=IkDgimcd2BLXOY%2FnyOuY8Tbr8E8%3D&Expires=1789692770' alt='OCR图片'/></div>

## Apple iOS

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970917.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=ilv%2BpkXnd%2BvJucsyq5QTxPNvbu4%3D&Expires=1789692770' alt='OCR图片'/></div>

<div align="center">

Step 5:Arduino Sketch code Installation:

</div>

Unzip the downloaded file, enter the mc-lesson6 folder, you will see two sub-folder : mc-lesson6A and mc-lesson6B.

These two folders have program for two Wi-Fi modes:STA mode and AP mode. The Arduino sketches for these two modes are different. Let's explain these two modes one by one.

## *STA MODE*

In STA mode, robot car does not work as a Wi-Fi hotspot. Instead, it will become an internet node in your LAN. You need to tell Arduino sketch what is your local router's Wi-Fi SSID and password, then Arduino talks to the router and get its own LAN IP address from DHCP server. You can use a Mobile APP to access the robot car's IP address and control its movement.

(1) Unzip the mc-lesson6 file, you will see a folder named mc-lesson6b, then load the mc-lesson6b.ino code into Arduino.

(2) You need to change the code Line 180 and Line 181 :

$$
\mathrm {c h a r s s i d} [ ] = \mathrm {“ Y O U R _ R O U T E R _ S S I D ”} / / \mathrm {r e p l a c e t h i s w i t h y o u r r o t e r w i f i S S I D}
$$

$$
\mathrm {c h a r p a s s} [ ] = \mathrm {“ Y O U R _ R O U T E R _ W I F I _ P A S S W O R D ”} / / \mathrm {r e p l a c e w i t h y o u r w i f i p s p o s s w o r d}
$$

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970922.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=cKOHSIsgA1Oi%2BKmjgB0FAIcc5ng%3D&Expires=1789692770' alt='OCR图片'/></div>

```c

pinMode(RightMotorDirPin1B, OUTPUT);

pinMode(RightMotorDirPin2B, OUTPUT);

pinMode(speedPinLB, OUTPUT);

pinMode(LeftMotorDirPin1B, OUTPUT);

pinMode(LeftMotorDirPin2B, OUTPUT);

pinMode(speedPinRB, OUTPUT);

stop_Stop();

}

#include "WiFiEsp.h"

#include "WiFiEspUDP.h"

char ssid[] = "********"; // replace ***** with your network SSID (name)

char pass[] = "********"; // replace ***** with your network password

int status = WL_IDLE_STATUS;

// use a ring buffer to increase speed and reduce memory allocation

char packetBuffer[5];

WiFiEspUDP Udp;

unsigned int localPort = 8888; // local port to listen on

void setup()

```

(3) Upload the sketch to Arduino. Finally, click the Serial monitor window in upper right corner of Arduino IDE, you will see following result:

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970933.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=N3rMYjmiL9SrlDj7Jd8jYHKh5gw%3D&Expires=1789692770' alt='OCR图片'/></div>

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970937.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=N9%2FkPGAXPyV7q8UUfRlVtA06gp8%3D&Expires=1789692770' alt='OCR图片'/></div>

(4) In this mode, you will see an IP address, which is our LAN IP address assigned by my router. Please write down this IP address 192.168.0.117 and click Setting to set up robot IP address and set this IP address 192.168.0.117 to your APP Setting section (see circle 2 in following picture) no need to change default port 8888 in APP.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970946.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=hxejl3fXfjlMSeCZGgHsurnlY7M%3D&Expires=1789692770' alt='OCR图片'/></div>

(5) Now your Robot car is connected to your LAN, you can use Mobile phone under the same LAN to control the robot car. If your APP is in WAN, you need to go to your Router Control Panel, forward Port 80 to Robot car LAN IP address, then you can use Router IP to control the car. This feature makes our robot car A REAL INTERNET OF THING device.

(6) )You can click the $ \triangleleft $ $ \triangleright $ $ \triangleleft $ $ \blacktriangleright $ direction keys to make the car move. Use “ $ || $ ” pause key to stop the car movement.

Click Obstacle to shift left side, Click Tracking to shift right side.

Click F1 to make upper-left diagonal movement, Click F3 to make upper-right diagonal movement.

Click F4 to make back-left diagonal movement, Click F6 to make back-right diagonal movement.

## *AP MODE*

When working in AP mode, our robot car itself will become a Wi-Fi Hot Spot. Our cell phone can connect to Robot Car as its Wi-Fi client. The IP address of Robot is fixed as 192.168.4.1. In this case, both the robot car and your cell phone are not connected to WAN.

(1) Unzip the mc-lesson6.zip file, you will see a folder named mc-lesson6A, upload the code into Arduino.

(2) Open your Arduino Serial monitor, and you will see a similar result as AP mode. A new Wi-Fi SSID "osoyoo_robot" with IP address 192.168.4.1 will show up in the window. This means your Robot car has a Wi-Fi Hot Spot name "osoyoo_robot", its IP address is 192.168.4.1

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970962.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=FdhOXLJobs8wde9ij%2FtP8dyAMsc%3D&Expires=1789692770' alt='OCR图片'/></div>

(3) Now your Robot car become a Wi-Fi Hot Spot and set IP address as "192.168.4.1"to your APP Setting section.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_2_1789087970968.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=8SmYN4DNwppTRtPK%2BOCAi5tY9yE%3D&Expires=1789692770' alt='OCR图片'/></div>

(4) Connect your cell phone to "osoyoo_robot" wifi hot_spot, and you can use the Mobile phone to control the robot car.

<div style='text-align: center;'><img src='https://maas-watermark-prod-new.cn-wlcb.ufileos.com/ocr%2Fcrop%2F20260911085216bc6f881ac22e4b30%2Fcrop_1_1789087970972.png?UCloudPublicKey=TOKEN_6df395df-5d8c-4f69-90f8-a4fe46088958&Signature=nsWHhEHigjRVd3jkhkideW1uJfw%3D&Expires=1789692770' alt='OCR图片'/></div>

(5) You can click the $ \triangleleft $ $ \triangleright $ $ \triangleleft $ $ \blacktriangleright $ direction keys to make the car move. Use “ $ || $ ” pause key to stop the car movement.

Click Obstacle to shift left side, Click Tracking to shift right side.

Click F1 to make upper-left diagonal movement, Click F3 to make upper-right diagonal movement

Click F4 to make back-left diagonal movement, Click F6 to make back-right diagonal movement.

## FAQ about the Wifi UDP APP and sketch Code:

Q1)How to tune the robot car speed?

A: If you want to change the speed performance of the robot car, please following parameters in line 11 to 13:

#define SPEED 85

#define TURN_SPEED 90

#define SHIFT_SPEED 130

SPEED value determines forward moving speed

TURN_SPEED value determines turning speed

SHIFT_SPEED value determines parallel shifting speed

Q2)What happened when you press buttons in OSOYOO WiFi UDP Robot Car APP?

A: When you press a button of the APP, APP will send a single-letter message through UDP protocol to target device (in this example, our WIFI Shield)

<table border="1"><tr><td>Button</td><td>UDP message</td></tr><tr><td>F1</td><td>F</td></tr><tr><td>F2</td><td>G</td></tr><tr><td>F3</td><td>H</td></tr><tr><td>F4</td><td>I</td></tr><tr><td>F5</td><td>J</td></tr><tr><td>F6</td><td>K</td></tr><tr><td>▲</td><td>A</td></tr><tr><td>▼</td><td>B</td></tr><tr><td>►</td><td>R</td></tr><tr><td>◄</td><td>L</td></tr><tr><td>square</td><td>E</td></tr><tr><td>F7</td><td>O</td></tr><tr><td>F8</td><td>T</td></tr></table>

Q3)How does Arduino handle the UDP command?

Line 230 to line 245 in mecanum-2560-lesson5A.ino file are the codes which react to Cell phone command. For example, when $ \triangle $ is pressed, according to Q1 table, a letter "A" command was sent from Cell phone to Arduino. Line 233 case "A" ... statement will make the car make car moving forward.

char c=packetBuffer[0];

switch (c) //serial control instructions

{

case ‘A’:go_advance(SPEED);;break;

case ‘L’:left_turn(TURN_SPEED);break;

case ‘R’:right_turn(TURN_SPEED);break;

case ‘B’:go_back(SPEED);break;

case ‘E’:stop_Stop();break;

case ‘F’:left_shift(0,150,0,150);break; //left ahead

case ‘H’:right_shift(180,0,150,0);break; //right ahead

case ‘I’:left_shift(150,0,150,0); break;//left back

case ‘K’:right_shift(0,130,0,130); break;//right back

case ‘O’:left_shift(200,150,150,200); break;//left shift

case ‘T’:right_shift(200,200,200,200); break;//left shift

default:break;

}