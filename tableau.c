#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
#include "parse.h"


int Fsize=50; /*enough space for the fmlas we use*/
int i;

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
}*tab, *node, *node1, *kid, *pa;

int find_above(struct tableau *t, char *g) /*Is g label of current node or above?*/
{
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
  if (t==NULL) return(0);
  else
    {
    }
}
		  
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
}

void  add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
{
}

void alpha(struct tableau *t, char *g, char *h)/*not for double negs, adds g then h at every leaf below*/
{
}

void  add_two(struct tableau *t, char *g, char *h)/*for beta s, adds g, h on separate branches at every leaf below*/
{
}

void expand(struct tableau *tp)/*must not be null.  Checks the root.  If literal, does nothing.  If beta calls add_two with suitable fmlas, if alpha calls alpha with suitable formulas unless a double negation then … */
{ 
}

void complete(struct tableau *t)/*expands the root then recursively expands any children*/
{ if (t!=NULL)
    { 
      expand(t);
      complete((*t).left);
      complete((*t).right); 
    }
}


int main()
{ /*input a string and check if its a propositional formula */

  char *name = malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);
  if switch(parse(name))
	{
	0:printf("Not a formula\n");
	1:printf("A proposition\n");
	2:printf("A negation\n");
	3:printf("A binary formula\n");
	}
  printf("the type is ");
  switch(type(name))
  {
	0:printf("I told you, not a fmla\n");
	1:printf("a literal\n");
	2:printf("alpha\n");
	3:printf("beta\n");
	4:printf("double negation\n");
  } 
  If (type(name)>1)
printf("first expansion fmla is %s and second expansion is %s\n", firstexp(name), secondexp(name));

  /*make new tableau with name at root, no children, no parent*/
  struct tableau t={name, NULL, NULL, NULL};

  /*expand the root, recursively complete the children*/
  complete(&t);

 /*check if closed*/
 if (closed(&t)) printf("%s is not satisfiable", name);
 else printf("%s is satisfiable", name);
 
 
  return(0);
}

