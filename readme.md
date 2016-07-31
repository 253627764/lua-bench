lua bench
=========

This is the repository for benchmarking Lua binding libraries. The results can be found in the `lua - results` folder, and are hosted here:

http://sol2.readthedocs.io/en/latest/benchmarks.html

The libraries found here are the ones I was told about VIA the Lua Mailing List, on reddit, by colleagues, and other places.

The code here is mostly made to work for VC++ and Visual Studio. I would imagine some of the other frameworks don't compile cleanly without some form of additional work for both g++: it will be a while before I can appropriately clean up the code.

You can generate the results by building the VC++ project in Release Mode, x64. To avoid overhead, please execute the final executable using the command line: no additional arguments are required.

You can generate graphs based on what's in the `lua - results` folder by executing:

````
python lua crunch.py
````

in the top level directory of the project. I will probably at the ability to change what directories these things point at in the near future to make things handle better... but for now, it works.