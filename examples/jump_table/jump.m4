divert(`-1')
# forloop(var, from, to, stmt)
define(`forloop',
  `pushdef(`$1', `$2')_forloop(`$1', `$2', `$3', `$4')popdef(`$1')')
define(`_forloop',
  `$4`'ifelse($1, `$3', ,
    `define(`$1', incr($1))_forloop(`$1', `$2', `$3', `$4')')')
divert`'dnl

#include <stdio.h>
#include <stdlib.h>


void perform_menu_action(int menu_choice) {
	int to_print = 0;
	switch (menu_choice) {
forloop(`i', `1', `45', `dnl
		case i: {
			to_print = i;
			break;
		}
')dnl
	}
	printf("to_print: %d\n", to_print);
	return;
}

int main() {
  int user_menu_choice = 0;
  /*
   * We would get the input from the user
   * in a real application.
   */
  perform_menu_action(2);
  return 0;
}
