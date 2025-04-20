/*#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Structure for input buffer
struct EquationElement {
    char value;
    bool isExponent;
    bool isFraction;
};

// Buffer for user input
std::vector<EquationElement> equationBuffer;
int cursorPos = 0;
int screenStart = 0;
int xpos = 5, ypos = 20;

void setup() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
}

// Function to update the display
void updateScreen() {
    tft.fillScreen(TFT_BLACK);
    int x = 5, y = 20;

    for (int i = screenStart; i < equationBuffer.size(); i++) {
        EquationElement elem = equationBuffer[i];

        if (elem.isExponent) {
            tft.setTextSize(1);  // Smaller text for exponent
            tft.setCursor(x, y - 5);
        } else {
            tft.setTextSize(2);
            tft.setCursor(x, y);
        }

        if (elem.isFraction) {
            if (i > 0 && i < equationBuffer.size() - 1) {
                drawFraction(equationBuffer[i - 1].value, equationBuffer[i + 1].value, x, y);
                i++; // Skip denominator since it's already drawn
            }
        } else {
            tft.print(elem.value);
        }

        x += 12;
        if (x > 150) { // Move to next row
            x = 5;
            y += 20;
        }
    }

    // Draw cursor
    tft.fillRect(x, y + 5, 10, 2, TFT_WHITE);
}

// Function to draw fractions
void drawFraction(char numerator, char denominator, int x, int y) {
    tft.setCursor(x, y - 7);
    tft.setTextSize(1);
    tft.print(numerator);
    
    tft.drawLine(x - 2, y, x + 8, y, TFT_WHITE);  // Draw fraction bar
    
    tft.setCursor(x, y + 7);
    tft.print(denominator);
}

// Function to handle input
void addCharacter(char c) {
    EquationElement elem;
    elem.value = c;
    elem.isExponent = (c == '^');
    elem.isFraction = (c == '/');

    if (c == '/') {
        equationBuffer[equationBuffer.size() - 1].isFraction = true; // Mark numerator
    }

    equationBuffer.push_back(elem);
    cursorPos++;

    if (cursorPos >= 22) {
        screenStart++;
    }

    updateScreen();
}

// Function to handle backspace
void backspace() {
    if (cursorPos > 0) {
        equationBuffer.pop_back();
        cursorPos--;
        updateScreen();
    }
}

void loop() {
    // Simulate input for testing
    delay(1000);
    addCharacter('3');
    addCharacter('^');
    addCharacter('2');
    addCharacter('+');
    addCharacter('5');
    addCharacter('/');
    addCharacter('8');
    delay(3000);
    backspace();
    delay(3000);
}
*/