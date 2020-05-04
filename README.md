# Midi2trigger
Midi2trigger is Eurorack compatible module PCB for external MIDI device to trigger example drum modules. It’s a 100% non-commercial effort developed purely for own educational purposes where I’m trying to learn to understand schematics, KiCad and PCB making.

I’d like to hear your feedback if you built this module so I can improve these files.

# Design
At the beginning I never meant to make this as a PCB but I wanted to learn KiCad and schematics so I made this as a learning purposes.

Schematic parts has taken from default Arduino MIDI in/thru schematics and various places.

Arduino Pins are assigned in ascending order per semi tone starting with C of the specified octave for Pin2. For example: if set to 1 --> Pin2 = C1, Pin3 = C#1, Pin4 = D1 etc. (standard for most drum sequencers).
You can change the octave at the following line of code (change the int on "int octave = 1;" to example 3, "int octave = 3;"):

# Code
On the original code Midi thru was OFF ("MIDI.turnThruOff();"), since we have the MIDI >thru option on the PCB I have changed the code so that this is turn ON. If you do not need this option, change it back to OFF.

# Panel
Currently there’s no already made panel for this.

# Possible updates to v1.2
- Add: bypass caps to power line, 10uf to positive and GND before and after LM78L05
- Change: route +5v line from LM78L05 to Arduino +5v instead VIN

These can be added to current PCB with soldering capacitors straight to LM78L05 and cutting trace and adding jump wire to Arduino +5v pin.

# Notes
I have tested and verified this board and code.

# Thanks to
- https://www.lookmumnocomputer.com, where I saw this concept on one of the youtube video
- Pieterv1 @circuitbenders.com, code and explanations that I found here: https://www.circuitbenders.co.uk/forum/index.php?topic=2656.0 

# License
Code (AVR projects): GPL3.0.<br><br>
Code (STM32F projects): MIT license.<br><br>
Hardware: cc-by-sa-3.0

# Disclaimer of liability
The material and information contained on this website is for general information purposes only. You should not rely upon the material or information on the website as a basis for making any business, legal or any other decisions.
Whilst I endeavour to keep the information up to date and correct, I make no representations or warranties of any kind, express or implied about the completeness, accuracy, reliability, suitability or availability with respect to the website or the information, products, services or related graphics contained on the website for any purpose. Any reliance you place on such material is therefore strictly at your own risk.

I will not be liable for any false, inaccurate, inappropriate or incomplete information presented on the website.
