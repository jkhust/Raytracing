//
//  RTLight.h
//  GL_Project4
//
//  Created by Justin Hust on 4/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTLight_h
#define GL_Project4_RTLight_h

#include "VecMath.h"

/**************************************************************
 * RTMaterial
 * RTMaterial will hold ambient, diffuse and specular data.
 * Also transparency and reflectivity.
 * And finally, will hold texture map data as well as
 * bump map data.
 *************************************************************/
class RTMaterial {
public:
  // four values for ambient calculation
  RTColor ambient;
  RTColor diffuse;
  RTColor specular;
  GLfloat fShininess;
  GLfloat fOpacity;
  
  
  RTMaterial(void);
  ~RTMaterial(void);
  
  void SetAmbient(RTColor *c);
  void SetAmbient(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetAmbient(void);
  
  void SetDiffuse(RTColor *c);
  void SetDiffuse(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetDiffuse(void);
  
  void SetSpecular(RTColor *c);
  void SetSpecular(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetSpecular(void);
  
  void SetShininess(GLfloat fShininess_);
  GLfloat GetShininess(void);
  
  void SetOpacity(GLfloat fOpacity_);
  GLfloat GetOpacity(void);
  
  void Clear(void);
  
};


/**************************************************************
 * RTTexture
 * PPM texture.  Loads data, saves width, height.
 *************************************************************/
class RTTexture {
private:
  GLubyte *pixels;
  int iWidth;
  int iHeight;
  
public:
  RTTexture(void);
  RTTexture(char *filename);
  ~RTTexture(void);
  
  // image loading.
  void LoadFile(char *filename);
  int GetWidth(void);
  int GetHeight(void);
  
  // get color at particular UV.
  RTColor GetPixelColor(int x, int y);
  RTColor GetColorAtUV(GLfloat u, GLfloat v);
  
};

/**************************************************************
 * RTLight
 * Lights have intensity and either position or direction.
 *************************************************************/
class RTLight {
public:
  Vec3 vPos;
  
  bool bShow;
  
  RTColor ambient;
  RTColor diffuse;
  RTColor specular;
  
  RTLight(void);
  ~RTLight(void);
  
  void SetPos(Vec3 *pos);
  void SetPos(GLfloat x_, GLfloat y_, GLfloat z_);
  Vec3 GetPos(void);
  void Move(GLfloat x_, GLfloat y_, GLfloat z_);
  
  void SetVisible(bool bShow_);
  bool ToggleShow(void);
  bool IsShowing(void);
  
  void SetAmbient(RTColor *c);
  void SetAmbient(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetAmbient(void);
  
  void SetDiffuse(RTColor *c);
  void SetDiffuse(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetDiffuse(void);
  
  void SetSpecular(RTColor *c);
  void SetSpecular(GLfloat r_, GLfloat g_, GLfloat b_);
  RTColor GetSpecular(void);
    
  void Clear(void);
  
  // *** commands export ***
  void ExportCommands(int useIndex);
  
};

#endif
