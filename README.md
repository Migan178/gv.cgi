<!-- SPDX-License-Identifier: GPL-2.0-only -->
<!-- Copyright 2026 Siwoo Jeon -->
<!-- i know, i know README doesn't need a SPDX identifier, but i "just" insert it XD!! -->

# gv.cgi (git viewer cgi)

# I made this to learn C, so it may contain some bugs like buffer overflows, etc. (but i use ASan to catch the bugs btw XD!!) anyway, YOU SHOULD CONSIDER USING cgit INSTEAD OF THIS IN PRODUCTION.

- It is licensed under "GPL-2.0-only"! ("NOT" GPL-2.0-or-later!)
- It is a git viewer (NOT <!-- logic gate(?) -->editor).
- This depends on libgit2 with dynamic linking (i know, i know and know i can use another license in this project 'cause the lib uses GPL-2.0-with-linking-exception, but I "just" wanna use GPL-2.0-only (but "I ain't a fan of FSF/RMS". so I ain't use gcc)).
- It is tested on Silicon Mac (umm... i think it should work on Windows(with MSYS2, "NOT" msvc) and Linux("NOT" GNU/Linux) btw ¯\\\_(ツ)_/¯ i hope so)

## Build

- It uses Make (i ain't know how to fight with CMake).
- It uses **clang** (but you can use gcc or zig cc(gcc and zig cc not tested), however, you "SHOULD NOT" use msvc(it uses POSIX API("NOT" Win32 API)). instead, consider using MSYS2(MSYS2 also not tested)).

```sh
# if you wanna kill the bugs, use DEBUG=1 make
make
```
