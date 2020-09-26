# Wireless control of your Pi-Bot

Now you have wireless access to your pi and can send data, the next step is to be able to control it remotely.  This will mean modifying the server and client code we gave you yesterday (or writing your own, possibly in python) to be able to receive a constant stream of instructions until instructed to close down.  It also means integrating some means of communicating between this server and the Arduino.  Finally, it would be nice to be able to see what your Pi is looking at, so we will install the camera and set up to stream data to a website hosted by the Pi.

## Running a server on the Pi

So far you have a server and client set-up that allows you to communicate information from computer Pi to the robot pi.  This server is running in C using very few external packages aside from the essential ones.  However, there are plenty of other ways you might want to set up this communication.  The same server (and client) could be written in Python using the `socket` library with substantially fewer lines of code.  You could use also libraries such as [`ZeroMQ`](https://zeromq.org/ "zmq") which has implementations in C/C++ and Python (as well as a bunch of other funky languages).  Zmq lets you implement different kinds of messaging routines, such as Pub-Sub and Server/Client and might be helpful for your more advanced robot behaviours.

## Setting up the camera on your Pi

This is the bit we've all been waiting for.  Plug the camera into your Pi as directed by by the instructions on github.  The picamera software is already installed on your Pi but you will need to enable it by doing 