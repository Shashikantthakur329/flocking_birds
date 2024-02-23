# FLOCKING BIRDS
![FLOCKING BIRDS](./simulation_gif.gif#center)

## Overview 
This project is a simulation of flocking behavior observed in birds in the air and fishes in the water. The simulation is implemented entirely in C++ using the Raylib library.

## Features
* Flocking behaviour: Simulates the collective motion of a group of entities(birds or fishes) exhibiting cohesion, alignment and separation behaviours.
* Dynamic Parameters: Parameters like cohesion radius, alignment radius, separation radius can be set with sliders.
* Raylib Integration: Utilizes the Raylib library for graphics rendering and user input.

## Algorithm Overview
The flocking simulation is based on three fundamental behaviors observed in collective animal motion: Cohesion, Separation, and Alignment.

### Cohesion
* Cohesion represents the tendency of individuals to move towards the average position of their nearby neighbors.
* Each entity (bird or fish) evaluates its proximity to others within a defined cohesion radius.
* The entity calculates the average position of its neighbors.
* It then adjusts its current velocity to steer towards this average position.

### Separation
* Separation focuses on avoiding collisions and maintaining personal space between entities.
* Entities assess the distance to their neighbors within a specified separation radius.
* The entity adjusts its velocity to move away from neighbors that are too close.

### Alignment
* Alignment aims to make entities move in the same direction as their neighbors.
* Entities consider the velocities of nearby neighbors within an alignment radius.
* The entity adjusts its velocity to align with the average velocity of its neighbors.

## Requirements
C++ Compiler
Raylib Library (Ensure you have the latest version of Raylib installed)


## Getting Started
* Clone the repository:

```<bash>
git clone https://github.com/Shashikantthakur329/flocking_birds.git
```

* Build the project using a C++ compiler.

* Run the executable.


## Controls
* Use sliders to control the radius of separation, alignment and cohesion

## Acknowledgments
[Raylib Library](https://www.raylib.com/): A simple and easy-to-use C library for graphics and games.

## Contributing
Feel free to contribute to the project by opening issues or pull requests.