# Pipex

![C](https://img.shields.io/badge/language-C-blue.svg)

A program that simulates the functionality of shell pipes in C.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Challenges and Solutions](#challenges-and-solutions)
- [Contributing](#contributing)
- [License](#license)

## Overview

Pipex is a C program that mimics the behavior of shell pipes. It allows you to execute a series of commands, piping the output of each command to the input of the next, and ultimately writing the final output to a file. This project demonstrates advanced concepts in Unix programming, including process creation, inter-process communication, and file descriptor manipulation.

## Features

- Execute multiple shell commands in a pipe-like fashion
- Support for input and output file redirection
- Handling of environment variables for command execution
- Implementation of here_doc functionality (bonus feature)
- Robust error handling and memory management

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/g-garibotti/pipex.git
   ```
2. Navigate to the project directory:
   ```
   cd pipex
   ```
3. Compile the project:
   ```
   make
   ```

## Usage

The program can be used in two modes:

1. Standard mode:
   ```
   ./pipex file1 cmd1 cmd2 ... cmdn file2
   ```
   This is equivalent to: `< file1 cmd1 | cmd2 | ... | cmdn > file2` in shell.

2. Here_doc mode (bonus feature):
   ```
   ./pipex here_doc LIMITER cmd cmd1 file
   ```
   This is equivalent to: `cmd << LIMITER | cmd1 >> file` in shell.

Example:
```
./pipex infile "ls -l" "wc -l" outfile
```
This will execute `ls -l`, pipe its output to `wc -l`, and write the result to `outfile`.

## Project Structure

- `pipex.c`: Main program logic
- `init.c`: Initialization functions
- `execute.c`: Command execution and pipe handling
- `process.c`: Child process management
- `heredoc.c`: Here_doc functionality
- `cleanup.c`: Memory cleanup and error handling
- `utils.c`: Utility functions
- `pipex.h`: Header file with function prototypes and struct definitions

## Implementation Details

- **Process Management**: The program uses `fork()` to create child processes for each command.
- **Inter-Process Communication**: Pipes are created using the `pipe()` function to allow communication between processes.
- **File Descriptor Manipulation**: `dup2()` is used to redirect standard input and output for each command.
- **Command Execution**: `execve()` is used to execute shell commands with proper environment variables.
- **Error Handling**: Comprehensive error checking is implemented throughout the program, with appropriate error messages.

## Challenges and Solutions

1. **Challenge**: Handling multiple pipes for an arbitrary number of commands.
   **Solution**: Implemented a dynamic pipe creation system based on the number of commands.

2. **Challenge**: Implementing the here_doc functionality.
   **Solution**: Created a separate function to handle here_doc input, writing to a temporary file before execution.

3. **Challenge**: Proper cleanup of resources in case of errors.
   **Solution**: Implemented a robust cleanup function that frees all allocated memory and closes file descriptors.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

