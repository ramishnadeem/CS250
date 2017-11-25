#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    float balance = 0.0;
    cout << "Current Balance: "  << balance << endl;
    queue<float> transactions;

    transactions.push(100.42);
    transactions.push(-5.58);
    transactions.push(50.78);
    transactions.push(-20.50);

    while (!transactions.empty())
    {
        cout << transactions.front() << " Pushed to account "<< endl;
        balance = transactions.front() + balance;
        transactions.pop();
    }

    cout << "Final Balance: $" << balance;


    return 0;
}