ESOINN
=========

An enhanced self-organizing incremental neural network (ESOINN) for online unsupervised learning.

This project consists of the implementation of the ESOINN neural network and an environment to test and preview the results of this network.

The ESOINN code is written in pure C++. The UI and testing components are implemented as a Qt v5 project using QML and C++.

The ESOINN code itself is located in the ESOINNlib/ESOINNLibSources folder in the following files:

- neuron.h, neuron.cpp
- connection.h, connection.cpp
- cluster.h, cluster.cpp
- esoinn.h, esoinn.cpp

UI Description:
1. Load Image Section: Loads an image (as a 2D array) into the program to be used as input data for ESOINN. The loaded image is displayed in the left part of the program window. It supports .png, .jpg, and .jpeg formats, converts them to grayscale, and uses them as input for ESOINN.
2. ESOINN Input Global Parameters: These parameters can be modified at the top of the program window.
3. Canvas: Displays the current structure of the ESOINN, representing the nodes as points and the connections as lines.


On MNIST data ESOINN found 20 clusters, we marked them and it had 98.21% recognition rate.
Each vector had 784 dimmensions. Here is typical neurons of each cluster:
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso6.jpg?raw=true)

Examples of 2-dimmensional data clustarization:
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso3.jpg?raw=true)
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso2.jpg?raw=true)
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso4.jpg?raw=true)
![alt text](https://github.com/VincentoLaw/ESOINNlib/blob/master/eso5.jpg?raw=true)
