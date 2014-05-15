//
//  RTRay.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTRay_h
#define GL_Project4_RTRay_h

class Vec3;
class RTMaterial;
class RTHitResult;

#include "RTScene.h"

/**************************************************************
 * RTRay
 * Holds position and direction of the current ray being worked with.
 * holds a lifetime value so we can keep track of the number of 
 * bounces left.
 *************************************************************/
class RTRay {
private:
  // keep this private so we use accessors to modify it.
  int iBouncesLeft;
  
public:
  Vec3 vStart;
  Vec3 vDir;

  RTRay(void);
  RTRay(Vec3 vInitStart, Vec3 vInitDir, int iNumBounces);
  ~RTRay(void);
    
  // what is the point at the specified t-value?
  void SetStart(float x, float y, float z);
  Vec3 PointAtTValue(float t);

  // if last bounce, return false. ray is dead at that point.
  void SetBounces(int iBounces);
  bool RemoveBounce(void);
  bool HasBouncesLeft(void);
  int GetBouncesLeft(void);
  
  // advance the start position into dir by the specified amount.
  void Advance(GLfloat t);
  
};

/**************************************************************
 * RTHitResult
 * Derived classes of RTPrimitive can calculate their intersection
 * data with a given ray, and return the value in a RTHitResult.
 * This conveniently packages all data needed to perform proper
 * shading for a given canvas pixel.
 *************************************************************/
class RTHitResult {
public:
  // is it a hit?
  bool bHit;
  // t-value of the hit.
  float t;
  // what was the point where the hit occurred.
  Vec3 vPointHit;
  // normal where the hit occurred.
  Vec3 vNormalHit;
  // material where the hit occurred
  RTMaterial_Type matHit;
  // texture for object where hit occurred, and coordinates.
  RTTexture_Type texHit;
  Vec3 texUV;
  
  // default ctors, etc.
  RTHitResult(void);
  ~RTHitResult(void);
  
  // is the hit result closer than another
  void Clear(void);
  bool IsAHit(void);
  bool IsCloserThan(RTHitResult *hOther);
  
};

#endif
