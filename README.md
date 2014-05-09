## Arduino Lemma

### Getting Started - Using

Copy the Lemma Lib to your Arduino Libraries directory
name the directory "Lemma"


### Getting started - Development

This repository contains submodules, so after clone it you must execute the following

        git submodule init
        git submodule update

This library can be used in one of two ways.  You can either use the command-line makefiles or the Arduino IDE


### Arduino IDE

  Copy the 'aJson' and 'lemmaLib' directories from this project into your arduino libraries folder
  For example: ~/Documents/Arduino/libraries
  
  Run (or restart) Arduino IDE, and you will see the LemmaExampleSketch under file->Examples->LemmaLib->Examples

### Commandline Makefiles (Arduino IDE must still be installed)

  make a copy of the lemmaApp directory and rename it to be the name of your new sketch
  edit Makefile in that directory

        BOARD_TAG    = mega2560
        ARDUINO_PORT = /dev/tty.usbmodem*
        ARDUINO_LIBS = Ethernet Ethernet/utility spi arduinounit aJson aJson/utility lemmaLib
        USER_LIB_PATH = ..

        include ../Arduino-Makefile/arduino-mk/Arduino.mk

BOARD_TAG - should match the board you are targeting.  For a list of tags see
/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/boards.txt

ARDUINO_PORT - should match the serial port on your computer connected to the arduino.  You can see a list of these inside the Arduino IDE

from a command line, enter the director of your sketch

        make
will build your project and

        make upload

will send your project to the arduino connected at ARDUINO_PORT
