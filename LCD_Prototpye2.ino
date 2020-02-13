
/*
|| @version 1.0
|| @author Peter Hager
|| @contact peter.hager@ph-ooe.at
||
|| @description
|| | Labyrinth demo
|| | TO DO: 
|| | 1. format output properly, no umlaute so far, no printing column by column
|| | 2. only check if the riddle has been solved when keying in '0'
|| | 3. display the maze by adjusting the cursor accordingly
|| | 4. create an interface to feed to program with different mazes
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//initialize LCD module
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//initialize demo labyrinth
//start at: 1/0, end at; 1/6, follow the path consisting of 0s
//control: up = 2, down = 8; left = 4, right = 6; OK = 0

  const int LEN = 7;
  int matrix[LEN][LEN] = {
    {1,1,1,1,1,1,1},
    {0,0,1,1,0,0,0},
    {1,0,1,1,0,1,1},
    {1,0,1,1,0,1,1},
    {1,0,1,1,0,1,1},
    {1,0,0,0,0,1,1},
    {1,1,1,1,1,1,1}
  };
  
  int startRow = 1;
  int startCol = 0;
  
  int finRow = 1;
  int finCol = 6;

  bool isCorrect = true;

void setup(){
  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("Gib den richtigen Pfad ein: ");
}
  
void loop(){

  if (isCorrect) {
    
    char customKey = customKeypad.getKey();
    
    isCorrect = checkIfMazeIsSolved(customKey);

    if (!isCorrect) {
      lcd.clear();
      lcd.print("Schade! Raetsel leider nicht geloest!");
    }
  }
}

bool checkIfMazeIsSolved(char customKey) {
  if (customKey == '2' || customKey == '8' || customKey == '4' || customKey == '6') {
      lcd.print(customKey);

      if ((customKey == '2') && (startRow-1 >= 0)) {       
        startRow--;
      }
      else if ((customKey == '8') && (startRow+1 < LEN)) {       
        startRow++;
      }
      else if ((customKey == '4') && (startCol-1 >= 0)) {       
        startCol--;
      }
      else if ((customKey == '6') && (startCol+1 < LEN)) {       
        startCol++;
      }
      else {
        return false;
      }
    
      if ((startRow == finRow) && (startCol == finCol)) {     
        lcd.clear();
        lcd.print("Super! Raetsel geloest!");
      }
      if (matrix[startRow][startCol] == 1) {
        return false;
      }
    }

    return true;
}
