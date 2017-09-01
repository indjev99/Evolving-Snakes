# Evolving Snakes
Snakes from the classical game are controlled by neural networks and are evolved using a genetic algorithm. The snakes eat the food and grow, but passively lose body mass. If the run out of body parts, they die. They can also split in order to multiply.

![Evolving snakes](https://cloud.githubusercontent.com/assets/12662877/13763264/981f20b8-ea4d-11e5-94d7-91d2242d5c01.png)

This project uses the GLFW library and OpenGL.

Controls:
* f1 - cycle trough the snakes  (the selected snake will blink; its neural network is shown in the other window)
* f2 - pause
* f3 - toggle off/on drawing the window with the snakes
* f4 - toggle off/on drawing the window with the neural networks
* f5 - cycle trough drawing modes for the NNs (regular; connections showing thier current effect; relative importance as a linear sum; relative importance as a sum of squares)
* f6 - enter new delay between steps in seconds in the console (0 for no delay - max speed)
* f7 - save the current state, enter the name of the file in the console
* f8 - load a save, eneter the name of the file in the console
* f9 - reset, enter 'y' or 'n' in the console to choose whether to chenge the settings, the current settings will be shown in brackets
* f10 - toggle on/off controlling the selected snake with the arrow keys.

There are more options for the loading:

1. You can load multiple save files at once like this:
* 'save1+save2+save3+...+saveN'
* The settings of the environment are that of save1.

2. You can load only the settings of a save like this:
* '-save1+save2+save3+...+saveN'
* The settings of the environment are again that of save1, but its food pieces and snakes are not loaded.
* Typing only '-save1' will load the settings of save1, but will reset all the food and snakes.

3. You can also start with a '+':
* '+save1+save2+save3+...+saveN'
* This will load the snakes and food from all save files, but will also keep the current ones. The settings will not change.

4. If you instead want to change the settings:
* '+-save1+save2+save3+...saveN'
* This will load the snakes and food from all save files except save1, but will also keep the current ones. The settings will be those of save1.

5. If you want to change the settings but also load the food snakes:
* '+!save1+save2+save3+...saveN'
* This will load the snakes and food from all save files, but will also keep the current ones. The settings will be those of save1.

P.S. Don't have save files with '+'s, '-'s and '!'s in their names.
