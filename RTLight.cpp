//
//  RTLight.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RTPrimitive.h"
#include "RTLight.h"
#include "readppm.h"

const int RED_OFS = 0;
const int GREEN_OFS = 1;
const int BLUE_OFS = 2;

// ************************************************************
RTMaterial::RTMaterial(void) {
  Clear();
  
}

// ************************************************************
RTMaterial::~RTMaterial(void) {
  // no cleanup code
  
}

// ************************************************************
void RTMaterial::Clear(void) {
  this->ambient.Clear();
  this->diffuse.Clear();
  this->specular.Clear();
  this->fShininess = 0.0f;
  
}

// ************************************************************
void RTMaterial::SetAmbient(RTColor *c) {
  this->ambient.x = c->r();
  this->ambient.y = c->g();
  this->ambient.z = c->b();
  
}

// ************************************************************
void RTMaterial::SetAmbient(GLfloat r_, GLfloat g_, GLfloat b_) {
  this->ambient.x = r_;
  this->ambient.y = g_;
  this->ambient.z = b_;
  
}

// ************************************************************
RTColor RTMaterial::GetAmbient(void) {
  return ambient;
  
}

// ************************************************************
void RTMaterial::SetDiffuse(RTColor *c) {
  this->diffuse.x = c->r();
  this->diffuse.y = c->g();
  this->diffuse.z = c->b();
  
}

// ************************************************************
void RTMaterial::SetDiffuse(GLfloat r_, GLfloat g_, GLfloat b_) {
  this->diffuse.x = r_;
  this->diffuse.y = g_;
  this->diffuse.z = b_;  
  
}

// ************************************************************
RTColor RTMaterial::GetDiffuse(void) {
  return diffuse;
  
}

// ************************************************************
void RTMaterial::SetSpecular(RTColor *c) {
  this->specular.x = c->r();
  this->specular.y = c->g();
  this->specular.z = c->b();
  
}

// ************************************************************
void RTMaterial::SetSpecular(GLfloat r_, GLfloat g_, GLfloat b_) {
  this->specular.x = r_;
  this->specular.y = g_;
  this->specular.z = b_;
  
}

// ************************************************************
RTColor RTMaterial::GetSpecular(void) {
  return specular;
  
}

// ************************************************************
void RTMaterial::SetShininess(GLfloat fShininess_) {
  fShininess = fShininess_;
  
}

// ************************************************************
GLfloat RTMaterial::GetShininess(void) {
  return fShininess;
  
}


// ************************************************************
void RTMaterial::SetOpacity(GLfloat fOpacity_) {
  fOpacity = fOpacity_;
  
}

// ************************************************************
GLfloat RTMaterial::GetOpacity(void) {
  return fOpacity;
  
}

// ************************************************************
RTTexture::RTTexture(void) {
  pixels = NULL;
  iWidth = -1;
  iHeight = -1;
  
}

// ************************************************************
RTTexture::RTTexture(char *filename) {
  LoadFile(filename);
  
}

// ************************************************************
void RTTexture::LoadFile(char *filename) {
  if(pixels != NULL) {
    delete pixels;
    pixels = NULL;
    
  }
  
  pixels = readPPMfile(filename, &iWidth, &iHeight);
  
}

// ************************************************************
RTTexture::~RTTexture(void) {
  if(pixels == NULL)
    free(pixels);
  
  pixels = NULL;
  
}

// ************************************************************
// get color at UV coord.
RTColor RTTexture::GetPixelColor(int x, int y) {
  int iPos = y*3*iWidth + x*3;
  
  return RTColor((GLfloat) pixels[iPos + RED_OFS] / (GLfloat) 255.0f,
                 (GLfloat) pixels[iPos + GREEN_OFS] / (GLfloat) 255.0f, 
                 (GLfloat) pixels[iPos + BLUE_OFS] / (GLfloat) 255.0f);
  
}

// ************************************************************
// get color at UV coord.
RTColor RTTexture::GetColorAtUV(GLfloat u, GLfloat v) {
  int s = u * (GLfloat) iWidth;
  int t = v * (GLfloat) iHeight;
  
  return this->GetPixelColor(s, t);
  
}

// ************************************************************
int RTTexture::GetWidth(void) {
  return iWidth;
  
}

// ************************************************************
int RTTexture::GetHeight(void) {
  return iHeight;
  
}

// ************************************************************
RTLight::RTLight(void) {
  Clear();
  
  bShow = true;
  
}

// ************************************************************
RTLight::~RTLight(void) {
  // no cleanup code
  
}

// ************************************************************
void RTLight::SetVisible(bool bShow_) {
  bShow = bShow_;
  
}

// ************************************************************
bool RTLight::ToggleShow(void) {
  bShow = !bShow;
  return bShow;
  
}

// ************************************************************
bool RTLight::IsShowing(void) {
  return bShow;
  
}

// ************************************************************
void RTLight::SetPos(Vec3 *vNewPos) {
  vPos.x = vNewPos->x;
  vPos.y = vNewPos->y;
  vPos.z = vNewPos->z;
  
}

// ************************************************************
void RTLight::SetPos(GLfloat x_, GLfloat y_, GLfloat z_) {
  vPos.x = x_;
  vPos.y = y_;
  vPos.z = z_;
  
}

// ************************************************************
Vec3 RTLight::GetPos(void) {
  return vPos;
  
}

// ************************************************************
void RTLight::Move(GLfloat x_, GLfloat y_, GLfloat z_) {
  vPos.x += x_;
  vPos.y += y_;
  vPos.z += z_;
  
}

// ************************************************************
void RTLight::SetAmbient(RTColor *c) {
  ambient.x = c->x;
  ambient.y = c->y;
  ambient.z = c->z;
  
}

// ************************************************************
void RTLight::SetAmbient(GLfloat r_, GLfloat g_, GLfloat b_) {
  ambient.x = r_;
  ambient.y = g_;
  ambient.z = b_;
  
}

// ************************************************************
RTColor RTLight::GetAmbient(void) {
  return ambient;
  
}

// ************************************************************
void RTLight::SetDiffuse(RTColor *c) {
  diffuse.x = c->x;
  diffuse.y = c->y;
  diffuse.z = c->z;
  
}

// ************************************************************
void RTLight::SetDiffuse(GLfloat r_, GLfloat g_, GLfloat b_) {
  diffuse.x = r_;
  diffuse.y = g_;
  diffuse.z = b_;  
  
}

// ************************************************************
RTColor RTLight::GetDiffuse(void) {
  return diffuse;
  
}

// ************************************************************
void RTLight::SetSpecular(RTColor *c) {
  specular.x = c->x;
  specular.y = c->y;
  specular.z = c->z;
  
}

// ************************************************************
void RTLight::SetSpecular(GLfloat r_, GLfloat g_, GLfloat b_) {
  specular.x = r_;
  specular.y = g_;
  specular.z = b_;
  
}

// ************************************************************
RTColor RTLight::GetSpecular(void) {
  return specular;
  
}

// ************************************************************
void RTLight::Clear(void) {
  vPos.Clear();
  ambient.Clear();
  diffuse.Clear();
  specular.Clear();
  
}

// ************************************************************
// *** commands export ***
void RTLight::ExportCommands(int useIndex) {
  printf("\n");
  printf("RTLight * light%d = new RTLight();\n", useIndex);
  printf("light%d->SetPos(%f, %f, %f);\n", useIndex, vPos.x, vPos.y, vPos.z);
  
  if(IsShowing())
    printf("light%d->SetVisible(true);\n", useIndex);
  else
    printf("light%d->SetVisible(false);\n", useIndex);
 
  printf("light%d->SetAmbient(%f, %f, %f);\n", useIndex, ambient.x, ambient.y, ambient.z);
  printf("light%d->SetDiffuse(%f, %f, %f);\n", useIndex, diffuse.x, diffuse.y, diffuse.z);
  printf("light%d->SetSpecular(%f, %f, %f);\n", useIndex, specular.x, specular.y, specular.z);
  
  printf("AddLight(light%d);\n", useIndex);
  
}