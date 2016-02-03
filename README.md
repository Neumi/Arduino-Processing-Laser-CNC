# Arduino-Processing-Laser-CNC
Arduino feat. Processing Laser CNC Project


Hey Ho,

This is a project I made in 2015 and now publishing.
The core of the Project is a hardware made out of two CD drive stepper motors an mechanics, two L298 motor drivers and an arduino Mega.

The one axis controls the 150mw 405nm laser and the oder axis moves the table.

The Processing codes generates strings from a .png or .jpg file and send them via serial to the Arduino, wich then moves the table and laser and triggers the laser in the moment, when a black pixel showing up in the string.
Burning time is set in the Arduino code. Pictures are imported manually and have to be in the folder, where the processing sketch is located.

I wrote some new stepper motor functions because I lost steps with the embedded Arduino lib. Its all some kind of sketchy, but it works perfectly fine and really fast.

In future versions I might implement a transmission of gray scales to change the exposure time on the laser while the laser is operating. With this technique it might be possible to burn real grayscale pictures in different materials like wood, paper etc.
 

Watch
https://www.youtube.com/watch?v=gs4uoEPE4Lk
for further information.

If you like this project feel free to buy me a coffee! https://ko-fi.com/Buttons/Buy/1669O9K1BCOA

Best regards,

Neumi
