# Editor

A barebones text editor written in C++ and OpenGL.

Platform | Status
-------- | -------------------
MacOS    | In Development
Windows  | In Development
Linux    | Not Supported (yet)

## Build Instructions

### Windows

#### Visual Studio

1. Clone the repo
2. Create a new Empty Project with a path to the cloned directory. NOTE: When choosing a path for the project, DO USE the parent folder. e.g D:\Development NOT D:\Development\editor
3. In the Solution Explorer click "All Files", right click "src" and "Include in Project"
4. Right click in the Solution Explorer and select Properties
5. Under "General" change the following: ![General Settings](https://i.imgur.com/Uwzwugj.png)
6. Under "C/C++" > "General" > "Additional Include Directories" add the following: ![Include Directories](https://i.imgur.com/42SH8lZ.png)
7. Under "Linker" > "General" add the following: ![Linker Settings](https://i.imgur.com/yQ0Z4ie.png)
8. Under "Linker" > "Input" > "Additional Dependencies" add the following: ![Linker Dependencies](https://i.imgur.com/4UjClHW.png)
9. Finally, under "Linker" > "System", change the SubSystem to Console.

  APPLY EACH CHANGE AS YOU GO!

10. Hit Ctrl-Shift-B and build the project, it still won't run :(

11. Copy the contents of `dependencies/BINARIES` to `bin/Win32/Debug`
12. Return to Visual Studio and it should now run :)

### macOS

#### Xcode

1. Create a new macOS Console Project
2. `git clone <repo> <path_to_project>`
3. Setup remote origin stuff (if you know, you know)
4. `brew install freetype`
5. Drag each framework from `dependencies/frameworks/` into the Xcode frameworks
6. Add framework: `/usr/local/lib/libfreetype.6.dylib` and `GL.framework`
7. Add `src/` to Xcode
8. Add Header Paths APART FROM GL
9. Edit scheme and set working directory to the root of the project
10. Edit project settings and set build path to `bin/macos` and intermediates to `bin/macos/intermediates`
11. Done :)

### Linux

Coming soon :)
