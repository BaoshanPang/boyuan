#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct _win_border_struct {
  chtype ls, rs, ts, bs, 
    tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

  int startx, starty;
  int height, width;
  WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int judge(char ttt[3][3])
{
  if(ttt[0][0] != 0 && ttt[0][0] == ttt[0][1] && ttt[0][0] == ttt[0][2]) return 1;
  if(ttt[1][0] != 0 && ttt[1][0] == ttt[1][1] && ttt[1][0] == ttt[1][2]) return 1;
  if(ttt[2][0] != 0 && ttt[2][0] == ttt[2][1] && ttt[2][0] == ttt[2][2]) return 1;

  if(ttt[0][0] != 0 && ttt[0][0] == ttt[1][0] && ttt[0][0] == ttt[2][0]) return 1;
  if(ttt[0][1] != 0 && ttt[0][1] == ttt[1][1] && ttt[0][1] == ttt[2][1]) return 1;
  if(ttt[0][2] != 0 && ttt[0][2] == ttt[1][2] && ttt[0][2] == ttt[2][2]) return 1;

  if(ttt[0][0] != 0 && ttt[0][0] == ttt[1][1] && ttt[0][0] == ttt[2][2]) return 1;
  if(ttt[2][0] != 0 && ttt[2][0] == ttt[1][1] && ttt[2][0] == ttt[0][2]) return 1;

  if(ttt[0][0] != 0 && ttt[1][0] != 0 && ttt[2][0] != 0 
     && ttt[0][1] != 0 && ttt[1][1] != 0 && ttt[2][1] != 0
     && ttt[0][2] != 0 && ttt[1][2] != 0 && ttt[2][2] != 0)
    return 2;

  return 0;
}

int main(int argc, char *argv[])
{
  WIN win;
  WIN win0;
  int ch;
  int turn = 0;
  char str[100];
  char ttt[3][3] = { 0 };

  initscr();/* Start curses mode */
  start_color();/* Start the color functionality */
  cbreak();/* Line buffering disabled, Pass on
	    * everty thing to me */
  keypad(stdscr, TRUE);/* I need that nifty F1 */
  noecho();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  /* Initialize the window parameters */
  init_win_params(&win);
  print_win_params(&win);

  attron(COLOR_PAIR(1));
  refresh();
  /*  attroff(COLOR_PAIR(1));*/
  win0 = win;

  mvaddch(win.starty - 1, win.startx+5, 'A');
  mvaddch(win.starty + 1, win.startx-2, '1');
  create_box(&win, TRUE);
  win.startx = win.startx + win.width;
  mvaddch(win.starty - 1, win.startx+5, 'B');
  create_box(&win, TRUE);
  win.startx = win.startx + win.width;
  mvaddch(win.starty - 1, win.startx+5, 'C');
  create_box(&win, TRUE);

  win = win0;
  win.starty = win.starty + win.height;
  mvaddch(win.starty + 1, win.startx-2, '2');
  create_box(&win, TRUE);
  win.starty = win.starty + win.height;
  mvaddch(win.starty + 1, win.startx-2, '3');
  create_box(&win, TRUE);

  win = win0;
  win.startx = win.startx + win.width;
  win.starty = win.starty + win.height;
  create_box(&win, TRUE);
  win.starty = win.starty + win.height;
  create_box(&win, TRUE);

  win = win0;
  win.startx = win.startx + win.width;
  win.startx = win.startx + win.width;
  win.starty = win.starty + win.height;
  create_box(&win, TRUE);
  win.starty = win.starty + win.height;
  create_box(&win, TRUE);


  echo();
  do{
    int won;
    int row, col;

    if(turn) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }
    mvaddstr(win.starty+win.height+3, 0, "\t\t");
    mvaddstr(win.starty+win.height+3, 0, turn == 0 ? "O:" : "X:");
    ch = getnstr(str, 100);
    if(strlen(str) != 2) {
      printw("Invalid move\n");
      continue;
    }
    if((str[0] >= '1' && str[0] <= '3') 
       && ((str[1] >= 'a' && str[1] <= 'c') 
	   || (str[1] >= 'A' && str[1] <= 'C'))){
      row = str[0] - '1';
      col = str[1] - (str[1] >= 'a' ? 'a' : 'A');
    } else if ((str[1] >= '1' && str[1] <= '3') 
	       && ((str[0] >= 'a' && str[0] <= 'c') 
		   || (str[0] >= 'A' && str[0] <= 'C'))){
      row = str[1] - '1';
      col = str[0] - (str[0] >= 'a' ? 'a' : 'A');
    } else {
      mvaddstr(win.starty+win.height+4, 0, "Invalid move");
      continue;
    }
    if(ttt[row][col] != 0) {
      mvaddstr(win.starty+win.height+4, 0, str);
      continue;      
    } else {
      ttt[row][col] = (turn == 0 ? 'O' : 'X');
    }
    if(turn) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }
    mvaddch(win0.starty + win0.height*row+2, win0.startx + win0.width*col+5, ttt[row][col]);
    attron(COLOR_PAIR(1));
    mvaddstr(win.starty+win.height+4, 0, "\t\t");
    won = judge(ttt);
    if(won == 1) {
      mvaddstr(win.starty+win.height+4, 0, "The Winner is ");
      if(turn) {
	attron(COLOR_PAIR(2));
      } else {
	attron(COLOR_PAIR(3));
      }
      printw(turn == 0 ? "O" : "X");
      attron(COLOR_PAIR(1));
      printw("\nPrint any key to exit");
      getch();
      break;
    } else if (won == 2) {
      mvaddstr(win.starty+win.height+4, 0, "It's even");
      printw("\nPrint any key to exit");
      getch();
      break;
    }
    turn = (turn == 0 ? 1 : 0);
  } while(1);
  endwin();/* End curses mode  */
  return 0;
}
void init_win_params(WIN *p_win)
{
  p_win->height = 3;
  p_win->width = 10;
  p_win->starty = 3;
  p_win->startx = 3;

  p_win->border.ls = '|';
  p_win->border.rs = '|';
  p_win->border.ts = '-';
  p_win->border.bs = '-';
  p_win->border.tl = '-';
  p_win->border.tr = '-';
  p_win->border.bl = '-';
  p_win->border.br = '-';

}
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
  mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
	   p_win->width, p_win->height);
  refresh();
#endif
}
void create_box(WIN *p_win, bool flag)
{int i, j;
  int x, y, w, h;

  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if(flag == TRUE)
    {mvaddch(y, x, p_win->border.tl);
      mvaddch(y, x + w, p_win->border.tr);
      mvaddch(y + h, x, p_win->border.bl);
      mvaddch(y + h, x + w, p_win->border.br);
      mvhline(y, x + 1, p_win->border.ts, w - 1);
      mvhline(y + h, x + 1, p_win->border.bs, w - 1);
      mvvline(y + 1, x, p_win->border.ls, h - 1);
      mvvline(y + 1, x + w, p_win->border.rs, h - 1);

    }
  else
    for(j = y; j <= y + h; ++j)
      for(i = x; i <= x + w; ++i)
	mvaddch(j, i, ' ');
  
  refresh();

}
