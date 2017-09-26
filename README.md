# Evolving Snakes
Snakes from the classical game are controlled by neural networks and are evolved using a genetic algorithm. The snakes eat the food and grow, but passively lose body mass. If the run out of body parts, they die. They can also split in order to multiply.

![Evolving snakes](https://cloud.githubusercontent.com/assets/12662877/13763264/981f20b8-ea4d-11e5-94d7-91d2242d5c01.png)

Video demo: https://www.youtube.com/watch?v=eQoa-uFyXFw

This project uses the GLFW library and OpenGL.

Controls:
* f1 - cycle trough the snakes  (the selected snake will blink; its neural network is shown in the other window)
* f2 - pause
* f3 - toggle off/on drawing the window with the snakes
* f4 - cycle trough drawing modes for the snake window (regular; only living snakes; only not yet hatched snakes; only dead, not decomposed snakes)
* f5 - toggle off/on drawing the window with the neural networks
* f6 - cycle trough drawing modes for the NNs (regular; connections showing thier current effect; relative importance as a linear sum; relative importance as a sum of squares)
* f7 - cycle trough the output neurons, the effect each neuron has on that output neuron is shown, the importances are shown only for that output neuron
* f8 - enter new delay between steps in seconds in the console (0 for no delay - max speed)
* f9 - save the current state, enter the name of the file in the console
* f10 - load a save, eneter the name of the file in the console
* f11 - change settings/reset, enter 'y' or 'n' in the console to choose whether to reset and then whether to chenge the settings, the current settings will be shown in brackets
* f12 - toggle on/off controlling the selected snake with the arrow keys.

There are more options for the loading:

1. You can load multiple save files at once like this:
    * `save1+save2+save3+...+saveN`
    * The settings of the environment are that of save1.

2. You can load only the settings of a save like this:
    * `-save1+save2+save3+...+saveN`
    * The settings of the environment are again that of save1, but its food pieces and snakes are not loaded.
    * Typing only `-save1` will load the settings of save1, but will reset all the food and snakes.

3. You can also start with a `+`:
    * `+save1+save2+save3+...+saveN`
    * This will load the snakes and food from all save files, but will also keep the current ones. The settings will not change.

4. If you instead want to change the settings:
    * `+-save1+save2+save3+...saveN`
    * This will load the snakes and food from all save files except save1, but will also keep the current ones. The settings will be those of save1.
    * Typing only `+-save1` will load the settings of save1, but will keep all the current food and snakes.

5. If you want to change the settings but also load the food snakes:
    * `+!save1+save2+save3+...saveN`
    * This will load the snakes and food from all save files, but will also keep the current ones. The settings will be those of save1.
    * Typing only `+!save1` will load the settings, food and snakes of save1, but will also keep all the current food and snakes.

P.S. Don't have save files with '+'s, '-'s and '!'s in their names.

Build commands:

For all files: `mingw32-g++.exe -Wall -fexceptions -O2 -std=c++11 -Iinclude -c sources\[.cpp file] -o obj\Debug\sources\[.o file]`

`mingw32-g++.exe -Llib-mingw -o "bin\Debug\Evolving Snakes.exe" obj\Debug\sources\colours.o obj\Debug\sources\controller.o obj\Debug\sources\ctrBasic.o obj\Debug\sources\ctrNeuralNetwork.o obj\Debug\sources\ctrRandom.o obj\Debug\sources\ctrRandomEvolving.o obj\Debug\sources\draw.o obj\Debug\sources\draw_neural_net.o obj\Debug\sources\food.o obj\Debug\sources\main.o obj\Debug\sources\point.o obj\Debug\sources\randomisation.o obj\Debug\sources\run.o obj\Debug\sources\sight.o obj\Debug\sources\snake.o obj\Debug\sources\window_functions.o obj\Debug\sources\window_size.o  -s  -lglfw3 -lgdi32 -lopengl32`
