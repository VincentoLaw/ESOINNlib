ESOINNlib
=========

ESOINN abstract library for any sizes and types of input data.

Functionality:

This project is a realization of ESOINN neural network and environment for testing it. 

Network code is C++ code, Environment code using QML and C++, all project was created in QT and recommended to run in it.

Project consist of 4 parts:


1) Loading image as byte array to program, to be loaded as input data for ESOINN. This image also will be shown in left part of program window.

It can load .png, .jpg, .jpeg images, make them grayscale and use them as input for ESOINN.


2) ESOINN settings. They can be changed in the top of the program window.


3) Neural network ESOINN. It is used as self-learning middle layer of associative memory GAM. 

All code of ESOINN is in folder ESOINNlib/ESOINNLibSources in these files: 

neuron.h, neuron.cpp, connection.h, connection.cpp, cluster.h, cluster.cpp, esoinn.h, esoinn.cpp

This Neural network can be used separate from other project for image recognition and classification.


4) Canvas with the current structure of the ESOINN. It represents nodes of ESOINN as points, connections of ESOINN as lines.

Example of work:
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso1.jpg?raw=true)
