# Morse Code Memory Game
[Original Devpost](https://devpost.com/software/bithacks-hackathon-project)

https://github.com/user-attachments/assets/25d740ae-4769-4035-9ea9-6cedd25ccec9

## Inspiration
Many people are familiar with SOS standing for "Save Our Souls," but what most people don't know that "Save Our Souls" came after the creation of SOS to help people remember SOS as SOS was used since the morse code was easy to do and distinguishable.

We believe that morse code is an essential survival skill to know just like how swimming is suggested for children to learn as a survival skill as well.

Thus, we created our Morse Code Mastery Game, where it shows the patterns of morse code with the LED lights and the corresponding sounds in the format of a fun memory game that children can enjoy.

## What it does
The Morse Code Mastery Game has learning and challenge mode to teach the user morse code. In learning mode, the letters start out in order from A-Z to introduce them before being randomly chosen. Additionally, the LCD display shows the morse code letter and shows the corresponding morse code sequence in the LED lights along with an accompanying sound from the piezo buzzer. Then, the user inputs the morse code sequence with the corresponding buttons.

In challenge mode, letters are chosen at random and only the LCD display shows the desired letter without any hints to test the user's knowledge of morse code.

## How we built it
We used Arduino IDE to program the ESP-32 board, which is the brains of the project. Then, we connected it to an LCD display, piezobuzzer, push buttons, and LEDS on top of two breadboards. The LCD display shows the letter we want the user to input with the buttons, where one button selects between learning and challenge mode, one button is for a short beep input, one button for a long beep input, and another button to signal when the user is done using the input. Each button has an associated LED to it to give a visual cue and the piezobuzzer also plays an tone as well for the morse code input. Lastly, the piezobuzzer also plays a congratulations song or losing song depending on whether the user puts in the correct input or not.

## Challenges we ran into
One of our main challenges was implementing the morse coded lights -- their code for their durations and the correct schematics for them. Even after we figured out the correct connections to the esp32 for the pushbuttons and LEDs, there were several strange errors we had to debug, such as, one button controlling two LEDs when it should only control one, and another button controlling one LED and the LCD display. The issues resolved to be mainly coding-related, and we ended up learning more about Arduino IDE, such as how interrupts and tones work.

## What we learned
The challenges we faced throughout this project are the ones that taught us the most. Something we learned early on in the project was that handling time-sensitive code in the middle of an interrupt in Arduino wasn't the best tactic. Re-directing the time-sensitive aspect of the code to the loop function would be a better and ore effective method.

## Future Plans
We intend to add more features such as more testing phrases apart from letters, having the game adjust to user speed, include spaced repetition in learning mode for better retention, and including a mode of converting a morse code input back into text.
