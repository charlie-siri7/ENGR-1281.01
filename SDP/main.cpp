/************************************************/
/* Name: Charles Sirichoktanasup Date: 12/04/23*/
/* Name: Kelly Coleman Date: 12/04/23*/
/* Seat: 00 File: main.cpp */
/* Instructor: KMK 08:00 */
/************************************************/

#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHRandom.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <FEHImages.h>

//Various numbers that determine physics and gamefeel
//Defined here for easy modification and adjustment
//Like dials on a board
#define gravScale 1
#define gravLimit 6
#define momScale 0.8
#define bounceFact 12
#define TIMESCALE 0.02
#define winWidth 20
#define winHeight 20
#define SCORETIME 30

using namespace std;

//Menu stuff.
char mode[6] = "Life";
int lives = 3;
void showMenu();
void displayInstructions();
void displayCredits();
void useMenu();
void displayStats();
void updatemode();
void end(double timeStart, char mode[]);
void diplayHud(double timeStart);
void drawDisappearingGameElements();
void drawYellowLines();
void drawWindows();

bool gamingTime = true;
int highScore = 0;
double highTime = 0;
double finalTime = 0;

//Score
int score = 0;

/**
* The goal box. It increments score and moves to a new location when interact with ball
*
* Author: Kelly Coleman
*
* int positionX and positionY represent the coordinates of the upper-left corner of the box
* int height and width are the height and width of the box
*/

class winBox {
public:
int positionX, positionY;
int height, width;
winBox();
void drawBox(int positionX, int positionY);
void win();
void createNew();
};

/**
 * The line. Responsible for being drawn with user touch, being bouncy, and all kinds of fun.
 * Most bounce functionality is handled here.
 *
 * bool lineFin is a bool that shows if the line is finished or not
 * bool lineIsDraw is a bool that shows if the line is being drawn or not
 * int lineX1 and lineY1 are the coordinates of the beggining of the line
 * int lastLineX1 and lastLineY1 are the coordinates of the end of the line
 * float normX1 and normY1 are the coordinates of the unit normal vector of the line
 *
 * Author: Kelly Coleman
 */

class line {
private:
bool lineFin = false;
public:
bool lineIsDraw = false;
int lineX1, lineY1;
int lastLineX1, lastLineY1;
float normX1, normY1;

line();

void drawLine(int posX, int posY);
void finishLine(int posX, int posY);
void clearLine();
bool getIsDraw();
bool getLineFin();
void setLineFin(bool value);
void normalVector(int posX, int posY);
};

/**
 * THE ball. Responds to gravity, collision, and any kind of momentum.
 *
 * int posX and posY are the coordinated of the ball
 * float momX and momY are the momentum of the ball
 * bool bounced is a bool that shows if the ball bounced in the last frame
 *
 * Author: Kelly Coleman
*/

class ball {
public:
float momX, momY;
int posX, posY;
bool bounced;




ball(int coordX = 30, int coordY = 30, int momentumX = 1, int momentumY = -5);
void gravity();
void applyMom();
void bounce(line line);
bool isWin(winBox box);
bool isLose();
void reset();
};

bool isIntersect(line line, ball ball);

int dp(int x1, int y1, int x2, int y2);

int main()
{
cout << "************************************************" << endl;
cout << "* Name: Charles Sirichoktanasup Date: 12/04/23*" << endl;
cout << "* Name: Kelly Coleman Date: 12/04/23*" << endl;
cout << "* Seat: 00 File: SDP_4.cpp *" << endl;
cout << "* Instructor: KMK 08:00 *" << endl;
cout << "************************************************" << endl;

static int inputX, inputY;

menuStart:

showMenu();
Sleep(0.025);
useMenu();
LCD.Clear();

line linny;

ball ballArray[3];

ball ball1;

winBox win;

double timeStart = TimeNow();
gamingTime = true;
score = 0;
int randX = (Random.RandInt() / 32767.0 ) * 250 + 25;
int randY = (Random.RandInt() / 32767.0 ) * 170 + 30;
while (gamingTime) {
drawDisappearingGameElements();
//win.drawBox(randX, randY);
if ((ball1.isLose() && strcmp(mode, "Life") == 0)) {
lives--;
ball1.reset();
if (lives < 0) {
gamingTime = false;
end(timeStart, mode);
lives = 3;
//I know this line is evil and gross but I cannot be bothered to implement it properly.
//It jumps to the start of the main function and restarts menu functions.
goto menuStart;
}
}
if (TimeNow() - timeStart > SCORETIME && strcmp(mode, "Score") == 0) {
gamingTime = false;
end(timeStart, mode);
//I know this line is evil and gross but I cannot be bothered to implement it properly.
//It jumps to the start of the main function and restarts menu functions.
goto menuStart;
}
diplayHud(timeStart);
if (ball1.isWin(win)) {
LCD.SetFontColor(DARKBLUE);
LCD.FillRectangle(win.positionX, win.positionY, winWidth, winHeight);
randX = (Random.RandInt() / 32767.0 ) * 250 + 25;
randY = (Random.RandInt() / 32767.0 ) * 170 + 30;
ball1.reset();
}
win.drawBox(randX, randY);
ball1.gravity();
ball1.bounce(linny);
//This implementation right here sucks but the alternative is passing class pointers (scary)
if (ball1.bounced) {
linny.clearLine();
ball1.bounced = false;
}
ball1.applyMom();

//Line draw functions
if (LCD.Touch(&inputX, &inputY)) {
linny.drawLine(inputX, inputY);
}
if (linny.getIsDraw() && !LCD.Touch(&inputX, &inputY)) {
linny.finishLine(inputX, inputY);
}

for (ball object: ballArray) {
object.gravity();
}

//Sleep function is here to make game possible to play by slowing it.
//Alternative is taking a lot of time to adjust numbers and time is the thing I don't have a lot of right now
Sleep(TIMESCALE);
}

}

/**
* Sets x1 and y1 equal to the normal unit vector coordinates corresponding to line.
*/
void line::normalVector(int x1, int y1) {
float xSlope = (x1 - lineX1);
float ySlope = (y1 - lineY1);

float magnitude = sqrt(pow(xSlope, 2.0) + pow(ySlope, 2.0));

xSlope /= magnitude;
ySlope /= magnitude;

normX1 = ySlope;
normY1 = -xSlope;

if (normY1 > 0) {
normX1 *= -1;
normY1 *= -1;
}
}

/**
* Default constructor for ball.
*/
ball::ball (int coordX, int coordY, int momentumX, int momentumY) {
posX = coordX;
posY = coordY;

bounced = false;

momX = momentumX;
momY = momentumY;
}

/**
* Default constructor for line.
*/
line::line() {
lineX1= 0;
lineY1 = 0;
lastLineX1 = 0;
lastLineY1 = 0;
lineFin = 0;
}

/**
* default constuctor for winBox.
*/
winBox::winBox() {
height = winHeight;
width = winWidth;
positionX = 200;
positionY = 20;
}

/**
* Draws the goal box given a position.
*/
void winBox::drawBox(int positX, int positY) {
height = winHeight;
width = winWidth;
positionX = positX;
positionY = positY;
LCD.SetFontColor(GREEN);
LCD.FillRectangle(positionX, positionY, width, height);
LCD.SetFontColor(WHITE);
LCD.DrawLine(positionX + 0.25 * width, positionY + 0.75 * height, positionX + 0.75 * width, positionY + 0.75 * height);
LCD.DrawLine(positionX + 0.25 * width, positionY + 0.7 * height, positionX + 0.5 * width, positionY + 0.2 * height);
LCD.DrawLine(positionX + 0.75 * width, positionY + 0.7 * height, positionX + 0.5 * width, positionY + 0.2 * height);
}

/**
* Applies gravity to ball's momentum.
*/
void ball::gravity() {
if (momY < gravLimit) momY = momY + gravScale;
}

/**
* Applies momentum to ball based on set scale.
*/
void ball::applyMom() {
LCD.SetFontColor(DARKBLUE);
LCD.FillCircle(posX, posY, 2);
posX = posX + momX*momScale;
posY = posY + momY*momScale;
LCD.SetFontColor(WHITE);
LCD.FillCircle(posX, posY, 2);
}

/**
* Determines momentum for ball based on collisions.
*/
void ball::bounce(line line) {
if (posX <= 29) {
momX = abs(momX);
}
if (posX >= 291) {
momX = -1*abs(momX);
}

if (posY <= 4) {
//posY += 4;
momY = abs(-1*momY);
}

if (strcmp(mode, "Score") == 0) {
if( posY >= 220) {
momY = -momY - 8;
}
}
if ((line.getLineFin() && isIntersect(line, *this))) {
bounced = true;
momX += line.normX1*bounceFact;
momY = -momY;
momY += line.normY1*bounceFact;
}
}

/**
* Draws line following user input.
*/
void line::drawLine(int inputX, int inputY) {
if (!lineIsDraw){
clearLine();
lineIsDraw = true;
lineX1 = inputX;
lineY1 = inputY;
lastLineX1 = lineX1;
lastLineY1 = lineY1;
}
else {
LCD.SetFontColor(DARKBLUE);
LCD.DrawLine(lineX1, lineY1, lastLineX1, lastLineY1);
LCD.SetFontColor(GRAY);
LCD.DrawLine(lineX1, lineY1, inputX, inputY);
LCD.Update();
lastLineX1 = inputX;
lastLineY1 = inputY;
}
}

/**
* Sets line to be interactable and in a state of non-drawing.
*/
void line::finishLine(int inputX, int inputY) {
LCD.SetFontColor(DARKBLUE);
LCD.DrawLine(lineX1, lineY1, lastLineX1, lastLineY1);
LCD.SetFontColor(WHITE);
LCD.DrawLine(lineX1, lineY1, inputX, inputY);
lastLineX1 = inputX;
lastLineY1 = inputY;

lineIsDraw = false;

setLineFin(true);

normalVector(inputX, inputY);

}

/**
* Clears line.
*/
void line::clearLine() {
setLineFin(false);
LCD.SetFontColor(DARKBLUE);
LCD.DrawLine(lineX1, lineY1, lastLineX1, lastLineY1);
}
/**
* Getter function for lineFin. At some point I made all my variables in the classes public so getter functions are obsolete, but oh well.
*/
bool line::getIsDraw() {
return lineIsDraw;
}

/**
* Checks if line and ball are colliding and returns appropriate bool. Works about 95% of the time.
*/
bool isIntersect (line line, ball ball) {
float dx = line.lastLineX1 - line.lineX1;
float dy = line.lastLineY1 - line.lineY1;

float fx = line.lineX1 - ball.posX;
float fy = line.lineY1 - ball.posY;

float a = dp(dx, dy, dx, dy);
float b = 2*dp(fx, fy, dx, dy);
//ball is made to be bigger then actually is here, because otherwise actually implementing this is scary and hard
float c = dp(fx, fy, fx, fy) - 12;

float disc = b*b-4*a*c;

if (disc < 0) {
return false;
}
else {
disc = sqrt(disc);

float t1 = (-b - disc)/(2*a);
float t2 = (-b + disc)/(2*a);

if( t1 >= 0 && t1 <= 1 )
{
// t1 is the intersection, and it's closer than t2
// (since t1 uses -b - discriminant)
return true ;
}
if( t2 >= 0 && t2 <= 1 )
{
return true ;
}
return false;
}

}

/**
* Returns dot product of two 'vectors'
*/
int dp (int x1, int y1, int x2, int y2) {
return (x1*x2) + (y1*y2);
}

/**
* Getter function for lineFin.
*/
bool line::getLineFin() {
return lineFin;
}

/**
* Setter function for lineFin.
*/
void line::setLineFin(bool value) {
lineFin = value;
}

/**
* Checks if ball is in goal box and returns boolean + increments score.
*/
bool ball::isWin(winBox box) {
if (posX >= box.positionX - 1 && posX <= box.positionX + winWidth + 2 && posY >= box.positionY - 1 && posY <= box.positionY + winHeight + 2) {
score++;
return true;
}
else return false;
}

void menu() {
while (true) {
int inputX, inputY;
LCD.SetBackgroundColor(BLACK);
/* Clear the touch buffer so touches made before
this call are discarded */
LCD.ClearBuffer();
/* Wait until the user touches the screen */
while(!LCD.Touch(&inputX,&inputY)) {};
/* Wait until the touch releases */
while(LCD.Touch(&inputX,&inputY)) {};

}
}

/* Display the menu upon starting the application, completing a game,
or returning from an option on the menu. Author: Charles */
void showMenu() {
/* Clears screen, draws menu background image, writes game header, creates buttons
Image source: https://www.econlib.org/library/Enc/Recycling.html */
Sleep(100);
LCD.Clear();
FEHImage recycling;
recycling.Open("recyclingFEH.pic");
recycling.Draw(0, 0);
recycling.Close();

LCD.SetFontColor(BLACK);
LCD.WriteAt("WELCOME TO", 5, 5);
LCD.WriteAt("RECYCLING REBOUNDER!", 5, 25);

LCD.SetFontColor(RED);
LCD.FillRectangle(70,60,75,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Play",75,65);

LCD.SetFontColor(ORANGE);
LCD.FillRectangle(155,60,75,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Stats",160,65);

LCD.SetFontColor(GREEN);
LCD.FillRectangle(70,100,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Mode:",75,105);
LCD.WriteAt(mode, 155,105);

LCD.SetFontColor(BLUE);
LCD.FillRectangle(70,140,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Instructions",75,145);

LCD.SetFontColor(PURPLE);
LCD.FillRectangle(70,180,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Credits",75,185);
}

/* Allows buttons on the menu to be used, calling the respective function to display a new screen.
Author: Charles */
void useMenu() {
bool onMenu = true;
int inputX, inputY;

while (true) {

/* Set the menu background color to black when the image isn't present */
LCD.SetBackgroundColor(BLACK);
/* Clear the touch buffer so touches made before
this call are discarded */
LCD.ClearBuffer();
/* Wait until the user touches the screen */
while(!LCD.Touch(&inputX,&inputY)) {};
/* Wait until the touch releases */
while(LCD.Touch(&inputX,&inputY)) {};

if (onMenu) {
/* If a touch occurs when the current screen is the menu, set onMenu to false and go to
correct screen based on if the coordinates of the click lie within a button. If the touch
doesn't occur on any button, don't do anything and set onMenu back to true */
onMenu = false;
if ((inputX >= 70 && inputX <= 145) && (inputY >= 60 && inputY <= 90)) {
/* If user presses play button, change background color, play game, and update
high score and time afterwards */

LCD.SetBackgroundColor(DARKBLUE);
//game1.play();
return;
//game1.updateHighScore();

} else if ((inputX >= 155 && inputX <= 225) && (inputY >= 60 && inputY <= 90)) {
/* Show stats upon stat button being pressed */

displayStats();

} else if ((inputX >= 70 && inputX <= 230) && (inputY >= 100 && inputY <= 130)) {
/* Update mode and remain on menu if updatemode button is pressed */

updatemode();

onMenu = true;
showMenu();
} else if ((inputX >= 70 && inputX <= 230) && (inputY >= 140 && inputY <= 170)) {
/* Display instructions upon pressing of instructions button */
displayInstructions();
} else if ((inputX >= 70 && inputX <= 230) && (inputY >= 180 && inputY <= 210)) {
/* Display credits when credits button is pressed */
displayCredits();
} else {
/* If none of the above buttons are pressed, keep onMenu as true */
onMenu = true;
}

} else if ((inputX >= 70 && inputX <= 230) && (inputY >= 180 && inputY <= 210)) {
/* If the current screen isn't the menu, detect if the touch coordinates lie within the
'Back to Menu' button, as it is in the same location for all non-menu screens. If the
button is pressed, go back to the main menu. */
onMenu = true;
showMenu();
}
/* Wait for half a second so accidentally double tapping doesn't make screen change back */
Sleep(50);
}

}

/* The purpose of displayInstructions is show the user how to play the game accessible through the
menu. Author: Charles */
void displayInstructions() {
/* Clear screen, display instructions with header, make button to go back to menu */
LCD.Clear();
LCD.WriteLine("Instructions:");

LCD.WriteAt("1. Touch and drag screen",0,20);
LCD.WriteAt(" to draw trampoline",0,40);
LCD.WriteAt("2. Try to get plastic",0,60);
LCD.WriteAt(" ball into recycling bin",0,80);
LCD.WriteAt("3. In life mode, don't",0,100);
LCD.WriteAt(" let recycling hit road",0,120);

LCD.SetFontColor(RED);
LCD.FillRectangle(70,180,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Back to menu",75,185);

}

/* displayCredits: shows who was responsible for the development and inspiration of the game
Author: Charles */
void displayCredits() {
/* Clear screen, display credits with header, make button to go back to menu */
LCD.Clear();
LCD.WriteLine("Credits:");

LCD.WriteAt("-Developers:",25,25);
LCD.WriteAt(" Charles Sirichoktanasup",25,50);
LCD.WriteAt(" and Kelly Coleman",25,75);

LCD.SetFontColor(RED);
LCD.FillRectangle(70,180,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Back to menu",75,185);
}

/* Shows the statistics of the game with context when the "Stats" option of the menu is selected.
Displayed stats include score, high score, time, and high time. Author: Charles */
void displayStats() {
LCD.Clear();
LCD.WriteLine("Stats:");

LCD.WriteAt("High Score: ",25,25);
LCD.WriteAt(highScore, 180, 25);
LCD.WriteAt("Last Score: ",25,50);
LCD.WriteAt(score, 180, 50);

LCD.WriteAt("High Time: ",25,100);
LCD.WriteAt(highTime, 160, 100);
LCD.WriteAt("Last Time: ",25,125);
LCD.WriteAt(finalTime, 160, 125);

LCD.SetFontColor(RED);
LCD.FillRectangle(70,180,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Back to menu",75,185);
}

/* Updates the game's mode, setting it to the option of 2 that it currently is not.
Author: Charles */
void updatemode() {
if (strcmp(mode, "Score") == 0) {
strcpy(mode, "Life");
} else {
strcpy(mode, "Score");
}
}

/* Clears screen and adds landfill background, tells user they lost or ran out of time, displays
score and time of the game, add button to go back to menu so the game can be replayed. Author: Charles */
void end(double time, char mode[]) {

finalTime = TimeNow() - time;
char endText[] = "Haha you ran out of time";
if (strcmp(mode, "Life") == 0) {
strcpy(endText, "Haha you lost");
}
LCD.Clear();
/* Image source: https://www.covanta.com/blog/the-dug-up-truth-about-landfill-disposal */
FEHImage landfill;
landfill.Open("landfillFEH.pic");
landfill.Draw(0, 0);
landfill.Close();

LCD.SetFontColor(BLACK);
LCD.WriteAt(endText, 5, 5);
LCD.WriteAt("Your score: ", 5, 25);
LCD.WriteAt(score, 150, 25);
LCD.WriteAt("Your time: ", 5, 50);
LCD.WriteAt(finalTime, 150, 50);

/* Make button to go back to menu */
LCD.SetFontColor(RED);
LCD.FillRectangle(70,180,160,30);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Back to menu",75,185);

if (score > highScore) {
highScore = score;
}
if (finalTime > highTime) {
highTime = finalTime;
}

int inputX, inputY;

while (true) {
while(!LCD.Touch(&inputX, &inputY));

if (((inputX >= 70 && inputX <= 230) && (inputY >= 180 && inputY <= 210))) {
Sleep(50);
return;
}
}
}

bool ball::isLose() {
if (posY > 225) {
return true;
}
else return false;
}

void diplayHud(double timeStart) {
LCD.SetFontColor(DARKBLUE);
LCD.WriteAt("Score: ", 180, 10);
LCD.WriteAt(score-1, 260, 10);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Score: ", 180, 10);
LCD.WriteAt(score, 260, 10);

if (strcmp(mode, "Score") == 0) {
LCD.SetFontColor(DARKBLUE);
LCD.WriteAt("Time: ", 30, 10);
LCD.WriteAt(SCORETIME -((int)TimeNow() - (int)timeStart -1), 100, 10);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Time: ", 30, 10);
LCD.WriteAt(SCORETIME -((int)TimeNow() - (int)timeStart), 100, 10);
}
else {
LCD.SetFontColor(DARKBLUE);
LCD.WriteAt("Lives: ", 30, 10);
LCD.WriteAt(lives + 1, 120, 10);
LCD.SetFontColor(WHITE);
LCD.WriteAt("Lives: ", 30, 10);
LCD.WriteAt(lives, 120, 10);
}
}

void ball::reset() {
LCD.SetFontColor(DARKBLUE);
LCD.FillCircle(posX, posY, 2);
posX = 30;
posY = 30;
momX = 1;
momY = -5;
}

/* Redraws elements in case the ball overlaps them, including buildings and road. Author: Charles */
void drawDisappearingGameElements() {

LCD.SetFontColor(GRAY);
LCD.FillRectangle(0, 0, 25, 225);
LCD.SetFontColor(GRAY);
LCD.FillRectangle(295, 0, 25, 225);

drawWindows();

LCD.SetFontColor(BLACK);
LCD.FillRectangle(0, 225, 320, 15);

drawYellowLines();
}

/* Method to draw the yellow lines of the road in the game. Author: Charles */
void drawYellowLines() {
LCD.SetFontColor(YELLOW);
for (int i = 10; i < 320; i+=40) {
LCD.FillRectangle(i, 230, 20, 5);
}
}

/* Draws the windows of the skyscraper boundaries of the game. Author: Charles */
void drawWindows() {
LCD.SetFontColor(CYAN);
for (int i = 5; i < 220; i+=10) {
LCD.FillRectangle(5, i, 5, 5);
LCD.FillRectangle(15, i, 5, 5);
LCD.FillRectangle(300, i, 5, 5);
LCD.FillRectangle(310, i, 5, 5);
}
}



