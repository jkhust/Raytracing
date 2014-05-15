//
//  RTCanvas.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>
#include "RTCanvas.h"
#include "RTPrimitive.h"

const int RED_OFS = 0;      /* offset to red byte */
const int GREEN_OFS = 1;    /* offset to green byte */
const int BLUE_OFS = 2;     /* offset to blue byte */

// ********************************************************
RTCanvas::RTCanvas(int iWidth_, int iHeight_) {
  pixels = new GLubyte[iWidth_*iHeight_*3];
  iWidth = iWidth_;
  iHeight = iHeight_;
  ClearToWhite();
    
}
  
// ********************************************************
RTCanvas::~RTCanvas(void) {
  if(pixels != NULL)
    delete[] pixels;
  
  pixels = NULL;
  
}

// ************************************************************
int RTCanvas::GetWidth(void) {
  return iWidth;
  
}

// ************************************************************
int RTCanvas::GetHeight(void) {
  return iHeight;
  
}
  
// ************************************************************
void RTCanvas::SetCanvasProjection(void) {
    // init openGL drawing mode to something the canvas can use.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); 
    
}
  
// ************************************************************
void RTCanvas::ClearToWhite(void) {
  // set every pixel to white
  for(int i=0; i < iWidth*iHeight*3; i++) {
    pixels[i] = 0xFF;
      
  }
    
}


// ************************************************************
void RTCanvas::ClearToGray(void) {
  // set every pixel to white
  for(int i=0; i < iWidth*iHeight*3; i++) {
    pixels[i] = 0x77;
    
  }
  
}

  
// ************************************************************
void RTCanvas::PlotPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  assert(x >= 0 && x < iWidth);
  assert(y >= 0 && y < iHeight);
  
  int iPixelPos = 3*iWidth*y + 3*x;
  
  char red = (char) (r*255);
  char green = (char) (g*255);
  char blue = (char) (b*255);
    
  pixels[iPixelPos + RED_OFS] = red;
  pixels[iPixelPos + GREEN_OFS] = green;
  pixels[iPixelPos + BLUE_OFS] = blue;

}

// ************************************************************
void RTCanvas::PlotPixel(int x, int y, RTColor *c) {
  PlotPixel(x, y, c->r(), c->g(), c->b());
  
}
  
// ************************************************************
void RTCanvas::SendToFrameBuffer(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glRasterPos3f(0.0,0.0,0.0);
  glDrawPixels(iWidth,iHeight,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    
}