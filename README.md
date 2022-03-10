# Project of data exchange between ThingSpeak, Matlab environment and WiFi module

## 1. Introduction

> Cloud technology is increasingly used in the exchange and storage of information in today's world and is used to store customer data without setting up your own database and ensuring its security, which causes huge costs for small and medium-sized enterprises. Using the ThingSpeak cloud, you can send and receive measurement data from it, used e.g. for process reporting. Communication with API key authentication is used to send this information, which is most often used in IoT and home automation.

## 2. Purpose and scope of the project

> The aim of the project is to program and connect the ESP8266 (ESP12E) module in such a way that it can work continuously throughout the house on a 230 VAC 50 HZ socket. The module's task is to exchange data with the ThingSpeak server and to execute commandsthere, received from MatLab installed on another computer in a different network.

> Activities performed in the designed system:
>
> - setting the set temperature by the computer by placing it in the ThingSpeak for 2-position control,
> - the built electronic circuit connects only to a known network,
> - after establishing the connection, the designed system reads the set temperature stored in the ThingSpeak cloud with a programmed frequency,
> - the system processes the received data and sends the status of the network connection and temperature in the facility, and generates a signal to control the furnace,
> - 4 LEDs indicate the operating status of the system,
> - after losing the WiFi connection, the system automatically tries to find and reconnect with the known network. Additionally, it turns off the heater in order to protect it against overheating.

## 3. Implementation

> The entire system consists of a computer connected to the WiFi network (to send the set temperature to ThingSpeak), CP2101 adapter (used for diagnostics and programming), switching power supply and ESP12E module with all electrical connections.

![Complete photo of system](https://github.com/SMATEO49/Arduino-ESP12e/blob/master/readmefiles/realView.jpg?raw=true)<figcaption>Fig. 1 Made the circuit connected to the computer and power supply 1) CP2101 adapter, 2) switching power supply, 3) ESP12e</figcaption>

> Fig. 2 shows the wiring diagram for the connections of the components. All resistors in the wiring diagram are 10 kΩ resistance. The diagram is made using [1].

![Wiring diagram](https://github.com/SMATEO49/Arduino-ESP12e/blob/master/readmefiles/electric.png?raw=true)<figcaption>Fig. 2 Wiring diagram</figcaption>

> The program uses the library of the creators of the ESP8266 modules and the WiFi library. The most important task in the program is to maintain the stability of the program (handling of exceptions and errors), which has been confirmed by 24 hours of continuous operation registered on ThingSpeak during the failure of the connection several times for a short time and the certainty that the used regulators and the module do not heat up after such a long time during operation (management of generated heat fulfilled). The program was written with the support of [2].

![TS schreenshot](https://github.com/SMATEO49/Arduino-ESP12e/blob/master/readmefiles/TSscr.png?raw=true)<figcaption>Fig. 3 Robot for painting objects: a) side view, b) top view, c) cycle of painting metal objects, d) cycle of painting non-metal objects</figcaption>

## Literature

[1] https://www.instructables.com/Getting-Started-with-the-ESP8266-ESP-12/

[2] https://uk.mathworks.com/help/thingspeak/read-and-post-temperature-data.html
