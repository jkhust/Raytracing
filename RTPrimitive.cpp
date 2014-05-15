//
//  RTPrimitive.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RTPrimitive.h"
#include "assert.h"

// ************************************************************
RTPrimitive::RTPrimitive(Vec3 vPos, RTMaterial_Type mat) {
  SetPos(vPos);
  SetMaterial(mat);
  
  // no texture by default.
  SetTexture(TEX_NONE);
  
  // show this object by default.
  bShow = true;
  
}

// ************************************************************
RTPrimitive::~RTPrimitive(void) {
  // no cleanup code
  
}

// ************************************************************
// set position
void RTPrimitive::SetPos(Vec3 vPos_) {
  vPos = vPos_;
  
}

// ************************************************************
// toggle whether to show this object.
bool RTPrimitive::ToggleShow(void) {
  bShow = !bShow;
  
  return bShow;
  
}


// ************************************************************
bool RTPrimitive::IsShowing(void) {
  return bShow;
  
}

// ************************************************************
void RTPrimitive::SetMaterial(RTMaterial_Type matIndex) {
  mat = matIndex;
  
}

// ************************************************************
RTMaterial_Type RTPrimitive::GetMaterial(void) {
  return mat;
  
}

// ************************************************************
void RTPrimitive::SetTexture(RTTexture_Type texIndex) {
  tex = texIndex;
  
}

// ************************************************************
RTTexture_Type RTPrimitive::GetTexture(void) {
  return tex;
  
}

// ************************************************************
// cycle through material
void RTPrimitive::CycleMaterial() {
  mat++;
  if(mat >= MAT_NONE)
    mat = MAT_RED_RUBBER;
  
}

// ************************************************************
// cycle through material
void RTPrimitive::CycleTexture() {
  tex++;
  if(tex > TEX_NONE)
    tex = TEX_MARS;
  
}

// ************************************************************
// all child classes of primitive override the hit result
// method (sphere intersection, triangle intersection, 
//         NURBS intersection, etc.)
RTHitResult RTPrimitive::GetHitResult(RTRay *r) { 
  // virtual does nothing.
  RTHitResult hr;
  return hr;
  
}

// ************************************************************
Vec3 RTPrimitive::GetPos(void) {
  return vPos;

}

// ************************************************************
void RTPrimitive::Move(GLfloat x, GLfloat y, GLfloat z) {
  vPos = vPos.Add(x, y, z);
  
}

// ************************************************************
void RTPrimitive::ExportCommands(int useIndex) {
  printf("Unimplemented.\n");
  
}

// ************************************************************
RTSphere::RTSphere(Vec3 vInitPos, float fInitRad, RTMaterial_Type mat) :
  RTPrimitive(vInitPos, mat) {
  
  SetRad(fInitRad);
  
}

// ************************************************************
RTSphere::~RTSphere(void) {
  // no cleanup needed
  
}

// ************************************************************
// set radius
void RTSphere::SetRad(float fRad_) {
  fRad = fRad_;
  
}

// ************************************************************
// ray collision calculation;
RTHitResult RTSphere::GetHitResult(RTRay *r) {
  RTHitResult hr;
  hr.Clear();
  
  /* transform ray so that sphere center is at origin */
  /* don't use matrix, just translate! */
  Vec3 org = r->vStart.Sub(this->vPos);
    
  /* coefficients of quadratic equation */
  double a = vec3_dot(&r->vDir, &r->vDir);
  double b = 2 * vec3_dot(&r->vDir, &org);
  double c = vec3_dot(&org, &org) - (this->fRad * this->fRad);
  
  /* discriminant */
  double D = b * b - 4 * a * c;
  
  /* no intersection */
  if (D < 0)  /* no intersection */
    return hr;
  
  D = sqrt(D);
    
    double t;
    /* First check the root with the lower value of t: */
    /* this one, since D is positive */
    t = (-b - D) / (2*a);
    /* ignore roots which are less than zero (behind viewpoint) */
    if (t < 0) {
      t = (-b + D) / (2*a);
    }
    
    if (t < 0) { 
      return(hr);
      
    } else {
      // build a hit result and return it.
      hr.bHit = true;
      hr.t = t;
      hr.vPointHit = r->PointAtTValue(t);
      hr.vNormalHit = this->GetNormalAtPoint(&hr.vPointHit);
      hr.matHit = this->GetMaterial();
      hr.texHit = this->GetTexture();
      
      // calculate UV coords based on point hit, if there is a texture.
      if(hr.texHit != TEX_NONE)
        hr.texUV = vec3_get_spherical_uv(&this->vPos, &hr.vPointHit);
      
      return hr;
      
    }
    
  
  //return hr;
  
}

// ************************************************************
Vec3 RTSphere::GetNormalAtPoint(Vec3 *p) {
  Vec3 n;
  n.x = (p->x - this->vPos.x) / this->fRad;  
  n.y = (p->y - this->vPos.y) / this->fRad;
  n.z = (p->z - this->vPos.z) / this->fRad;
  
  return n;
  
}

// ************************************************************
void RTSphere::ExportCommands(int useIndex) {
  printf("\n");
  printf("RTSphere * sphere%d = new RTSphere( Vec3(%f,%f,%f), %f, (RTMaterial_Type) %d);\n", 
         useIndex, vPos.x, vPos.y, vPos.z, fRad, mat);
  printf("sphere%d->SetTexture( (RTTexture_Type) %d);\n", useIndex, tex);  
  printf("AddPrimitive(sphere%d);\n", useIndex);
  
}

// ************************************************************
RTPlane::RTPlane(Vec3 vInitPos, RTMaterial_Type mat) :
RTPrimitive(vInitPos, mat) {
  
}

// ************************************************************
RTPlane::~RTPlane(void) {
  // no cleanup code
  
}

// ************************************************************
void RTPlane::SetNormal(GLfloat x, GLfloat y, GLfloat z) {
  vNormal = Vec3(x, y, z);
  
}

// ************************************************************
// get hit result with a ray.
RTHitResult RTPlane::GetHitResult(RTRay *r) {  
  /*
  Ray = r->vStart + t * r->vDir
   and
  vNormal dot (vOrigin - vPointOnPlane) = 0.
  
  So substitute the ray equation r(t) in for x and solve for t:
    
    vNormal dot (vOrigin - ray(t)) = 0
    vNormal dot (vOrigin - vStart - vDir*t) = 0
    vNormal dot (vOrigin - vStart) = (vNormal dot vDir) * t
    t = [ vNormal dot (vOrigin - vStart) ] / (vNormal dot vDir)
  */
  
  Vec3 vDirToOrigin = vPos.Sub(r->vStart);
  vDirToOrigin.Normalize();
  
  Vec3 vDirNormalized = r->vDir.GetNormalized();
  
  
  GLfloat numerator = vec3_dot(&vNormal, &vDirToOrigin);
  GLfloat denominator = vec3_dot(&vNormal, &vDirNormalized);

  GLfloat t = (GLfloat) (numerator / denominator);
  
  RTHitResult hr;
  hr.Clear();
  
  // if line wasn't parallel or directly on the plane,
  if(t >= 0) {
    // find point hit
    hr.vPointHit = r->PointAtTValue(t);
    
    // if point hit was at a reasonable distance
    if(vec3_distance(&r->vStart, &hr.vPointHit) > 30) {
      hr.bHit = false;
      return hr;
    
    } else {
      // return a hit result containing the point, normal, etc.
      hr.bHit = true;
      hr.t = t;
      hr.vNormalHit = vNormal;
      hr.matHit = mat;
      
    }

  }
  
  return hr;
  
}

// ************************************************************
// get normal at point (will be same as anywhere.)
Vec3 RTPlane::GetNormalAtPoint(Vec3 *p) {
  // normal is the same at any point.
  return vNormal;
  
}

// ************************************************************
RTPolygon::RTPolygon(Vec3 vInitPos, RTMaterial_Type mat) :
  RTPrimitive(vInitPos, mat) {
  
  // start with no vertices
  iNumVertices = 0;
  verts[0].Clear();
  verts[1].Clear();
  verts[2].Clear();
  verts[3].Clear();
    
  vNormal.Clear();
  
}

// ************************************************************
RTPolygon::~RTPolygon(void) {
  // no cleanup code
  
}

// ************************************************************
bool RTPolygon::AddVertex(Vec3 *v) {
  return AddVertex(v->x, v->y, v->z);
  
}


// ************************************************************
bool RTPolygon::AddVertex(GLfloat x, GLfloat y, GLfloat z) {
  iNumVertices++;
  
  verts[iNumVertices - 1].x = vPos.x + x;
  verts[iNumVertices - 1].y = vPos.y + y;
  verts[iNumVertices - 1].z = vPos.z + z;
  
  if(iNumVertices >= 3)
    GenerateNormal();
  
  return true;
  
}

// ************************************************************
void RTPolygon::Move(GLfloat x, GLfloat y, GLfloat z) {
  for(int i=0;i<iNumVertices; i++)
    verts[i] = verts[i].Add(x, y, z);
  
}

// ************************************************************
void RTPolygon::GenerateNormal(void) {
  vNormal = vec3_normal(verts[0], verts[1], verts[2], true);
  
}

// ************************************************************
// get hit result with a ray.
RTHitResult RTPolygon::GetHitResult(RTRay *r) {
  // hit result means find out the intersection in the plane.
  // then, find out if the intersection point is within
  // the 
  
  Vec3 vDirToOrigin = verts[0].Sub(r->vStart);
  vDirToOrigin.Normalize();
  
  Vec3 vDirNormalized = r->vDir.GetNormalized();
  
  
  GLfloat numerator = vec3_dot(&vNormal, &vDirToOrigin);
  GLfloat denominator = vec3_dot(&vNormal, &vDirNormalized);
  
  GLfloat t = (GLfloat) (numerator / denominator);
  
  RTHitResult hr;
  hr.Clear();
  
  // if line wasn't parallel or directly on the plane,
  if(t >= 0) {
    // find point hit
    hr.vPointHit = r->PointAtTValue(t);
    
    // if point hit was not inside the polygon,
    if(!PointInside(&hr.vPointHit)) {
      // return a failed hit test.
      hr.bHit = false;
      return hr;
      
    } else {
      // return a hit result containing the point, normal, etc.
      hr.bHit = true;
      hr.t = t;
      hr.vNormalHit = vNormal;
      hr.matHit = mat;
      
    }
    
  }
  
  return hr;
    
}

// ************************************************************
// get normal at point (will be same as anywhere.)
Vec3 RTPolygon::GetNormalAtPoint(Vec3 *p) {
  return vNormal;
  
}

// ************************************************************
bool RTPolygon::PointInside(Vec3 *p) {
  // be sure to account for the actual position of the vertex
  Vec3 worldVert0 = vPos.Add(verts[0]);
  Vec3 worldVert1 = vPos.Add(verts[1]);
  Vec3 worldVert2 = vPos.Add(verts[2]);
  Vec3 worldVert3 = vPos.Add(verts[3]);
  
  
  // for each edge of the polygon,
  // see if the point is on the inside
  // by using the dot product of that edge with a third point on the polygon.
  // and seeing if the resulting dot product is the same.
  
  // algorithm found here:
  // http://www.blackpawn.com/texts/pointinpoly/
  
  // need 3 or 4 vertices.
  assert(iNumVertices >= 3 && iNumVertices <= 4);
  
  if(iNumVertices == 3) {
    // if the point lines on the inside of every edge.
    // (only use the fourth vertex if we need it)
    if(points_same_side_of_ab(p, &worldVert2, &worldVert1, &worldVert0) &&
       points_same_side_of_ab(p, &worldVert0, &worldVert2, &worldVert1) &&
       points_same_side_of_ab(p, &worldVert1, &worldVert0, &worldVert2))
      return true;
    else
      return false;
    
  } else if(iNumVertices == 4) {
    // if the point lines on the inside of every edge.
    // (only use the fourth vertex if we need it)
    if(points_same_side_of_ab(p, &worldVert2, &worldVert1, &worldVert0) &&
       points_same_side_of_ab(p, &worldVert3, &worldVert2, &worldVert1) &&
       points_same_side_of_ab(p, &worldVert0, &worldVert3, &worldVert2) &&
       points_same_side_of_ab(p, &worldVert1, &worldVert3, &worldVert0))
      return true;
    else
      return false;
    
  } else {
    return false;
    
  }

}

// ************************************************************
void RTPolygon::ExportCommands(int useIndex) {
  printf("\n");
  printf("RTPolygon * poly%d = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) %d);\n", useIndex,mat);
  
  for(int i=0;i<iNumVertices; i++) {
    printf("poly%d->AddVertex(%f,%f,%f);\n", useIndex, verts[i].x, verts[i].y, verts[i].z);
    
  }

  printf("poly%d->GenerateNormal();\n", useIndex);
 
  printf("AddPrimitive(poly%d);\n", useIndex);
  
}

// ************************************************************
RTCube::RTCube(Vec3 vInitPos, GLfloat fSize, RTMaterial_Type mat) :
  RTPrimitive( vInitPos, mat) {

  GLfloat pos = fSize / 2.0f;
  GLfloat neg = -1.0f * (fSize / 2.0f);
      
  // bottom
  sides[0] = new RTPolygon( vInitPos, mat);
  sides[0]->AddVertex(neg, neg, neg);
  sides[0]->AddVertex(pos, neg, neg);
  sides[0]->AddVertex(pos, neg, pos);
  sides[0]->AddVertex(neg, neg, pos);
  
  // front
  sides[1] = new RTPolygon( vInitPos, mat);
  sides[1]->AddVertex(neg, neg, neg);
  sides[1]->AddVertex(pos, neg, neg);
  sides[1]->AddVertex(pos, pos, neg);
  sides[1]->AddVertex(neg, pos, neg);
  
  // left
  sides[2] = new RTPolygon( vInitPos, mat);
  sides[2]->AddVertex(neg, neg, neg);
  sides[2]->AddVertex(neg, pos, neg);
  sides[2]->AddVertex(neg, pos, pos);
  sides[2]->AddVertex(neg, neg, pos);
  
  // right
  sides[3] = new RTPolygon( vInitPos, mat);
  sides[3]->AddVertex(pos, neg, neg);
  sides[3]->AddVertex(pos, pos, pos);
  sides[3]->AddVertex(pos, neg, pos);
  sides[3]->AddVertex(pos, pos, neg);
  
  // back
  sides[4] = new RTPolygon( vInitPos, mat);
  sides[4]->AddVertex(pos, pos, pos);
  sides[4]->AddVertex(neg, pos, pos);
  sides[4]->AddVertex(neg, neg, pos);
  sides[4]->AddVertex(pos, neg, pos);
  
  // top
  sides[5] = new RTPolygon( vInitPos, mat);
  sides[5]->AddVertex(neg, pos, neg);
  sides[5]->AddVertex(pos, pos, neg);
  sides[5]->AddVertex(pos, pos, pos);
  sides[5]->AddVertex(neg, pos, pos);
  
}

// ************************************************************
RTCube::~RTCube(void) {
  // no cleanup code
  for(int i=0; i < 6; i++) {
    delete sides[i];
    sides[i] = NULL;
    
  }
  
}

// ************************************************************
// get hit result with a ray.
RTHitResult RTCube::GetHitResult(RTRay *r) {
  RTHitResult hrNearest;
  hrNearest.Clear();
  
  // for each side,
  for(int i=0;i < 6; i++) {
    RTHitResult hr;
    hr.Clear();
    
    // test against code
    hr = sides[i]->GetHitResult(r);
    
    // use it if closer
    if(hr.IsCloserThan(&hrNearest))
      hrNearest = hr;
    
  }
  
  return hrNearest;
  
}

// ************************************************************
void RTCube::Move(GLfloat x, GLfloat y, GLfloat z) {
  for(int i=0;i<6;i++)
    sides[i]->Move(x, y, z);
  
}

// ************************************************************
void RTCube::CycleMaterial() {
  for(int i=0;i<6;i++)
    sides[i]->CycleMaterial();
  
}

// ************************************************************
void RTCube::CycleTexture() {
  for(int i=0;i<6;i++)
    sides[i]->CycleTexture();
  
}