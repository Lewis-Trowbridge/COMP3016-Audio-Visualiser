# 2022-COMP3016-C2: Free Project

# Introduction

This project is intended to visualise the audio of MP3 files in 3D space using OpenGL, in a similar process to traditional audio visualisers often used in online music videos (One example here: https://youtu.be/YieDIB7G0J8).

![A GIF of the visualiser in locked mode](https://user-images.githubusercontent.com/22503395/211068714-08ea60d6-657a-4e8f-9714-6e1954259296.gif)

The visualiser playing a [sine wave](https://onlinetonegenerator.com/).


# Code structure
[![](https://mermaid.ink/img/pako:eNqFVntv4zYM_yqC_0pTJ837dcOAIbceArTXYr1twBDgoFi0rU2WMklOmxb97qNsJ3IS3xogiUX--CZFvwWRYhAsgkhQYz5zmmiarfVaum9BIw86SsFYTa3S5M3RCX46xPBX-G5JlG_A1KiWLRaI5jIhMRcgaQaey1S-EUBozrh6gkhJZu5AJjb1kI1SgmwF3aMGT12iGk3v0VcSHR8PfjrI9YmfrcKrKy-vtiBv0R2MUKikdeXFnKlfnD-P-FBnRBqohaVTtJJLriMBjXK3mLGKs7bXhGn6vFTSaiWMp2ZqB2UMv_EktU2MO4hr9GiP9nzUJeP9tDKf0RTUanJNEpEtFhm1owXZcXhuZGy1-hsiy5U8q9oOqUr_9OUu59L-TCy82FyD-eRhJctpcG3yqZ7_0pfL_LWuyD2YtO3pBmy-rQNdxupnoSj7VhpvVU48UpvWEDvQlkdUiP0T_oIz0Mrw52uebUCHZEdFDlcIbUiaA9dTdhp6jMYx9tKA7-vrxgxxyf4PVOnCEJZKafYRTiqdUVFDVdneUbWSDF48oziCIZs8jkGvLrwoB1Pm2QWrMkYiJVSui-Q19Ag2JQNxT3GKX3zxPdvQHTDPPmoo6uDLxCW3t1plbu5ah7vgqhjwI6ZohjO5s37AiZZGuFZ6Cck-JK-eZVwAB3JY-uW5WlknRWUiICSXwogug2gcrsdUyeTODSteRCsZq1rTFKnA-g0JzTYcpG3gCCf6qEwDi_E4zg0siyI08M0WolxQfQY4FM-kmFkJxpwk_8LfWgrLkavGtinY8gLUasdZ_ULpZNukPxh-T6lkAtqk_C-vqI7rTdDevRMdx4vscPE2NAByE7DV9XkyE-VEeEy5Ix7iAruS1eZAoXKfNAR0q-HfHGS0vwyqsFlyOZgWo5aGOErRP2DNj9w40_4HNzkV3ODwZV9-X_2JF4F6rvVHscNMqp6rEA7nXLCHk0XkK-TXZvtkb6K03wLt8-VXqm7X9yXSyqy0CQi6NcC-8exkVTZ6fyhY2SoHD8KawfBgJXSKsUcLxZWYn9ljqk7eG9ZBfx2QdqdTPZXr4kPYSU99iL4o-ocSjalwUtVqreN73W4bD-6y-gHCPV2MocMGYYBZzChn-Kb15qqwDmwKWJZggY8MYpoLuw4wewiluVVPexkFixj3AYRBvsUmherl7Iz6K-MY2JHodifg8S2w-617r0u4sagTBybmiaPnWiA5tXZrFjc3jt1NuE3zTTdS2Y3hLKXaprv55GYymMzoYAiT6ZCOh0MWbfrzWTwY9WM27fUHNHh_DwMo7N9XL5HuLwy2VP6lFHpqdQ7F0Rl-CRad4aTbm_Vns8lg3h_3hvPeJAz2SJ_OuuNxfzoZj0b92Xw0HqLm10JFvzubT8e90WQ6m4yGo97o_T_t1J2Z?type=png)](https://mermaid.live/edit#pako:eNqFVntv4zYM_yqC_0pTJ837dcOAIbceArTXYr1twBDgoFi0rU2WMklOmxb97qNsJ3IS3xogiUX--CZFvwWRYhAsgkhQYz5zmmiarfVaum9BIw86SsFYTa3S5M3RCX46xPBX-G5JlG_A1KiWLRaI5jIhMRcgaQaey1S-EUBozrh6gkhJZu5AJjb1kI1SgmwF3aMGT12iGk3v0VcSHR8PfjrI9YmfrcKrKy-vtiBv0R2MUKikdeXFnKlfnD-P-FBnRBqohaVTtJJLriMBjXK3mLGKs7bXhGn6vFTSaiWMp2ZqB2UMv_EktU2MO4hr9GiP9nzUJeP9tDKf0RTUanJNEpEtFhm1owXZcXhuZGy1-hsiy5U8q9oOqUr_9OUu59L-TCy82FyD-eRhJctpcG3yqZ7_0pfL_LWuyD2YtO3pBmy-rQNdxupnoSj7VhpvVU48UpvWEDvQlkdUiP0T_oIz0Mrw52uebUCHZEdFDlcIbUiaA9dTdhp6jMYx9tKA7-vrxgxxyf4PVOnCEJZKafYRTiqdUVFDVdneUbWSDF48oziCIZs8jkGvLrwoB1Pm2QWrMkYiJVSui-Q19Ag2JQNxT3GKX3zxPdvQHTDPPmoo6uDLxCW3t1plbu5ah7vgqhjwI6ZohjO5s37AiZZGuFZ6Cck-JK-eZVwAB3JY-uW5WlknRWUiICSXwogug2gcrsdUyeTODSteRCsZq1rTFKnA-g0JzTYcpG3gCCf6qEwDi_E4zg0siyI08M0WolxQfQY4FM-kmFkJxpwk_8LfWgrLkavGtinY8gLUasdZ_ULpZNukPxh-T6lkAtqk_C-vqI7rTdDevRMdx4vscPE2NAByE7DV9XkyE-VEeEy5Ix7iAruS1eZAoXKfNAR0q-HfHGS0vwyqsFlyOZgWo5aGOErRP2DNj9w40_4HNzkV3ODwZV9-X_2JF4F6rvVHscNMqp6rEA7nXLCHk0XkK-TXZvtkb6K03wLt8-VXqm7X9yXSyqy0CQi6NcC-8exkVTZ6fyhY2SoHD8KawfBgJXSKsUcLxZWYn9ljqk7eG9ZBfx2QdqdTPZXr4kPYSU99iL4o-ocSjalwUtVqreN73W4bD-6y-gHCPV2MocMGYYBZzChn-Kb15qqwDmwKWJZggY8MYpoLuw4wewiluVVPexkFixj3AYRBvsUmherl7Iz6K-MY2JHodifg8S2w-617r0u4sagTBybmiaPnWiA5tXZrFjc3jt1NuE3zTTdS2Y3hLKXaprv55GYymMzoYAiT6ZCOh0MWbfrzWTwY9WM27fUHNHh_DwMo7N9XL5HuLwy2VP6lFHpqdQ7F0Rl-CRad4aTbm_Vns8lg3h_3hvPeJAz2SJ_OuuNxfzoZj0b92Xw0HqLm10JFvzubT8e90WQ6m4yGo97o_T_t1J2Z)

The code is structured as above - the Orchestrator class is responsible for the coordination of the different elements of the application, such as managing visualiser cubes, passing audio data to be processed and rendered, and button management. Each of these more specialised tasks is handled by a class which is contained in the Orchestrator.

The code uses the provided LoadShaders and loadTexture components, repackaging the OpenGL setup and drawing into an object-oriented format. On top of this, the code retains the init and display loop concepts provided in Project.cpp, but uses this object-oriented framework.

# Setup

This project uses VCPKG, a package manager for C++, which integrates with CMake. The setup instructions are provided here: https://vcpkg.io/en/getting-started.html. The project uses VCPKG's manifest mode.

Once installed, either open the project in Visual Studio as a CMake project, or use CMake to build the project as normal.

If using Visual Studio, you may need some extra setup to make sure that VCPKG is configured correctly. Using ```vcpkg integrate install``` should allow this, however if this doesn't work, try settting the VCPKG CMake toolchain file manually in CMakeSettings.json.

![image](https://user-images.githubusercontent.com/22503395/211206779-e2be87ab-c408-402b-9b3b-ceb166fff804.png)

On top of this, to use MinGW you will need to update the path in CMakeSettings.json.

![image](https://user-images.githubusercontent.com/22503395/211209543-5068e83f-9461-48c1-82d5-2b6b99bd06a9.png)


# Usage
## Tests
Once built, an executable file called "visualiser" will be produced. To control whether tests are run, use:

- ```--exit``` to run only tests
- ```--no-run``` to skip tests and run the application
- Neither to run tests and then the main application.

## Application controls
On opening, the application will open a file prompt to allow you to select an MP3 file to play. Once selected, the visualisation will begin, and the following controls can be used:

- Spacebar: switch camera control modes, cycling from locked, automatic and manual control.
- Left and right arrow keys: Move the camera left and right while in manual control mode.

Automatic mode:

![The camera moving around the visualiser automatically](https://user-images.githubusercontent.com/22503395/211069741-9c3189e4-63ea-4d95-b48d-fd742eda90c6.gif)

Manual mode:

![The camera moving around the visuliser under manual control](https://user-images.githubusercontent.com/22503395/211070497-436f4f41-5082-478c-9166-a889f1f59507.gif)


The ImGUI window can also be used to pause and continue playback, as well as open new files at will.

![Opening a file in the visualiser, which is loaded and played.](https://user-images.githubusercontent.com/22503395/211071367-2c3cf6d4-548e-46e8-a858-58813ee0e108.gif)

# Proposal

At its core, the project is an audio visualiser. The project will render a fixed number of 3D cubes in a circle, each representing a different band of frequency, that will vertically extend and retract dynamically in time with a given audio track, similar to how traditional 2D audio visualisers use bars to represent different frequencies.

The user will interact with the project by selecting between 3 different camera control modes. The first and default will automatically circle around the cubes at a fixed rate, the second will stop the camera in place and the third will allow for manual control of the camera by the user. In this mode, the camera can be moved left and right using the arrow keys, remaining in place when there is no input.

The project will use the following libraries/packages on top of OpenGL:
- Dear ImGui: Simple GUI to allow the user to view and control audio playback, including the “resolution” of the visualiser (the sample time slice to visualise)
- Tiny File Dialogs: Allow the user to open an audio file at runtime
- MPG123: Convert MP3 data into PCM to be processed (changed from LAME)
- KissFFT: Calculate frequencies from PCM data (changed from FFTW)
- Doctest: Unit testing

# Video
The link is here: https://www.youtube.com/watch?v=nuM0bxKY09I

Update: In the video it is stated that MinGW compilation does not work. This was true at the time of recording, but using the instructions above in the setup section should allow it to start working.
