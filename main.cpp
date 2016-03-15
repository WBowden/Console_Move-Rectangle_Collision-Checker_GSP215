// lab2: rectangles
// William Bowden
// read main.cpp, and follow the instructions at the bottom of main.cpp

#define NOMINMAX // prevent Windows API from conflicting with "min" and "max"

#include <stdio.h>   // C-style output. printf(char*,...), putchar(int)
#include <conio.h>   // _getch()
#include <stdlib.h>
#include <time.h>
#include "Rectangle.h"
#include "Vector2.h"
#include "moveCursor.h"

/**
 * moves the console cursor to the given x/y coordinate
 * 0, 0 is the upper-left hand coordinate. Standard consoles are 80x24.
 * @param x
 * @param y
 */

void setRandom(Rect & r) // Chris Randall helped me understand with this part.
	{
		// srand(time(NULL)); mistake

		int x = rand() % 50;
		int y = rand() % 20 + 3;
		int x2 = rand() % 8+2;
		int y2 = rand()% 8 + 2;
		Vec2 min(x,y); 
		r.setMin(min);
		Vec2 max(x+x2, y+y2);
		r.setMax(max);
	}

void checkCollision(Rect &userRect, Rect * rect, int rectNum)
{

	for(int i = 0; i < rectNum; i++)
		{
				if(userRect.isOverlapping( rect[i] ) ) // checks if player overlaps with other rects
				{
				
					userRect.draw('+');
					moveCursor(40, 0);
					printf("Collision");
				}

		}
	
}

int main()
{
	srand(time(NULL));

	const int Number_of_Rects = 5;

	// initialization

	Rect userRect(7, 5, 10, 9); // Controlled Square Size

	Rect * rect = new Rect[Number_of_Rects]; // creates an array of 5 rectangles.

//	Rect * rect1 = new Rect; // (1, 6, 5, 15)
// rect1->setRandomByPointer(rect1);

	int userInput;

	for(int i = 0; i < Number_of_Rects; i++) // sets 5 rectanges to a random position
		{
		  setRandom(rect[i]); 
		}

	

	do
	{
		// draw
		for(int i = 0; i < Number_of_Rects; i++) // draw 5 rectangles that are numbered from 0 - 4
		{
			rect[i].draw('0'+i); 
		}
		
		//rect1->draw('1');
		moveCursor(0, 0);	// re-print instructions
		printf("move with 'w', 'a', 's', and 'd'");
		userRect.draw('#');

		moveCursor(40, 0);
		printf("No Collision");
		
		checkCollision(userRect, rect, Number_of_Rects); // collision detection. Prints "+" if player collides with other Rects
		
		
		/*for(int i = 0; i < Number_of_Rects; ++i) // old collision detector
		{
			if(userRect.isOverlapping( rect[i] ) )
			{
				
				userRect.draw('+');
				moveCursor(40, 0);
				printf("Collision");
			}
			else
			{
				moveCursor(40, 0);
				printf("No Collision");
			}
		}*/

		// user input
		userInput = _getch();
		
		// update
		Vec2 move;

		switch(userInput) // takes userInput to move controlled rectangle
		{
		case 'w':	move = Vec2( 0,-1);	break;
		case 'a':	move = Vec2(-1, 0);	break;
		case 's':	move = Vec2( 0,+1);	break;
		case 'd':	move = Vec2(+1, 0);	break;
		}
		userRect.draw(' ');	// un-draw before moving
		userRect.translate(move); // Draws square at new location
		
	}while(userInput != 27); // escape key
	delete [] rect; 
	return 0;
}

// INSTRUCTIONS
// ------------
// Compile this code. You should see 3 rectangles, one of which you can move 
// with the 'w', 'a', 's', and 'd' keys.
//
// Read through this code! Try to understand it before starting the assignment.
// Comment confusing lines with what you think code is doing, and experiment
// with existing code to test your understanding.
// Once you feel comfortable with this code, accomplish each of the following,
// and make sure your code compiles and runs after each step is completed.
//
// 1) Get and set functions
//   a) In Rect, create a get and set methods for "min" and "max". Use the
//      signature "void setMin(Vec2 const & min)" and
//      "void setMax(Vec2 const & max)". Use the "this" pointer to disambiguate
//      "min" and "max".
//   b) Make the "min" and "max" objects in Rect private.
// 1) Refactor userRect to be dynamic
//   a) Make userRect a dynamic object. That means it should be declared as
//      "Rect * userRect" instead of "Rect userRect". Use new to dynamically
//      allocate.
//   b) the member operator '.' will need to be replaced with the
//      pointer-to-member operator '->'
//   c) Don't forget to delete userRect at the end of the program!
// 2) Operator Overloading
//   a) Overload the += operator for Vec2, and have it do exactly what
//      Vec2::add does.
//   b) Replace uses of Vec2::add with the += operator. For example, instead of
//      "min.add(delta);", use "min += delta;".
// 3) Random rectangles, by reference and by pointer
//   a) create a method with the method signature "void setRandom(Rect & r)".
//      This function will give the passed-in Rect object a random location.
//      The random x should be between 0 and 50 x. The random y should be
//      between 0 and 20. Limit the possible width and height to a minimum of 2
//      and a maximum of 10.
//   b) test "void setRandom(Rect & r)" on the local Rect object "rect0".
//   c) create a method with the method signature
//      "void setRandomByPointer(Rect * r)", which functions the same as
//      "void setRandom(Rect & r)", except that the argument is
//      passed-by-pointer.
//   d) test "void setRandomByPointer(Rect * r)" on the local Rect object
//      "rect1".
// 4) Test and show overlap
//   a) Using the existing function "isOverlapping(Rect const &)", test to see
//      if userRect collides with any other Rect objects. If userRect is
//      overlapping, draw it with '+' instead '#'.
//   b) Create a Rect * pointer that points to the address if the Rect object
//      that userRect collides with. It should point at NULL if userRect is
//      colliding with no other Rect objects.
//   c) Print to the screen the width and height of a Rect object that userRect
//      collides with. If no collision is happening, print "no collision"
//      instead.
// 5) Array of objects
//   a) Replace the Rect objects rect0 and rect1 with an array of 2 Rect
//      objects, "rect[2]".
//   b) Make sure you replace every remaining "rect0" with "rect[0]", and every
//      "rect1" with "rect[1]".
//   c) Increase the size of the "rect" array to 5. Make sure all 5 Rect
//      objects are randomized, drawn to the screen, and tested for collision.
//   d) If you have not already done so, replace
//      duplicate-code-using-array-elements with a for-loop. For example:
//      If you have:
//          rect[0].draw('0');
//          rect[1].draw('1');
//          rect[2].draw('2');
//          rect[3].draw('3');
//          rect[4].draw('4');
//      Replace it with:
//          for(int i = 0; i < NUMBER_OF_RECTS; i++)
//          {
//              rect[i].draw('0'+i);
//          }
//      Do this where objects are randomized, drawn, and tested for collision

// Achievements: (if you finished, and would like a challenge, try these)
//
// [Dat Rectangle] Implement an interface that allows the user to select the
//     moving rectangle, cycling through all possible rectangles with the tab
//     key, indicating the selected rectangle by drawing it with '#'.
// [One Size Fits All] Implement an interface that allows the user to increase
//     or decrease the size of the selected rectangle. For example, if 'w',
//     'a', 's', and 'd' is used to move the rectangle, 'W', 'A', 'S', and 'D'
//     could move the Rect's max location up, left, down, and right.
// [Add Another] When the user presses space, dynamically resize the rect array
//     to hold an additional random rectangle.
// [One Too Many] When the user presses backspace, dynamically resize the rect
//     array to hold one less rectangle, removing the last one in the list.

// When finished:
// 1) Make sure your name is at the top of this source file
// 2) Submit this project online
//   a) Right-click on the .cpp file's name within visual studio, and select
//      "Open Containing Folder"
//   b) Close Visual Studio (you may re-open this .cpp file by right-clicking
//      on it in the file system, and slecting edit)
//   c) Make sure the following files are DELETED from the project's file
//      structure:
//      * Any file with the extension: ".ncb", ".sdf"
//      * Any folder named: "Debug" or "ipch"
//      * If Visual Studio is open, you will not be able to delete some files
//      * If you do not see file extensions, press Alt in the file explorer,
//        select "Tools"->"Folder options..."->"View", and uncheck
//        "Hide extensions for known file types".
//   d) zip the file structure (the project), which is now missing the
//      temporary files
//      * Select all of the files in the project folder
//      * If the resulting zip file is more than 1mb, you have included
//        temporary files mentioned above. Delete temporary files (that don't
//        have a .cpp or .h extension) and try again.
//   e) upload the project to the appropriate week's iLab at the GSP125
//      website, linked from http://www.devryu.net
