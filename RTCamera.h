//
//  RTCamera.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTCamera_h
#define GL_Project4_RTCamera_h

/**************************************************************
 * RTCamera
 * Holds eye, fov and near plane distance.
 *************************************************************/
class RTCamera {
public:
  Vec3 vEye;
  GLfloat pnear;
  GLfloat fovx;
  
};

#endif
