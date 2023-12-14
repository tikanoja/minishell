# minishell - A simple Bash-like Unix shell

*This project was developed as part of the Ecole 42 curriculum in collaboration with [Joonatan Aurasmaa](https://github.com/Jaurasma).*

## Overview

`minishell` is a simple Bash-like shell written in C. It supports command execution, environment variables, basic built-in commands, and more.

<img src="imgs/irssi.png" width="80%" align="center">

## Description

The `minishell` project is a complex programming challenge about operating system principles and logic. Some of the core components:

- **Parsing**: Handling and interpreting the user input.
- **Signals**: Manipulating the signals to function properly.
- **Environmental Variables**: Support for managing and using environment variables.
- **Redirection and Pipes**: Basic redirection, pipe and heredoc capabilities to work in conjuction with the commands.
- **Built-in Commands**: Includes essential built-in commands like cd, echo, pwd, export, unset, and exit.
- **Command Execution**: Execute commands and programs available in the system.
- **Error Handling**: The shell shouldn't crash no matter what. Be the problem in the user or system.

## Learning

### Soft Skills

Project planning was one of the main lessons while working on `minishell`. It was the largest project we had worked on so far, and we found ourself having regular meetings to plan the structure of the program and to update each other on the changes made. The project called for great communication and teamwork to succeed!

### Technical Skills

Many of the concepts were already familiar to us, but `minishell` put our skills to the test to make everything as robust and foolproof as possible. Some of the technical challenges included:

- **Parsing techniques**
- **Understanding system calls and processes**
- **File I/O and Redirection**
- **Modularity and code organization**
- **Debugging and Testing**
- **Version control with Git**

## Installation

```bash
git clone https://github.com/tikanoja/minishell minishell && cd minishell && make
```

## Usage

In the installation location:

```bash
./minishell
```
