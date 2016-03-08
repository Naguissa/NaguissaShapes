# ESP8266 shapes & colors game

## What is this repository for? ##

Simple color and shapes educational game.

It creates an AP on a ESP8266 with a ILI9340 TFT (320x240px). t provides a web server with a simple page to choose shapes and colors.

Selecting a shape and a color a preview is shown at same page, and that shape and color is displayed at TFT screen.

You need a browser connected to created AP (NaguissaShapes). You can use a computer, a phone, anything. Control page is VERY simple, but uses SVG for shapes, JavaScript for interaction and a hidden iframe to comunicate (rudimentary but compatible AJAX).


## How do I get set up? ##

Download file an open it using Arduino IDE. You can use Glenn Irwin original ILI9340 library (removing the "_esp" suffix in include) or the verson provided with that program, proved to work.

Electrical schema with a ESP201 is available here: http://www.naguissa.com/arduino/NaguissaShapes.png



## Who do I talk to? ##

 * [Naguissa](https://github.com/Naguissa)
 * http://www.naguissa.com
