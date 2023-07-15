// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    // The tax should be added to the bill amount before calculating the tip. Finally, you will return exactly half of the full amount, including the bill amount, the tax and the tip.
    tax = tax / 100.0;
    bill += (bill * tax);
    bill += (bill * ((float)tip / 100.0));
    return (bill / 2.0);
}
