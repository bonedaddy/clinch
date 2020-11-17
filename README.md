# clinch

`clinch` is a library for building CLI tools that support one or more commands. Support for multiple commands revolves around the use of a CLI flag called `--command` or `-c` for short. Using this you supply the same of the command to run. It is built around argtable3 as the flag handling library, and include a few pre-defined default argtable values (version, file, output) to use as building blocks and to showcase example usage.


Example output:


```
<@clinch/build>-<⎇ main>-<±>-> ./cli
Usage: ./cli [--some-string=<str>] [--help] [--version] [--file=<file>]... [--output=<file>] [-c <command>]
 --some-string=<str>       input a random string
 --help                    displays help menu
 --version                 0.0.1
 --file=<file>             file(s) to load data from max of 10
 --output=<file>           file to output data too
 -c, --command=<command>   command to run
<@clinch/build>-<⎇ main>-<±>-> ./cli --command=some-str
some-str flag empty
[info] command executed successfully

<@clinch/build>-<⎇ main>-<±>-> ./cli --some-str=hello --command=some-str
some-str flag value: hello
[info] command executed successfully
```

# dependencies

* pthread
* ulog
* argtable3