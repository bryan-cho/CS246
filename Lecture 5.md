# Lecture 5 - September 29, 2015

`egrep "^$1$" /usr/share/dict/words > /dev/null` <-- Takes the first argument when executing the shell script and looks through `words`

```bash
if [ $? -eq 0 ]; then
    echo Not a good password
else
    echo Maybe a good password
fi
```

There is a problem with this script. The script depends on the fact that there is exactly one argument. 

We can add the following as an error check:

This will check if there is one argument and if not it will show the usage by printing $0 which is the path of the file and "password" to indicate that a parameter is expected.

```bash
if [ ${#} -ne 1 ]; then
    echo "Usage: $0 password"
    exit 1
fi
```

## Looping

### While
* e.g.) Print #s from 1 to ${1}

```bash
x=1
while [ ${x} -le $1 ];
do
    echo ${x}
    x=$((x + 1))
done
``` 

We can modify the above by adding some checks:

```bash
usage () {
    echo "Usage: $0 limit" 1>&2
    echo " where limit is at least 1" 1>&2
    exit 1
}
```

This will check for the right number of arguments (1):

```bash
if [$# -ne 1]; then
    usage
fi
```

This will check if the argument is less than 1:

```bash
if [ $1 -lt 1 ]; then
    usage
fi
```

Note: this redirects the stderr and writes to the `err.log` file.
`./count 2> err.log` 

### For

* e.g.) Rename all .c files to .cc

We have the command: `mv file.c file.cc`
To do this with variable file names:

```bash
file=hello.c
mv ${file} ${file%c}cc
```

`%c` will remove the trailing suffix

`cc` will concatenate the new suffix

`#abc` removes 'abc' prefix - e.g.) abchello.c -> hello.c

**Loop Syntax**

```bash
for x in a b c d; <-- iterator = x, (a b c d) elements to iterate over
do echo $x; <-- do something
done
```

Note: we can change the delimiter. For instance, read a comma-separated CSV file

Going back to our example we can write our script to rename the files: 

```bash
for name in *.c; do
    mv ${name} ${name%c}cc
done
```

e.g.) How many times does word $1 appear in file $2?

```bash
x=0
for word in (cat "$2"); do <-- brackets are necessary
    if [ ${word} = "${1}" ]; then  (check for word)
        x=$((x + 1))
    fi
done
echo $x
```

Note: the " " around $2 and ${1} prevents a syntax error in the case someone inputs a word with spaces
Rule of thumb: put " " around any input from user

e.g.) Write a script that tells you when you get paid by using `cal` and obtaining the last Friday of the month

```bash
answer () {
    if [ $1 -eq 31 ]; then
        echo "on the ${1}st."
    else
        echo "on the ${1}th."
    fi
}

if [ ${#} -ne 0 ]; then
    echo "Usage: $0"
fi
answer cal | awk ' { print $6 } ' | egrep [0-9] | tail -n 1
```

A variation of this is adding the ability to specify a month

```bash
answer () {
    if [ $2 ]; then
        preamble=${2}
    else
        preamble="This month"
    fi
    if [ $1 -eq 31 ]; then
        echo "${preamble}'s payday is on the ${1}st."
    else
        echo "${preamble}'s payday is on the ${1}th."
    fi
}
answer `cal $1 $2 | awk '{print $6}' | grep "[0-9]" | tail -1` $1
```

## Testing

### Black Box Testing
* Writing tests before coding
* Functional testing - test features
  * positive/negative
  * edge cases - boundaries
  * corner cases - two boundaries meet
 
