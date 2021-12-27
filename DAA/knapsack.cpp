// Name: Abhishek Ajay Avati
// Rollno: 33106
// PS :- Write a menu driven C++ program for--
//a. Write a program to implement Fractional knapsack using Greedy algorithm
//b. 0/1 knapsack using dynamic programming.
//c. Show that Greedy strategy does not necessarily yield an optimal solution over a dynamic programming approach.

// header files
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

// structure to store the items value weight and density
typedef struct {
   float value;											// value of item
   float weight;										// weight of item
   float density;										// density of item
} Item;

// method to get max of two numbers
float max(float a,float b){								// two int parametes
	return a>b?a:b;										// if a>b return a else return b
}

// method to take input in array
void input(Item *items,int n){							
	for(int i=0;i<n;i++){								// looping through size of array
		cout<<"Enter "<<i+1<<" value and"				// message
		<<" weight resp. ";
		cin>>items[i].value								// scanning weight and value of item
		>>items[i].weight;
		items[i].density=items[i].value/items[i].weight;// calculating items density
	}
}

// method to display array
void display(Item *items,int n){	
	cout<<"Value\tWeight\tDensity"<<endl;				// message
	for(int i=0;i<n;i++){								// looping through size of array
		cout<<items[i].value<<"\t"						// printing the value of item
		<<items[i].weight<<"\t"							// printing the weight of item
		<<items[i].density<<endl;						// printing the density of item
	}	
}

// method to compare density of two items
bool compareDensity(Item I1,Item I2){					// return type= bool
	return I1.density>I2.density;						// returns true if first item density is large
}

// method for greedy fractional knapsack
float GFractional(Item *items,int n,int W){				
	sort(items,items+n,compareDensity);					// sorts the array on basis of density
	float finalWeight=0,finalValue=0;					// variables for final weight and final value
	for(int i=0;i<n;i++){								// looping through items array
		if(finalWeight + items[i].weight<= W) {			// checking if addition of weight doesn't exceed capacity
        	finalValue += items[i].value ;				// if true add the item
        	finalWeight += items[i].weight;				// calculate final weight
      	}else{
      		int wt = W-finalWeight;						// else add some fraction of that item
         	finalValue += (wt * items[i].density);		// calculating final value
         	finalWeight += wt;							// calculating final weight
         	break;										// after adding some fraction break the loop
		}
	}
	return finalValue;									// return the max profit gain
}

// greedy for 0/1knapsack
int G01Knapsack(int capacity,Item *items,int n){		
		sort(items,items+n,compareDensity);				// sort items acc to density
		int i=0;										// index variable
		int result=0;									// final profit/ result variable
		while(i<n){										// looping through items
			if(items[i].weight<=capacity){				// checking if weight of sack exceeds capacity
				result+=items[i].value;					// if true add the item in sack
				capacity-=items[i].weight;				// reducing the capacity
			}
			i++;										// increment index variable
		}
		return result;									// return final result
}

// dp approach for knapsack
float DpKnapsack(int capacity,Item *items,int n){		
	float arr[n+1][capacity+1];							// creation of 2D dp array of n X capacity
	for(int i=0;i<=n;i++) arr[i][0]=0;					// initializing the 0th column to 0
	for(int i=0;i<=capacity;i++) arr[0][i]=0;			// initializing the 0th row to 0
	for(int i=1;i<=n;i++){								// now looping through remaining rows
		for(int j=1;j<=capacity;j++){					// looping through ith row upto capacity count
			if(j-items[i-1].weight>=0){				 
				// take the maximum of these two possibilities to fill the current state.
				arr[i][j]=max(arr[i-1][j],
						arr[i-1][j-int(items[i-1].weight)]+
						items[i-1].value);
			}
			else{
				// else the state will be equal to previous
				arr[i][j]=arr[i-1][j];
			}
		}
	}
	return arr[n][capacity];							// return the max profit present at nth row capacity th column 						
}
// menu driven function
int menu(){
	// the following are messages/ option for user to make choice
	cout<<"\n\n---MENU---"<<endl;
	cout<<"1.Knapsack using Greedy Approach"<<endl;
	cout<<"2.0/1 Knapsack using greedy approach"<<endl;
	cout<<"3.O/1 Knapsack using dp approach"<<endl;
	cout<<"4.Exit"<<endl;
	cout<<"\nEnter Your Choice :: ";		
	int choice;											// variable for user's choice
	cin>>choice;										// scanning user choice
	return choice;										// return user choice
}
// main function
int main(){
	int capacity;										// max weight to carry
	cout<<"Enter Capacity Of Bag:- ";					// message
	cin>>capacity;										// scanning capacity from user
	
	int noOfItems;										// variable to store no of items
	cout<<"\n\nEnter No Of Items:- ";					// message
	cin >>noOfItems;									// scanning no of items	
	Item *items=new Item[noOfItems];					// declaring array of items
	
	input(items,noOfItems);								// invoking input method
	
	cout<<"\n\nTHE ITEMS ARE"<<endl;					// message
	display(items,noOfItems);							// invoking display method
	
	while(1){											// while loop for menu driven code
		switch(menu()){									// switch case according to user choice fetched from menu() function
			case 1:{									// case 1: apply knapsack greedy approach
				cout <<"\n\nMax value for "<< capacity 
				<<" weight using greedy approach is "
				<< GFractional(items,noOfItems,capacity);// invoking function and printing the max profit
				break;									// breaking the switch case 
			}
			case 2:{									// case 2: apply 0/1 knapsack greedy approach
				cout<<"\n\nMax value for "<< capacity 
				<<" weight using 0/1 knapsack greedy approach is "
				<< G01Knapsack(capacity,items,noOfItems)<<endl;//invoking and printing the max profit
				break;									// breaking the switch case
			}
			case 3:{									// case 3: apply 0/1 knapsack dynamic approach
				cout<<"\n\nMax value for "<< capacity 	
				<<" weight using DP approach is "
				<<DpKnapsack(capacity,items,noOfItems)<<endl;// invoking function and printing max result
				break;									// breaking the switch case
			}
			case 4:{									// case 4: user wants to exit the program
				cout<<"\nThank You!!"<<endl;			// message
				return 0;								// exit the code 
			}
			default:{									// In case user give invalid choice
				cout<<"Invalid Choice :("<<endl;		// message
				break;									// break switch case and again ask for choice 
			}
		}
	}
	return 0;											// exit the code
}


// OUTPUT

// TEST CASE 1
/*

Enter Capacity Of Bag:- 50


Enter No Of Items:- 3
Enter 1 value and weight resp. 60 10
Enter 2 value and weight resp. 100 20
Enter 3 value and weight resp. 120 30


THE ITEMS ARE
Value   Weight  Density
60      10      6
100     20      5
120     30      4


---MENU---
1.Knapsack using Greedy Approach
2.0/1 Knapsack using greedy approach
3.O/1 Knapsack using dp approach
4.Exit

Enter Your Choice :: 1


Max value for 50 weight using greedy approach is 240

---MENU---
1.Knapsack using Greedy Approach
2.0/1 Knapsack using greedy approach
3.O/1 Knapsack using dp approach
4.Exit

Enter Your Choice :: 2


Max value for 50 weight using 0/1 knapsack greedy approach is 160


---MENU---
1.Knapsack using Greedy Approach
2.0/1 Knapsack using greedy approach
3.O/1 Knapsack using dp approach
4.Exit

Enter Your Choice :: 3


Max value for 50 weight using DP approach is 220


---MENU---
1.Knapsack using Greedy Approach
2.0/1 Knapsack using greedy approach
3.O/1 Knapsack using dp approach
4.Exit

Enter Your Choice :: 5
Invalid Choice :(


---MENU---
1.Knapsack using Greedy Approach
2.0/1 Knapsack using greedy approach
3.O/1 Knapsack using dp approach
4.Exit

Enter Your Choice :: 4

Thank You!!

*/ 

// TEST CASE 2

/*

Enter Capacity Of Bag:- 15

Enter No Of Items:- 7                                                                                                   
Enter 1 value and weight resp. 10 2                                                                                     
Enter 2 value and weight resp. 5 3                                                                                      
Enter 3 value and weight resp. 15 5                                                                                     
Enter 4 value and weight resp. 7 7                                                                                      
Enter 5 value and weight resp. 6 1                                                                                      
Enter 6 value and weight resp. 18 4                                                                                     
Enter 7 value and weight resp. 3 1                                                                                                                                                                                                                                                                                                                                      


THE ITEMS ARE                                                                                                           
Value   Weight  Density                                                                                                 
10      2       5                                                                                                       
5       3       1.66667                                                                                                 
15      5       3                                                                                                       
7       7       1                                                                                                       
6       1       6                                                                                                       
18      4       4.5                                                                                                     
3       1       3                                                                                                                                                                                                                                                                                                                                                       

---MENU---                                                                                                              
1.Knapsack using Greedy Approach                                                                                        
2.0/1 Knapsack using greedy approach                                                                                    
3.O/1 Knapsack using dp approach                                                                                        
4.Exit                                                                                                                                                                                                                                          
Enter Your Choice :: 1                                                                                                                                                                                                                                                                                                                                                  


Max value for 15 weight using greedy approach is 55.3333                                                                                                                                                                                        


---MENU---                                                                                                              
1.Knapsack using Greedy Approach                                                                                        
2.0/1 Knapsack using greedy approach                                                                                    
3.O/1 Knapsack using dp approach                                                                                        
4.Exit                                                                                                                                                                                                                                          
Enter Your Choice :: 2                                                                                                                                                                                                                                                                                                                                                  


Max value for 15 weight using 0/1 knapsack greedy approach is 52                                                                                                                                                                                                                                                                                                        


---MENU---                                                                                                              
1.Knapsack using Greedy Approach                                                                                        
2.0/1 Knapsack using greedy approach                                                                                    
3.O/1 Knapsack using dp approach                                                                                        
4.Exit                                                                                                                                                                                                                                          
Enter Your Choice :: 3                                                                                                                                                                                                                                                                                                                                                  

Max value for 15 weight using DP approach is 54                                                                                                                                                                                                                                                                                                                         


---MENU---                                                                                                              
1.Knapsack using Greedy Approach                                                                                        
2.0/1 Knapsack using greedy approach                                                                                    
3.O/1 Knapsack using dp approach                                                                                        
4.Exit                                                                                                                                                                                                                                          
Enter Your Choice :: 4                                                                                                                                                                                                                          

Thank You!!   


*/
