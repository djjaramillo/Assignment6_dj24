
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"
#include <cmath>

using namespace std;

// Add a coordinate to the end of the list
void add_coordinate(Coordinate *list_end, float x, float y)
{
    Coordinate *new_coord = new Coordinate;

    new_coord->x = x;
    new_coord->y = y;

    Coordinate *current = list_end->previous;
    int max_id = 0;

    while (current->previous != nullptr)
    {
        if (current->coord_id > max_id)
        {
            max_id = current->coord_id;
        }

        current = current->previous;
    }

    new_coord->coord_id = max_id + 1;

    new_coord->next = list_end;
    new_coord->previous = list_end->previous;

    list_end->previous->next = new_coord;
    list_end->previous = new_coord;
}


// Display coordinates from beginning to end
void forward_display(Coordinate *list_beginning)
{
    Coordinate *current = list_beginning->next;

    cout << "\nForward Display:\n";

    while (current->next != nullptr)
    {
        cout << "ID: " << current->coord_id
             << " X: " << current->x
             << " Y: " << current->y << endl;

        current = current->next;
    }
}


// Display coordinates from end to beginning
void backward_display(Coordinate *list_end)
{
    Coordinate *current = list_end->previous;

    cout << "\nBackward Display:\n";

    while (current->previous != nullptr)
    {
        cout << "ID: " << current->coord_id
             << " X: " << current->x
             << " Y: " << current->y << endl;

        current = current->previous;
    }
}

// Delete a coordinate using its ID
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
    Coordinate *current = list_beginning->next;

    while (current->next != nullptr)
    {
        if (current->coord_id == coord_id_to_delete)
        {
            current->previous->next = current->next;
            current->next->previous = current->previous;


            delete current;

            cout << "\nCoordinate deleted.\n";
            return;
        }

        current = current->next;
    }

    cout << "\nCoordinate not found.\n";
}


// Count the number of coordinates
int list_length(Coordinate *list_beginning)
{
    int count = 0;

    Coordinate *current = list_beginning->next;

    while (current->next != nullptr)
    {
        count++;
        current = current->next;
    }

    return count;
}


// Find the closest coordinate to the given x and y
void closest_to(Coordinate *list_beginning, float x, float y)
{
    Coordinate *current = list_beginning->next;

    if (current->next == nullptr)
    {
        cout << "\nList is empty.\n";
        return;
    }

    Coordinate *closest = current;

    float min_distance = sqrt(pow(current->x - x, 2)
                            + pow(current->y - y, 2));

    current = current->next;

    while (current->next != nullptr)
    {
        float distance = sqrt(pow(current->x - x, 2)
                            + pow(current->y - y, 2));

        if (distance < min_distance)
        {
            min_distance = distance;
            closest = current;
        }

        current = current->next;
    }
    cout << "\nClosest Coordinate:\n";
    cout << "ID: " << closest->coord_id << endl;
    cout << "X: " << closest->x << endl;
    cout << "Y: " << closest->y << endl;
    cout << "Distance: " << min_distance << endl;
}





int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        cout << "Usage: ./main <number>" << endl;
        return 1;
    }

    int num = atoi(argv[1]);

    if (num <= 0)
    {
        cout << "Enter a positive number." << endl;
        return 1;
    }

    srand(time(0));

    // Create beginning and end nodes
    Coordinate *list_beginning = new Coordinate;
    Coordinate *list_end = new Coordinate;

    list_beginning->previous = nullptr;
    list_beginning->next = list_end;

    list_end->previous = list_beginning;
    list_end->next = nullptr;

    // Generate random coordinates
    for (int i = 0; i < num; i++)
    {
        float x = rand() % 100;
        float y = rand() % 100;

        add_coordinate(list_end, x, y);
    }

    // Display list forward
    forward_display(list_beginning);

    // Display list backward
    backward_display(list_end);

    // Display length
    cout << "\nList Length: "
         << list_length(list_beginning) << endl;

    // Find closest coordinate to (50, 50)
    closest_to(list_beginning, 50, 50);

    // Delete coordinate with ID 1
    delete_coordinate(list_beginning, 1);

    // Display updated list
    forward_display(list_beginning);

    cout << "\nUpdated List Length: "
         << list_length(list_beginning) << endl;

    // Free all allocated memory
    Coordinate *current = list_beginning;

    while (current != nullptr)
    {
        Coordinate *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
