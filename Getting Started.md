# Getting Started

# Step 1: Generating Project Files

![Right click on .uproject file. On Windows 10, you’ll see a Generate Visual Studio Project files. On Windows 11, you might have to click Show more options to see it.](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled.png)

Right click on .uproject file. On Windows 10, you’ll see a Generate Visual Studio Project files. On Windows 11, you might have to click Show more options to see it.

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%201.png)

![Note that a Source file, and the project .sln file will be generated. The source folder has all the project header and source files. To open the project, you will need to build the project by opening the .sln file first. ](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%202.png)

Note that a Source file, and the project .sln file will be generated. The source folder has all the project header and source files. To open the project, you will need to build the project by opening the .sln file first. 

# Step 2: Building the Solution (.sln file)

 

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%203.png)

## If using Visual Studio

(Sorry, my Visual Studio was installed in Korean, and I still don’t know how to change it… But the toolbar options will most likely be in the same order)

![Ctrl + Shift + B or just Ctrl + B to build.](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%204.png)

Ctrl + Shift + B or just Ctrl + B to build.

Or alternatively, you can just press F5 or Ctrl + F5 or the green play button to run the project. This will automatically build the solution.

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%205.png)

## If using Jetbrains Rider (Recommended)

![Similarly, you can build the solution by clicking the option in the toolbar, or just press Ctrl + B.](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%206.png)

Similarly, you can build the solution by clicking the option in the toolbar, or just press Ctrl + B.

![Or you can just press Run or Debug, and it will build automatically](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%207.png)

Or you can just press Run or Debug, and it will build automatically

![This will open up the project](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%208.png)

This will open up the project

![Note that after you build the solution, and as long as there are no changes in the code, you can open the project by clicking the .uproject file](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%209.png)

Note that after you build the solution, and as long as there are no changes in the code, you can open the project by clicking the .uproject file

# Step 3: Playing in VR Mode

## Install SteamVR

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2010.png)

## Connect your Oculus headset to the PC

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2011.png)

![Enable Quest Link](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2012.png)

Enable Quest Link

![You can either do Air Link or Rift Link. From a hardware standpoint, it is recommended that you connect the headset to your PC with the Rift Link. (You don’t have to necessarily get the official Link cable. A regular cable will suffice)](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2013.png)

You can either do Air Link or Rift Link. From a hardware standpoint, it is recommended that you connect the headset to your PC with the Rift Link. (You don’t have to necessarily get the official Link cable. A regular cable will suffice)

![Make sure you are in this white room, before opening the project.](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2014.png)

Make sure you are in this white room, before opening the project.

![Click the ellipsis button → Run in VR Preview](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2015.png)

Click the ellipsis button → Run in VR Preview

![Note that if you open the project before enabling Oculus Link, the VR Preview option will be greyed out.](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2016.png)

Note that if you open the project before enabling Oculus Link, the VR Preview option will be greyed out.

# Additional Info: Locating the Source files

## Method 1: In the Solution File

You can press Ctrl + Alt + L, to open up the Solution Explorer. Locate the Source folder, and you will find what you need.

![Visual Studio](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2017.png)

Visual Studio

![Rider](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2018.png)

Rider

Note: The .Build.cs file is a C# file that has the Module includes. Not important at the moment, but if you want to utilize more plugins or modules, you can include them here.

![GesureRecognition.Build.cs](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2019.png)

GesureRecognition.Build.cs

## Method 2: In the Project Folder

![./Source/GestureRecognition](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2020.png)

./Source/GestureRecognition

## Method 3: From the Content Browser

1. You can either press the Window option → Content Browser → Content Browser 1
2. Or if it’s already open, you’ll find it in the bottom of the Unreal Engine editor
3. Or you can just press Ctrl + Space (Doesn’t work on MacOS)

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2021.png)

Then under C++ Classes folder → Gesture Recognition → Public, you can find the files you are looking for

![Untitled](Getting%20Started%201e3ad0e6f6844b10988ecf8198ba516c/Untitled%2022.png)