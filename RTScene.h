//
//  RTScene.h
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef GL_Project4_RTScene_h
#define GL_Project4_RTScene_h

#include "common.h"
#include "VecMath.h"
#include "RTLight.h"

class RTPrimitive;
class RTRay;
class RTLight;
class RTCanvas;
class RTCamera;
class RTMaterial;
class RTHitResult;

const int iMaxMaterials = 8;
const int iMaxLights = 10;
const int iMaxPrimitives = 10;
const int iMaxTextures = 3;

// max level rays can go to.
const int iMaxRayDepth = 5;

typedef unsigned int uint32_t;

enum RTPrimitive_Type {
  PRIM_NONE = 0,
  PRIM_SPHERE = 1,
  PRIM_CUBE = 2,
  PRIM_PYRAMID = 3,
  
};

enum RTSetting {
  SETT_AMBIENT = 1,
  SETT_DIFFUSE = 2,
  SETT_SPECULAR = 4,
  SETT_REFLECTION = 8,
  SETT_TRANSPARENCY = 16,
  SETT_TEXTURING = 32,
  SETT_ANTIALIAS = 64,
  SETT_ATTENUATION = 128,
 // SETT_BUMP = 256,
 // SETT_REFRACTION = 512

};

enum RTMaterial_Type {
  MAT_RED_RUBBER = 0,
  MAT_JADE = 1,
  MAT_BLUE_EMERALD = 2,
  MAT_BLACK_RUBBER = 3,
  MAT_CHROME = 4,
  MAT_CLEAR = 5,
  MAT_CLEAR_TRANS = 6,
  MAT_MIRROR = 7,
  MAT_NONE = 8
  
};

enum RTTexture_Type {
  TEX_BACKGROUND = 0,
  TEX_MARS = 1,
  TEX_EARTH = 2,
  TEX_NONE = 3
  
};

void pFree(RTPrimitive *p);
void pFree(RTLight *l);
void pFree(RTMaterial *m);

/**************************************************************
 * RTScene
 * Scene is highest layer object.  Has lights, primitives,
 * and allows render from a given eye point into a frame 
 * buffer
 *************************************************************/
class RTScene {
private:  
  // materials, lights, primitives.
  // prims have a pointer to a preallocated material.
  // (material settings NOT saved per-object)
  RTMaterial * mats[iMaxMaterials];
  RTLight * lights[iMaxLights];
  RTPrimitive * prims[iMaxPrimitives];
  
  uint32_t settings;
  
  // how deep can rays go?  5 levels? 
  uint32_t iRayDepth;
  
  RTTexture textures[iMaxTextures];
  
public:
  // default constructor
  RTScene(void);  
  ~RTScene(void);
  
  bool IncreaseRayDepth(void);
  bool DecreaseRayDepth(void);
  void SetRayDepth(uint32_t depth);
  uint32_t GetRayDepth(void);
  
  // cleanup code
  void RemoveAllMaterials(void);
  void RemoveAllLights(void);
  void RemoveAllPrimitives(void);
  
  void LoadBackground(char *filename);
  
  // adding code
  int AddLight(RTLight *light);
  int AddRandomLight(void);
  int GetNumLights(void);

  void LoadMaterialPresets(void);
  RTMaterial * GetMaterial(RTMaterial_Type mat);
  RTLight * GetLightWithIndex(int lightIndex);
  RTPrimitive * GetPrimitiveWithIndex(int primIndex);
  
  int AddPrimitive(RTPrimitive *p);
  int AddRandomPrimitive(void); 
  int GetNumPrimitives(void);

  void CreateRandomScene(void);  
  void CreateSimpleScene(void);
  void LoadPresetScene1(void);
  void LoadPresetScene2(void);
  void LoadPresetScene3(void);
  void ExportScript(void);
  
  // render the scene to the canvas.
  void RenderToCanvas(RTCamera *cam, RTCanvas *canvas);
  RTColor CalculateIntensity(RTCamera *cam, RTRay *r, int screenX, int screenY);
  RTHitResult GetNearestHit(RTRay *r);

  
  /*** render settings ***/
  void Enable(RTSetting s);
  void Disable(RTSetting s);
  bool Toggle(RTSetting s);
  bool IsEnabled(RTSetting s);
  
};


#endif

