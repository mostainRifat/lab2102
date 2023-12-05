#include <iostream>

using namespace std;

// Function to count the number of set bits in an integer
int countSetBits(int n)
{
    int count = 0;
    while (n > 0)
    {
        if ((n & 1) == 1)
        {
            count++;
        }
        n >>= 1; // Shift n to the right by 1 bit
    }
    return count;
}

// Function to count set bits from lower limit A to upper limit B
int countSetBitsRange(int A, int B)
{
    // Check if A and B are valid inputs
    if (A < 0 || B < 0 || A > B)
    {
        return -1; // Error condition
    }

    int totalSetBits = 0;
    for (int i = A; i <= B; i++)
    {
        totalSetBits += countSetBits(i);
    }
    return totalSetBits;
}

int main()
{
    int A, B;

    cout << "Enter lower limit A: ";
    cin >> A;

    cout << "Enter upper limit B: ";
    cin >> B;

    int result = countSetBitsRange(A, B);

    if (result == -1)
    {
        cout << "Error: Invalid input" << endl;
    }
    else
    {
        cout << "Total set bits from " << A << " to " << B << ": " << result << endl;
    }

    return 0;
}
