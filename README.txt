Keegan Donley
CS 315
Project 4

My program works very well to traverse directory structures.
I've outline the behavior of any caveats or important information below.

Running my executable will result in a sort of emulator, which allows for using commands
just as you would in a normal filesystem.
The shell opens three times, once with the main directory, once again with
a duplicate directory to ensure they are not linked in any way, and once more with
a duplicated portion of a directory. Typing `logout` exits each consecutive shell.

Solution can be built using the command `make`. `make run` runs the program with the input file long.json

# cd() and cd(<string>) functions
-   cd behaves just like a normal filesystem
        `cd` and `cd ~` return to the root directory
        `cd <directory>` changes to the child directory with the indicated name
        `cd <path>` changes to the child directories in order following the path
        `cd ..` returns to the parent. If at the root node, pwd remains the sample
        (Very rarely (less than once every 30 or so times), `cd ..` causes an error when in the root dir)
        `cd .` stays in the current directory

# ls() and ls(<string>) functions
-   ls behaves just like a normal filesystem
        Just like cd, ls uses relative paths and follows them in order, listing the file name and type

# move() function
-   Move can be accessed using either mv or move from within the demo
    CAVEAT: On some occasions, the file that was moved to another directory doesn't disappear when using `ls`
            until the directory has been changed to something else and then returned back. This only happens for the first
            move command of a session, and after that subsequent move commands work properly. Otherwise,
            move works well and takes special care to maintain proper paths.

JSON parsing
-   The program is able to parse a proper JSON file, however in some cases it doesn't catch all errors
    in the syntax gracefully. However, for major structural errors, the application will exit with a
    useful message

Testing hasSubstructure
-   This is one of the hardest for me to test. I have included a file called sub.json that is read in
    and contains a substructure of my file long.json, which I used for the majority of my tests. Running
    the program with short.json should lead to the hasSubstructure function returning true, however with
    other input files that isn't the case.

Testing areTheSame()
-   My test of this in main() should be true then false when using long.json, and should be true then true
    when using short.json

    This function and hasSubstructure both do not take into account that fact that files can be in different orders -
    All children must be in the same order in both structures for them to return true. It was unclear whether this
    is the proper behavior or not, but it is one caveat to keep in mind.


NOTES
*   In some cases I was unsure as to the exact workings of a function and how the results
    should be formatted. In those situations, I attempted to follow the behavior of a real
    UNIX filesystem as closely as I could.
