A Sun For the Moon - A Zero-Overhead Lua Abstraction using C++
==============================================================

Lua Rocks
---------
- What is it (scripting language)
- Who uses it (everybody - associated with game developers, but seriously, everybody, even server managers)
- Why is it used (MIT licensed, proven in industry, deployed everywhere, very few competitors (ChaiScript?))

Lua Also Sucks
--------------
- Specifically, the C API (stack-based, low-level)
- Multiple different ways to do the same thing (with different performance implications)
- One optimal, right way to do things (but nobody will tell you exactly how)
- Breaking API changes between versions ("rapid" deprecation, hard removal, function signature changes)
- Hard-line LuaJIT (Stuck at Lua 5.1 -- over a decade old in terms of API)

"But People Have Wrapped Lua Before"
--------------------------------------------------
- And it was done poorly (Section 3 of https://github.com/ThePhD/lua-bench/blob/master/paper/A%20Sun%20for%20the%20Moon.pdf) (Summarize other frameworks, MAYBE, if time permits)
- With varying levels of performance (Selene most popular, WORST performance, aaaahhh!)
- Others are REALLY great in some categories (OOLua/luacppinterface with function calls)
- Others fail REALLY hard in some categories (Selene with table abstraction, etc.)

sol2 - Doing Lua Justice
------------------------------
- Let's do a Binding to C++, the right way
- A History (Oncologist with C++ kink helping out a Professor - Rapptz, "Sol v1.0" | Lua Enthusiast and graphics/game developer Bartek,  "Lundi")
- What are the primitives? (Table, Function, Userdata)
- What is the lua way to support these primitives? (reference, stack_reference)
- What is the glue between these primitives and their functionality? (stack::(probe_)get_field, stack::set_field, stack::push, stack::get, stack::check, stack::check_get)

Making it Fast
------------------
- ... By being lazy (lazy evaluation of operator[] = LOOOADS-A-SPEEEED)
- By encoding information into types and operations (global table -> sol::global_table -> trigger optmizations all the way in "stack")
- Like all good systems, BATCHING (Get a table once, pull EVERYTHING YOU CAN FROM THE TABLE, then pop it off the stack)
- No different from Mike Acton's style of C - we just put the information in types rather than forcing the user to type it out in copy-paste style of programming
