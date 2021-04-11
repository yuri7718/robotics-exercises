# Largest Pathway

Example

```bash
make
./largestPath labyrinth1.txt
./largestPath labyrinth2.txt
./largestPath otherLabyrinthSchema.txt
```

If the input file is named "example.txt", then the program generates a solution file named "example_soln.txt".

As the program needs to overwrite the holes (.) with the order in which the hole has been visited, the program only supports a pathway of a maximum length of 10 so that the holes could be overwritten with digits from 0 to 9.

Currently, if the program tries to write 10 to a certain place in the labyrinth schema, then 10 becomes the ascii character converted from decimal 58 as the ascii caracter '0' is decimal 48.