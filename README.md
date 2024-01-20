# Quantum Effects
 
<div align="center">
  <a href="https://github.com/ahmedkerouat/quantum-effects">
    <img src="source\resources\quantum-effects.png" alt="Logo" width="400" height="125">
  </a>
</div>

## Table of content

- [About the project](#aboutproject)
- [Getting Started](#getstarted)
- [Structure](#structure)
- [Usage](#usage)
- [Controls](#controls)
- [Screenshots](#screenshots)
- [Contributing](#contributing)
- [License](#license)

<a name="aboutproject"></a>

## About the project

This project aims to provide an interactive and visually compelling representation of various quantum phenomena. The primary goal of this visualization project is to provide an accessible and intuitive way for users to engage with and comprehend complex quantum principles rather than to mimic the true characteristics of quantum particles.

<a name="getstarted"></a>

## Getting Started

### Dependencies

- git (https://git-scm.com/downloads)
- cmake (https://cmake.org/download)
- make (http://ftp.gnu.org/gnu/make)
- g++ (https://gcc.gnu.org) _you can use another compiler if you want_
- glfw (https://www.glfw.org/)
- glad (https://glad.dav1d.de/)
- glm (https://glm.g-truc.net/)
- imgui (https://github.com/ocornut/imgui)
- stb (https://github.com/nothings/stb/) _used stb_image for icon_

### Installation

```shell
> git clone https://github.com/ahmedkerouat/quantum-effects.git
> cd quantum-effects
> mkdir build
> cd build
> cmake ..
> make
> ./quantum-effects
```

<a name="structure"></a>

## Structure

The project consists of multiple header files, each providing specific functionalities. Here's an overview of the key components:

- **[quantumRepresentation.h](source/include/quantumRepresentation.h)** : The header file offers OpenGL functions for rendering Quantum Effects. These functions utilize shader programs, VAOs, sphere indices, time, and colors to achieve animated visual outcomes.

- **[sphere.h](source/include/sphere.h)**: This header file contains the Sphere class, which is used for rendering paritcles. It allows customization of the number of vertices and triangles that make up a sphere.

- **[grid.h](source/include/grid.h)** : This header file contains the Grid class, which is used for rendering the grid. It returns vertices and indices based width, height, rows, and columns.

- **[shader.h](source/include/shader.h)** : The shader.h file provides functions for loading and compiling OpenGL shaders and creating shader programs. For instance, it includes a utility function, loadShaderSource, to load shader source code from external files.

- **[shader_config.h](source/shaders/shader_config.h.in)**: This header includes the configuration data for fragment & vertex shaders.

- **[camera.h](source/include/camera.h)**: The Camera class defined in this header is responsible for controlling the view and perspective within the simulations. It manages user input for camera movements.

<a name="usage"></a>

## Usage

You can control various aspects of the simulations through the user interface.

- **Render Functions** : Choose between rendering a simple particle, or quantum representations of wave-particle duality, tunneling, entaglement, superposition, uncertainty, and spin.

- **Grid Controls** : Adjust grid visibility, color, rotation angle, size, and translation.

- **Function specific Controls** : Adjust the diverse parameters for each phenomenon including but not limited to colors and animation durations.

<a name="controls"></a>

## Controls

Within the simulations, you can control diverse camera parameters :

- **Right Mouse Button** : Controls the camera's rotation.

- **Left Mouse Button** : Controls the camera's position.

- **Scroll**: Zoom in and out of the simulation.

- **Space button** : Resets camera position to default _(you could also use the reset camera button in the menu)_.

_On the menu Ctrl + Lmb to change precisely a simulation parameter using the slider_

<a name="screenshots"></a>

## Screenshots

<div align="center">
    <img src="source\resources\Screenshot_1.png" alt="1">
    <img src="source\resources\Screenshot_2.png" alt="2">
    <img src="source\resources\Screenshot_3.png" alt="3">
</div>

<a name="contributing"></a>

## Contributing

Your contributions are greatly appreciated! If you have any suggestions to enhance the project, please feel free to create a pull request. Alternatively, you can open an issue to discuss your ideas. Don't forget to give a star ⭐️ – it's like a virtual high-five! Thank you for your valuable input!

<a name="license"></a>

## License

Project is licensed under the [MIT LICENSE](https://choosealicense.com/licenses/mit/)