# Custom-PCB-Arcade-Console-Embedded-C-Coded-Game-Engine-Longhorn-Racer-
This is my C coded video game, Longhorn Racer, which is implemented on a custom PCB video game console which I made in KiCAD

Please see this YouTube video for a video demonstration on gameplay :) https://youtu.be/efSY2miP3bw?si=rm0MrgWzhUOSOycD
<br><br>

- Designed custom PCB (KiCAD)  integrating ARM Cortex MCU with ST7735 LCD, ADC potentiometer, audio DAC, and LEDs 
- Programmed bare metal C drivers and Timer ISRs for real-time I/O sampling to process asynchronous player inputs and game logic
- Designed a low latency multi bit R-2R DAC audio engine, utilizing 11.025 kHz periodic interrupts to fetch flash stored audio samples
- Developed a C graphics engine with sprite collision detection & chroma keying to composite sprites onto background matrices 
- Implemented fixed point math & localized string matrix for multi language gameplay, minimizing overhead within a 128 kB MCU footprint

<img width="385" height="490" alt="Gameplay Image" src="https://github.com/user-attachments/assets/99cffab4-4b00-4b1c-b606-ef77105c236f" />

<br><br>
Schematic and layout for reference
<br><br>
<img width="732" height="507" alt="Custom Video Game Schematic " src="https://github.com/user-attachments/assets/9996abbf-9e8a-4a2b-b202-9c312c95be4d" />


<br><br>
PCB editor in KiCAD
<br><br>
<img width="1119" height="662" alt="Custom PCB Video Game" src="https://github.com/user-attachments/assets/c9214b1f-8627-4f50-9b7f-0b2d79e38c4e" />


<br><br>
Physical Custom PCB with all parts soldered 
This is what the gameplay looks like
<br><br>
Again, please see this YouTube video for a video demonstration on gameplay :) https://youtu.be/efSY2miP3bw?si=rm0MrgWzhUOSOycD
<br><br>
<img width="485" height="600" alt="Gameplay Image" src="https://github.com/user-attachments/assets/99cffab4-4b00-4b1c-b606-ef77105c236f" />


<br><br>
Longhorn Racer starting and end screens (I drew these! I also drew the longhorn and squirrel sprites myself!)
<br><br>

<img width="490" height="600" alt="Starter Screen" src="https://github.com/user-attachments/assets/e4a3d226-fa6e-4522-8ce3-eb3457303a48" />
<img width="490" height="600" alt="End Screen Page" src="https://github.com/user-attachments/assets/638ea709-f738-4c38-a6ea-13a3518c66c7" />









