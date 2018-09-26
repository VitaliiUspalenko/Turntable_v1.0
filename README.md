# Automatic turntable with shutter release

This turntable was designed for photogrammetry purposes. 
Full article can be found here: 
Video demonstration:

## Folders
- **Libraries** - Required libraries for firmware. Install it via Arduino IDE
- **Images** - Couple of devide photo and schematics

## Schematic
![Schematic](https://github.com/VitaliiUspalenko/Turntable_v1.0/blob/master/Images/fig1.jpg)

## Materials
* Arduino Nano V3.0 replica http://bit.ly/2Lep1au
* 5V Stepper 28BYJ-48 http://bit.ly/2LeYOZh
* Motor driver L298N http://bit.ly/2uqzwh4
* Optocoupler 4N35 (10pcs) http://bit.ly/2KUv9VQ
* 10k resistor (100pcs) http://bit.ly/2L8pGdj
* 220R resistor (100pcs) http://bit.ly/2L8pGdj
* 10k Potentiometer (2pcs) http://bit.ly/2Jqujuu
* 2 Position Toggle Switch http://bit.ly/2mkd9p8
* Momentary push button http://bit.ly/2NgN7i8
* WS2812 RGB LED http://bit.ly/2KX0BCY
* MC-DC2 Wired Remote Shutter Release (this one for my Nikon D5300) http://bit.ly/2Li2j1j
* 4-core silicone wire 26AWG http://bit.ly/2uDG4sT
* Prototype board http://bit.ly/2mkhGry

Full part list with approx prices - https://docs.google.com/spreadsheets/d/1PMvBrpW4V9y2Off9e3PEgwps5Go9wzZ_gY8cqPPg8gQ/edit?usp=sharing

## 3D printed parts
 https://www.thingiverse.com/thing:3018451

## Code setup
  #define photoCount 32         //default number of photos
  #define focusDelay 1200       //holding focus button time (ms)
  #define shootDelay 700        //holding shutter button (ms)
  #define releaseDelay 500      //delay after shutter button release (ms)

  
  
