# Arduino-Processing-Laser-CNC
Arduino feat. Processing Laser CNC Project


Hey Ho,

This is a project I made in 2015 and now publishing.
The core of the Project is a hardware made out of two CD drive stepper motors an mechanics, two LM298 motor drivers and an arduino Mega.

The one axis controlls the 150mw 405nm laser and the oder axis moves the table.

The Processing codes generates strings from a .png or .jpg file and send them via serial to the arduino, wich then moves the table and laser and triggers the laser in the moment, when a black pixel showing up in the string.
Burning time is set in the arduino code. Pictures are importet manually and have to be in the folder, where the processing sketch is located.

Watch
https://www.youtube.com/watch?v=gs4uoEPE4Lk
for further information.
