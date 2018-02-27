# util_bin

This is a collection of command-line utilities originally written for Windows' Command Prompt, but many of the source files included here are portable to UNIX-like (i.e., macOS, BSD, and Linux distros), although some small changes will likely need to be made.

These utilities serve a number of varied purposes, mostly related to mathematics. Currently, this repository includes, but is not limited to, the following:

* A prime factorization utility that works for all possible values of 64-bit integers.
* A random number generation utility that prints a specified number of randomly-generated integers to a file.
* A primality test utility that also finds the next largest prime.
* ...and much more!

## Installation

Installation for a specific utility(ies) takes a few simple steps:

1. Clone this repository.
2. Use your compiler of choice to build the utility(ies) you wish to use.
3. Move the compiled executables to the directory you wish to access them from.

## Usage

Using one of the utilities is as simple as calling it from the terminal/cmd.

```
> ./utiilty [args]
```

The user can also add the utility(ies) to their PATH to have global access to them.

```
> utility [args]
```

Please consult the source code for additional details on how to use each utility.

## Contributing

### Bug Reports and Utility/Feature Requests

Please feel free to alert me of any potential bugs or vulnerabilities you may encounter when using this code by using the [issue tracker](https://github.com/MrM21632/util_bin/issues).

If you have any suggestions for adding functionality to a utility, or if you wish to request a utility for this repo, please feel free to message me about this as well.

### Development

Pull requests are welcome. If you are interested, please feel free to browse the TODO file included with this repo for a list of what needs to be completed.