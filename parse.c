#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
/* Use p, q, r, s for propositions.  Use ~ for negation.  Use v for OR, use ^ for AND, use > for implies.  Brackets are (, ). */


/* List processing methods  */

char *mytail(char *list)  /*given non-empty string, returns string without the first char*/
{
    return list+1;
}

char *segment(char *list, int i, int j)/* characters from pos i up to j-1, provided i<=j*/
{
    char* copy = malloc((j-i+1)*sizeof(char));
    memmove(copy, list, j-i);
    copy[j] = '\0';
    return copy;
}

/* Basics.  Recognise propositions and connectives.  */

int prop(char x)
{if((x='p')||(x='q')||(x='r')||(x='s')) return(1);else return(0);}

int bc(char x)
{if ((x=='v')||(x=='^')||(x=='>')) return(1);else return(0);}


/* The actual parsing methods.  */
int bin_index(char *g)
{
    int brackets = 0;
    int i = 0;
    for ( i = 0; g[i] != '\0'; i++){
        if (g[i] == '(') brackets++;
        if (i > 50) printf("What the fk ??? \n");
        else if (g[i] == ')') brackets--;
        else if (bc(g[i]) == 1 && brackets == 1) return i;
    }
    return 0;
}

int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
    
    // Check for negation,
    if (g[0] == '~' && parse(mytail(g)) != 0 ) {
        return 2;
    }
    
    // Check for proposition
    if (prop(g[0]) == 1){
        return 1;
    }
    
    // Check for binary fml
    if (g[0] == '(' && parse(partone(g)) != 0 && parse(parttwo(g)) != 0){
        return 3;
    }
    
    return 0;
    
}

char *partone(char *g)
{/* for binary connective formulas, returns first part*/
    int bc_index = bin_index(g);
    char* part = segment(g, 0, bc_index-1);
    return part;
}

char *parttwo(char *g)
{/* for binary connective formulas, returns second part*/
    int bc_index = bin_index(g);
    char* part = segment(g, bc_index+1, strlen(g));
    return part;
}

char bin(char *g)
{/*for binary connective formulas, returns binary connective*/
    int bc_index = bin_index(g);
    return g[bc_index];
}


int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
    int result = parse(g);
    if (result < 2 ) return result;
    if ((parse(g)==2) && (parse(mytail(g))==2) return 4;
    
    
}

char *negate(char *g){
    char* copy = malloc((1+strlen(g))*sizeof(char));
    memmove(copy+1, g, strlen(g));
    copy[0] = '~';
    return copy;
}
char *firstexp(char *g)
{/* for alpha and beta formulas*/
  if (parse(g)==3)/*binary fmla*/  
    switch(bin(g))
    {
         case('v'): return(??);break;
         case('^'): return(??);break;
         case('>'): return(??);break;
         default:printf("what the f**k?");return(0);
    }
  if ((parse(g)==2)&& (parse(mytail(g))==2)/*double neg*/) return(mytail(mytail(g)));/*throw away first two chars*/

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
