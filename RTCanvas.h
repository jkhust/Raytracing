//
//  RTCanvas.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTCanvas_h
#define GL_Project4_RTCanvas_h

#include "common.h"
#include "RTPrimitive.h"

/**************************************************************
 * RTCanvas
 * Holds canvas onto which ray results are recorded.
 *************************************************************/
class RTCanvas {
private:  
  // canvas pixels
  int iWidth;
  int iHeight;
  GLubyte *pixels;
  
public:
  RTCanvas(int iWidth_, int iHeight_);
  ~RTCanvas(void);
  
  int GetWidth(void);
  int GetHeight(void);
  
  // functionality provided by project 4 starter code.
  void SetCanvasProjection(void);
  void ClearToWhite(void);  
  void ClearToGray(void);  
  void PlotPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b);  
  void PlotPixel(int x, int y, RTColor *c);  
  void SendToFrameBuffer(void);  
  
};

#endif
