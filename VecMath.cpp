//
//  VecMath.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
/*
 * data.cpp
 * --------
 * Contains routines to help manage the data for the Midpoint Subdivision.
 * Starter code for Project 3.
 *
 * Group Members: <FILL IN>
 */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "common.h"
#include "VecMath.h"

// *******************************************************
// return a random float in the range 0.0f to 1.0f
GLfloat maxf(GLfloat num1, GLfloat num2) {
  if(num1 < num2)
    return num2;
  else
    return num1;
  
}

// ****************************
// default ctor
Vec3::Vec3(void) {
  x = 0;
  y = 0;
  z = 0;
  
}

// ****************************
Vec3::Vec3(GLfloat x_, GLfloat y_, GLfloat z_) {
  x = x_;
  y = y_;
  z = z_;
  
}

// ****************************
Vec3::Vec3(Vec3 *v) {
  x = v->x;
  y = v->y;
  z = v->z;
  
}

// ****************************
void Vec3::Clear(void) {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  
}

// ****************************
Vec3 Vec3::ClampTo1(void) {
  Vec3 vRet;
  vRet.x = this->x;
  vRet.y = this->y;
  vRet.z = this->z;
  
  if(vRet.x > 1.0f) vRet.x = 1.0f;
  if(vRet.y > 1.0f) vRet.y = 1.0f;
  if(vRet.z > 1.0f) vRet.z = 1.0f;

  return vRet;
  
}

// ****************************
void Vec3::Set(GLfloat x_, GLfloat y_, GLfloat z_) {
  x = x_;
  y = y_;
  z = z_;
  
}

// ****************************
Vec3 Vec3::Add(GLfloat x_, GLfloat y_, GLfloat z_) const {
  Vec3 vRet;
  
  vRet.x = this->x + x_;
  vRet.y = this->y + y_;
  vRet.z = this->z + z_;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::Add(const Vec3 v) const {
  Vec3 vRet;
  
  vRet.x = this->x + v.x;
  vRet.y = this->y + v.y;
  vRet.z = this->z + v.z;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::Add(const Vec3 *v) const {
  Vec3 vRet;
  
  vRet.x = x + v->x;
  vRet.y = y + v->y;
  vRet.z = z + v->z;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::Sub(const Vec3 v) const {
  Vec3 vRet;
  
  vRet.x = x - v.x;
  vRet.y = y - v.y;
  vRet.z = z - v.z;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::Sub(const Vec3 *v) const {
  Vec3 vRet;
  
  vRet.x = x - v->x;
  vRet.y = y - v->y;
  vRet.z = z - v->z;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::MultBy(GLfloat f) const {
  Vec3 vRet;
  
  vRet.x = x * f;
  vRet.y = y * f;  
  vRet.z = z * f;
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::DivideBy(GLfloat f) const {
  Vec3 vRet;
  
  vRet.x = x / f;
  vRet.y = y / f;  
  vRet.z = z / f;
  
  return vRet;
  
}

// ****************************
GLfloat Vec3::Length(void) const {
  return sqrt(x*x + y*y + z*z);
  
}

// ****************************
void Vec3::Normalize(void) {
  GLfloat fLength = this->Length();
  
  x /= fLength;
  y /= fLength;
  z /= fLength;
    
}

// ****************************
Vec3 Vec3::GetNormalized(void) {
  Vec3 vRet(x,y,z);
  vRet.Normalize();
  
  return vRet;
  
}

// ****************************
Vec3 Vec3::RotateYDeg(float fDeg) const {
  float fRad = fDeg * PI / 180;
  
  Vec3 vNew;
  vNew.x = x * cos(fRad) + z * sin(fRad);
  vNew.y = y;
  vNew.z = -x * sin(fRad) + z * cos(fRad);
  
  return vNew;
  
}

// ****************************
GLfloat Vec3::r(void) {
  return x;
  
}

// ****************************
GLfloat Vec3::g(void) {
  return y;
  
}

// ****************************
GLfloat Vec3::b(void) {
  return z;
  
}

// ****************************
Vec3 vec3_direction(const Vec3 *p, const Vec3 *q) {
  return(q->Sub(p));
    
}

// ****************************
GLfloat vec3_dot(const Vec3 *v1, const Vec3 *v2) {
  return( v1->x * v2->x + 
          v1->y * v2->y + 
          v1->z * v2->z );
  
}

// ****************************
Vec3 vec3_cross(const Vec3 *v, const Vec3 *w) {
  Vec3 n;
  n.x = (v->y * w->z) - (w->y * v->z);
  n.y = (w->x * v->z) - (v->x * w->z);
  n.z = (v->x * w->y) - (w->x * v->y);
  
  return n;
  
}

// ****************************
Vec3 vec3_normal(const Vec3 *v1, const Vec3 *v2, const Vec3 *v3, bool bNormalize) {
  // build 2 vectors to find a normal.
  Vec3 v(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
  Vec3 w(v3->x - v2->x, v3->y - v2->y, v3->z - v2->z); 
  
  // calc cross product of v,w
  Vec3 n = vec3_cross(&v, &w);
  
  if(bNormalize)
    n.Normalize();
  
  return n;
  
}

// ****************************
Vec3 vec3_normal(const Vec3 v1, const Vec3 v2, const Vec3 v3, bool bNormalize) {
  // build 2 vectors to find a normal.
  Vec3 v(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
  Vec3 w(v3.x - v2.x, v3.y - v2.y, v3.z - v2.z); 
  
  // calc cross product of v,w
  Vec3 n = vec3_cross(&v, &w);
  
  if(bNormalize)
    n.Normalize();
  
  return n;
  
}


// ****************************
Vec3 vec3_avg(const Vec3 *v1, const Vec3 *v2) {
  return (v1->Add(v2)).DivideBy(2);
  
}

// ****************************
Vec3 vec3_avg(const Vec3 *v1, const Vec3 *v2, const Vec3 *v3, const Vec3 *v4) {
  Vec3 vRet;
  
  vRet = v1->Add(v2);
  vRet = vRet.Add(v3);
  vRet = vRet.Add(v4);
  vRet = vRet.DivideBy(4);
  
  return vRet;
  
}

// ****************************
// reflection vector
// 2(NdotL)*N - L
Vec3 vec3_reflect(const Vec3 *v1, const Vec3 *norm) {
  GLfloat dot = maxf(0, vec3_dot(v1, norm));
  
  Vec3 vReflect;
  vReflect = norm->MultBy(2.0f * dot);
  vReflect = vReflect.Sub(v1);
  vReflect.Normalize();
    
  return vReflect;
  
}

// ****************************
GLfloat vec3_distance(const Vec3 *p, const Vec3 *q) {
  Vec3 v = q->Sub(p);
  return v.Length();
  
}

// ****************************
Vec3 vec3_get_spherical_uv(const Vec3 *vCenter, const Vec3 *vPointOnSphere) {
  Vec3 vToPoint = vPointOnSphere->Sub(vCenter);
  vToPoint.Normalize();
  
  Vec3 vYAxis = Vec3(0.0f, 1.0f, 0.0f);
    
  GLdouble arctan_value = atan2(vToPoint.z, vToPoint.x);
  if(arctan_value < 0.0f)
    arctan_value += 2.0f * PI;
  
  GLfloat u = (arctan_value / (2.0f * PI));
  
  GLfloat phi = acosf( -1.0f * vec3_dot(&vYAxis, &vToPoint) );
  GLfloat v = phi / (GLfloat) PI;
  
  return Vec3(u, v, 0.0f);
  
}


// ************************************************************
bool points_same_side_of_ab(Vec3 *p1, Vec3 *p2, Vec3 *a, Vec3 *b) {
  Vec3 BsubA = b->Sub(a);
  BsubA.Normalize();
  
  Vec3 P1subA = p1->Sub(a);
  P1subA.Normalize();
  
  Vec3 P2subA = p2->Sub(a);
  P2subA.Normalize();
  
  Vec3 cp1 = vec3_cross(&BsubA, &P1subA);
  Vec3 cp2 = vec3_cross(&BsubA, &P2subA);
  
  if(vec3_dot(&cp1, &cp2) >= 0)
    return true;
  else
    return false;
  
}

// ****************************
RTColor color_modulate(const RTColor *c1, const RTColor *c2) {
  RTColor colorRet;
  colorRet.x = c1->x * c2->x;
  colorRet.y = c1->y * c2->y;
  colorRet.z = c1->z * c2->z;
  
  return colorRet;
  
}
