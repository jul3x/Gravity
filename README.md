![VERSION][version] [![Build Status](https://travis-ci.com/jprolejko/Gravity.svg?branch=develop)](https://travis-ci.com/jprolejko/Gravity)

# Gravity

Simulation of gravitational forces between planets with user interaction. Provides interface for easy creation of your own scenarios of **cosmic movement**.

![Simple simulation of cosmic movement][logo]

-----

## Control
Application handles mouse and keyboard events. Click ``left mouse button`` to place a planet (don't release!) and then move mouse somewhere else to adjust starting velocity of the planet. To change size (and mass) of the desired object use combination of ``Left Ctrl`` + ``mouse scroll``. Be careful - size of each planet is limited!

To move the view of your own planetary system use ``keyboard arrows``. If you want to zoom in or zoom out - use ``mouse scroll``.

-----

## Build Options

Build is as **simple** as it is possible [CMake]. Use provided in package ``build_and_run.bash`` script to build and open window with application. Additionally, ``run.bash`` script runs already builded **Gravity** app.  

## Dependencies

* C++14 compiler 
* CMake >=3.6
* SFML >=2.4 library
* GTest - latest master

-----
  
If you want to build unit tests - run ``build_and_run_tests.bash`` script in main directory.

-----

## Description

**Gravity** consists of **ODE** solver (Runge-Kutta 4th order) to determine movement of system of planets. Each planet is computed separately which gives a simple touch of **reality**. Planets collide with each other, so every meeting ends with **destruction** and momentum conservation.
**Future** development is described in ``Issues``. Have fun!

-----

## Changelog

* 03-07-2019 - Gravity 0.4.0
    - Upgraded and fixed UI.

* 27-06-2019 - Gravity 0.3.0
    - Added textures for planets.
    - Minor fixes.
    - Code fully refactored and prepared for future development.

* 13-06-2019 - Gravity 0.2.0
    - Added procedurally generated background with moving and glowing stars.

* 06-06-2019 - Gravity 0.1.0

---

~jprolejko

[VERSION]: https://img.shields.io/badge/version-0.5.0-blue.svg
[logo]: data/logo.png
