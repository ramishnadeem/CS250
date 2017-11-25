#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

void AddCourses ( list<string>& courses )
{
    courses.push_front("CS 250");
    courses.push_front("CS 200");
    courses.push_front("CS 210");
    courses.push_front("CS 235");
    courses.push_front("CS 134");
    courses.push_front("CS 211");

}

void SortList ( list<string>& courses )
{
    courses.sort();
}

void ReverseList ( list<string>& courses )
{
    courses.reverse();
}

void DisplayCourses (list<string>& courses)
{
    int counter = 0;
    for( list<string >::iterator it = courses.begin();
        it != courses.end(); it++ )
    {
        if ( counter != 0 )
        {
            cout << " , ";
        }

        cout << counter++ << " . " << (*it); }
}


int main() {
    list<string> courses;

    AddCourses(courses);
    DisplayCourses(courses);
    cout << endl;
    SortList(courses);
    DisplayCourses(courses);
    cout << endl;
    ReverseList(courses);
    DisplayCourses(courses);
    cout << endl;


    return 0;
}