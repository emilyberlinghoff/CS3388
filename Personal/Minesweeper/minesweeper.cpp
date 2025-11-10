#include <iostream>
#include <cstdlib>
using namespace std;

int main() {

    // Welcome screen
    cout << "Welcome to Minesweeper!" << endl;
    // Get input for dimensions
    int width, height, mines;
    cout << "Enter width: "; cin >> width;
    cout << "Enter height: "; cin >> height;
    cout << "Enter number of mines: "; cin >> mines;
    cout << endl;

    // Answer grid
    string answer[width][height];
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            answer[i][j] = "   ";
        }
    }
    // For loop that places the mines
    int i = 0;
    while (i < mines) {
        int x = rand()%width;
        int y = rand()%height;
        // Check if there's already a mine in the chosen spot
        if (answer[x][y] != "  M") {
            answer[x][y] = "  M"; i++;
            // Update the numbers around
            // If square is on the edge, don't update all the numbers around because it'll loop around
            // Top left corner
            if ((x == 0) && (y == 0)) {
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
                if (answer[x+1][y+1] == "   ") {
                    answer[x+1][y+1] = "  1";
                }
                else if (answer[x+1][y+1] == "  1") {
                    answer[x+1][y+1] = "  2";
                }
                else if (answer[x+1][y+1] == "  2") {
                    answer[x+1][y+1] = "  3";
                }
                else if (answer[x+1][y+1] == "  3") {
                    answer[x+1][y+1] = "  4";
                }
                else if (answer[x+1][y+1] == "  4") {
                    answer[x+1][y+1] = "  5";
                }
                else if (answer[x+1][y+1] == "  5") {
                    answer[x+1][y+1] = "  6";
                }
                else if (answer[x+1][y+1] == "  6") {
                    answer[x+1][y+1] = "  7";
                }
                else if (answer[x+1][y+1] == "  7") {
                    answer[x+1][y+1] = "  8";
                }
            }
            // Top right corner
            else if ((x == width-1) && (y == 0)) {
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x-1][y+1] == "   ") {
                    answer[x-1][y+1] = "  1";
                }
                else if (answer[x-1][y+1] == "  1") {
                    answer[x-1][y+1] = "  2";
                }
                else if (answer[x-1][y+1] == "  2") {
                    answer[x-1][y+1] = "  3";
                }
                else if (answer[x-1][y+1] == "  3") {
                    answer[x-1][y+1] = "  4";
                }
                else if (answer[x-1][y+1] == "  4") {
                    answer[x-1][y+1] = "  5";
                }
                else if (answer[x-1][y+1] == "  5") {
                    answer[x-1][y+1] = "  6";
                }
                else if (answer[x-1][y+1] == "  6") {
                    answer[x-1][y+1] = "  7";
                }
                else if (answer[x-1][y+1] == "  7") {
                    answer[x-1][y+1] = "  8";
                }
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
            }
            // Bottom left corner
            else if ((x == 0) && (y == height-1)) {
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
                if (answer[x+1][y-1] == "   ") {
                    answer[x+1][y-1] = "  1";
                }
                else if (answer[x+1][y-1] == "  1") {
                    answer[x+1][y-1] = "  2";
                }
                else if (answer[x+1][y-1] == "  2") {
                    answer[x+1][y-1] = "  3";
                }
                else if (answer[x+1][y-1] == "  3") {
                    answer[x+1][y-1] = "  4";
                }
                else if (answer[x+1][y-1] == "  4") {
                    answer[x+1][y-1] = "  5";
                }
                else if (answer[x+1][y-1] == "  5") {
                    answer[x+1][y-1] = "  6";
                }
                else if (answer[x+1][y-1] == "  6") {
                    answer[x+1][y-1] = "  7";
                }
                else if (answer[x+1][y-1] == "  7") {
                    answer[x+1][y-1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
            }
            // Bottom right corner
            else if ((x == width-1) && (y == height-1)) {
                if (answer[x-1][y-1] == "   ") {
                    answer[x-1][y-1] = "  1";
                }
                else if (answer[x-1][y-1] == "  1") {
                    answer[x-1][y-1] = "  2";
                }
                else if (answer[x-1][y-1] == "  2") {
                    answer[x-1][y-1] = "  3";
                }
                else if (answer[x-1][y-1] == "  3") {
                    answer[x-1][y-1] = "  4";
                }
                else if (answer[x-1][y-1] == "  4") {
                    answer[x-1][y-1] = "  5";
                }
                else if (answer[x-1][y-1] == "  5") {
                    answer[x-1][y-1] = "  6";
                }
                else if (answer[x-1][y-1] == "  6") {
                    answer[x-1][y-1] = "  7";
                }
                else if (answer[x-1][y-1] == "  7") {
                    answer[x-1][y-1] = "  8";
                }
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
            }
            // Left column
            else if (x == 0) {
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
                if (answer[x+1][y-1] == "   ") {
                    answer[x+1][y-1] = "  1";
                }
                else if (answer[x+1][y-1] == "  1") {
                    answer[x+1][y-1] = "  2";
                }
                else if (answer[x+1][y-1] == "  2") {
                    answer[x+1][y-1] = "  3";
                }
                else if (answer[x+1][y-1] == "  3") {
                    answer[x+1][y-1] = "  4";
                }
                else if (answer[x+1][y-1] == "  4") {
                    answer[x+1][y-1] = "  5";
                }
                else if (answer[x+1][y-1] == "  5") {
                    answer[x+1][y-1] = "  6";
                }
                else if (answer[x+1][y-1] == "  6") {
                    answer[x+1][y-1] = "  7";
                }
                else if (answer[x+1][y-1] == "  7") {
                    answer[x+1][y-1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
                if (answer[x+1][y+1] == "   ") {
                    answer[x+1][y+1] = "  1";
                }
                else if (answer[x+1][y+1] == "  1") {
                    answer[x+1][y+1] = "  2";
                }
                else if (answer[x+1][y+1] == "  2") {
                    answer[x+1][y+1] = "  3";
                }
                else if (answer[x+1][y+1] == "  3") {
                    answer[x+1][y+1] = "  4";
                }
                else if (answer[x+1][y+1] == "  4") {
                    answer[x+1][y+1] = "  5";
                }
                else if (answer[x+1][y+1] == "  5") {
                    answer[x+1][y+1] = "  6";
                }
                else if (answer[x+1][y+1] == "  6") {
                    answer[x+1][y+1] = "  7";
                }
                else if (answer[x+1][y+1] == "  7") {
                    answer[x+1][y+1] = "  8";
                }
            }
            // Top row
            else if (y == 0) {
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x-1][y+1] == "   ") {
                    answer[x-1][y+1] = "  1";
                }
                else if (answer[x-1][y+1] == "  1") {
                    answer[x-1][y+1] = "  2";
                }
                else if (answer[x-1][y+1] == "  2") {
                    answer[x-1][y+1] = "  3";
                }
                else if (answer[x-1][y+1] == "  3") {
                    answer[x-1][y+1] = "  4";
                }
                else if (answer[x-1][y+1] == "  4") {
                    answer[x-1][y+1] = "  5";
                }
                else if (answer[x-1][y+1] == "  5") {
                    answer[x-1][y+1] = "  6";
                }
                else if (answer[x-1][y+1] == "  6") {
                    answer[x-1][y+1] = "  7";
                }
                else if (answer[x-1][y+1] == "  7") {
                    answer[x-1][y+1] = "  8";
                }
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
                if (answer[x+1][y+1] == "   ") {
                    answer[x+1][y+1] = "  1";
                }
                else if (answer[x+1][y+1] == "  1") {
                    answer[x+1][y+1] = "  2";
                }
                else if (answer[x+1][y+1] == "  2") {
                    answer[x+1][y+1] = "  3";
                }
                else if (answer[x+1][y+1] == "  3") {
                    answer[x+1][y+1] = "  4";
                }
                else if (answer[x+1][y+1] == "  4") {
                    answer[x+1][y+1] = "  5";
                }
                else if (answer[x+1][y+1] == "  5") {
                    answer[x+1][y+1] = "  6";
                }
                else if (answer[x+1][y+1] == "  6") {
                    answer[x+1][y+1] = "  7";
                }
                else if (answer[x+1][y+1] == "  7") {
                    answer[x+1][y+1] = "  8";
                }
            }
            // Right column
            else if (x == width-1) {
                if (answer[x-1][y-1] == "   ") {
                    answer[x-1][y-1] = "  1";
                }
                else if (answer[x-1][y-1] == "  1") {
                    answer[x-1][y-1] = "  2";
                }
                else if (answer[x-1][y-1] == "  2") {
                    answer[x-1][y-1] = "  3";
                }
                else if (answer[x-1][y-1] == "  3") {
                    answer[x-1][y-1] = "  4";
                }
                else if (answer[x-1][y-1] == "  4") {
                    answer[x-1][y-1] = "  5";
                }
                else if (answer[x-1][y-1] == "  5") {
                    answer[x-1][y-1] = "  6";
                }
                else if (answer[x-1][y-1] == "  6") {
                    answer[x-1][y-1] = "  7";
                }
                else if (answer[x-1][y-1] == "  7") {
                    answer[x-1][y-1] = "  8";
                }
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x-1][y+1] == "   ") {
                    answer[x-1][y+1] = "  1";
                }
                else if (answer[x-1][y+1] == "  1") {
                    answer[x-1][y+1] = "  2";
                }
                else if (answer[x-1][y+1] == "  2") {
                    answer[x-1][y+1] = "  3";
                }
                else if (answer[x-1][y+1] == "  3") {
                    answer[x-1][y+1] = "  4";
                }
                else if (answer[x-1][y+1] == "  4") {
                    answer[x-1][y+1] = "  5";
                }
                else if (answer[x-1][y+1] == "  5") {
                    answer[x-1][y+1] = "  6";
                }
                else if (answer[x-1][y+1] == "  6") {
                    answer[x-1][y+1] = "  7";
                }
                else if (answer[x-1][y+1] == "  7") {
                    answer[x-1][y+1] = "  8";
                }
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
            }
            // Bottom row
            else if (y == height-1) {
                if (answer[x-1][y-1] == "   ") {
                    answer[x-1][y-1] = "  1";
                }
                else if (answer[x-1][y-1] == "  1") {
                    answer[x-1][y-1] = "  2";
                }
                else if (answer[x-1][y-1] == "  2") {
                    answer[x-1][y-1] = "  3";
                }
                else if (answer[x-1][y-1] == "  3") {
                    answer[x-1][y-1] = "  4";
                }
                else if (answer[x-1][y-1] == "  4") {
                    answer[x-1][y-1] = "  5";
                }
                else if (answer[x-1][y-1] == "  5") {
                    answer[x-1][y-1] = "  6";
                }
                else if (answer[x-1][y-1] == "  6") {
                    answer[x-1][y-1] = "  7";
                }
                else if (answer[x-1][y-1] == "  7") {
                    answer[x-1][y-1] = "  8";
                }
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
                if (answer[x+1][y-1] == "   ") {
                    answer[x+1][y-1] = "  1";
                }
                else if (answer[x+1][y-1] == "  1") {
                    answer[x+1][y-1] = "  2";
                }
                else if (answer[x+1][y-1] == "  2") {
                    answer[x+1][y-1] = "  3";
                }
                else if (answer[x+1][y-1] == "  3") {
                    answer[x+1][y-1] = "  4";
                }
                else if (answer[x+1][y-1] == "  4") {
                    answer[x+1][y-1] = "  5";
                }
                else if (answer[x+1][y-1] == "  5") {
                    answer[x+1][y-1] = "  6";
                }
                else if (answer[x+1][y-1] == "  6") {
                    answer[x+1][y-1] = "  7";
                }
                else if (answer[x+1][y-1] == "  7") {
                    answer[x+1][y-1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
            }
            // Rest of the squares
            else {
                if (answer[x-1][y-1] == "   ") {
                    answer[x-1][y-1] = "  1";
                }
                else if (answer[x-1][y-1] == "  1") {
                    answer[x-1][y-1] = "  2";
                }
                else if (answer[x-1][y-1] == "  2") {
                    answer[x-1][y-1] = "  3";
                }
                else if (answer[x-1][y-1] == "  3") {
                    answer[x-1][y-1] = "  4";
                }
                else if (answer[x-1][y-1] == "  4") {
                    answer[x-1][y-1] = "  5";
                }
                else if (answer[x-1][y-1] == "  5") {
                    answer[x-1][y-1] = "  6";
                }
                else if (answer[x-1][y-1] == "  6") {
                    answer[x-1][y-1] = "  7";
                }
                else if (answer[x-1][y-1] == "  7") {
                    answer[x-1][y-1] = "  8";
                }
                if (answer[x-1][y] == "   ") {
                    answer[x-1][y] = "  1";
                }
                else if (answer[x-1][y] == "  1") {
                    answer[x-1][y] = "  2";
                }
                else if (answer[x-1][y] == "  2") {
                    answer[x-1][y] = "  3";
                }
                else if (answer[x-1][y] == "  3") {
                    answer[x-1][y] = "  4";
                }
                else if (answer[x-1][y] == "  4") {
                    answer[x-1][y] = "  5";
                }
                else if (answer[x-1][y] == "  5") {
                    answer[x-1][y] = "  6";
                }
                else if (answer[x-1][y] == "  6") {
                    answer[x-1][y] = "  7";
                }
                else if (answer[x-1][y] == "  7") {
                    answer[x-1][y] = "  8";
                }
                if (answer[x-1][y+1] == "   ") {
                    answer[x-1][y+1] = "  1";
                }
                else if (answer[x-1][y+1] == "  1") {
                    answer[x-1][y+1] = "  2";
                }
                else if (answer[x-1][y+1] == "  2") {
                    answer[x-1][y+1] = "  3";
                }
                else if (answer[x-1][y+1] == "  3") {
                    answer[x-1][y+1] = "  4";
                }
                else if (answer[x-1][y+1] == "  4") {
                    answer[x-1][y+1] = "  5";
                }
                else if (answer[x-1][y+1] == "  5") {
                    answer[x-1][y+1] = "  6";
                }
                else if (answer[x-1][y+1] == "  6") {
                    answer[x-1][y+1] = "  7";
                }
                else if (answer[x-1][y+1] == "  7") {
                    answer[x-1][y+1] = "  8";
                }
                if (answer[x][y-1] == "   ") {
                    answer[x][y-1] = "  1";
                }
                else if (answer[x][y-1] == "  1") {
                    answer[x][y-1] = "  2";
                }
                else if (answer[x][y-1] == "  2") {
                    answer[x][y-1] = "  3";
                }
                else if (answer[x][y-1] == "  3") {
                    answer[x][y-1] = "  4";
                }
                else if (answer[x][y-1] == "  4") {
                    answer[x][y-1] = "  5";
                }
                else if (answer[x][y-1] == "  5") {
                    answer[x][y-1] = "  6";
                }
                else if (answer[x][y-1] == "  6") {
                    answer[x][y-1] = "  7";
                }
                else if (answer[x][y-1] == "  7") {
                    answer[x][y-1] = "  8";
                }
                if (answer[x][y+1] == "   ") {
                    answer[x][y+1] = "  1";
                }
                else if (answer[x][y+1] == "  1") {
                    answer[x][y+1] = "  2";
                }
                else if (answer[x][y+1] == "  2") {
                    answer[x][y+1] = "  3";
                }
                else if (answer[x][y+1] == "  3") {
                    answer[x][y+1] = "  4";
                }
                else if (answer[x][y+1] == "  4") {
                    answer[x][y+1] = "  5";
                }
                else if (answer[x][y+1] == "  5") {
                    answer[x][y+1] = "  6";
                }
                else if (answer[x][y+1] == "  6") {
                    answer[x][y+1] = "  7";
                }
                else if (answer[x][y+1] == "  7") {
                    answer[x][y+1] = "  8";
                }
                if (answer[x+1][y-1] == "   ") {
                    answer[x+1][y-1] = "  1";
                }
                else if (answer[x+1][y-1] == "  1") {
                    answer[x+1][y-1] = "  2";
                }
                else if (answer[x+1][y-1] == "  2") {
                    answer[x+1][y-1] = "  3";
                }
                else if (answer[x+1][y-1] == "  3") {
                    answer[x+1][y-1] = "  4";
                }
                else if (answer[x+1][y-1] == "  4") {
                    answer[x+1][y-1] = "  5";
                }
                else if (answer[x+1][y-1] == "  5") {
                    answer[x+1][y-1] = "  6";
                }
                else if (answer[x+1][y-1] == "  6") {
                    answer[x+1][y-1] = "  7";
                }
                else if (answer[x+1][y-1] == "  7") {
                    answer[x+1][y-1] = "  8";
                }
                if (answer[x+1][y] == "   ") {
                    answer[x+1][y] = "  1";
                }
                else if (answer[x+1][y] == "  1") {
                    answer[x+1][y] = "  2";
                }
                else if (answer[x+1][y] == "  2") {
                    answer[x+1][y] = "  3";
                }
                else if (answer[x+1][y] == "  3") {
                    answer[x+1][y] = "  4";
                }
                else if (answer[x+1][y] == "  4") {
                    answer[x+1][y] = "  5";
                }
                else if (answer[x+1][y] == "  5") {
                    answer[x+1][y] = "  6";
                }
                else if (answer[x+1][y] == "  6") {
                    answer[x+1][y] = "  7";
                }
                else if (answer[x+1][y] == "  7") {
                    answer[x+1][y] = "  8";
                }
                if (answer[x+1][y+1] == "   ") {
                    answer[x+1][y+1] = "  1";
                }
                else if (answer[x+1][y+1] == "  1") {
                    answer[x+1][y+1] = "  2";
                }
                else if (answer[x+1][y+1] == "  2") {
                    answer[x+1][y+1] = "  3";
                }
                else if (answer[x+1][y+1] == "  3") {
                    answer[x+1][y+1] = "  4";
                }
                else if (answer[x+1][y+1] == "  4") {
                    answer[x+1][y+1] = "  5";
                }
                else if (answer[x+1][y+1] == "  5") {
                    answer[x+1][y+1] = "  6";
                }
                else if (answer[x+1][y+1] == "  6") {
                    answer[x+1][y+1] = "  7";
                }
                else if (answer[x+1][y+1] == "  7") {
                    answer[x+1][y+1] = "  8";
                }
            }
        }
    }

    // Calculate how many squares are safe
    int safeSquares = (width*height) - mines;

    // 2D array to store the contents of the grid
    string arr[width][height];
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            arr[i][j] = "|__";
        }
    }

    // Loop that asks for the next guess as long as user doesn't loose
    while(safeSquares > 0) {
        // Print grid
        // For loop to print the column numbers
        for (int i = 1; i <= 9; i++) { // center single-digit numbers
            cout << " " << i << " ";
        }
        for (int i = 10; i <= width; i++) { // no space after to compensate for double-digits
            cout << " " << i;
        }
        cout << endl;
        // Print the grid with row numbers at the end
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                cout << arr[i][j]; // print the grid
            }
            cout << "| " << j + 1 << endl; // add an extra | and prints row numbers
        }

        // Get user input for guesses
        int guessX, guessY;
        cout << "Enter row for guess: "; cin >> guessY;
        cout << "Enter column for guess: "; cin >> guessX;
        guessX -= 1;
        guessY -= 1;
        while (arr[guessX][guessY] != "|__") {
            cout << "Already entered. Try again.\n";
            cout << "Enter row for guess: "; cin >> guessY;
            cout << "Enter column for guess: "; cin >> guessX;
        }
        safeSquares -= 1;
        // Check if there's a mine
        if (answer[guessX][guessY] == "  M") {
            cout << "You loose!\n";
            // Print answer grid to see where they went wrong
            for (int i = 1; i <= 9; i++) { // center single-digit numbers
                cout << " " << i << " ";
            }
            for (int i = 10; i <= width; i++) { // no space after to compensate for double-digits
                cout << " " << i;
            }
            cout << endl;
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    cout << answer[i][j]; // print the grid
                }
                cout << "| " << j + 1 << endl; // add an extra | and prints row numbers
            }
            break;
        }
        // Update cell from answer grid
        arr[guessX][guessY] = answer[guessX][guessY];
        // If square is empty, show the squares around it
        // while (arr[guessX][guessY] == "   ") {
        //     // If square is on the edge, don't show all the numbers around because it'll loop around
        //     // Top left corner
        //     if ((guessX == 0) && (guessY == 0)) {
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY+1] = answer[guessX+1][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else if (arr[guessX+1][guessY+1] == "   ") {
        //             guessX += 1;
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Top right corner
        //     else if ((guessX == width-1) && (guessY == 0)) {
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY+1] = answer[guessX-1][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX-1][guessY+1] == "   ") {
        //             guessX -= 1;
        //             guessY += 1;
        //         }
        //         else if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Bottom left corner
        //     else if ((guessX == 0) && (guessY == height-1)) {
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY-1] = answer[guessX+1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY-1] == "   ") {
        //             guessX += 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Bottom right corner
        //     else if ((guessX == width-1) && (guessY == height-1)) {
        //         arr[guessX-1][guessY-1] = answer[guessX-1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY-1] == "   ") {
        //             guessX -= 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Top row
        //     else if (guessY == 0) {
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY+1] = answer[guessX-1][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY+1] = answer[guessX+1][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX-1][guessY+1] == "   ") {
        //             guessX -= 1;
        //             guessY += 1;
        //         }
        //         else if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else if (arr[guessX+1][guessY+1] == "   ") {
        //             guessX += 1;
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Left side
        //     else if (guessX == 0) {
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY-1] = answer[guessX+1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY+1] = answer[guessX+1][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else if (arr[guessX+1][guessY-1] == "   ") {
        //             guessX += 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else if (arr[guessX+1][guessY+1] == "   ") {
        //             guessX += 1;
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Right side
        //     else if (guessX == width-1) {
        //         arr[guessX-1][guessY-1] = answer[guessX-1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY+1] = answer[guessX-1][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY-1] == "   ") {
        //             guessX -= 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX-1][guessY+1] == "   ") {
        //             guessX -= 1;
        //             guessY += 1;
        //         }
        //         else if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Bottom row
        //     else if (guessY == height-1) {
        //         arr[guessX-1][guessY-1] = answer[guessX-1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY-1] = answer[guessX+1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY-1] == "   ") {
        //             guessX -= 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY-1] == "   ") {
        //             guessX += 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        //     // Rest of the squares
        //     else {
        //         arr[guessX-1][guessY-1] = answer[guessX-1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY] = answer[guessX-1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX-1][guessY+1] = answer[guessX-1][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY-1] = answer[guessX][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX][guessY+1] = answer[guessX][guessY+1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY-1] = answer[guessX+1][guessY-1];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY] = answer[guessX+1][guessY];
        //         safeSquares -= 1;
        //         arr[guessX+1][guessY+1] = answer[guessX+1][guessY+1];
        //         safeSquares -= 1;
        //         if (arr[guessX-1][guessY-1] == "   ") {
        //             guessX -= 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX-1][guessY] == "   ") {
        //             guessX -= 1;
        //         }
        //         else if (arr[guessX-1][guessY+1] == "   ") {
        //             guessX -= 1;
        //             guessY += 1;
        //         }
        //         else if (arr[guessX][guessY-1] == "   ") {
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX][guessY+1] == "   ") {
        //             guessY += 1;
        //         }
        //         else if (arr[guessX+1][guessY-1] == "   ") {
        //             guessX += 1;
        //             guessY -= 1;
        //         }
        //         else if (arr[guessX+1][guessY] == "   ") {
        //             guessX += 1;
        //         }
        //         else if (arr[guessX+1][guessY+1] == "   ") {
        //             guessX += 1;
        //             guessY += 1;
        //         }
        //         else {
        //             break;
        //         }
        //     }
        // }
    }

    // If all safe squares were found, they win
    if (safeSquares == 0) {
        cout << "You win!\n";
        // Print answer grid
        for (int i = 1; i <= 9; i++) { // center single-digit numbers
            cout << " " << i << " ";
        }
        for (int i = 10; i <= width; i++) { // no space after to compensate for double-digits
            cout << " " << i;
        }
        cout << endl;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                cout << answer[i][j]; // print the grid
            }
            cout << "| " << j + 1 << endl; // add an extra | and prints row numbers
        }
    }
    return 0;
}