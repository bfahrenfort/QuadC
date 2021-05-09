# Complacent Complaint Chat Client
## aka QuadC
A Win32 Homestuck-analogue chat client written in C/C++.

Current functionality is a CLI typing quirk/color storage and parsing system via the use of 'quirkfiles', a text file with the .qrk extension.

Plan of action:
  * Create win32 window client that allows text coloring
  * Implement user identification, chat, and servers
  * Acquire hosting

## Build instructions
run `cmake` with your desired compiler and arguments (`cmake .` for default) and then build the resulting project file (tested with LLVM and NMake).
