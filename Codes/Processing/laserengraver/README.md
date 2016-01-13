# Arduino-Processing-Laser-CNC
Arduino feat. Processing Laser CNC Project

11.01.2016

Readme for Processing Code



This readme will describe how to use the Processing sketch…

Setting up Serial:
At first you have to set up the serial connection between the Arduino and your computer or Processing sketch. For my computer it was Serial port nr 9, but for your setup it should be a different port. Find out by print the Serial.list(), before you run the processing sketch! When you found the port number, change it in the Processing sketch by me. 

Setting um pictures:
Then you can import pictures to the program. The pictures can be in .jpg and .png formats and have to have a resolution of 300x300 pixels. Furthermore the pixels have to be totally black, because the algorithm is searching only for black pixels and only translates them into a ‚1‘ in the serial string.

Running:
While the laser is running, you have to keep the connection to the computer. After every two lines the Arduino sends a ‚give me a newline‘ in form of a ‚k‘ char! When Processing receives the newlines instruction, processing generates the string for the next two pixel lines and sends them to the Arduino. This repeats until the picture is completely transmitted.

