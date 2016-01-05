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
    if (strcmp(g, t->root) == 0) return 1;
    else{
    return find_above(t->parent, g);
    }
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
  if (t==NULL) return(0);
  else
    {
        char* string = t->root;
        if (string[0] == '~'){
            string = mytail(string);               
        }
        else{
            string = negate(string);
        }
        result =  find_above(t, string);
        free(string); // Prevent Memory Leak
        return result;
    }
}
		  
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
    if (t==NULL) return(0);
    else{
        if (closed1(t)==1 || closed(t->left) == 1 || closed(t->right) == 1) return 1;
        else return 0;
    }
}

void  add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
{
    if (t->left != NULL)
        add_one(t->left, g);
    if (t->right!= NULL)
        add_one(t->right, g);
    if(t->left == NULL && t->right == NULL){
        struct tableau* new = malloc(sizeof(struct tableau));   
        strcpy(new->root, g);
        new->parent = t;
        new->left = NULL;
        new->right = NULL;
        t->left = new;
        return;              
    }   
}

void alpha(struct tableau *t, char *g, char *h)/*not for double negs, adds g then h at every leaf below*/
{
    if (type(t) == 4) return;
    add_one(t, g);
    add_one(t, h);
    return;
}

void  add_two(struct tableau *t, char *g, char *h)/*for beta s, adds g, h on separate branches at every leaf below*/
{
    if (t->left != NULL)
        add_one(t->left, g);
    if (t->right != NULL)
        add_one(t->right, g);
    if(t->left == NULL && t->right == NULL){
        struct tableau* new1 = malloc(sizeof(struct tableau));
        strcpy(new1->root, g);
        new1->parent = t;
        new1->left = NULL, new1->right = NULL;
        t->left = new1;
        struct tableau* new2 = malloc(sizeof(struct tableau));
        strcpy(new2->root, h);
        new2->parent = t;
        new2->left = NULL, new2->right = NULL;
        t->right = new2;
        return;
}

void expand(struct tableau *t)/*must not be null.  Checks the root.  If literal, does nothing.  If beta calls add_two with suitable fmlas, if alpha calls alpha with suitable formulas unless a double negation then  */
{
    int fml = type(t->root);
    if (fml <= 1 ) return;
    if (fml == 2){
        alpha(t, firstexp(t->root), secondexp(t->root));
    }
    if (fml == 3){
        add_two(t, firstexp(t->root), secondexp(t->root));
    }
    if (fml == 4){
        add_one(t, mytail(mytail(t->root)));
    }
    return; 
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

