#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int inputs=6;


int i;
int j;

/*typedef struct tableau tableau;*/

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
}*tab, *node, *node1, *kid, *pa;                  
  
  
        
/*
 * %%%% Parser portion %%%%
 */

 char *mytail(char *list)  /*given non-empty string, returns string without the first char*/
{
    return list+1;
}

char *segment(char *list, int x, int y)/* characters from pos x up to y-1, provided x<=y*/
{
    char* copy = malloc((y-x+1)*sizeof(char));
    memmove(copy, list, y-x);
    copy[y] = '\0';
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
    int x = 0;
    for ( x = 0; g[x] != '\0'; x++){
        if (g[x] == '(') brackets++;
        if (x > 50) printf("What the fk ??? \n");
        else if (g[x] == ')') brackets--;
        else if (bc(g[x]) == 1 && brackets == 1) return x;
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


int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
    
    // Check for negation,
    if (g[0] == '~' && parse(mytail(g)) != 0 ) {
        return 2;
    }
    
    // Check for proposition
    if (prop(g) == 1){
        return 1;
    }
    
    // Check for binary fml
    if (g[0] == '(' && parse(partone(g)) != 0 && parse(parttwo(g)) != 0){
        return 3;
    }
    
    return 0;
    
}


char bin(char *g)
{/*for binary connective formulas, returns binary connective*/
    int bc_index = bin_index(g);
    return g[bc_index];
}



int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
    int result = parse(g);
    if ( result == 1 || result == 2 ){
        return 1;
    } 
    else if ((parse(g)==2) && parse(mytail(g))==2) return 4;
    else if (g[0] == '~'){
        switch(bin(g)){
            case('v'): return(2);break;
            case('>'): return(2);break;
            case('^'): return(3);break;
        
        }
    }
    else if(g[0] == '('){
        switch(bin(g)){
            case('v'): return(3);break;
            case('^'): return(2);break;
            case('>'): return(3);break;
        }   
    }
    else return 0;
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
         case('v'): return partone(g);break;
         case('^'): return partone(g);break;
         case('>'): return negate(partone(g));break;
         default:printf("what the f**k?");return(0);
    }
  if ((parse(g)==2)&& (parse(mytail(g))==2)/*double neg*/) return(mytail(mytail(g)));/*throw away first two chars*/

  if ((parse(g)==2)&&parse(mytail(g))==3) /*negated binary*/ 
  switch(bin(mytail(g)))
  {
    case('v'): return negate(partone(g));break;
    case('^'): return negate(partone(g));break;
    case('>'): return partone(g);break;
  } 
  return(0);
}        


char *secondexp(char *g)
{/* for alpha and beta formulas, but not for double negations, returns the second expansion formula*/ 
    if (parse(g) == 3) /*binary fmla*/{
        switch(bin(g)){
            case('v'): return parttwo(g);break;
            case('^'): return parttwo(g);break;
            case('>'): return parttwo(g); break;
        }
    }
    else if( parse(g)==2 && parse(mytail(g))==3){
        switch(bin(g)){
            case('v'): return negate(parttwo(g)); break;
            case('^'): return negate(parttwo(g)); break;
            case('>'): return negate(parttwo(g)); break;
        }   
    }   
}


/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
2. 
void complete(struct tableau *t)
which expands the root of the tableau and recursively completes any child tableaus.
3. 
int closed(struct tableau *t)
which checks if the whole tableau is closed.
Of course you will almost certainly need many other functions.

You may vary this program provided it reads 6 formulas in a file called "input.txt" and outputs in the way indicated below to a file called "output.txt".
*/


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

void add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
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
{ /*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/



  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
 
  /*lets check your parser*/
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
	{
	case(0):fprintf(fpout,"%s is not a formula", names[i]);break;
	case(1):fprintf(fpout,"%s is a proposition",names[i]);break;
	case(2):fprintf(fpout,"%s is a negation",names[i]);break;
	case(3):fprintf(fpout,"%s is a binary formula",names[i]);break;
	default:fprintf(fpout,"%s is not a formula",names[i]);break;
	}
    }
 
  /*make 6 new tableaus each with name at root, no children, no parent*/

  struct tableau tabs[inputs];

  for(i=0;i<inputs;i++)
    {
      tabs[i].root=names[i];
      tabs[i].parent=NULL;
      tabs[i].left=NULL;
      tabs[i].right=NULL;

      /*expand each tableau until complete, then see if closed */ 

      complete(&tabs[i]);
      if (closed(&tabs[i])) fprintf(fpout,"%s is not satisfiable\n", names[i]);
      else fprintf(fpout,"%s is satisfiable\n", names[i]);
    }
 
  fclose(fp);
  fclose(fpout);
 
  return(0);
}
