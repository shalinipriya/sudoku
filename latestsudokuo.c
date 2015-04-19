/*SUDOKU SOLVER

Preeti U Murthy	08IT95
Shalini Priya	08IT01
Anusha K	08IT12
Meenal Dongle	08IT37
Meghana G	08IT38

*/

// SUDOKU SOLVER

//INPUT:		user entered inputs

//DATA STRUCTURE USED:  A 2-D array of Linked lists

//MECHANISM:		using the various functions included we eliminate the possibilities of an element in each linked list

//OUTPUT:		solved 2-D array


#include<stdio.h>
#include<stdlib.h>

int elementCount;

struct sudoku
{
	int data;
	struct sudoku *link;
}
*head[9][9],*temp;


struct HiddenPair   // structure used for calculating hidden pairs
{
	int count;
	int position[9];
};


void deleteFromRow(int row, int element)  //function to delete the existing element from that particular row
{
int i;
struct sudoku *curr,*prev;
for(i=0;i<9;i++)
{	
	if(head[row][i]->data==0) //delete only if head->data=0, check for head node
	{
	 	curr=head[row][i]; 
		prev=curr;
		while(curr!=NULL) // check if link list is not empty
		{
			 if (curr->data==element) 
			{
				 prev->link=curr->link;
				 free(curr);        //deallocating the memory
				 break;
			}
			else
			{
				 prev=curr;
				 curr=curr->link;
			}
		}
	}
}
}

void deleteFromColumn(int column, int element)  //function to delete the existing element from that particular column
{
int j;
struct sudoku *curr,*prev;
for(j=0;j<9;j++)  //delete only if head->data=0, check for head node
{	
	if(head[j][column]->data==0)
	{
		curr=head[j][column];
		prev=curr;
		while(curr!=NULL) // check if link list is not empty
		{
			 if (curr->data == element)
			{
				 prev->link=curr->link;
				 free(curr);      //dellocating the memory
				 break;
			}
			else
			{
				 prev=curr;
				 curr=curr->link;
			}
		}
	}
}
}


void deleteFromBox(int row, int column, int element) //function to delete the existing element from that particular box
{
  int box,i,j,k,l,boxRow,boxColumn;
  struct sudoku *curr,*prev;
  box=findBox(row, column);
  boxRow=(box/3); 
  if(box%3==0)
  boxRow--;
  boxColumn=(box%3);
  if(boxColumn==0)
  boxColumn=3;
  boxColumn--;

for(i=(boxRow)*3,j=0; j<3; i++,j++)
{	
	for(k=(boxColumn)*3,l=0; l<3; k++,l++)
  	{
		if(head[i][k]->data==0) //delete only if head->data=0, check for head node
		{
			curr=head[i][k];
			prev=curr;
			while(curr!=NULL) // check if link list is not empty
			{
	 			if (curr->data==element)
				{
		 			prev->link=curr->link;
		 			free(curr);       //deallocating the memory
		 			break;
				}
				else
				{
					 prev=curr;
					 curr=curr->link;
				}
			}
		}
	}
 }
}



int findBox(int row, int column)	 // function to find the box number
{
 int boxRow, boxColumn; 
 boxRow=(row+1)/3;

 if ((row+1)%3!=0) boxRow++;
 boxColumn=(column+1)/3;

 if ((column+1)%3!=0) boxColumn++;
 return (3*(boxRow-1)+boxColumn);
}

void deleteElement(int row, int column) //function to delete the existing element from that row,column and box
{
int element;
element=head[row][column]->data;  	// assigning element equal to the number given by the user
deleteFromRow(row,element);       	// deleting the existing element from that particular row
deleteFromColumn(column,element); 	// deleting the existing element from that particular column
deleteFromBox(row,column,element); 	// deleting the existing element from that particular box
}


void find_Index_Userinput(int row)
{

 int j;
 for(j=0;j<=8;j++)
 {	
 	if(head[row][j]->data!=0)		 	
	{
		 elementCount++; 	//changed here
		 deleteElement(row,j);
	}
 }
}

void find_Singles_HiddenSingles(int row)
{
 int i,j,col,desp;
 int count[2][10];
 struct sudoku *temp,*current,*prev;
 for(i=0;i<2;i++)
 	for(j=0;j<10;j++)
	count[i][j]=0;

 for(j=0;j<=8;j++)					//finding the index of single solution
 {
	
	if(head[row][j]->data==0)			// excluding the confirmed values in cells of the row
	{	
		prev=head[row][j]->link;

		if((prev->link==NULL))			//checking if the column has only single element, unconfirmed
		{				
			 head[row][j]->data=prev->data;  //make the next node as head node.
			 free(head[row][j]->link);
			 head[row][j]->link=NULL;
			 elementCount++;
			 deleteElement(row,j);
		}
	}
 }


 for(j=0;j<=8;j++)					//finding the unique solution
 {
 	if(head[row][j]->data==0)			//excluding the confirmed values
	{
		current=head[row][j]->link;
 		while(current!=NULL)		 	//traversing the linked list of the column and finding the number of times each value occurs
		{
			count[0][current->data]=count[0][current->data]+1;
			count[1][current->data]=j;
			current=current->link;
			
		}
	}
 }

 for(j=1;j<=9;j++)	
 {

	if(count[0][j]==1)	
	{
		col=count[1][j];		//col is the column number of the unique solution
		head[row][col]->data=j;		//making the unique value the value of the head of linked list		
	
	
	 	current=head[row][col]->link;	//freeing the rest of the linked list in the array
		while(current!=NULL)
		{
			temp=current;
			current=current->link;
			free(temp);
		}

		head[row][col]->link=NULL;	
		elementCount++;
		deleteElement(row,col);
	}

 }
}



void findHiddenDoubles(int number, int RCB)
{
struct sudoku *curr,*prev;
struct HiddenPair element[9];
int num[2];					//has the numbers which has count 2
int flag=0;
int i,j,k=0,l;
int num1, num2;
int boxRow,boxColumn,box;
for(i=0;i<9;i++)
for(j=0;j<9;j++)
element[i].position[j]=0;

if(RCB==3)
{
	box=number+1;
	boxRow=(box/3); 
	if(box%3==0)
	boxRow--;
	boxColumn=(box%3);
	if(boxColumn==0)
	boxColumn=3;
	boxColumn--;
}

for(i=0;i<9;i++)
{	//conditions for row/col/box
	
	if (RCB==1)					//for row
 	curr=head[number][i];
	if (RCB==2)					//for column
	curr=head[i][number];
	if(RCB==3)					//for box
	{	
		if(i<3)
		{
			for(j=0;j<3;j++)
			{	
				
				curr=head[boxRow*3+i][boxColumn*3+j];
			}						
		}
	}
	
	while(curr!=NULL)
	{
		 if(curr->data!=0) 
		{
			 element[curr->data-1].count++;
			 element[curr->data-1].position[i]=1;
		}
		curr=curr->link;
	}
}

//to check for elements occuring twice

for(i=0;i<9;i++)
{
	if(element[i].count==2)
	{	
		num[k++]=i;
	}
}	
	
if(k>=2)
{

	for(j=0;j<k;j++)
	{
		for(l=0;l<k;l++)
		{
			for(i=0;i<9;i++)
			{
		
				if(element[j].position[i]==element[l].position[i]) 
				{
					flag=1;		//to check if it is hidden pair	
					num1=j;
					num2=l;
				}
			}
		}
	}

//to delete the rest of the elements

if (flag==0)
{
	for(i=0;i<9;i++)
	{
		if(element[num1].position[i]==1)
		{	
			 if(RCB==1)
			 curr=head[number][i];
			 if(RCB==2)
			 curr=head[i][number];
			 if(RCB==3)					//for box
			{	
				if(i<3)
				{
					for(j=0;j<3;j++)
					{	
				
						curr=head[boxRow*3+i][boxColumn*3+j];
					}						
				}
			}
			 prev=NULL;
			 if(curr->link!=NULL)
			{
				 while(curr!=NULL)
				 {
					if(curr->data!=num1&&curr->data!=num2&&curr->data!=0)
					{
						 prev->link=curr->link;
					 	 free(curr);       //deallocating the memory
					 	 break;
					}
					else
					{
						 prev=curr;
						 curr=curr->link;
					 }
				 }
			}
		}

	}
}
}
}
 
 
//creating a structure node

void createnode()
{
temp=(struct sudoku *)malloc(sizeof(struct sudoku));
if(!temp) 
{
	printf("\nNot enough memory");exit(0);	
}
temp->link=NULL;
}


//creation of all possible elements in 3rd dimension cell by cell
void create3Dpillar( struct sudoku *base)
{
int i;
for(i=1;i<=9;i++)
{
	createnode();
	temp->data=i;
	base->link=temp;
	base=temp;
}
}


//find the naked pairs 

/**
Naked_Pair_module(ext:for row)
variables:i,j,k,l  - loop variables
	  pairs[10]  - holds column no. of the cell having only 2 (pillar)elements 
**/

void find_naked_pairs_in_row(int row)
{
int j,i,l,k=-1,pairs[10];
for(j=0;j<9;j++)	//finding the cells containin 2 elements
{
	if(head[row][j]->link!=NULL)
	{
		if(head[row][j]->link->link!=NULL)
		{
			if(head[row][j]->link->link->link==NULL)
			pairs[++k]=j;
		}
	}
}
for(i=k;i>0;i--)	//comparin the elements in cells havin 2 elements
	{
		l=1;
		while(i-l>=0)
			{
				if(head[row][pairs[i]]->link->data==head[row][pairs[i-l]]->link->data)
					{	
						//if found equal,deletion of elements from other cells
						if(head[row][pairs[i]]->link->link->data==head[row][pairs[i-l]]->link->link->data)			
							{
								head[row][pairs[i]]->data=head[row][pairs[i]]->link->data;
								head[row][pairs[i-l]]->data=head[row][pairs[i-l]]->link->link->data;
								deleteFromRow(row,head[row][pairs[i]]->data);
								deleteFromRow(row,head[row][pairs[i-l]]->data);

								
								head[row][pairs[i]]->data=0;
								head[row][pairs[i-l]]->data=0;
							}
					}
				l++;

			}
	}

}




/**
Naked_Pair_module(ext:for column)
variables:i,j,k,l  - loop variables
	  pairs[10]  - holds row no. of the cell having only 2 (pillar)elements 

**/

void find_naked_pairs_in_col(int col)         
{
int j,i,l,k=-1,pairs[10];
for(j=0;j<9;j++)                //finding all the cells containing 2 elements in t col

{
	if(head[j][col]->link!=NULL)
	{
		if(head[j][col]->link->link!=NULL)
		{
			if(head[j][col]->link->link->link==NULL)
			pairs[++k]=j;
		}
	}
}

for(i=k;i>0;i--)      //comparin the elements in cells havin 2 elements
{
	l=1;
	while(i-l>=0)
		{
			if(head[pairs[i]][col]->link->data==head[pairs[i-l]][col]->link->data)
			{
				if(head[pairs[i]][col]->link->link->data==head[pairs[i-l]][col]->link->link->data)
				{
					head[pairs[i]][col]->data=head[pairs[i]][col]->link->data;
					head[pairs[i-l]][col]->data=head[pairs[i-l]][col]->link->link->data;

					//if found equal,deletion of elements from other cells in the col
					deleteFromColumn(col,head[pairs[i]][col]->data);
					deleteFromColumn(col,head[pairs[i-l]][col]->data);

					head[pairs[i]][col]->data=0;
					head[pairs[i-l]][col]->data=0;
				}
			}

			l++;

		}
}

}


/**
Naked_Pairs_module(ext:for box)
variables:i,j,k,l  - loop variables
	  pairs[10][2]  - holds row & column no. of the cell having only 2 (pillar)elements 
**/

void find_naked_pairs_in_box(int boxRow,int boxColumn)
{

	int j,i,k,l,count=-1,pairs[10][2];     //finding all the pairs in a box
	for(i=(boxRow)*3,j=0; j<3; i++,j++)
	{
		for(k=(boxColumn)*3,l=0; l<3; k++,l++)
  		{
			if(head[i][k]->link!=NULL)
			{
				if(head[i][k]->link->link!=NULL)
				{
					if(head[i][k]->link->link->link==NULL)
					{
						pairs[++count][0]=i;
						pairs[count][1]=k;
					}			
				}
			}	
		}
	}



for(i=count;i>0;i--)     
{
	l=1;
	while((i-l)>=0)     	//finding pairs which are havin same elements
	{
		if(head[pairs[i][0]][pairs[i][1]]->link->data==head[pairs[i-l][0]][pairs[i-l][1]]->link->data)
		{
			if(head[pairs[i][0]][pairs[i][1]]->link->link->data==head[pairs[i-l][0]][pairs[i-l][1]]->link->link->data)
			{
				head[pairs[i][0]][pairs[i][1]]->data=head[pairs[i][0]][pairs[i][1]]->link->data;      
			head[pairs[i-l][0]][pairs[i-l][1]]->data=head[pairs[i-l][0]][pairs[i-l][1]]->link->data;                                           
				//if found ,deletion of the elements from the rest of the box
				
				deleteFromBox(pairs[i][0],pairs[i][1],head[pairs[i][0]][pairs[i][1]]->data);     
				deleteFromBox(pairs[i-l][0],pairs[i-l][1],head[pairs[i-l][0]][pairs[i-l][1]]->data);
				head[pairs[i][0]][pairs[i][1]]->data=0;
				head[pairs[i-l][0]][pairs[i-l][1]]->data=0;
			}
		}
		l++;

	}
}

}


/**
Naked_Pairs_module:finding naked pairs ,ie,cells containin the same 2 elements in a row/col/box
helps:elimination of such elements from rest of t row/col/box cells
variables:implicitly known
**/
		
void findNakedPairs()
{
int row,col,boxcol,boxrow;
for(row=0;row<9;row++)
{
	find_naked_pairs_in_row(row);			//finding such pairs in all row (called row-wise once)
}


	for(col=0;col<9;col++)
	{
		find_naked_pairs_in_col(col);		//pairs in all col(called col-wise once)
	}



	for(boxrow=0;boxrow<3;boxrow++)
	{

		for(boxcol=0;boxcol<3;boxcol++)
			{
				find_naked_pairs_in_box(boxrow,boxcol);     //pairs in all box (called box-wise)
			}
	}	
}	


//to delete element from 2boxes other than where its present.

void LcDeleteRow(int element,int row,int searchFrom)
{
int j,k;
int rangeBegin=searchFrom;
int rangeEnd=(searchFrom+5);

struct sudoku *curr,*prev;
for(j=rangeBegin;j<=rangeEnd;j++)
{	//delete only if head->data=0, check for head node
	k=j%9;	
	if(head[row][k]->data==0)
	{
	curr=head[row][k]->link;
	prev=head[row][k];
	while(curr!=NULL)
		{
		 if (curr->data==element)
			{
			 prev->link=curr->link;
			 free(curr);        //deallocating the memory
			 break;
			}
		else
			{
			 prev=curr;
			 curr=curr->link;
			}
		}
	}
}
	curr=head[0][7];
	while(curr!=NULL)	
	{
		curr=curr->link;
	}
}


//to delete element from 2boxes other than where its present.

void LcDeleteCol(int element,int col,int searchFrom)
{
int i,k;
int rangeBegin=searchFrom;
int rangeEnd=(searchFrom+5);

struct sudoku *curr,*prev;

for(i=rangeBegin;i<=rangeEnd;i++)
{
	//delete only if head->data=0, check for head node
	k=i%9;	
	if(head[k][col]->data==0)
	{
	curr=head[k][col]->link;
	prev=head[k][col];
	while(curr!=NULL)
		{
		 if (curr->data==element)
			{
			 prev->link=curr->link;
			 free(curr);        //deallocating the memory
			 break;
			}
		else
			{
			 prev=curr;
			 curr=curr->link;
			}
		}
	}
}
	curr=head[0][7];
	while(curr!=NULL)	
	{
		curr=curr->link;
	}
}


//deleting an element excluding coloumn J, in a box
//identified by 1st 2 parameters passed.

void LcDeleteFromBox_lc2col(int boxBeginI,int boxBeginJ,int J,int element)
{
int i,j;
struct sudoku *curr,*prev;
for(i=boxBeginI;i<=(boxBeginI+2);i++)
{
	for(j=boxBeginJ;j<=(boxBeginJ+2);j++)
	{
		if(j!=J)
		{
			if(head[i][j]->data==0)
			{
				curr=head[i][j]->link;
		
				prev=head[i][j];
				while(curr!=NULL)
				{
		 			if (curr->data==element)
					{
			 			prev->link=curr->link;
			 			free(curr);       //deallocating the memory
						break;
					}
					else
					{
			 		prev=curr;
			 		curr=curr->link;
					}
				}
			}
		}

	}
}

}

//deleting an element excluding row J, in a box
//identified by 1st 2 parameters passed.

void LcDeleteFromBox_lc2row(int boxBeginI,int boxBeginJ,int J,int element)
{
int i,j;
struct sudoku *curr,*prev;
for(i=boxBeginI;i<=(boxBeginI+2);i++)
{
	for(j=boxBeginJ;j<=(boxBeginJ+2);j++)
	{
		if(i!=J)
		{
			if(head[i][j]->data==0)
			{
				curr=head[i][j]->link;
		
				prev=head[i][j];
				while(curr!=NULL)
				{
		 			if (curr->data==element)
					{
			 			prev->link=curr->link;
			 			free(curr);       //deallocating the memory
						break;
					}
					else
					{
			 		prev=curr;
			 		curr=curr->link;
					}
				}
			}
		}

	}
}

}


/*a number occurring possibility if its equal to 2 in a row, and its locked
in a box,then we delete that number possibilities in rest of elements
in that box */

void LcFindLockedCandidate2_row()
{

int a,i,j,k,s,box,boxRow,boxColumn,boxBeginI=0,boxBeginJ=0;
struct sudoku *t;
struct lock{
	int ocurrences;
	int col[2];
	}num[10];

//to find 2 occurrences of a number in the col and storing that indices

for(j=0;j<=9;j++)
{
	num[j].ocurrences=0;
	num[j].col[0]=0;
	num[j].col[1]=0;
}	

for(i=0;i<9;i++)
{
	for(j=0;j<9;j++)
	{
		if(head[i][j]->data==0)
		{
			t=head[i][j]->link;
			while(t!=NULL)
			{
			(num[t->data].ocurrences)++;
			t=t->link;	
			}
		}
	}

	//now i hav no. of each numbr in tat coloumn.
	
	for(k=1;k<=9;k++)
	{
		if(num[k].ocurrences == 2)			//if occurence of numbr =2, find that number's 2 row indices
		{						//in which the number is present
			s=0;			
			for(j=0;j<9;j++)
			{
				if(head[i][j]->data==0)
				{
					t=head[i][j]->link;

					while(t!=NULL)
					{
						if(t->data == k)
						{
							num[k].col[s]=j;
							s++;
						}
						t=t->link;	
					}
				}
			
						
			
			}
		//here once traversal of that coloumn with pillars is done n we hav indices of ele occurin twice			
		//here i check for indices to lie in same box or not n then call delete frm box.
				
			if((num[k].col[0]>=0 && num[k].col[1]>=0) && (num[k].col[0]<=2 && num[k].col[1]<=2))				
			{
				a=findBox(i,0);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2row(boxBeginI,boxBeginJ,i,k);
	
			}		
			if((num[k].col[0]>=3 && num[k].col[1]>=3) && (num[k].col[0]<=5 && num[k].col[1]<=5))				
			{
				a=findBox(i,4);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2row(boxBeginI,boxBeginJ,i,k);
	
			}			
			if((num[k].col[0]>=6 && num[k].col[1]>=6) && (num[k].col[0]<=8 && num[k].col[1]<=8))				
			{
				a=findBox(i,7);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2row(boxBeginI,boxBeginJ,i,k);
			}

			// now the box where ele needs to be deleted is found! 
					
		}	//end of if()		
		
	}
for(i=0;i<=9;i++)
{
	num[i].ocurrences=0;
	num[i].col[0]=0;
	num[i].col[1]=0;
}	

}

}
/*a number occurring possibility if=2 in a coloumn, and its locked
in a box,then we delete that number possibilities in rest of elements
in that box */

void LcFindLockedCandidate2_col()
{

int a,i,j,k,s,box,boxRow,boxColumn,boxBeginI=0,boxBeginJ=0;
struct sudoku *t;
struct lock{
	int ocurrences;
	int row[2];
	}num[10];

//to find 2 occurrences of a number in the row and storing that indices

for(i=0;i<=9;i++)
{
	num[i].ocurrences=0;
	num[i].row[0]=0;
	num[i].row[1]=0;
}	

for(j=0;j<9;j++)
{
	for(i=0;i<9;i++)
	{
		if(head[i][j]->data==0)
		{
			t=head[i][j]->link;
			while(t!=NULL)
			{
			(num[t->data].ocurrences)++;
			t=t->link;	
			}
		}
	}

	//now i have no. of each numbr in tat coloumn.
	
	for(k=1;k<=9;k++)
	{
		if(num[k].ocurrences == 2)		//if occurence of numbr =2, find that number's 2 row indices
		{					//in which the number is present
			s=0;				
			for(i=0;i<9;i++)
			{
				if(head[i][j]->data==0)
				{
					t=head[i][j]->link;

					while(t!=NULL)
					{
						if(t->data == k)
						{
							num[k].row[s]=i;
							s++;
						}
						t=t->link;	
					}
				}
			
			}
		//here once traversal of that coloumn with pillars is done n we hav indices of ele occurin twice			
		//here i check for indices to lie in same box or not n then call delete frm box.
				
			if((num[k].row[0]>=0 && num[k].row[1]>=0) && (num[k].row[0]<=2 && num[k].row[1]<=2))				
			{
				a=findBox(0,j);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2col(boxBeginI,boxBeginJ,j,k);
	
			}		
			if((num[k].row[0]>=3 && num[k].row[1]>=3) && (num[k].row[0]<=5 && num[k].row[1]<=5))				
			{
				a=findBox(4,j);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2col(boxBeginI,boxBeginJ,j,k);
	
			}			
			if((num[k].row[0]>=6 && num[k].row[1]>=6) && (num[k].row[0]<=8 && num[k].row[1]<=8))				
			{
				a=findBox(7,j);
				boxRow=(a/3); 
				if(a%3==0)
					boxRow--;
				boxColumn=(a%3);
				if(boxColumn==0)
					boxColumn=3;
			        boxColumn--;
			
				boxBeginI=boxRow*3;
				boxBeginJ=boxColumn*3;
				LcDeleteFromBox_lc2col(boxBeginI,boxBeginJ,j,k);
			}

			// now the box where ele needs to be deleted is found! yippee.
			//printf("\n %d-Begini %d-beginj %d-a %d-j",boxBeginI,boxBeginJ,a,j);
					
		}	//end of if()		
		
	}
for(i=0;i<=9;i++)
{
	num[i].ocurrences=0;
	num[i].row[0]=0;
	num[i].row[1]=0;
}	

}
LcFindLockedCandidate2_row();

}

// to find locked candidates

void LcFindLockedCandidate1()
{

struct sudoku *t;
int i=0,j=0,cc,ii,p,q;

struct lock
{
	int r[3];
	int c[3];
}box[10];		//structure for 1 box, counts


/* from box1 to box 9,initialising number of times
 a number occurs in each row n coloumn in that box to 0*/

for(i=0;i<=9;i++)
{
	box[i].r[0]=0;
	box[i].r[1]=0;
	box[i].r[2]=0;
	box[i].c[0]=0;
	box[i].c[1]=0;
	box[i].c[2]=0;
}

for(i=0;i<=6;i+=3)				//going to every box
{
	for(j=0;j<=6;j+=3)
	{
		for(p=0;p<=2;p++)		//each box's row and coloumn
		{
			for(q=0;q<=2;q++)
			{
				if(head[p+i][q+j]->data==0) 	//if not input number
				{
					t=head[p+i][q+j]->link;
					while(t!=NULL)		//for 1 pillar, count of nos. is calculated
					{
					(box[t->data].r[p])++;
					(box[t->data].c[q])++;
					t=t->link;
					}
				}

			}
		}
		cc=1;
		//data for a box is ready
		while(cc<=9)
		{
			if(box[cc].r[0]==0 && box[cc].r[1]==0 && box[cc].r[2]==2)
				LcDeleteRow(cc,(i+2),(j+3));

			if(box[cc].r[0]==0 && box[cc].r[1]==2 && box[cc].r[2]==0)
				LcDeleteRow(cc,(i+1),(j+3));

			if(box[cc].r[0]==2 && box[cc].r[1]==0 && box[cc].r[2]==0)
				LcDeleteRow(cc,(i+0),(j+3));

			
			if(box[cc].c[0]==0 && box[cc].c[1]==0 && box[cc].c[2]==2)
				LcDeleteCol(cc,(j+2),(i+3));

			if(box[cc].c[0]==0 && box[cc].c[1]==2 && box[cc].c[2]==0)
				LcDeleteCol(cc,(j+1),(i+3));

			if(box[cc].c[0]==2 && box[cc].c[1]==0 && box[cc].c[2]==0)
				LcDeleteCol(cc,(j+0),(i+3));
			cc++;			
			
		}
			//aftr 1 box, initialise struture to all 0s.
		for(ii=0;ii<=9;ii++)
		{
			box[ii].r[0]=0;
			box[ii].r[1]=0;
			box[ii].r[2]=0;
			box[ii].c[0]=0;
			box[ii].c[1]=0;
			box[ii].c[2]=0;
		}
	}

}
LcFindLockedCandidate2_col();
}

void errorCheck()
{
int i,j,k,l,count[10];
for(k=0;k<10;k++)
		count[k]=0;

for(i=0;i<9;i++)
{
	for(j=0;j<9;j++)
	{
		count[head[i][j]->data]++;
	}
	for(k=1;k<=9;k++)
	{
		if (count[k]>1) 
		{
			printf("\nError");
			exit(0);
		}
	}
	for(k=0;k<10;k++)
		count[k]=0;
}


for(i=0;i<9;i++)
{
	for(j=0;j<9;j++)
	{
		count[head[j][i]->data]++;
	}
	for(k=1;k<=9;k++)
	{
		if (count[k]>1) 
		{
			printf("\nError");
			exit(0);
		}
	}
	for(k=0;k<10;k++)
		count[k]=0;
}

for(i=0;i<=6;i+=3)
{
	for(j=0;j<=6;j+=3)
	{
		for(k=0;k<=2;k++)
		{
			for(l=0;l<=2;l++)
			{
				count[head[i+k][j+l]->data]++;
			}
		}

		for(k=1;k<=9;k++)
		{
			if (count[k]>1) 
			{
				printf("\nError");
				exit(0);
			}
		}
		for(k=0;k<10;k++)
			count[k]=0;
	}	
}
}

	
	
void main()
{
	
int row, col,j;
int prevElementCount=0;
struct sudoku *curr;
FILE *fp;
elementCount=0;
printf("Welcome to Sudoku solver!\n");		
fp=fopen("array7.txt","r+");			//reading input numbers from textfile.
if(fp==NULL)
	{
	printf("\n File does not exist");
	exit(0);
	}

for(row=0;row<9;row++)
{
	for(col=0;col<9;col++)
	{	
		temp=(struct sudoku *)malloc(sizeof(struct sudoku));
		if(!temp)
		{
			printf("\nNot enough Memory");
			exit(0);
		}
		fscanf(fp,"%d ",&temp->data);
		if(temp->data<0||temp->data>9)
		{
			printf("\nInput Not within 1-9");
			exit(0);
		}		
		temp->link=NULL;
		head[row][col]=temp;

		if(head[row][col]->data!=0)
		elementCount++;

	}

}

printf("\nThe input you hav entered is:\n");		//printing the input array
for(row=0;row<9;row++)
{
	for(col=0;col<9;col++)
		printf("%d   ",head[row][col]->data);
		
	printf("\n\n");
}
  
//creation of 3rd dimension element storage

for(row=0;row<9;row++)
{
	for(col=0;col<9;col++)
	{	
		if(head[row][col]->data == 0)
		{
			create3Dpillar(head[row][col]);
		}
	}
}
elementCount=0;

//sending each row to deal with cancellation of possible elements made impossible by input data

for(row=0;row<9;row++)
{
	find_Index_Userinput(row);	
}

j=1;

printf("\nAfter index count %d",elementCount);



while(1)
{
errorCheck();
prevElementCount=elementCount;

for(row=0;row<9;row++)					//once traversal of whole sudoku to remove possibilities
	{						//of input elements in its corresp row, col and box
		find_Singles_HiddenSingles(row);
	}

for(row=0;row<9;row++)
	{
		findHiddenDoubles(row,1);	//for every row
		findHiddenDoubles(row,2);	//for every column
		findHiddenDoubles(row,3);	//for every box	
	}
findNakedPairs();
LcFindLockedCandidate1();

if(elementCount==prevElementCount) break;
}

printf("\nThe solved sudoku is %d:\n",elementCount);	//printing solved sudoku.
for(row=0;row<9;row++)
{
	for(col=0;col<9;col++)
	{
		printf("%d   ",head[row][col]->data);
	}
printf("\n\n");
}
}



