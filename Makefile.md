# Makefile

Solve the problem of having to worry about compilation each time you make a change to each module.

```Makefile
<target>: [ <dependency > ]*
   [ <TAB> <command> <endl> ]+
```

The above will run the commands listed for any targets that have dependencies that have been updated.

```Makefile
.PHONY: <target>`
```

`.PHONY` are used to tell Make that the target is not associated with files.

An example is `clean`

```Makefile
.PHONY: clean
clean:
  rm -rf *.o
```

You can now run `make clean` even if you have a file named clean.

We can use variables instead of listing all of our commands separately.

```Makefile
CXX = g++
CXXFLAGS = -Wall (warn all)
OBJECTS = main.o book.o ...
EXEC = main

${EXEC}: ${OBJECTS}
    ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: <dependencies>

book.o <dependencies>

...

.PHONY: clean

clean: 
    rm ${OBJECTS} ${EXEC}
```

Doing this will go through the OBJECTS and abstracts away the commands that were entered manually before.

We can take this one step further:

```Makefile
CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = main
OBJECTS = main.o book.o textbook.o comic.o ...
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
    ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
    rm ${OBJECTS} ${EXEC} ${DEPENDS}
```

* Now all we have to do is change the list of OBJECTS whenever we add more files to the project
* `-include` will look for the files in DEPENDS and include them in the Makefile (these are other Makefiles)
    * Notice the addition of -MMD, which will auto-create the list of dependencies that we had to manually enter before
        * e.g.) main.o: <dependencies>
    * These will be created as `.d` files and then Make will include them much like a copy and paste
* The line `${OBJECTS:.o=.d}` takes the value of `${OBJECTS}` and replaces `.o` with `.d`
* The `-` infront of `-include` is needed since `.d` files may not exist for newly created files in the project. The hyphen tells Make to skip the warning and move on.
* If the `.d` file doesn't exist, then neither will the `.o` so the command will be executed and both will be created. 

**PROTIP**:

If getting an error: `Makefile:_: *** missing separator. Stop`

Use `Ctrl-V, Ctrl-I` in VIM while in insert mode to insert a real tab character.

(Just in case your VIM isn't configured to use tabs)
