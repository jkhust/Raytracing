//
//  RTPrimitive.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTPrimitive_h
#define GL_Project4_RTPrimitive_h

#include <math.h>
#include "common.h"
#include "VecMath.h"
#include "RTRay.h"
#include "RTScene.h"

/**************************************************************
 * RTPrimitive
 * Abstract base class for scene objects.
 * All scene objects must derive, then implement hit 
 * detection capability.
 *************************************************************/
class RTPrimitive {
protected:
  // every primitive has a position and a material
  Vec3 vPos;
  RTMaterial_Type mat;
  RTTexture_Type tex;
  
  // show this primitive?  used to toggle prims on and off
  // for testing.
  bool bShow;
  
public:
  RTPrimitive(Vec3 vPos_, RTMaterial_Type mat);
  ~RTPrimitive(void);
  
  // toggle whether to show this object.
  bool ToggleShow(void);
  bool IsShowing(void);
  
  void SetPos(Vec3 vPos_);
  Vec3 GetPos(void);

  
  void SetMaterial(RTMaterial_Type matIndex);
  RTMaterial_Type GetMaterial(void);
  
  void SetTexture(RTTexture_Type texIndex);
  RTTexture_Type GetTexture(void);
  
  
  // overridable by children
  virtual void Move(GLfloat x, GLfloat y, GLfloat z);
  virtual void CycleMaterial();
  virtual void CycleTexture();
  
  // all child classes of primitive override the hit result
  // method (sphere intersection, triangle intersection, 
  //         NURBS intersection, etc.)
  virtual RTHitResult GetHitResult(RTRay *r);
  
  
  // *** export commands ***
  virtual void ExportCommands(int useIndex);
  
};

/**************************************************************
 * RTSphere
 * Simplest scene object.  Uses bounding sphere for 
 * hit detection.
 *************************************************************/
class RTSphere: public RTPrimitive {
protected:
  // radius of sphere
  float fRad;
  
public:
  RTSphere(Vec3 vInitPos, float fInitRad, RTMaterial_Type mat);
  ~RTSphere(void);
  
  // set radius
  void SetRad(float fRad_);
  
  // ray collision calculation;
  RTHitResult GetHitResult(RTRay *r);
  Vec3 GetNormalAtPoint(Vec3 *p);
  
  // *** export commands ***
  void ExportCommands(int useIndex);
  
};


/**************************************************************
 * RTPlane
 * Plane Object
 * Already has a position from parent.
 * Now it needs actual vertices.
 *************************************************************/
class RTPlane: public RTPrimitive {
protected:
  Vec3 vNormal;

public:
  RTPlane(Vec3 vInitPos, RTMaterial_Type mat);
  ~RTPlane(void);

  void SetNormal(GLfloat x, GLfloat y, GLfloat z);
  
  // get hit result with a ray.
  RTHitResult GetHitResult(RTRay *r);
  // get normal at point (will be same as anywhere.)
  Vec3 GetNormalAtPoint(Vec3 *p);
  
};

/**************************************************************
 * RTPolygon
 * Polygon Object
 * Has a position, but also has individual vertices that 
 * make up the polygon.
 * Handles triangle or quad.
 *************************************************************/
class RTPolygon: public RTPrimitive {
protected:
  int iNumVertices;
  Vec3 verts[4];
  Vec3 vNormal;
  
public:
  RTPolygon(Vec3 vInitPos, RTMaterial_Type mat);
  ~RTPolygon(void);
  
  bool AddVertex(Vec3 *v);
  bool AddVertex(GLfloat x, GLfloat y, GLfloat z);
  void GenerateNormal(void);
  
  void Move(GLfloat x, GLfloat y, GLfloat z);
  
  // get hit result with a ray.
  RTHitResult GetHitResult(RTRay *r);
  // get normal at point (will be same as anywhere.)
  Vec3 GetNormalAtPoint(Vec3 *p);
  bool PointInside(Vec3 *p);
  bool OnSameSide(Vec3 *p1, Vec3 *p2, Vec3 *a, Vec3 *b); 
    
  // *** export commands ***
  void ExportCommands(int useIndex);
  
};

/**************************************************************
 * RTCube
 * Cube Object
 * Has a position and size.
 * Makes 6 faces around it.
 *************************************************************/
class RTCube: public RTPrimitive {
protected:
  RTPolygon *sides[6];
  GLfloat fWidth;
  
public:
  RTCube(Vec3 vInitPos, GLfloat fSize, RTMaterial_Type mat);
  ~RTCube(void);
  
  // get hit result with a ray.
  RTHitResult GetHitResult(RTRay *r);

  // overrides moving and cycling of texture and material, to apply
  // to all polygons
  void Move(GLfloat x, GLfloat y, GLfloat z);
  void CycleMaterial(void);
  void CycleTexture(void);
  
};


#endif
