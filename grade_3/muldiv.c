#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int min = 0;
int max = 10;

int get_factor()
{
  int i = rand() % (max + 1);
  while(i < min) i = (i + rand()) % (max + 1);
  return i;
}

int get_input()
{
  int i = 0;
  while(1) {
    char c;
    scanf("%c", &c);
    if ( c == '\n'){
      break;
    } 
    i = i*10 + c - '0';
  }
  return i;
}

int mul1()
{
  int m1 = get_factor();
  int m2 = get_factor();
  int r;
  printf("%d times %d = ?\t", m1, m2);
  r = get_input();
  return (r == (m1*m2));
}
int div1()
{
  int m1 = get_factor();
  int m2 = get_factor();
  int i;
  if(m1 == 0) m1 = 1;
  printf("%d divide %d = ?\t", m1*m2, m1);
  i = get_input();
  return ((m1*i) == (m1*m2));  
}

int mul2()
{
  int m1 = get_factor();
  int m2 = get_factor();
  int i;
  printf("%d times ? = %d\t", m1, m1*m2);
  i = get_input();
  return ((m1*i) == (m1*m2));
}
int div2()
{
  int m1 = get_factor();
  int m2 = get_factor();
  int i;
  while(m1 == 0) m1 = get_factor();
  while(m2 == 0) m2 = get_factor();
  printf("%d divide ? = %d\t", m1*m2, m1);
  i = get_input();
  return ((m1*i) == (m1*m2));  
}

int main()
{
  unsigned long begin_time;
  srand(time(NULL));

  printf("Please choose the minimum value for multiplication factor, the default is 0\n");
  min = get_input();
  printf("Please choose the maximum value for multiplication factor, the default is 10\n");
  max = get_input();
  if(max == 0 || max < min) max = min + 10;

  begin_time = time(0);

  int tot=0;
  int wrong=0;
  int pass = 0;
  while((time(0) - begin_time) <= 100) {
    char cmd[100];
    int ttt;
    int ret;
    int r = rand()%4; 

    if(r == 0) ret = mul1();
    else if(r == 1) ret = mul2();
    else if(r == 2) ret = div1();
    else ret = div2();
    tot++;
    if(!ret)
      wrong++;
    ttt = time(0) - begin_time;
    if((tot - wrong) >= 30 && (ttt <= 100)) {
      pass = 1;
      break;
    }
    printf("%lu:%d(%d)\t\t%s\n", ttt, tot, wrong, ret ?  "Correct :)" : "Wrong :(");

  }
  if (pass) printf("PASSED :) :) :)\n");
  else printf("FAILED :( :( :(\n");
  return 0;
}
