//C++ program to minimise cash flow among a set of friends who have borrowed money
#include <iostream>
#include <bits/stdc++.h>
//standard library that contains common functionality that we use in building all applications like containers, algorithms, etc.
using namespace std;

//Number of persons (or vertices in the graph)
// #define number_of_persons 3
int number_of_persons;

//A utility function that returns index of minimum value in array[]
int get_Minimum(vector<int> &array)
{
    int min_Index = 0;
    for(int i = 1; i < number_of_persons; i++)
    {
        if(array[i] < array[min_Index])
            min_Index = i;
    }
    
    //returns the index of the minimum value
    return min_Index;
}

//A utility function that returns index of maximum value in array[]
int get_Maximum(vector<int> &array)
{
    int max_Index = 0;
    for(int i = 1; i < number_of_persons; i++)
    {
        if(array[i] > array[max_Index])
            max_Index = i;    
    }
    
    //returns the index of maximum value
    return max_Index;
}

//A utility function to return minimum of 2 values
int minimum_of_two(int number1, int number2)
{
    if(number1 < number2)
        return number1;
    else
        return number2;
}

//amount[p] indicates the net amount to be credited or debited to r from person 'p'
//If amount[p] is positive, then ith person will take amount[i]
//If amount[p] is negative, then ith person will give -amount[i]

void minCashFlowRecursion(vector<int> &amount)
{
    //Find the index of minimum and maximum values in amount[]
    //amount[maxCredit] indicates the maximum amount to be given to (or credited to) any person 
    //amout[maxDebit] indicates the maximum amount to be taken (or debited) from any person
    //So, if there is a positive value in amount[], then there must be a negative value
    
    int maxCredit = get_Maximum(amount), maxDebit = get_Minimum(amount);
    
    //If both amounts are 0, then all amounts are settled
    if(amount[maxCredit] == 0 && amount[maxDebit] == 0)
        return;
        
    //Find the minimum of the two amounts
    int minimum = minimum_of_two(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= minimum;
    amount[maxDebit] += minimum;
    
    //If minimum is the maximum amount to be
    cout<<"Person "<<maxDebit+1<<" pays "<<minimum<<" to "<<maxCredit+1<<"."<<endl;
    
    //Recur for the amount array. Note that it is guaranteed that the recursion would terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRecursion(amount);
}

//Given a set of persons as graph[] where graph[i][j] indicates the amount that person i needs to pay person j, this function finds and prints the minimum cash flow to settle all debts
void minCashFlow(vector<vector<int>> &graph)
{
    //Create an array amount[], initialize all value in it as 0
    vector<int> amount(number_of_persons, 0);
    
    //Calculate the net amount to be paid to person 'p' and stores it in amount[p]
    //The value of amount[p] can be calculated by subtracting debts of 'p' from credits of 'p'
    
    for(int p = 0; p < number_of_persons; p++)
    {
        for(int i = 0; i < number_of_persons; i++)
        {
            amount[p] += (graph[i][p] - graph[p][i]);
        }
    }
    
    minCashFlowRecursion(amount);
}

//Initial Display UI
void initialUI()
{
  system("clear");
  cout << "Welcome to the splitwise app";
  cout << "\nEnter the no. of people: ";
  cin >> number_of_persons;
}

//UI to take data from the users
void transactionUI(vector<vector<int>> &graph)
{
    int run = 1;
    while (run)
    {
      cout << "\nEnter user who pays: ";
      int payor;
      cin >> payor;
      cout << "Enter user who receives: ";
      int receiver;
      cin >> receiver;
      cout << "Enter amount to be paid: ";
      int payment;
      cin >> payment;
      graph[payor-1][receiver-1] += payment;

      cout << "Do you want to add another transaction? (Y/N) ";
      char input;
      cin >> input;
      while (input!='y' and input!='Y' and input!='n' and input!='N')
        {
          cout << "\nInvalid input, please re-enter you choice: ";
          cin >> input;
          if (input == 'y' or input == 'Y' or input == 'n' or input == 'N') break;
        }
      if (input == 'n' or input == 'N') 
      {
        run = 0;
        cout << "\n";
      }
    }
}
//Driver function
int main()
{
    //graph[i][j] indicates the amount that person i needs to pay person j
    initialUI();
    
    vector<vector<int>> graph(number_of_persons, vector<int> (number_of_persons, 0));

    transactionUI(graph);
    //print the solution
    minCashFlow(graph);
    
    return 0;
}