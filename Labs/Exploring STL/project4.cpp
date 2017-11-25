#include <iostream>
#include <string>
#include <stack>
using namespace std;


int main()
{
    stack<string> sentence;
    bool done = false;
    cout << "Enter the next word of the sentence , or UNDO to undo , or DONE to stop ." << endl;
    while (!done)
    {
        string word;
        cout << ">> ";
        cin >> word;
        if (word == "UNDO")
        {
            sentence.pop();
        }
        else if (word == "DONE")
        {
            done = true;
        }
        else
        {
            sentence.push(word);
        }
    }
    cout << endl << endl << "Finished sentence: ";

    while (!sentence.empty())
    {
        cout << sentence.top() << " ";
        sentence.pop();
    }
}