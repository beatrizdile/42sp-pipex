<h1 align=center>
  42 Cursus
 </h1>
<h2 align=center>
  pipex
</h2>
<h2 align=center>

  ![pipex Logo](https://game.42sp.org.br/static/assets/achievements/pipexm.png)
</h2>

The **pipex** project aims to provide a program that emulates the behavior of the Unix shell command pipex, allowing users to redirect the output of one command as the input to another, similar to using pipes in the command line.

## Description

The project pipex challenges students to recreate the functionality of the Unix shell command pipex, emphasizing the mastery of low-level programming concepts and a deep understanding of Unix system calls. As part of the curriculum, this project is designed to enhance students' skills in handling file descriptors, processes, pipes, and command execution, while adhering to the 42's pedagogical philosophy of peer-to-peer learning and project-based education.

## Features

- Input redirection from a file
- Output redirection to a file
- Command chaining with pipes
- Error handling for invalid input

## Installation

Before proceeding with the installation, make sure you have the following dependencies:

- A Unix-like operating system (Linux, macOS, etc.)
- GCC compiler

Follow the steps below to test the project: 

1. Clone the repository to your local machine:

```bash
git clone git@github.com:beatrizdile/42sp-pipex.git
```

2. Compile the project:
```bash
make
```
3. To compile the project with bonus:
```bash
make bonus
```
4. Run the program with the following syntax:
```bash
./pipex infile cmd1 cmd2 outfile
```
- **infile**: Input file to read data from.
- **cmd1**: First command to execute.
- **cmd2**: Second command to execute.
- **outfile**: Output file to write results to.

### Examples
```bash
./pipex input.txt "grep keyword" "sort -r" output.txt
```

## Test Bonus
1. To test the first part of the bonus, use three or more commands:
```bash
./pipex input.txt "grep keyword" "sort -r" "wc -l" output.txt
```

2. To test the second part of the bonus, run:
```bash
./pipex here_doc "grep keyword" "sort -r" "wc -l" output.txt
```
In the second part of the bonus instead of using an already existing file as input, you use "here_doc" to write the input text yourself.

