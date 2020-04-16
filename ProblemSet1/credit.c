// check the validity and type of a credit card number using Luhn's Algorithm

#include <cs50.h>
#include <stdio.h>

int sum_of_even_digits_x2(long);
int sum_of_odd_digits(long);
bool is_valid(long);
int get_ones(int);
int get_tens(int);

int main(void)
{
    long card_number = get_long("Number: "); 

    bool valid = is_valid(card_number);
    if (valid)
    {
        printf("Valid\n");
    }
    else 
    {
        printf("Invalid\n");
    }
}

bool is_valid(long num)
{
    int sum = 0;
    sum += sum_of_even_digits_x2(num);
    sum += sum_of_odd_digits(num);

    if (sum % 10 == 0) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// extract all even digits, double them, and sum their digits
int sum_of_even_digits_x2(long num)
{
    // find all the even digits x2
    int sum_of_evens_x2 = 0; 

    // this loop extracts all even position digits
    // multiplies that digit by 2 and then
    // adds the digits of the mulitple of two for each even position
    for (long i = 10; i < 100000000000000000; i*=100)
    {
        int digit = (num / i) % 10; 
        sum_of_evens_x2 += get_ones(digit * 2); 
        sum_of_evens_x2 += get_tens(digit * 2);
    }

    return sum_of_evens_x2;
}

// extract all odd digits and sum them
int sum_of_odd_digits(long num)
{
    // find all the even digits
    int sum_of_odds = 0; 

    // this loop extracts all odd position digits
    // and sums them
    for (long i = 1; i < 100000000000000000; i*=100)
    {
        int digit = (num / i) % 10;
        sum_of_odds += digit; 
    }

    return sum_of_odds;
}



int get_ones(int num)
{
    return num % 10; 
}

int get_tens(int num)
{
    return (num / 10) % 10; 
}
