#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 3x3 array
    int cats[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    char move;
    vector<pair<int, int>> position = {{0, 0}}; // Initial position

    while (true) {
        cout << "Move: " << "\n" << endl;
        cin >> move;

        // Save old position for checking bounds
        int newX = position[0].first;
        int newY = position[0].second;

        // Determine new position based on the move
        switch (move) {
            case 'w': newX--; break;  // Move up
            case 's': newX++; break;  // Move down
            case 'a': newY--; break;  // Move left
            case 'd': newY++; break;  // Move right
            default: break;           // Invalid move
        }

        // Check bounds to prevent overflow
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            position[0].first = newX;
            position[0].second = newY;
            cout << "Moved to position (" << newX << ", " << newY << "), value: " << cats[newX][newY] << "\n";
        } else {
            cout << "Invalid move! Out of bounds.\n";
        }

        // Display current position
        cout << "Current position: (" << position[0].first << ", " << position[0].second << ")\n";
    }

    return 0;
}
