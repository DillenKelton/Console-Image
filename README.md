# Console-Image
Displays an image within a console window
Currently only works on Windows - A Linux-compatible version is planned

### COMPILATION:
Compiled with gcc version 8.1.0 (x86_64-win32-seh-rev0, Built by MinGW-W64 project)  
MinGW-W64 is a fork of the MinGW project and can be found at [this](http://mingw-w64.org/doku.php/start) link  
To compile, just run make with the provided makefile

### USAGE:
Use the following format: ConsoleImage.exe [image-name].[extension] [desired-width] [desired-height]
Example: ConsoleImage.exe myImage.jpg 100 100
If width and height are not specified, a default value will be used.