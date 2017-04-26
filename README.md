# File Structure Simulator

C++ program written for a project in my data structures class.

Recursively parses a JSON file and turns it into a structure of directories and files that can be navigated as if it were a unix filesystem.

### Runnng
`make run` builds and runs with the file long.json as the input

To use your own JSON, use `make` and then run using `./de.x <filename>`

## Functions
- cd
- cd <dirname>
- ls <dirname>
- mv <from> <destination>
- pwd
- depth (gets number of directories from root
- find <path>
