// time.c
//
// A Lua module written in C to provide the time in subsecond resolution.
//

#include "lua.h"
#include "lauxlib.h"

#include <stdio.h>

#ifdef __APPLE__
#include <mach/mach.h>
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

static double now() {
#ifdef __APPLE__
  static int did_initialize = FALSE;
  static mach_timebase_info_data_t timebase_info;
  if (!did_initialize) {
    mach_timebase_info(&timebase_info);
    did_initialize = TRUE;
  }

  uint64_t abs_time = mach_absolute_time();
  return (double)abs_time * timebase_info.numer / timebase_info.denom / 1e9f;
#else
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  return (double)time.tv_sec + (double)time.tv_nsec / 1e9f;
#endif
}

int get_time(lua_State *L) {
  double t = now();
  lua_pushnumber(L, t);
  return 1;  // Number of values to return that are on the stack.
}

int luaopen_time(lua_State *L) {
  luaL_Reg fns[] = {
    {"get_time", get_time},
    {NULL, NULL}
  };
  luaL_newlib(L, fns);
  //luaL_register(L, "time", fns);
  return 1;  // Number of Lua-facing return values on the Lua stack in L.
}
