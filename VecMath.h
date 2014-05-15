//
//  VecMath.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_VecMath_h
#define GL_Project4_VecMath_h

#include "common.h"


// vec4 used for lighting and materials
class Vec4 {
public:
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat w;
  
  Vec4(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat w_) {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
    
  }
  
};

// *******************************************
class Vec3 {
public:
  GLfloat x;
  GLfloat y;
  GLfloat z;
  
  // default ctor
  Vec3(void);
  Vec3(GLfloat x, GLfloat y, GLfloat z);
  Vec3(Vec3 *v);
  
  void Clear(void);
  Vec3 ClampTo1(void);
  
  void Set(GLfloat x_, GLfloat y_, GLfloat z_);
  Vec3 Add(GLfloat x_, GLfloat y_, GLfloat z_) const;
  Vec3 Add(const Vec3 v) const;
  Vec3 Add(const Vec3 *v) const;
  Vec3 Sub(const Vec3 v) const;
  Vec3 Sub(const Vec3 *v) const;
  Vec3 MultBy(GLfloat f) const;
  Vec3 DivideBy(GLfloat f) const;
  
  GLfloat Length(void) const;
  // normalize this vector's internal data.
  void Normalize(void);
  // leave self alone, but return a normalized version of self.
  Vec3 GetNormalized(void);
  
  Vec3 RotateYDeg(float fDeg) const;
  
  GLfloat r(void);
  GLfloat g(void);
  GLfloat b(void);
  
};

// some useful routines that don't really belong as part of a class.
GLfloat maxf(GLfloat num1, GLfloat num2);
Vec3 vec3_direction(const Vec3 *p, const Vec3 *q);
GLfloat vec3_dot(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_cross(const Vec3 *v, const Vec3 *w);
Vec3 vec3_normal(const Vec3 *v1, const Vec3 *v2, const Vec3 *v3, bool bNormalize);
Vec3 vec3_normal(const Vec3 v1, const Vec3 v2, const Vec3 v3, bool bNormalize);
Vec3 vec3_avg(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_avg(const Vec3 *v1, const Vec3 *v2, const Vec3 *v3, const Vec3 *v4);
Vec3 vec3_reflect(const Vec3 *v1, const Vec3 *norm);
GLfloat vec3_distance(const Vec3 *p, const Vec3 *q);
Vec3 vec3_get_spherical_uv(const Vec3 *vCenter, const Vec3 *vPointOnSphere);
bool points_same_side_of_ab(Vec3 *p1, Vec3 *p2, Vec3 *a, Vec3 *b);

typedef Vec3 RTColor;

RTColor color_modulate(const RTColor *c1, const RTColor *c2);

#endif
