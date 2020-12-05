# Advent of Code 2020

All challenges done in C

All solutions tested on Ubuntu 20.04 but should run most systems

Solutions are for the 2020 Advent of Code: https://adventofcode.com/

## Structure of Repo

All directories have a C file in format adventX.c and an input (in.txt).

Directory numbers correspond to a challenge number, e.g. 5 is Day 2, Part 1

## Build Solutions

To build a solution using gcc run ``gcc challenge.c -o challenge``, then run using ``./challenge args``

## Debug a Solution

If you make any changes and want to debug your own solution, you can do this with gdb:
1. Build the solution with debug symbols ``gcc -g challenge.c -o challenge``
2. Run solution in gdb ``gdb --args ./challenge args``
3. Run the program within gdb ``run`` and watch for any issues, breakpoints can also be set
