# Writing Lua modules in C

This repo contains a small demo file, `time.c` which can be compiled on Mac OS X
into the shared object file `time.so` and used as a module in Lua. If you're
working on a different platform, the notes
[here](http://lua-users.org/wiki/BuildingModules) explain how to compile in many
different settings.

## Compiling and using

Run

    $ make

in the shell to build `time.so`. Then from Lua, use code like this:

    local time = require 'time'
    local start_time = time.get_time()
    -- Do some stuff you want to time.
    local end_time = time.get_time()
    print((end_time - start_time) .. ' seconds have passed)

## Video

This small repo was built during a video tutorial of the basics of Lua's C
interface. That video is available
[here](https://www.youtube.com/watch?v=UiZ051A22h8).

## Notes on the time confusion in the video

If you watch the video, at one point I'm confused about why the return value of
`time.get_time()` doesn't match the return value of `os.time()`. This is because
`os.time()` gives the number of seconds passed since the
beginning of [the epoch](https://en.wikipedia.org/wiki/Unix_time),
while `time.get_time()` returns the number of seconds elapsed from an
*unspecified* initial point.

Why would you care about an unspecified initial time point?
This is useful for measuring time *intervals*; disassociating a
high-resolution clock from the real-world time can get around tricky cases such
as a user changing the system time.
