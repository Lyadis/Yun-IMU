# ViMoSy (Vibration Monitoring System) 

ViMoSy is prototype of vibration monitoring system developed in ThingML for Arduino Yùn. It aims at both experimenting and demostrating the possibilities of model driven generation of heterogeneous communications layers for distributed Cyber Physical Systems.

It trys to use at best the resources of the Yùn micro-processor for computational tasks, and leave only some real time control task to the micro-controller.

In order to build this project, both the ThingML compiler and a c cross compiler for AR9331 are needed (or yun-gcc if you wish to compile it on the Yun directly).

You can find the ThingML compiler at 
A docker container providing the cross compiler at 

It is recommanded to update the Arduino Yùn version of openwrt before trying to run this project, furthermore the bridge Library must be deactivated in order to work properly.

This is only a prototype, and subject to frequent modifications.
