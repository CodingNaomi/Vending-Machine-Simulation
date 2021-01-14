#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MULTIPLE 5
#define LOWPRICE 30
#define HIGHPRICE 105
#define MAX 2
#define DIME 10
#define NICK 5
#define QUART 25
#define ZERO 0
#define ONE 1


/*FUNCTION PROTOTYPES*/

int moneyrec(int);
int moneydue(int, int);
int dimeref(int, int);
int nickref(int, int);
int eretdime(int);
int eretnick(int);
void change(int, int, int);
void endorbreak(int);
void runmachine(int);


/*MAIN PROGRAM*/

int
main(int argc, char *argv[])
{

  /*declaration of variables*/
  char coin_type;
  int coin, dime_ret, nick_ret;
  int price;
  int amt_rec, amt_due, amt_ret;


  /*arguments passed to the program*/

  if(argc < MAX)
  {
    printf("Please specify selling price as a command line argument.\n");
    printf("Usage: pop [price]\n");
  }

  if(argc==MAX)
  {
    price = atoi(argv[1]);

      if(price < LOWPRICE || price > HIGHPRICE)
      {
        printf("Price must be from %d to %d cents inclusive.\n", LOWPRICE, HIGHPRICE);
      }
      else if(price % MULTIPLE != ZERO)
      {
        printf("Price must be a multiple of %d.\n", MULTIPLE);
      }
      else
      {
        runmachine(price);/*this function puts machine in service once the price is set*/
      }
   }
return(0);
}
/*end of main program*/




/*FUNCTIONS*/


void
runmachine(int x)
{
  
  /*declaration of variables in runmachine function*/
  char coin_type;
  int coin, dime_ret, nick_ret;
  int price = x;
  int amt_rec, amt_due, amt_ret;

  do
  {

    /*intialize variables to zero*/
    amt_rec = 0, dime_ret = 0, amt_rec = 0, amt_due = 0, amt_ret = 0;


    /*In service welcome message to prompt for additional sales*/
    printf("\nWelcome to my C Pop Machine!\n");
    printf("\nPop is %d cents. Please insert any combination of nickels [N or n], dimes [D or d] or quarters [Q or q]. You can also press R or r for return coin.\n", x);


      /*prompt user to enter a coin*/
      while(amt_rec<price)
      {
        printf("\nEnter a coin: ");
        scanf(" %c", & coin_type);

          if(coin_type == 'R' || coin_type == 'r')
          {
            endorbreak(amt_rec);//end program and refund money
            break;
          }
          else if (coin_type =='E' || coin_type == 'e')
          {
            endorbreak(amt_rec);
            printf("System is shutting down. Goodbye.\n");
            exit(0);
          }
          else if(coin_type == 'N' || coin_type == 'n')
          {
            printf("  Nickel detected.\n");
            coin = NICK;
          }
          else if(coin_type == 'D' || coin_type == 'd')
          {
            coin = DIME;
            printf("  Dime detected.\n");
          }
          else if(coin_type == 'Q' || coin_type == 'q')
          {
            coin = QUART;
            printf("  Quarter detected.\n");
          }
          else
          {
            printf("  Unknown coin rejected.\n");
            coin = ZERO;
          }

        /*call functions to tally amounts received, still owing and coins to be returned*/
        amt_rec=amt_rec + coin;
        amt_due=moneydue(amt_rec, price);
        dime_ret = dimeref(amt_rec, price);
        nick_ret = nickref(amt_rec, price);

        /*tell user how much money has been entered and how much more money to enter*/
        printf("    You have inserted a total of %d cents.\n", amt_rec);
          if(amt_rec < price)
          {
            printf("    Please insert %d more cents.\n", amt_due);
          }
      }/*end of while loop*/

    /*dispense pop once paid and return any change due*/
    if(amt_rec >= price)
    {
      printf("    Pop is despensed. Thank you for your business! Please come again.\n");
    }
    if(amt_rec > price)
    {
      amt_ret = amt_rec - price;
      change(amt_ret, dime_ret, nick_ret);
    }
  
  }while(coin_type != 'E');/*end of do-while loop*/

}
/*end of runmachine function*/


/*other functions (called in runmachine() function)*/

int
moneydue(int x, int y)
{
  int due=0;
  due = y - x;
  return(due);
}


int
dimeref(int x, int y)
{
  int num_dime=0, over_pay;
  over_pay = x - y;
  num_dime = over_pay/DIME;
    if(num_dime>ZERO)
    {
      return(num_dime);
    }
   // else
    //{
      //return(-num_dime);
    //}
}


int
nickref(int x, int y)
{
  int num_nick, over_pay;
  over_pay = y - x;
    if(over_pay>0 && over_pay%DIME != ZERO)
    {
      num_nick = 1;
    }
    else
    {
      num_nick = 0;
    }
  return(num_nick);
}

int
eretdime(int x)
{
  int dimedue;
  dimedue = x/DIME;
  return(dimedue);
}


int
eretnick(int x)
{
  int nickdue;
    if(x%DIME != ZERO)
    {
      nickdue = 1;
    }
    else
    {
      nickdue = 0;
    }
  return(nickdue);
}


void
change(int x, int y, int z)
{
  printf("    Change given: %d cents as %d dimes(s) and %d nickels(s).\n", x, y, z);
}


void
endorbreak(int x)
{
  int dime, nick;
  dime = eretdime(x);
  nick = eretnick(x);
  change(x, dime, nick);
}

/*end of all functions*/





