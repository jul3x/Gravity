![VERSION][version] [![Build Status](https://travis-ci.com/jul3x/Gravity.svg?branch=master)](https://travis-ci.com/jul3x/Gravity)

# Gravity

Simulation of gravitational forces between planets with user interaction. Provides interface for easy creation of your own scenarios of **cosmic movement**.

![Simple simulation of cosmic movement][logo]

-----

## Usage
Every cosmic system can be loaded and saved by using menu bar on the left side of application. Simulation can be paused and resumed - depending on what you need.  

## Control
Application handles mouse and keyboard events. Click ``left mouse button`` to place a planet (don't release!) and then move mouse somewhere else to adjust starting velocity of the planet. To change size (and mass) of the desired object use combination of ``Left Ctrl`` + ``mouse scroll``. Be careful - size of each planet is limited!

To move the view of your own planetary system use ``keyboard arrows``. If you want to zoom in or zoom out - use ``mouse scroll``.

## Configuration
Environment configuration is editable via config.j3x file in data directory. Feel free to modify it.

-----

## Build Options

Build is as **simple** as it is possible [CMake]. Use provided in package ``build_and_run.bash`` script to build and open window with application. Additionally, ``run.bash`` script runs already builded **Gravity** app.  

## Dependencies

* C++14 compiler
* CMake >=3.6
* SFML >=2.4 library
* TGUI 0.8.5 library
* GTest - latest master

-----
  
If you want to build unit tests - run ``build_and_run_tests.bash`` script in main directory.

-----

## Description

**Gravity** consists of **ODE** solver (Runge-Kutta 4th order) to determine movement of system of planets. Each planet is computed separately which gives a simple touch of **reality**. Planets collide with each other, so every meeting ends with **destruction** and momentum conservation.
**Future** development is described in ``Issues``. Have fun!

-----

## Changelog
* 24-09-2019 - Gravity 0.7.0
    - Added menu bar with map saving/loading and pausing button.
    - Added spawning animation.
    - Auto screen resolution detection added.

* 06-09-2019 - Gravity 0.6.1
    - Fixed building issues.

* 05-09-2019 - Gravity 0.6.0
    - Added trails of planets.
    - Added destruction animation.

* 28-08-2019 - Gravity 0.5.0
    - GTest integration with unit testing.
    - Travis CI integration.
    - Configuration file extracted from code.

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

~jul3x

[VERSION]: https://img.shields.io/badge/version-0.7.0-blue.svg
[logo]: data/textures/logo.png
