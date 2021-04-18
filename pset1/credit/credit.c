#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool luhn_check(long cc_number);
void cc_type(long cc_number);

int main(void)
{
    // Checks if a given credit card number is valid, and if so, what kind of
    // credit card it is.

    // Get the number.
    long cc_number = get_long("Number: ");

    // Perform a Luhn check.
    if (luhn_check(cc_number))
    {
        cc_type(cc_number);
    }
    // Failed the Luhn check.
    else
    {
        printf("INVALID\n");
    }
}

bool luhn_check(long cc_number)
{
    // Performs a Luhn check on a credit card number.
    // Initialize the check sum.
    int check_sum = 0;
    // Initialize the position, starting from the right.
    int position = 1;
    long divisor = 1;
    while (divisor < cc_number)
    {
        int digit = (cc_number / divisor) % 10;
        // If we are in an even position, we need to multiply by 2.
        if (position % 2 == 0)
        {
            digit *= 2;
        }
        if (digit < 10)
        {
            check_sum += digit;
        }
        else
        {
            check_sum += (digit % 10);
            // If the doubled number is two digits, the first digit must be 1.
            check_sum += 1;
        }
        position++;
        divisor *= 10;
    }
    return (check_sum % 10 == 0);
}

void cc_type(long cc_number)
{
    // Use log to determine the length of the number.
    int length = (int)(log10(cc_number) + 1);
    // Get the first two digits of the credit card number.
    int start = (int)(cc_number / pow(10, length - 2));
    // Amex is 15 digits long and starts with 34 or 37.
    if (length == 15 && (start == 34 || start == 37))
    {
        printf("AMEX\n");
    }
    // MasterCard is 16 digits long and starts 51-55.
    else if (length == 16 && (start >= 51 && start <= 55))
    {
        printf("MASTERCARD\n");
    }
    // Visa is either 13 or 16 digits long and starts with 4.
    else if ((length == 13 || length == 16) && (start >= 40 && start <= 49))
    {
        printf("VISA\n");
    }
    // Else, the card is invalid.
    else
    {
        printf("INVALID\n");
    }
}