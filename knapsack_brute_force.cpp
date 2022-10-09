#include "iostream"
#include "cmath"
#include "Rcpp.h"
using namespace Rcpp;



// set_of_weight is a vector of weights, set_of_profit is a vector of profits, and W_max is the maximum weight inputted
// from R IDE. And the function returns the maximum profit that can be obtained from the given set of weights and profits.
// [[Rcpp::export]]

double bruteforce_knapsack(NumericMatrix set_of_weight, NumericMatrix set_of_profit, int W_max, int R_number)
{
    int k, j, total_profit, total_weight, max_weight, max_profit, max_set[R_number];
    int set_counter;

    // Number of possible combinations
    int number_of_subsets = pow(2.0, R_number);


    total_profit = 0;
    total_weight = 0;
    max_weight = 0;
    max_profit = 0;
    //set_counter is the counter for the number of subsets
    set_counter = 0;

    // k is the counter for the number of bits in the binary number
    for(k=0; k<number_of_subsets; k++)
    {
        //std::cout << "k = " << k << std::endl;
        //R_number is the number of items from R IDE
        for (j = 0; j < R_number; j++) {
        //This loop calculates the total weight of the items to be included in the knapsack
        //std::cout << "j = " << j << std::endl;
        //use left shift operator to check for set membership and it's much faster
            if ((1 << j) & k) {
                set_counter++;
                total_profit = total_profit + set_of_profit[j];
                total_weight = total_weight + set_of_weight[j];
                //setting the counter
                max_set[set_counter - 1] = j + 1;
            }
        }
        //std::cout << "set_counter: " << set_counter << std::endl;
        //std::cout << "total_profit: " << total_profit << std::endl;

        if(total_weight <= W_max)
        //If the total weight is greater than the maximum weight, then the total profit is set to zero.

        {
            //This if statement checks the value of the total profit and updates the maximum profit and maximum weight
            if(total_profit >= max_profit)
            {
                //why don't we calculate the difference between total_profit and max_weight?
                max_weight = total_weight;
                max_profit = total_profit;
            }
        }
        // reset the counters to prepare for next set
        total_profit = 0;
        total_weight = 0;
        set_counter = 0;
    }

    return max_profit;

}
