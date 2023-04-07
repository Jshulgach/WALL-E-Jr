[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
## WALL-E Jr
![](https://github.com/Jshulgach/WALL-E-Jr/blob/main/doc/walle-jr.png)

The WALL-E Jr robot was the result of the 2015 final project for the ENME 408 course at [UMBC](https://me.umbc.edu/). The course was an introduction to the [Arduino](https://www.arduino.cc/) microcontroller platform and hands-on tutorials with designing simple circuits with electronic components, along with an introduction to CAD modelling. The requirements for the final project were dscribed below:

+ Design a circuit using a microcontroller
+ Demonstrate a feature not previously shown in the class (design, task, etc.)
+ Completed design with a budget of less than $100

My focus was on desigining a creative frame to handle a line-following policy using a PID controller. The WALL-E character was the inspiration for the external look ( it's such a cute robot!) which incorporated an ultrasonic range sensor, LED indicators, Infra-red sensors, piezo buzzer, and a tank-tread mobile base.

## Where to start ? 

Table of Contents
---
+ [Assembly](#assembly)
+ [Programing](#programming)
+ [Calibration and Quick Start](#quick-start)
+ [Entertain Mode](#entertain)

---

<a name="assembly"/>

### Assembly:

   + The full list of parts with product links needed to assemble Wall-E Jr. can be found in the [B.O.M]https://github.com/Jshulgach/WALL-E-Jr/blob/master/doc/bom.xlsx).
   + The [final report](https://github.com/Jshulgach/WALL-E-Jr/blob/main/doc/ENME_408_Project_Report_Jonathan_Shulgach.pdf) document also contains detailed assembly and wiring instructions. 
   + Robot structure components were designed using [Autodesk Fusion 360](https://www.autodesk.com/products/fusion-360/overview?term=1-YEAR&tab=subscription) and lasercut with Basswood material.
   + A wiring diagram is provided below:
   ![alt](https://github.com/Jshulgach/WALL-E-Jr/blob/main/doc/wiring.png)

Note 1#: This version never contained a power switch in the original circuit, so I'd recommend implementing your own unless removing the battery to turn off the robot is ok.
Note 2#: the files for the robot frame are currently missing. As soon as they are found they will be moved to the repo! Modelling your own pieces could be a good challenge if you'd like to make the robot.
---


<a name="programming"/>

### Programming:

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software) software specific to your computer's OS following their installation steps. If you're using the IDE environment for the first time, their [guide](https://www.arduino.cc/en/Guide/Environment) has helpful information on getting started.
2. Open the `WALLE_Jr_Final.ino` sketch and connect the board to the PC via USB cable.
3. Select the appropriate board and COM settings and upload the code.

---

<a name="quick-start"/>

### Calibration and Line-Follow mode

When WALL-E Jr first turns on, there is a calibration process he needs to go through with the infrared sensors to adjust to the ambient lighting in its environment.

1) Turn the robot on to enter "standby" mode with the Yellow LED flashing.
2) Press the button to start the "Line-Follow" mode beginning with the calibration routine.
  a) While the blue LED is on, position both IR sensors over the dark line path.
  b) The calibration process ends when all lights flash on and off.
3) Place the robot on the ground over the line and after a few seconds Wall-E Jr will begin his line-following program which consists of a few routines:
  + If either IR sensor detects a change in the baseline light, WALL-E Jr's servo's will adjust their speed to realign and the blue LED will remain on until it's aligned with the path again.
  + If neither IR sensor detect a change in lighting, the blue LED stays off and WALL-E Jr remains on his path
  + If an object is detected along the path then a tone is played to signify a warning.
  + Press the button again to stop the routing and re-enter "Standby" mode.

<a name="entertain"/>

### Entertain Mode

When the button is pressed while the robot is in "Line-Follow" mode, it will switch to the entertain mode. It basically alternates its LEDs from on to off with 
```
RED -> GREEN -> YELLOW -> BLUE 
```
Then rotates both of its servo 90 degrees

--- 

<!---------------------------------------------------------------------
   References
---------------------------------------------------------------------->
