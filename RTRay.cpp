//
//  RTRay.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <Iostream>
#include "VecMath.h"
#include "RTRay.h"

RTRay::RTRay(void) {
  iBouncesLeft = 0;
  
}

// ****************************************************
RTRay::RTRay(Vec3 vInitStart, Vec3 vInitDir, int iNumBounces) {
  vStart = vInitStart;
  vDir = vInitDir;
  iBouncesLeft = iNumBounces;
  
}

// ****************************************************
RTRay::~RTRay(void) {
  // default dtor does nothing.
  
}


// ****************************************************
// what is the point at the specified t-value?
Vec3 RTRay::PointAtTValue(float t) {
  // add the direction multiplied by the t-value and return result
  Vec3 vRet = vStart.Add(vDir.MultBy(t));
  return vRet;
  
}

// ****************************************************
// if last bounce, return false. ray is dead at that point.
void RTRay::SetBounces(int iBounces) {
  iBouncesLeft = iBounces;
  
}

// ****************************************************
// Remove a bounce. Returns true if the ray is still alive.
bool RTRay::RemoveBounce(void) {
  iBouncesLeft--;
  if(iBouncesLeft < 0)
    iBouncesLeft = 0;
  
  return HasBouncesLeft();
  
}

// ****************************************************
bool RTRay::HasBouncesLeft(void) {
  return(iBouncesLeft > 0);
  
}

// ***************************************************
int RTRay::GetBouncesLeft(void) {
  return iBouncesLeft;
  
}

// ***************************************************
// advance the start position into dir by the specified amount.
void RTRay::Advance(GLfloat t) {
  Vec3 vToAdd = vDir.GetNormalized().MultBy(t);
  vStart = vStart.Add(vToAdd);

}

// ***************************************************
// default ctors, etc.
RTHitResult::RTHitResult(void) {
  Clear();
  
}

// ****************************************************
RTHitResult::~RTHitResult(void) {
  Clear();
  
}

// ****************************************************
// is the hit result closer than another
void RTHitResult::Clear(void) {
  bHit = false;
  t = 0.0f;
  vPointHit.Set(0.0f, 0.0f, 0.0f);
  vNormalHit.Set(0.0f, 0.0f, 0.0f);
  matHit = (RTMaterial_Type) 0;
  texHit = TEX_NONE;
  Vec3 texUV = Vec3(0.0f, 0.0f, 0.0f);
  
}

// ****************************************************
bool RTHitResult::IsAHit(void) {
  return bHit;
  
}

// ****************************************************
bool RTHitResult::IsCloserThan(RTHitResult *hOther) {
  if(!this->IsAHit()) return false;
  
  // closer if either hte other isn't a hit, or it is,
  // but we are closer.
  return(!hOther->IsAHit() || (this->t < hOther->t));
  
}