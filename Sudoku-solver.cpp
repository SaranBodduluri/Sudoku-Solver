#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
// THIS DOESN'T WORK//
#define N 9

void printS(int arr[N][N]){//function to print the sudoku array

   for(int i=0;i<N;i++)
   {
     if(i==0)cout<<"-----|-----|-----\n";
     for(int j=0;j<N;j++){
     cout<<arr[i][j]  ;
     cout<<" ";}
     cout<<endl;
     if (i==2||i==5) cout<<"-----|-----|-----\n";

   }
   cout<<"-----|-----|-----\n";
}

int isOK(int arr[N][N],int row, int col, int num){

//make sure that same num is not in the row
  for(int x=0;x<=8;x++)
  if(arr[row][x] == num)
  return 0;

//make sure that same num is not in the column
 for(int x=0;x<=8;x++)
   if(arr[x][col]==num)
   return 0;
//
//make sure that same num is not in the 3*3 subarr
int startRow = row - row%3; //startRow is the nearest three multiple to row
int startCol = col - col%3; //startCol is the nearest three multiple to col
//startCol and startRow are the begining of the subarr 3*3 matrix

for(int i=0;i<3;i++)
  for(int j=0;j<3;j++)
    if(arr[i+startRow	][j+startCol] == num)
    return 0;

//if everything is OK then return 1
 return 1;

}

//solve is a recursive function to
//fill all the elements in the sudoku matrix
//such that no duplication occurs in any row, col
//and in any submatrix

int solve(int arr[N][N], int row, int col){

//if we reached 8 th row and 9 th col
//then we can return 1 to stop further recursion
  if(row== N-1 && col == N)
  return 1;

//if the col value beomces 9, we
//go to next row, and make col 0
 if(col==N){
   row++;
   col=0;
 }

//if the element is non-zero
//then go for next column
if(arr[row][col]>0)
   return solve(arr,row,col+1);

for( int num =1;num<=N;num++){

  if(isOK(arr,row,col,num)==1){
    //if it is Ok to assign num
    //we assign and hope to be the right position
    arr[row][col] = num;

    if(solve(arr,row,col+1)==1)
    return 1;
  }
  //if the position is not correct
  //then unassigning .
  arr[row][col]=0;
}
  return 0;
}

int main(){

//using FILE i/o for input

FILE *fp;
char ch;
 fp=fopen("input.txt","r");

 if(fp==NULL){
   printf("File not present");
   return 0;
 }

 int arr[N][N];
//taking the input sudoku array into arr
 for(int i=0;i<N;i++){
   int j=0;
   do{
     fscanf(fp,"%d",&(arr[i][j]));
      j++;//increase the column variable
   }while(ch=fgetc(fp)!='\n' && j<9);//stop after reachinga \n  , stop after reaching 9th column
 }

 cout<<"\nThis program takes the sudoku array input from the text file.\n";
 cout<<"Give the sudoku array,into a text file, each element \nseparated by a space. ";
      cout<<"Empty palces are to be replaced by 0, \nand use \\n after every row.";
 cout<<"For sample input, check sampleSudoku.txt\n\n\n";


  if (solve(arr,0,0)==1)
  printS(arr);
  else
  cout<<"No solution exits";
return 0;
}
