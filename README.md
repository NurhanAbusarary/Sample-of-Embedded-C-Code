# Sample-of-Embedded-C-Code

This is a sample code written in Embedded C. This code is a part of my graduation project titled "Women Safety: A Device to Keep Women Safe". This project aims to create a system that helps women against harassment and sexual violence. The system consists of two pieces: a __Necklace__ (the main device), and __Bracelet__ which is an extra protection layer.  After the system is activated through the Necklace, it sends an SOS message to a guardians list (that was previously created as part of the system setup) that states the __type of the problem__ and the __victim's location__, then, it records videos so it can be used as an evidence later. The location is updated every two minutes. As an extra protection layer, the Bracelet was added. It contains a bunch of sensors such as temperature, heart rate, and an accelerometer (which is used to measure the user's balance, in other words, it monitors if she faints). If any of these sensors caught an abnormal biometric reading/s, the system is immediately activated and repeats the previous process. There is also a Website that the user can access along with her guardians (with limited authorities) to view all the recorded videos and the abnormal biometric readings with the time and location it is was captured.
The system can be activated by one of the three methods:
Pressing a switch for three seconds (to avoid the false signals).
By voice activation.
By the abnormal biometric readings as mentioned.
This is a sample of the code used to create the Bracelet.
The directory contains the following files:
main.cpp: it contains the main function.
definitions.h: it contains the macros definitions.
interrupts.h: it contains the interrupt handlers.
functions.h_: it contains all the functions.
variables.h_: it contains all the defined variables.
