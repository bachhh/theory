#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
/* Use p, q, r, s for propositions.  Use ~ for negation.  Use v for OR, use ^ for AND, use > for implies.  Brackets are (, ). */


/* List processing methods  */

char *mytail(char *list)  /*given non-empty string, returns string without the first char*/
{
    return list++;
}

char *segment(char *list, int i, int j)/* characters from pos i up to j-1, provided i<=j*/
{
}

/* Basics.  Recognise propositions and connectives.  */

int prop(char x)
{if((x='p')||(x='q')||(x='r')||(x='s')) return(1);else return(0);}

int bc(char x)
{if ((x=='v')||(x=='^')||(x=='>')) return(1);else return(0);}


/* The actual parsing methods.  */

int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
}

char *partone(char *g)
{/* for binary connective formulas, returns first part*/
}

char *parttwo(char *g)
{/* for binary connective formulas, returns second part*/
}

char bin(char *g)
{/*for binary connective formulas, returns binary connective*/
}


int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
}

char *firstexp(char *g)
{/* for alpha and beta formulas*/
  if (parse(g)==3)/*binary fmla*/  switch(bin(g))
		     {case('v'): return(??);break;
		     case('^'): return(??);break;
		     case('>'): return(??);break;
		     default:printf("what the f**k?");return(0);
		     }
  if ((parse(g)==2)&& (parse(mytail(g))==2)/*double neg*/) return(??);/*throw away first two chars*/

  if ((parse(g)==2)&&parse(mytail(g))==3) /*negated binary*/ 
	switch(bin(mytail(g)))
	{
		case('v'):return(??);break;
		case('^'):return(??);break;
		case('>'): return(??);break;
	} 
  return(0);
}		     


char *secondexp(char *g)
{/* for alpha and beta formulas, but not for double negations, returns the second expansion formula*/
}		     
