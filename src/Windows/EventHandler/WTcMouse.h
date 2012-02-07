#ifndef __WTCMOUSE_H__
#define __WTCMOUSE_H__
/**
 * \brief This will store all the input data for a single mouse.
 * It also controls the interpretation of the input and controls the cursor.
 * It allows the user to Lock the cursor to the centre of the screen reading mouse position based on the distance moved every frame.
 * The mouse inputs are buffered meaning that the mouse inputs are consistent for an entire process cycle.
 * It also means that the actual cursor speed can be calculated.
 */
class cMouse
{
 /// This is a pointer to the texture the system should use for the mouse cursor.
cTexture *mpImage;

/// This is a flag determining whether the cursor is shown or not.
bool miShown;

public:
 //Current Frames X, Y and Z values - IE use these
 // This stores the current frames X value (in pixels from the windows 0,0).
 int x;
// This stores the current frames Y value (in pixels from the windows 0,0).
 int y;
// This stores the current frames Z value (in pixels from the windows 0,0).
 int z;

 // This stores the mouses current left button state.
 bool left;
// This stores the mouses current right button state.
 bool right;
// This stores the mouses current middle button state.
 bool middle;
// This stores whether the mouse cursor is locked to the centre of the window.
 bool locked;
 //Distance Cursor moved since last frame
 // This will store the mouses current X speed. (pixels travelled since last frame).
 int xs;
// This will store the mouses current Y speed. (pixels travelled since last frame).
 int ys;
 //Actual current X and Y values, these track the cursor continuously.
// This is the real mouses X position. It will change as the mouse moves, so will not be consistent through out the frame. Should avoid being used.
 int cx;
// This is the real mouses Y position. It will change as the mouse moves, so will not be consistent through out the frame. Should avoid being used.
 int cy;
 ///Will return the current X Position of the mouse cursor in pixels from the left hand edge of the screen.
 int X();
 ///Will return the current Y Position of the mouse cursor in pixels from the bottom edge of the screen.
 int Y();
 ///Will return the current Z Position of the mouse cursor.
 int Z();
 ///Will return the number of horizontal pixels the cursor moved last frame. Moving Right is positive.
 int XSpeed();
 ///Will return the number of vertical pixels the cursor moved last frame. Moving Up is positive.
 int YSpeed();
 ///Will return the pressed state of the mouses left button.
 bool Left();
 ///Will return the pressed state of the mouses right button.
 bool Right();
///Will return the pressed state of the mouses middle button.
 bool Middle();

 #if WT_OS_TYPE==OS_WIN32
 /// Windows only variable. Windows format for mouse position...?
 tagPOINT Pos;
#endif

 cMouse();
 /// This will Update the mouse variable. Should be called every frame by cKernel.
 void Update();
 /// This will hide the mouse cursor.
 void Hide();
/// This will show the mouse cursor.
 void Show();
/// This will return whether the mouse curor is currently showing.
 bool Showing();
 /// This will lock the mouse cursor to the centre of the window (allowing unlimited scrolling).
 void Lock();
/// This will unlock the mouse cursor from the centre of the window.
 void Unlock();

};


#endif
