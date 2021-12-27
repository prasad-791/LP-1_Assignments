/*--------------------------------------------------------------------------------------------

NAME   : ABHISHEK AJAY AVATI
ROLLNO : 33106
BATCH  : M9
CLASS  : TE 9
PS	   : Write a recursive program to find the solution of placing n queens on the chessboard 
		 so that no two queens attack each other using Backtracking.

----------------------------------------------------------------------------------------------*/
#include<iostream>
using namespace std;

// checking if the position is safe to fill/place the queen
void fillBoard(int row,int col,int ** arr,int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i][col]++;
        arr[row][i]++;
    }
    for(int i=1;i<n;i++)
    {
        if(row-i>=0&&col+i<n)			// checking the right top corner of position
        {
            arr[row-i][col+i]++;
        }
        if(col-i>=0&&row+i<n)			// checking the right bottom corner of position
        {
            arr[row+i][col-i]++;
        }
        if(row-i>=0&&col-i>=0)			// checking left top corner of the position
        {
            arr[row-i][col-i]++;
        }
        if(row+i<n&&col+i<n)			// checking left bottom corner of position
        {
            arr[row+i][col+i]++;
        }
    }
    arr[row][col]=n+1;					
}


// following function will be useful in clearing the board while backtracking
void clearBoard(int row,int col,int ** arr,int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i][col]--;
        arr[row][i]--;
    }
    for(int i=1;i<n;i++)
    {
        if(row-i>=0&&col+i<n)		
        {
            arr[row-i][col+i]--;
        }
        if(col-i>=0&&row+i<n)
        {
            arr[row+i][col-i]--;
        }
        if(row-i>=0&&col-i>=0)
        {
            arr[row-i][col-i]--;
        }
        if(row+i<n&&col+i<n)
        {
            arr[row+i][col+i]--;
        }
        
    }
    arr[row][col]=0;
}

// function helps to print on board
void printBoard(int * * arr,int n)
{
    static int i=1;					// static integer to count no of solutions
    cout<<endl;
    cout<<"Solution no:"<<i<<endl;
    i++;
    for(int i=0;i<n;i++)
    {
        for( int j=0;j<n;j++)
        {
            if(arr[i][j]==n+1)
            {
                cout<<"* ";
            }
            else
            {
                cout<<"- ";
            }
        }
        cout<<endl;
    }
}

void solveBoard(int * * arr,int n,int col)
{
    if(col>=n)
    {
        printBoard(arr,n);
        return ;
    }

   
    for(int i=0;i<n;i++)
    {   
        if(arr[i][col]==0)
        {
            fillBoard(i,col,arr,n); 
            solveBoard(arr,n,col+1);
            clearBoard(i,col,arr,n);
        }
    }    
}

int main()
{
    int n;
    cout<<"Enter Value of N ";
    cin>>n;
    int * * arr=new int*[n];
    for(int i=0;i<n;i++)
    {
        arr[i]=new int[n];
        for( int j=0;j<n;j++)
        {
            arr[i][j]=0;
        }
    }
    solveBoard(arr,n,0);
    return 0;

}

// OUTPUT

// test case 1

//Enter Value of N 4
//
//Solution no:1
//- - * -
//* - - -
//- - - *
//- * - -
//
//Solution no:2
//- * - -
//- - - *
//* - - -
//- - * -

// test case 2

//Enter Value of N 5
//
//Solution no:1
//* - - - -
//- - - * -
//- * - - -
//- - - - *
//- - * - -
//
//Solution no:2
//* - - - -
//- - * - -
//- - - - *
//- * - - -
//- - - * -
//
//Solution no:3
//- - * - -
//* - - - -
//- - - * -
//- * - - -
//- - - - *
//
//Solution no:4
//- - - * -
//* - - - -
//- - * - -
//- - - - *
//- * - - -
//
//Solution no:5
//- * - - -
//- - - * -
//* - - - -
//- - * - -
//- - - - *
//
//Solution no:6
//- - - - *
//- - * - -
//* - - - -
//- - - * -
//- * - - -
//
//Solution no:7
//- * - - -
//- - - - *
//- - * - -
//* - - - -
//- - - * -
//
//Solution no:8
//- - - - *
//- * - - -
//- - - * -
//* - - - -
//- - * - -
//
//Solution no:9
//- - - * -
//- * - - -
//- - - - *
//- - * - -
//* - - - -
//
//Solution no:10
//- - * - -
//- - - - *
//- * - - -
//- - - * -
//* - - - -
