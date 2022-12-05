# 2021-COMP3016-W2: Free Project

Please update this file and include the instructions and use this document for your report.

Make sure to work entirely using OpenGL4.X which you can check if your project relies on shader files and does not use fixed functions for rendering.

Ideally keep the setup Rendering toolchain to reduce the trial and error process of finding something new that works for you.

Work incrementally and be aware of the scale and scope of your project.

# Proposal

At its core, the project is an audio visualiser. The project will render a fixed number of 3D cubes in a circle, each representing a different band of frequency, that will vertically extend and retract dynamically in time with a given audio track, similar to how traditional 2D audio visualisers use bars to represent different frequencies.

The user will interact with the project by selecting between 3 different camera control modes. The first and default will automatically circle around the cubes at a fixed rate, the second will stop the camera in place and the third will allow for manual control of the camera by the user. In this mode, the camera can be moved left and right using the arrow keys, remaining in place when there is no input.

The project will use the following libraries/packages on top of OpenGL:
- Dear ImGui: Simple GUI to allow the user to view and control audio playback, including the “resolution” of the visualiser (the sample time slice to visualise)
- Tiny File Dialogs: Allow the user to open an audio file at runtime
- OpenAL: Play audio files through speakers
- LAME: Convert MP3 data into PCM to be read into OpenAL
- FFTW: Calculate frequencies from PCM data
- Doctest: Unit testing

