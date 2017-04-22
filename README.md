# Arduino-Controlled-Motor-with-Encoder

For this project, I assembled the hardware to operate a 6V DC motor that has an encoder mounted on it, and wrote the code in Arduino to operate them. Attached is the shcematic, a board diagram in Fritzing, and my Ardunio code. A video of the motor and encoder in action can be found by following the link to my Google Drive.

I created the schematic in Fritzing. The motor and encoder are attached and move together, but for a clearer schematic, I showed them as two separate components.

I used a simple 6V motor with encoder with my main restrictions being cost and current supply. The motor and encoder work well enough, but the encoder seems to miss a few steps when operating at half speed. This caused some inconsistencies with my motor movements because the interrupt function would be skipped at times. In short, I could tell the motor to move for 1 second and sometimes it would, but other times it would run for half a second because the encoder skipped some readings and the interrupts that I had planned for were never seen. 

Since this is just a demonstration and I am fully aware that I traded off accuracy and repeatability for cost, I am okay with this issue for this project. If I were to run this project again with a larger budget and wanted more accuracy, I would do one of two things. I would prefer to buy a custom stepper motor with encoder. This would allow me to enter a number of steps and let the encoder read out as it will; which eliminates the need to tune and account for the time used by an interrupt function. Alternatively, I could use a higher quality DC motor and feedback encoder info to a loop that would run until it hits a desired amount of degrees turned. This would involve some tuning with the interrupt function, but hopefully with better hardware, that time delay from the interrupt would be more repeatable.

A demonstration of the motor movement can be seen at the following link. The encoder readout can be seen on the computer monitor in the Serial window. To fit everything on screen it may be a bit difficult to see the encoder read out well, but as expected, the encoder missed several steps so the encoder readout is not entirely precise for this demonstration. The Arduino code does, however, work as intended and outputs the encoder readout as the motor moves.

https://drive.google.com/open?id=0BzlL2mOr29jDQlBYeTNOMG5RX0U
