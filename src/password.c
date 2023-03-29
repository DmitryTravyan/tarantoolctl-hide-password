#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int getch() {
  int ch;

  struct termios old_settings, new_settings;

  tcgetattr(STDIN_FILENO, &old_settings);

  new_settings = old_settings;
  new_settings.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);

  return ch;
}

int await_password(lua_State *L) {
  char password[255];
  int i = 0;
  int ch;

  printf("Enter password: ");
  while ((ch = getch()) != '\n') {
    if (ch == 127 || ch == 8) {
      if (i != 0) {
        i--;
        printf("\b \b");
      }
    } else {
      password[i++] = ch;
      printf("*");
    }
  }
  password[i] = '\0';

  const char *s = password;

  lua_pushstring(L, s);

  return 1;
}

int luaopen_password(lua_State *L) {
  lua_register(L, "await_password", await_password);
  return 0;
}
