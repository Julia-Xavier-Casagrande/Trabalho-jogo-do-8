#include <stdio.h>
int board[3][3], HX, HY, moves;
void end_board()
{
  int x,y,val=1;

  for (y=0; y<3; y++)
  {
    for (x=0; x<3; x++)
      board[x][y] = val++;
  }

  board[2][2] = 0;
  HX=2;
  HY=2;
}
int swap_pos(int x, int y)
{
  int temp;

  if ((x==HX) && (y==HY))
    return 0;

  if ((x>2) || (x<0) || (y>2) || (y<0))
    return 0; 

  if (abs(HX-x)+abs(HY-y) > 1)
    return 0;

  temp = board[HX][HY];
  board[HX][HY] = board[x][y];
  board[x][y] = temp;

  HX=x;
  HY=y;

  return 1;
}
void shuffle_board()
{
  int x,y,r,rounds=50;
  int flag;

  srand(time(NULL));

  for (r=1; r<=rounds; r++)
  {
    flag=0;
    while (flag!=1)
    {
      flag = 1;
      x=rand()%3 - 1;
      y=rand()%3 - 1;

      flag = swap_pos(HX+x,HY+y);
    }
  }
}
void print_board()
{
  int x,y;

  for (y=0; y<3; y++)
  {
    for (x=0; x<3; x++)
    {
      if (board[x][y] == 0)
        printf("  ");
      else
        printf("%d ",board[x][y]);
    }
    printf("\n");
  }
}
void start_board()
{
  end_board();
  shuffle_board();
}
void player_turn()
{
  int num, flag=0;

  while (flag!=1)
  {
    flag=1;
    printf("Escolha um numero para mover: ");
    scanf("%d",&num);
    if ((num < 1) || (num > 8))
    {
      flag=0;
      printf("O numero deve ser entre 1 e 8!\n");
    }
    if (move_square(num)!=1)
    {
      flag=0;
      printf("O numero %d nao pode ser movido!\n",num);
     }
  }
}
void get_num_coords(int num, int *xx, int *yy)
{
  int x,y;

  for (y=0; y<3; y++)
  {
    for (x=0; x<3; x++)
    {
      if (board[x][y] == num)
      {
        *xx=x;
        *yy=y;
      }
    }
  }
}
int move_square(int num)
{
  int x,y;

  get_num_coords(num, &x, &y);

  if (swap_pos(x,y)!=1)
    return 0;

  return 1;
}
int check_win()
{
  int x,y,num=1;

  for (y=0; y<3; y++)
  {
    for (x=0; x<3; x++)
    {
      if (board[x][y] != (num++ % 9))
        return 0;
    }
  }

  return 1;
}
void game()
{
  moves=0;
  start_board();
  print_board();

  while (check_win()!=1)
  {
    player_turn();
    moves++;
    print_board();
  }

  printf("Jogo terminado em %d jogadas.\n",moves);
}
void flush_buffer(){
    int l;
    while((l = getchar()) != '\n' && l != EOF);
}
main()
{
    char C;
    printf("Jogo do 8! \n");
    printf("MENU\n");
    do
    { 
    printf("Deseja jogar? S/N \n");
    scanf("%c", &C);
    flush_buffer();
    switch(C)
    {
        case 'S': game();
        break;
        case 's': game();
        break;
        case 'N': return 0;
        break;
        case 'n': return 0;
        break;
        default: printf("Respota inválida\n");
    }
    }
    while ((C != 'S')||(C != 'N'));
}