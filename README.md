# Vulkan Tutorial Project

This repository contains a series of examples from the [Vulkan Tutorial](https://vulkan-tutorial.com/).



## Requirements

To use this repository, you will need:

- A C++17 compatible compiler (e.g., `g++`)
- Vulkan SDK
- GLFW library



## Building and Running Examples

This project uses a Makefile to compile and run the Vulkan examples. Below is how to use it:



- **all**: Builds all examples available in the `src` directory.

  ```sh
  make
  ```

- **ex**: Compiles and runs a specific example file. Replace `filename` with the name of the desired example (without the `.cpp` extension).

  ```sh
  make ex filename
  ```

  Example:

  ```sh
  make ex test
  ```

- **run**: Runs a specific program directly. Replace `program` with the desired program name.

  ```sh
  make run-program
  ```

- **clean**: Removes all compiled binaries and object files, allowing for a clean rebuild of the entire project.

  ```sh
  make clean
  ```

- **rebuild**: Cleans the project and then builds all examples from scratch.

  ```sh
  make rebuild
  ```

