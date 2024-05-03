# VexWare

Software Systems Final Project
Andrew Phillips, AJ Evans, Kate McCurley

### Project Overview

This project explores writing and injecting non-malicious malware from a plugged in USB device. The malware injection method is similar to a USB rubber ducky, injecting keystrokes into the target computer to download and run files from online (currently set up to download executables from this repo). In addition, the USB device injects keystrokes to determine if a computer is running Linux or Windows, and then downloads and runs the appropriate executables to run on the target OS. 

This repo also contains annoying executables for Linux and Windows. Linux programs run basic, harmless pranks like making the computer speak random phrases aloud and adding silly responses to certain terminal commands; however, they are also set up so the specific changes put in place are easy to modify. The Windows program opens a window in front of the users other windows and ignores requests to close through the GUI and through the Applications tab of Task Manager. Instead of closing the windows when a WM_CLOSE message is received, the application forces the user to navigate through a series of messages boxes to close the program.

### Keystroke Injection

This project utilizes an Arduino UNO R4 emulating an HID keyboard and inject keystroke commands. Depending on the target computer's operating system, a different keystroke sequence is injected into the system to open a terminal, download a desired file off of any GitHub repository, and run the downloaded file off on the target computer. The injection is designed so the Arduino does not need to remain connected to the target computer after the file is running on the target system.

### OS Recognition

There isn't any direct way for the Arduino to determine what operating system the target computer is running. To achieve OS recognition, The Arduino first injects keystrokes assuming a Linux OS. These keystrokes download and install pip and pyserial on to the logged in account, then downloads a python test script from the VexWare repo that sends strings over serial to the Arduino. The Arduino then temporarily ends keyboard emulation and reads from its serial port. If a string is detected, then the Arduino can determine that the computer is running Linux. If a string is not detected, then the Arduino assumes that the computer is running Windows. From this determination, the Arduino can then inject the appropriate keystrokes to download and run files on the target system's OS.

### Firmware Installation

An Arduino UNO R4 is required for HID emulation. The keystroke injection scripts can be downloaded from the `src/keystroke_injection` directory, and the scripts can be flashed to the Arduino using Arduino IDE with the Keyboard library installed. The scripts contain strings that can be replaced with the URL to the raw file to download off of GitHub using a `raw.githubusercontent.com/repository/file_location` format, and the name of the file to run.

### Linux VexWare Attack

The directory `linux_scripts` contains the source code for the executable that is downloaded and run in the Linux injection. This includes functions for modifying the bash config file and scheduling recurring jobs. The main program is currently set up to run basic, harmless pranks like making the computer speak random phrases aloud and adding silly responses to certain terminal commands; however, they are also set up so the specific changes put in place are easy to modify (for example, one of the functions creates a recurring job that runs whatever executable is given as input, so there is a lot of room for modifying what actions are done).

The injection script currently downloads the compiled version of `main.c` and runs it on the victims computer. To modify the actions being done by the virus, changes can be made to this file. Then, the link in the injection script needs to be updated following the installation directions above.

To undo changes done by this attack, 1. remove any new lines appended to the `~/.bashrc` file (then either start a new instance of bash or source the file) and 2. run `crontab -e` then remove any added lines (these changes will take effect as soon as the file is saved).

### Windows VexWare "Attack"

The `visuals` directory contains the C source code and executable for a Windows application that is downloaded from this repo and run when the Windows OS is detected during the injection process.

The application opens a window in front of the users other windows and ignores requests to close through the GUI and through the Applications tab of Task Manager. Instead of closing the windows when a WM_CLOSE message is received, the application forces the user to navigate through a series of messages boxes to close the program.

To close the window, either navigate through the story sequence or kill the process through the Processes tab of Task Manager (found by clicking *More Details*).
