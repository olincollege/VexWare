# VexWare

Software Systems Final Project
Andrew Phillips, AJ Evans, Kate McCurley

### Keystroke Injection

This project utilizes an Arduino R4 emulating an HID keyboard and inject keystroke commands. Depending on the target computer's operating system, a different keystroke sequence is injected into the system to open a terminal, download a desired file off of any GitHub repository, and run the downloaded file off on the target computer. The injection is designed so the Arduino does not need to remain connected to the target computer after the file is running on the target system.

### OS Recognition

There isn't any direct way for the Arduino to determine what operating system the target computer is running. To achieve OS recognition, The Arduino first injects keystrokes assuming a Linux OS. These keystrokes download and install pip and pyserial on to the logged in account, then downloads a python test script from the VexWare repo that sends strings over serial to the Arduino. The Arduino then temporarily ends keyboard emulation and reads from its serial port. If a string is detected, then the Arduino can determine that the computer is running Linux. If a string is not detected, then the Arduino assumes that the computer is running Windows. From this determination, the Arduino can then inject the appropriate keystrokes to download and run files on the target system's OS.

### Installation

An Arduino UNO R4 is required for HID emulation. The keystroke injection scripts can be downloaded from the `src/keystroke_injection` directory, and the scripts can be flashed to the Arduino using Arduino IDE with the Keyboard library installed. The scripts contain strings that can be replaced with the URL to the raw file to download off of GitHub using a `raw.githubusercontent.com/repository/file_location` format, and the name of the file to run.


