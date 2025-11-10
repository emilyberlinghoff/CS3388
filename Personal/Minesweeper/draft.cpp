#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // cout << "Welcome to Minesweeper!" << endl;

    // // Get input for dimensions
    // int width, height, mines;
    // cout << "Enter width: "; cin >> width;
    // cout << "Enter height: "; cin >> height;
    // cout << "Enter number of mines: "; cin >> mines;
    // cout << endl;

    // // For loop to print the column numbers
    // for (int i = 1; i <= 9; i++) { // center single-digit numbers
    //     cout << " " << i << " ";
    // }
    // for (int i = 10; i <= width; i++) { // no space in front to compensate for double-digits
    //     cout << " " << i;
    // }
    // cout << endl;

    // // 2D array to store the contents of the grid
    // for (int j = 0; j < height; j++) {
    //     for (int i = 0; i < width; i++) {
    //         arr[i][j] = "|__";
    //     }
    // }

    // // Print the grid with row numbers at the end
    // for (int j = 0; j < height; j++) {
    //     for (int i = 0; i < width; i++) {
    //         cout << arr[i][j]; // print the grid
    //     }
    //     cout << "| " << j + 1 << endl; // add an extra | and prints row numbers
    // }

    // Create actual grid with mines to compare user grid to
    // answer[width][height];
    // for (int j = 0; j < height; j++) {
    //     for (int i = 0; i < width; i++) {
    //         answer[i][j] = "  -";
    //     }
    // }

    // // For loop that iterates for the amount of mines
    // int i = 0;
    // while (i < mines) {
    //     int x = rand() %width;
    //     int y = rand() %height;

    //     // Check if there's aready a mine in the choosen spot and update the numbers around
    //     if (answer[x][y] != "  M") { // check if there's already a mine in the chosen spot
    //         answer[x][y] = "  M";

    //         // Update the numbers around
    //         // answer[x-1][y-1]
    //         if (answer[x-1][y-1] == "  -") {
    //             answer[x-1][y-1] = "  1";
    //         }
    //         else if (answer[x-1][y-1] == "  1") {
    //             answer[x-1][y-1] = "  2";
    //         }
    //         else if (answer[x-1][y-1] == "  2") {
    //             answer[x-1][y-1] = "  3";
    //         }
    //         else if (answer[x-1][y-1] == "  3") {
    //             answer[x-1][y-1] = "  4";
    //         }
    //         else if (answer[x-1][y-1] == "  4") {
    //             answer[x-1][y-1] = "  5";
    //         }
    //         else if (answer[x-1][y-1] == "  5") {
    //             answer[x-1][y-1] = "  6";
    //         }
    //         else if (answer[x-1][y-1] == "  6") {
    //             answer[x-1][y-1] = "  7";
    //         }
    //         else if (answer[x-1][y-1] == "  7") {
    //             answer[x-1][y-1] = "  8";
    //         }

    //         // answer[x-1][y]
    //         if (answer[x-1][y] == "  -") {
    //             answer[x-1][y] = "  1";
    //         }
    //         else if (answer[x-1][y] == "  1") {
    //             answer[x-1][y] = "  2";
    //         }
    //         else if (answer[x-1][y] == "  2") {
    //             answer[x-1][y] = "  3";
    //         }
    //         else if (answer[x-1][y] == "  3") {
    //             answer[x-1][y] = "  4";
    //         }
    //         else if (answer[x-1][y] == "  4") {
    //             answer[x-1][y] = "  5";
    //         }
    //         else if (answer[x-1][y] == "  5") {
    //             answer[x-1][y] = "  6";
    //         }
    //         else if (answer[x-1][y] == "  6") {
    //             answer[x-1][y] = "  7";
    //         }
    //         else if (answer[x-1][y] == "  7") {
    //             answer[x-1][y] = "  8";
    //         }

    //         // answer[x-1][y+1]
    //         if (answer[x-1][y+1] == "  -") {
    //             answer[x-1][y+1] = "  1";
    //         }
    //         else if (answer[x-1][y+1] == "  1") {
    //             answer[x-1][y+1] = "  2";
    //         }
    //         else if (answer[x-1][y+1] == "  2") {
    //             answer[x-1][y+1] = "  3";
    //         }
    //         else if (answer[x-1][y+1] == "  3") {
    //             answer[x-1][y+1] = "  4";
    //         }
    //         else if (answer[x-1][y+1] == "  4") {
    //             answer[x-1][y+1] = "  5";
    //         }
    //         else if (answer[x-1][y+1] == "  5") {
    //             answer[x-1][y+1] = "  6";
    //         }
    //         else if (answer[x-1][y+1] == "  6") {
    //             answer[x-1][y+1] = "  7";
    //         }
    //         else if (answer[x-1][y+1] == "  7") {
    //             answer[x-1][y+1] = "  8";
    //         }

    //         // answer[x][y-1]
    //         if (answer[x][y-1] == "  -") {
    //             answer[x][y-1] = "  1";
    //         }
    //         else if (answer[x][y-1] == "  1") {
    //             answer[x][y-1] = "  2";
    //         }
    //         else if (answer[x][y-1] == "  2") {
    //             answer[x][y-1] = "  3";
    //         }
    //         else if (answer[x][y-1] == "  3") {
    //             answer[x][y-1] = "  4";
    //         }
    //         else if (answer[x][y-1] == "  4") {
    //             answer[x][y-1] = "  5";
    //         }
    //         else if (answer[x][y-1] == "  5") {
    //             answer[x][y-1] = "  6";
    //         }
    //         else if (answer[x][y-1] == "  6") {
    //             answer[x][y-1] = "  7";
    //         }
    //         else if (answer[x][y-1] == "  7") {
    //             answer[x][y-1] = "  8";
    //         }

    //         // answer[x][y+1]
    //         if (answer[x][y+1] == "  -") {
    //             answer[x][y+1] = "  1";
    //         }
    //         else if (answer[x][y+1] == "  1") {
    //             answer[x][y+1] = "  2";
    //         }
    //         else if (answer[x][y+1] == "  2") {
    //             answer[x][y+1] = "  3";
    //         }
    //         else if (answer[x][y+1] == "  3") {
    //             answer[x][y+1] = "  4";
    //         }
    //         else if (answer[x][y+1] == "  4") {
    //             answer[x][y+1] = "  5";
    //         }
    //         else if (answer[x][y+1] == "  5") {
    //             answer[x][y+1] = "  6";
    //         }
    //         else if (answer[x][y+1] == "  6") {
    //             answer[x][y+1] = "  7";
    //         }
    //         else if (answer[x][y+1] == "  7") {
    //             answer[x][y+1] = "  8";
    //         }

    //         // answer[x+1][y-1]
    //         if (answer[x+1][y-1] == "  -") {
    //             answer[x+1][y-1] = "  1";
    //         }
    //         else if (answer[x+1][y-1] == "  1") {
    //             answer[x+1][y-1] = "  2";
    //         }
    //         else if (answer[x+1][y-1] == "  2") {
    //             answer[x+1][y-1] = "  3";
    //         }
    //         else if (answer[x+1][y-1] == "  3") {
    //             answer[x+1][y-1] = "  4";
    //         }
    //         else if (answer[x+1][y-1] == "  4") {
    //             answer[x+1][y-1] = "  5";
    //         }
    //         else if (answer[x+1][y-1] == "  5") {
    //             answer[x+1][y-1] = "  6";
    //         }
    //         else if (answer[x+1][y-1] == "  6") {
    //             answer[x+1][y-1] = "  7";
    //         }
    //         else if (answer[x+1][y-1] == "  7") {
    //             answer[x+1][y-1] = "  8";
    //         }

    //         // answer[x+1][y]
    //         if (answer[x+1][y] == "  -") {
    //             answer[x+1][y] = "  1";
    //         }
    //         else if (answer[x+1][y] == "  1") {
    //             answer[x+1][y] = "  2";
    //         }
    //         else if (answer[x+1][y] == "  2") {
    //             answer[x+1][y] = "  3";
    //         }
    //         else if (answer[x+1][y] == "  3") {
    //             answer[x+1][y] = "  4";
    //         }
    //         else if (answer[x+1][y] == "  4") {
    //             answer[x+1][y] = "  5";
    //         }
    //         else if (answer[x+1][y] == "  5") {
    //             answer[x+1][y] = "  6";
    //         }
    //         else if (answer[x+1][y] == "  6") {
    //             answer[x+1][y] = "  7";
    //         }
    //         else if (answer[x+1][y] == "  7") {
    //             answer[x+1][y] = "  8";
    //         }

    //         // answer[x+1][y+1]
    //         if (answer[x+1][y+1] == "  -") {
    //             answer[x+1][y+1] = "  1";
    //         }
    //         else if (answer[x+1][y+1] == "  1") {
    //             answer[x+1][y+1] = "  2";
    //         }
    //         else if (answer[x+1][y+1] == "  2") {
    //             answer[x+1][y+1] = "  3";
    //         }
    //         else if (answer[x+1][y+1] == "  3") {
    //             answer[x+1][y+1] = "  4";
    //         }
    //         else if (answer[x+1][y+1] == "  4") {
    //             answer[x+1][y+1] = "  5";
    //         }
    //         else if (answer[x+1][y+1] == "  5") {
    //             answer[x+1][y+1] = "  6";
    //         }
    //         else if (answer[x+1][y+1] == "  6") {
    //             answer[x+1][y+1] = "  7";
    //         }
    //         else if (answer[x+1][y+1] == "  7") {
    //             answer[x+1][y+1] = "  8";
    //         }

    //         i++;
    //     }
    // }
    // Print answer grid
    // Comment this out when not checking
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            cout << answer[i][j]; // print the grid
        }
        cout << "| " << j + 1 << endl; // add an extra | and prints row numbers
    }

    // Loop that asks for nexxt guess as long as user doesn't loose
    while(true) {
        int guessX, guessY;

        // Get user input for guesses
        cout << "Enter row for guess"; cin >> guessY;
        cout << "Enter column for guess"; cin >> guessX;
    }

    return 0;
}

// Function for getting next square to guess
    // Ask whether it's safe or flag

// Boolean to see whether they continue or loose

    // If continue, write the number of mines around that square
        // If 0, clear the 8 squares around and repeat steps for each square
    // Go back to function asking for next guess

    // If loose, go back to main menu

// Possble additions
    // Add levels easy, medium, hard, custom
    // Add hints that provides the value of a specified squared
        // Like when they pick a square and they say whether it safe or flag, add option for hint