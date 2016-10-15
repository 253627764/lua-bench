The Design of Lua - 9:30 AM
Robert Leuraschlimy


* Portability
	- Runs everywhere
	- RUNS. EVERYWHERE.
	- Only backed by ANSI C
* Simplicity
	- Officially less than 100 pages
* Small Size
	- Lua is tiny
	- Fits in a lot of places
* Scripting
	- Used internally in much larger products (Video games, robotics)
	- Easy to adapt (no forced static typing)

* Impact from the goals
	- CLOSURES: powerful feature (anonymous, immediately executable functions that capture variables)
	- TABLES: tables for everything and are simple
		+ Great for simplicity and ease of use and understanding ("just works")
		+ SUCKS for different data structures / emulating different data structures
	- Small size: becomes a slight problem when you want to grab library that doesn't exist (thrust into the ecosystem)

* Exception handling
	- simple semantics
	- no extra syntax (pcall??)
	- verbose

* Iterators
	- functions as first class stuff: function iterators and just returns if its done or not

* Modules
	- needs very new (almost no new) features, and easy to inferface with
	- flexible (piggybacks off of table)
	- Fails because it's 'not as good as real namespaces / modules'
	- too dynamic which 'require "math"' math.dll did it pick up, static analysis?)

Delegation (__index / __newindex)
	- flexible, easy to interface with othe rlanguages


"Performances is comparative"
"I regret adding '...' varargs into the language"
