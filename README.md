# C pipe-line bundle
This is a bundle of minimalistic pipe programs written in C.
Each program accepts stdin and modifies it sligtly.
Default stream for each program is stdout.
Everything else about compilation is written in Makefile, so just run
```
make
```
and read the output.
Beaware that Makefile will try to sudo gcc every source file, so either call 'compile-all' option
```
make compile-all
```
and then sudo cp it by yourself whenever you want, or call 'compile-and-send' options and it will move everything in one go to /usr/local/bin foldef.
```
make compile-and-send
```

# Usage
You can get the sizes of directories in your current directory by using some of these programs and xargs:
```
ls -a | getdirs | concat "" / | pex ./ ../ | xargs du --max-depth=0 | sort -n
```
This line will list all files (ls -a), filter only directories (getdirs), add '/' to the end of all of them (concat "" /), filter out current directory and parrent directory (pex ./ ../) (that's why we call 'concat "" /' earlier, not to filter out hidden folders by passing '.' and '..' as a arguments for pex), passing it all to du via xargs and then sort them out in ascending order)
Note that du will send you size in Kb, not bytes.

## Sinopsis for each program
### add
pushes every arg from i=1 to the end of the stream
### concat \[S\] \[E\]
add string S to the start of each line and E to the end of each line  
if you need to push only to the end call it with S = "". E.g.
```
cat file | concat "" ::endl;
```
will bring string "::endl;" to the end of each line into the stream.
### lines \[e/o\]
it will print every odd line (0, 2, 4, ...) or every even line (1, 3, 5, ...) from stdin  
Default parameter is o. It accepts only "e" or "o" as first argument after the name, anything else is ignored
### numerate
numerates every line in stdin with pattern "n:\<LINE\>". Numerating start from 0.
### pex
Piped EXclued or "anti-grep". It excludes every line from stdin if it has at least one of the arguments in line.
### inverse
Inverses every line in stream
### prm
removes every file from string in current directory by calling "rm" program
### pjoin
concats every line from file or stdin into one long line. Cap is 100Kb for line.
**Options**:
 - -f : File.      Program will read from next argv as a regular file instead of stdin.
 - -c : Connector. First char of next argv will be used as a connection char instead of ' ' as a default.
### calculate
performs atoi() for every line and prints the sum of every function's return
### statfiles \[-\[s/a/h\]\]
get size of files that are in stdin and in args (without the '-' prefix) and prints the info in stdout.  
**Options**:  
 - -s : Silent.    Program will not print the names of files before the size itself  
 - -a : All only.  Programm will print only the sum of all the sizes.  
 - -h : Human.     Transforms every size into human readable form. F.e. 9012 will become 8.80Kb and etc.  

**Note:**  
program will not try to find files. Don't hope that  
```
ls ./folder | statfiles
```
will work. Either do  
```
cd ./folder && ls | statfile
```
or use "concat" program and you can do such a thing:  
```
ls ./folder | concat ./folder | statfiles
```
I recommend you to put  
```
ls $1 | concat $1
```
in a function like "lsc" so you will type only  
```
lsc ./folder | statfiles
```
### align \<C\>
aligns every string on the max occurance of the \<C\> char. You can enter string, it will just use only first char.  
This means that
```
cat file | align :
```
and
```
cat file | align :test
```
are the same.
### mkstream
prints every argv as a line. Don't pass any stdin so the only use is to MaKe STREAM of lines
### cutlines
prints the input but every occurance of first char argv[1] will be printed as '\n'
### pset
pritns set of characters for every line in stdin
### getdirs
passes to stdout only directories. Every line should represent absolute or relative path
You can create a bash function using also **concat** in this bundle and it will be like that
```
find_dirs() {
    ls $0 | concat $0 | getdirs
}
```
now if you enter it in ~/.bash\_functions and type
```
source ~/.bash_functions
```
and then
```
find_dirs ~/
```
you will see every directory in your home directory on the terminal screen. Nice!
### normalize
parses every stdin line for long int and sees it as number of bytes. Then it just normalize number of bytes into KiloBytes, MegaBytes and etc.
Examples:
```
echo "10240" | normalize
```
will return **10.00Kb**
