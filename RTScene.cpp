//
//  RTScene.cpp
//  GL_Project4
//
//  Created by Justin Hust on 4/19/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "VecMath.h"
#include "RTRay.h"
#include "RTcamera.h"
#include "RTCanvas.h"
#include "RTScene.h"
#include "RTLight.h"
#include "RTPrimitive.h"

// *************************************************************
int rand_int(int min, int max) {
  return rand() % (max-min) + min;
  
}

// *************************************************************
GLfloat rand_float(GLfloat min, GLfloat max) {
  return(min + (float)rand() / ((float)RAND_MAX / ( max - min )));
  
}

// *******************************************************
// return a random float in the range 0.0f to 1.0f
GLfloat rand_float(GLfloat max) {
  return (float)rand() / ((float)RAND_MAX / max);
  
}

// ********************************************************
void pFree(RTPrimitive **p) {
  if(p != NULL)
    delete *p;
  
  *p = NULL;
  
}

// ********************************************************
void pFree(RTLight **l) {
  if(l != NULL)
    delete *l;
  
  *l = NULL;
  
}

// ********************************************************
void pFree(RTMaterial **m) {
  if(m != NULL)
    delete *m;
  
  *m = NULL;
  
}

// ********************************************************
RTScene::RTScene(void) {
  // reset all materials and init all prims, lights, etc.
  for(int i=0; i < iMaxMaterials; i++)
    mats[i] = NULL;
  
  for(int i=0; i < iMaxLights; i++)
    lights[i] = NULL;
  
  for(int i=0; i < iMaxPrimitives; i++)
    prims[i] = NULL;
  
  LoadMaterialPresets();
  
  textures[TEX_BACKGROUND].LoadFile("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/space.ppm");
  textures[TEX_MARS].LoadFile("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/mars_hi.ppm");
  textures[TEX_EARTH].LoadFile("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/earth.ppm");
  
  Enable(SETT_AMBIENT);
  Enable(SETT_DIFFUSE);
  Enable(SETT_SPECULAR);
  Enable(SETT_REFLECTION);
  Enable(SETT_TRANSPARENCY);
  Enable(SETT_TEXTURING);
  Disable(SETT_ANTIALIAS);
  Enable(SETT_ATTENUATION);
  
//  Enable(SETT_BUMP);
//  Enable(SETT_REFRACTION);

  iRayDepth = 5;

}

// ********************************************************
void RTScene::LoadMaterialPresets(void) {
  mats[MAT_RED_RUBBER] = new RTMaterial();
  mats[MAT_RED_RUBBER]->SetAmbient(0.05f, 0.0f, 0.0f);
  mats[MAT_RED_RUBBER]->SetDiffuse(0.5f, 0.4f, 0.4f);
  mats[MAT_RED_RUBBER]->SetSpecular(0.7f, 0.04f, 0.04f); 
  mats[MAT_RED_RUBBER]->SetShininess(.078125f * 128.0f); 
  mats[MAT_RED_RUBBER]->SetOpacity(1.0f);
  
  mats[MAT_JADE] = new RTMaterial();
  mats[MAT_JADE]->SetAmbient(0.135f, 0.2225f, 0.1575f);
  mats[MAT_JADE]->SetDiffuse(0.54f, 0.89f, 0.63f);
  mats[MAT_JADE]->SetSpecular(0.316228f, 0.316228f, 0.316228f); 
  mats[MAT_JADE]->SetShininess(.1f * 128.0f);
  mats[MAT_JADE]->SetOpacity(1.0f);
  
  mats[MAT_BLUE_EMERALD] = new RTMaterial();
  mats[MAT_BLUE_EMERALD]->SetAmbient(0.0215f, 0.0215f, 0.1745f);
  mats[MAT_BLUE_EMERALD]->SetDiffuse(0.07568f, 0.07568f, 0.61424f);
  mats[MAT_BLUE_EMERALD]->SetSpecular(0.633f, 0.633f, 0.727811f); 
  mats[MAT_BLUE_EMERALD]->SetShininess(.4f * 128.0f);
  mats[MAT_BLUE_EMERALD]->SetOpacity(1.0f);
  
  mats[MAT_CHROME] = new RTMaterial();
  mats[MAT_CHROME]->SetAmbient(0.25f, 0.25f, 0.25f);
  mats[MAT_CHROME]->SetDiffuse(0.4f, 0.4f, 0.4f);
  mats[MAT_CHROME]->SetSpecular(0.774597f, 0.774597f, 0.774597f); 
  mats[MAT_CHROME]->SetShininess(.6f * 128.0f); 
  mats[MAT_CHROME]->SetOpacity(1.0f);
  
  mats[MAT_BLACK_RUBBER] = new RTMaterial();
  mats[MAT_BLACK_RUBBER]->SetAmbient(0.02f, 0.02f, 0.02f);
  mats[MAT_BLACK_RUBBER]->SetDiffuse(0.01f, 0.01f, 0.01f);
  mats[MAT_BLACK_RUBBER]->SetSpecular(0.4f, 0.4f, 0.4f); 
  mats[MAT_BLACK_RUBBER]->SetShininess(.078125f * 128.0f); 
  mats[MAT_BLACK_RUBBER]->SetOpacity(1.0f);
  
  mats[MAT_CLEAR] = new RTMaterial();
  mats[MAT_CLEAR]->SetAmbient(0.0f, 0.0f, 0.0f);
  mats[MAT_CLEAR]->SetDiffuse(0.3f, 0.3f, 0.3f);
  mats[MAT_CLEAR]->SetSpecular(0.2f, 0.2f, 0.2f); 
  mats[MAT_CLEAR]->SetShininess(0.0f * 128.0f);
  mats[MAT_CLEAR]->SetOpacity(1.0f);
  
  mats[MAT_CLEAR_TRANS] = new RTMaterial();
  mats[MAT_CLEAR_TRANS]->SetAmbient(0.0f, 0.0f, 0.0f);
  mats[MAT_CLEAR_TRANS]->SetDiffuse(1.0f, 1.0f, 1.0f);
  mats[MAT_CLEAR_TRANS]->SetSpecular(0.2f, 0.2f, 0.2f); 
  mats[MAT_CLEAR_TRANS]->SetShininess(0.1f * 128.0f);
  mats[MAT_CLEAR_TRANS]->SetOpacity(0.3f);

  mats[MAT_MIRROR] = new RTMaterial();
  mats[MAT_MIRROR]->SetAmbient(0.0f, 0.0f, 0.0f);
  mats[MAT_MIRROR]->SetDiffuse(0.0f, 0.0f, 0.0f);
  mats[MAT_MIRROR]->SetSpecular(1.0f, 1.0f, 1.0f); 
  mats[MAT_MIRROR]->SetShininess(96.0f);
  mats[MAT_MIRROR]->SetOpacity(1.0f);
  
}

// ********************************************************
RTMaterial * RTScene::GetMaterial(RTMaterial_Type mat) {
  return mats[mat];
  
}

// ********************************************************
RTScene::~RTScene(void) {
  RemoveAllPrimitives();
  RemoveAllLights();
  RemoveAllMaterials();

}

// ********************************************************
bool RTScene::IncreaseRayDepth(void) {
  if(iRayDepth + 1 > iMaxRayDepth)
    return false;
  
  iRayDepth++;
  return true;
  
}

// ********************************************************
bool RTScene::DecreaseRayDepth(void) {
  if(iRayDepth - 1 < 1)
    return false;
  
  iRayDepth--;
  return true;
  
}

// ********************************************************
void RTScene::SetRayDepth(uint32_t depth) {
  iRayDepth = depth;
  
}

// ********************************************************
uint32_t RTScene::GetRayDepth(void) {
  return iRayDepth;
  
}

// ********************************************************
void RTScene::RemoveAllMaterials(void) {
  for(int i=0;i<iMaxMaterials; i++)
    pFree(&mats[i]);
  
}

// ********************************************************
void RTScene::RemoveAllLights(void) {
  for(int i=0;i<iMaxLights; i++)
    pFree(&lights[i]);
  
}

// ********************************************************
void RTScene::RemoveAllPrimitives(void) {  
  for(int i=0;i<iMaxPrimitives; i++)
    pFree(&prims[i]);
  
}

// ********************************************************
void RTScene::Enable(RTSetting s) {
  settings |= s;
  
}

// ********************************************************
void  RTScene::Disable(RTSetting s) {
  settings &= ~s;
  
}

// ********************************************************
bool RTScene::Toggle(RTSetting s) {
  settings ^= s;
  
  return IsEnabled(s);
  
}

// ********************************************************
bool RTScene::IsEnabled(RTSetting s) {
  return(settings & (int) s);

}

// ********************************************************
int RTScene::AddPrimitive(RTPrimitive *p) {    
  for(int i=0;i<iMaxPrimitives; i++) {
    if(prims[i] == NULL) {
      prims[i] = p;
      return i;
      
    }
    
  }
  
  return -1;
  
}

// ********************************************************
int RTScene::AddLight(RTLight *l) {    
  for(int i=0;i<iMaxLights; i++) {
    if(lights[i] == NULL) {
      lights[i] = l;
      return i;
      
    }
    
  }
  
  return -1;
  
}

// ********************************************************
int RTScene::GetNumLights(void) {
  int iNumLights = 0;
  
  for(int i=0;i<iMaxLights; i++) {
    if(lights[i] != NULL) {
      iNumLights++;
      
    } else {
      break;
      
    }
    
  }
  
  return iNumLights;

}

// ********************************************************
int RTScene::AddRandomLight(void) {
  GLfloat fAmbient = rand_float(0.2f);
  GLfloat fDiffuse = rand_float(0.6f);
  GLfloat fSpecular = rand_float(0.5f);
  
  for(int i=0;i<iMaxLights; i++) {
    if(lights[i] == NULL) {
      lights[i] = new RTLight();
      lights[i]->SetPos( rand_float(-10.0f, 10.0f), rand_float(-10.0f,10.0f), rand_float(-1.0f, -6.0f) );
      lights[i]->SetAmbient(fAmbient, fAmbient, fAmbient);
      lights[i]->SetDiffuse(fDiffuse, fDiffuse, fDiffuse);
      lights[i]->SetSpecular(fSpecular, fSpecular, fSpecular);
      return i;
      
    }
    
  }
  
  return -1;

}

// ********************************************************
int RTScene::AddRandomPrimitive(void) {
  for(int i=0;i<iMaxPrimitives; i++) {
    if(prims[i] == NULL) {
      
      int pt = PRIM_SPHERE;
      RTMaterial_Type mat = (RTMaterial_Type) rand_int(0, 4);

      switch(pt) {
          // randomly create sphere.
        case PRIM_SPHERE: {
          Vec3 vPos = new Vec3(rand_float(-1.0f,1.0f), rand_float(-1.0f,1.0f), 
                               rand_float(-4.0f, -8.0f));
          float fRad = 0.1f + rand_float(0.3f);
          
          prims[i] = new RTSphere(&vPos, fRad, mat);
          return i;
          break;
          
        }
      
        case PRIM_CUBE:
        case PRIM_PYRAMID:
        case PRIM_NONE:
        default:
          return -1;
          break;
          
      }
      
    }
    
  }
  
  return -1;
  
}

// ********************************************************
int RTScene::GetNumPrimitives(void) {
  int iNumPrimitives = 0;
  
  for(int i=0;i<iMaxPrimitives; i++) {
    if(prims[i] != NULL)
      iNumPrimitives++;
    else {
      break;
    }
  
  }
  
  return iNumPrimitives;
  
}

// ********************************************************
void RTScene::CreateRandomScene(void) {
  LoadBackground("/Users/jkhust/Desktop/GL_Project4/project4_src/space.ppm");
  
  RemoveAllPrimitives();
  RemoveAllLights();
    
  // add a red sphere right in the middle.
  RTSphere *s = new RTSphere( new Vec3(0.0f, 0.0f, -6.0f), 0.25f, MAT_JADE);
 // s->SetTexture(TEX_EARTH);
  AddPrimitive(s);
  
  
  
  // create a light that the sphere with material will interact with
  RTLight *l = new RTLight();
  l->SetPos(1.0f, 3.0f, 0.0f);
  l->SetAmbient(0.3f, 0.3f, 0.3f);
  l->SetDiffuse(0.8f, 0.8f, 0.8f);
  l->SetSpecular(0.8f, 0.8f, 0.8f);
  AddLight(l);

  
  // *** add a floor plane ***
  /*
  RTPlane *p1 = new RTPlane(Vec3(0.0f, -2.0f, 0.0f), MAT_CHROME);
  p1->SetNormal(0.0f, 1.0f, 0.0f);
  
  AddPrimitive(p1);
  */
  
  // *** add floor plane ***
  RTPolygon * poly1 = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) 5);
  poly1->AddVertex(-1.5000000,-2.000000,-3.000000);
  poly1->AddVertex(1.5000000,-2.000000,-3.000000);
  poly1->AddVertex(1.5000000,-2.000000,-9.000000);
  poly1->AddVertex(-1.5000000,-2.000000,-9.000000);
  poly1->GenerateNormal();
  AddPrimitive(poly1);
  
  
  //RTCube *c = new RTCube( Vec3(3.0f, 2.0f, -6.0f), 0.05f, MAT_BLUE_EMERALD);
  //AddPrimitive(c);
  
  
}

// *************************************************************
RTLight * RTScene::GetLightWithIndex(int lightIndex) {
  return lights[lightIndex];
  
}

// *************************************************************
RTPrimitive * RTScene::GetPrimitiveWithIndex(int primIndex) {
  return prims[primIndex];

}

// *************************************************************
// trace eye into scene. record result into framebuffer.
void RTScene::RenderToCanvas(RTCamera *cam, RTCanvas *canvas) {
  // save canvas dimensions for speed.
  int iCanvasWidth = canvas->GetWidth();
  int iCanvasHeight = canvas->GetHeight();
  
  // calculate the image width
  GLfloat imageWidth = 2 * cam->pnear * tan(cam->fovx/2);
  

  // *** send rays into scene for each pixel of display ***
  int i,j;
  for(i=0; i < iCanvasWidth; i++) {
    for(j=0; j < iCanvasHeight; j++) {

      RTColor pixelColor;
      pixelColor.Clear();
      
      // build ray starting from eye point...
      RTRay r;
      r.vStart = cam->vEye;
        r.SetBounces(iRayDepth);
      
      // and find a world pixel to cast towards based on screen dimensions
      Vec3 worldPix;
      worldPix.x = (i-(iCanvasWidth/2))  * ((GLfloat)(imageWidth)) / ( (GLfloat) (iCanvasWidth) );
      worldPix.y = (j-(iCanvasHeight/2)) * ((GLfloat)(imageWidth)) / ( (GLfloat) (iCanvasWidth) );
      worldPix.z = -1 * cam->pnear;
      
      r.vDir = vec3_direction(&r.vStart, &worldPix);      

      // if need to anti-alias,
      if(IsEnabled(SETT_ANTIALIAS)) {
        // do a ray in each of four directions around this pixel
        RTRay rLeft(r.vStart, r.vDir.Add(-0.001f, 0.0f, 0.0f), r.GetBouncesLeft());
        RTRay rRight(r.vStart, r.vDir.Add(0.001f, 0.0f, 0.0f), r.GetBouncesLeft());
        RTRay rUp(r.vStart, r.vDir.Add(0.0f, 0.001f, 0.0f), r.GetBouncesLeft());
        RTRay rDown(r.vStart, r.vDir.Add(0.0f, -0.001f, 0.0f), r.GetBouncesLeft());
        RTRay rCenter = r;
        
        RTColor colorLeft = CalculateIntensity(cam, &rLeft, i, j);
        RTColor colorRight = CalculateIntensity(cam, &rRight, i, j);
        RTColor colorUp = CalculateIntensity(cam, &rUp, i, j);
        RTColor colorDown = CalculateIntensity(cam, &rDown, i, j);       
        RTColor colorCenter = CalculateIntensity(cam, &rCenter, i, j);
        
        // antialias if any of the four pixels around us are a huge change in color.
        bool bNeedsAntiAlias = false;
        if((colorLeft.Sub(colorCenter)).Length() > 0.1f)
          bNeedsAntiAlias = true;
        if((colorRight.Sub(colorCenter)).Length() > 0.1f)
          bNeedsAntiAlias = true;
        if((colorUp.Sub(colorCenter)).Length() > 0.1f)
          bNeedsAntiAlias = true;
        if((colorDown.Sub(colorCenter)).Length() > 0.1f)
          bNeedsAntiAlias = true;
        
        
        if(bNeedsAntiAlias) {
          // if need to anti-alias the differences in color
          // add and average surrounding colors
          pixelColor = pixelColor.Add(colorLeft);
          pixelColor = pixelColor.Add(colorRight);
          pixelColor = pixelColor.Add(colorUp);
          pixelColor = pixelColor.Add(colorDown);
          pixelColor = pixelColor.Add(colorCenter);
          
          pixelColor = pixelColor.DivideBy(5.0f);
          
        } else {
          pixelColor = colorCenter;
          
        }
                
      } else {
        pixelColor = CalculateIntensity(cam, &r, i, j);
      
      }
      
      // plot the pixel
      canvas->PlotPixel(i, j, &pixelColor);
      
    }
    
  }
  
}

// *************************************************************
RTHitResult RTScene::GetNearestHit(RTRay *r) {
  RTHitResult hrNearest;
  hrNearest.Clear();
  
  // for each possible primitive in the scene,
  for(int i=0;i<iMaxPrimitives;i++) {
    // break early if no more.
    if(prims[i] == NULL)
      break;
    
    if(prims[i]->IsShowing()) {
      // calculate hit result
      RTHitResult hr;
      hr.Clear();
      
      hr = prims[i]->GetHitResult(r);
      
      // if a hit and closer than our best, we found a new best.
      if(hr.IsAHit()) {
        if(hr.IsCloserThan(&hrNearest))
          hrNearest = hr;
        
      }
      
    }
    
  } 
  
  return hrNearest;
  
}



// *************************************************************
// calculate final pixel color using all lights
RTColor RTScene::CalculateIntensity(RTCamera *cam, RTRay *r, int screenX, int screenY) {
  // abort if no more bounces for this ray.
  if(!r->HasBouncesLeft())
    return RTColor(0.0f, 0.0f, 0.0f);
  
  // does the ray hit anything?
  RTHitResult hr = GetNearestHit(r);
  r->RemoveBounce();
  
  // what's the background color in case we need it?
  RTColor colorBackground = textures[TEX_BACKGROUND].GetPixelColor(screenX, screenY);
  
  // if not a hit, return the background color
  // if first ray

  if(!hr.IsAHit()) {
    return colorBackground;

  }
    
  
  RTColor colorRet;
  
  
  // view vector
  Vec3 vView = cam->vEye.Sub(hr.vPointHit);
  vView.Normalize();
  
  // normal at hit point
  Vec3 vNormal = hr.vNormalHit.GetNormalized();
  
  // actual material hit
  RTMaterial *matHit = this->GetMaterial(hr.matHit);
  RTColor matAmbient = matHit->GetAmbient();
  RTColor matDiffuse = matHit->GetDiffuse();
  RTColor matSpecular = matHit->GetSpecular();
  
 

  
  // for each light in scene
  for(int i=0; i < iMaxLights; i++) {
    if(lights[i] == NULL)
      break;
    
    if(lights[i]->IsShowing()) {
      RTColor lightAmbient = lights[i]->GetAmbient();
      RTColor lightDiffuse = lights[i]->GetDiffuse(); 
      RTColor lightSpecular = lights[i]->GetSpecular();
      
      // direction to light
      Vec3 vLight = lights[i]->GetPos().Sub(hr.vPointHit);
      vLight.Normalize();
      
      // attenuation.
      GLfloat fDistanceToLight = (lights[i]->GetPos().Sub(hr.vPointHit)).Length();
      GLfloat fAttenuation = 1.0f / sqrt(sqrt(fDistanceToLight));
      
      // dot prod for both diffuse and specular.
      GLfloat NdotL = maxf(0, vec3_dot(&vNormal, &vLight));
      
      // half angle for specular.
      Vec3 vHalf = vLight.Add(vView);
      vHalf.Normalize();
      
      GLfloat NdotH = maxf(0, vec3_dot(&vNormal, &vHalf));
      
      // reflection vector
      Vec3 vReflect = vec3_reflect(&vLight, &vNormal);
      
      
      
      // **** test for shadow ***
      RTRay shadowRay(hr.vPointHit, vLight, 1);
      // advance a bit off our hit point.
      shadowRay.Advance(0.001);
      RTHitResult hrShadow = GetNearestHit(&shadowRay);
      
      bool bPointInShadow = (hrShadow.IsAHit());
      
      
      
      // *** if texturing enabled and we hit a texture ***
      if(IsEnabled(SETT_TEXTURING) && (hr.texHit != TEX_NONE)) {
        RTColor texColor = this->textures[hr.texHit].GetColorAtUV(hr.texUV.x, hr.texUV.y);
        colorRet = colorRet.Add(texColor);
        
      }
      
      
      //                *** ambient calculation always factors in ***
      // ambient = Ka*La
      if(IsEnabled(SETT_AMBIENT)) {      
        RTColor ambient = color_modulate(&lightAmbient, &matAmbient);
        colorRet = colorRet.Add( ambient );
        
      }
      //               *** diffuse calculation ***
      //              (only if point not in shadow)
      // diffuse = KdLd*(NdotL)
      if(IsEnabled(SETT_DIFFUSE) && !bPointInShadow) {      
        RTColor KdLd = color_modulate(&lightDiffuse, &matDiffuse);
        RTColor diffuse = KdLd.MultBy(NdotL);
        
        if(IsEnabled(SETT_ATTENUATION)) {
          diffuse = diffuse.MultBy(fAttenuation);
        }
        
        colorRet = colorRet.Add( diffuse );
        
      }
      
      //               *** specular calculation ***
      //              (only if point not in shadow)
      // specular = KsLs*(RdotV)^s
      if(IsEnabled(SETT_SPECULAR) && !bPointInShadow) {   
        RTColor KsLs = color_modulate(&lightSpecular, &matSpecular);
        RTColor specular =  KsLs.MultBy(powf(NdotH, matHit->GetShininess()));
        
        if(IsEnabled(SETT_ATTENUATION)) {
          specular = specular.MultBy(fAttenuation);
        }

        colorRet = colorRet.Add(specular);
        
      }
      
      
      // if transparency only
          // color is object / background ratio
      // if reflection only
          // color is object + reflection
      // if color is both
          // color is object plus (reflection / background ratio)
      // if neither
          // color is just object
      
      
      // color of object adjusted by transparency and background.
      if(IsEnabled(SETT_TRANSPARENCY)) {
        //colorRet = colorRet.MultBy(matHit->GetOpacity());
        colorRet = colorRet.Add(colorBackground.MultBy(1.0f - matHit->GetOpacity()));
        
      }
      
      
      //             *** reflection intensity calculation ***
      if(IsEnabled(SETT_REFLECTION)) {
        // calculate reflected ray.
        RTRay reflectedRay(hr.vPointHit, vReflect, r->GetBouncesLeft());
        reflectedRay.Advance(0.001);
        
        RTColor colorReflected = CalculateIntensity(cam, &reflectedRay, screenX, screenY);
        
        if(IsEnabled(SETT_TRANSPARENCY))
          colorReflected = colorReflected.MultBy(matHit->GetOpacity());
  
        colorRet = colorRet.Add( color_modulate(&matSpecular, &colorReflected));
        
      }
      
      
    }

  }
    
  colorRet = colorRet.ClampTo1();
  return colorRet;
  
}

// ********************************************************
void RTScene::LoadPresetScene1(void) {
  LoadBackground("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/space.ppm");


  RemoveAllLights();
  RemoveAllPrimitives();
  
  Enable(SETT_AMBIENT);
  Enable(SETT_DIFFUSE);
  Enable(SETT_SPECULAR);
  Enable(SETT_REFLECTION);
  Enable(SETT_TRANSPARENCY);
  Enable(SETT_TEXTURING);
  Disable(SETT_ANTIALIAS);
  Enable(SETT_ATTENUATION);
  
  SetRayDepth(5);
  
  RTLight * light0 = new RTLight();
  light0->SetPos(1.000000, 3.000000, 0.000000);
  light0->SetVisible(true);
  light0->SetAmbient(0.300000, 0.300000, 0.300000);
  light0->SetDiffuse(0.800000, 0.800000, 0.800000);
  light0->SetSpecular(0.800000, 0.800000, 0.800000);
  AddLight(light0);
  
  RTSphere * sphere0 = new RTSphere( Vec3(0.000000,0.000000,-6.000000), 0.250000, (RTMaterial_Type) 1);
  sphere0->SetTexture( (RTTexture_Type) 2);
  AddPrimitive(sphere0);
  
  RTPolygon * poly1 = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) 5);
  poly1->AddVertex(-1.500000,-2.000000,-3.000000);
  poly1->AddVertex(1.500000,-2.000000,-3.000000);
  poly1->AddVertex(1.500000,-2.000000,-9.000000);
  poly1->AddVertex(-1.500000,-2.000000,-9.000000);
  poly1->GenerateNormal();
  AddPrimitive(poly1);
  
  RTSphere * sphere2 = new RTSphere( Vec3(-0.973061,-0.233722,-5.658611), 0.120331, (RTMaterial_Type) 3);
  sphere2->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere2);
  
  RTSphere * sphere3 = new RTSphere( Vec3(-0.531384,0.030676,-4.127335), 0.109281, (RTMaterial_Type) 1);
  sphere3->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere3);
  
  RTSphere * sphere4 = new RTSphere( Vec3(0.775759,0.182660,-5.915115), 0.350006, (RTMaterial_Type) 2);
  sphere4->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere4);

}

// ********************************************************
void RTScene::LoadBackground(char *filename) {
  textures[TEX_BACKGROUND].LoadFile(filename);
  
}

// ********************************************************
void RTScene::LoadPresetScene2(void) {
  LoadBackground("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/sky.ppm");
  
  RemoveAllLights();
  RemoveAllPrimitives();
  
  Enable(SETT_AMBIENT);
  Enable(SETT_DIFFUSE);
  Enable(SETT_SPECULAR);
  Enable(SETT_REFLECTION);
  Enable(SETT_TRANSPARENCY);
  Enable(SETT_TEXTURING);
  Disable(SETT_ANTIALIAS);
  Enable(SETT_ATTENUATION);
  
  SetRayDepth(5);
  
  RTLight * light0 = new RTLight();
  light0->SetPos(7.000000, 7.000000, 0.000000);
  light0->SetVisible(true);
  light0->SetAmbient(0.300000, 0.300000, 0.300000);
  light0->SetDiffuse(0.800000, 0.800000, 0.800000);
  light0->SetSpecular(0.800000, 0.800000, 0.800000);
  AddLight(light0);
  
  RTSphere * sphere0 = new RTSphere( Vec3(0.000000,0.500000,-6.000000), 0.250000, (RTMaterial_Type) 7);
  sphere0->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere0);
  
  // *** add floor polygon ***
  RTPolygon * poly1 = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) 5);
  poly1->AddVertex(-1.5000000,-2.000000,-3.000000);
  poly1->AddVertex(1.5000000,-2.000000,-3.000000);
  poly1->AddVertex(1.5000000,-2.000000,-9.000000);
  poly1->AddVertex(-1.5000000,-2.000000,-9.000000);
  poly1->GenerateNormal();
  AddPrimitive(poly1);
  
  RTSphere * sphere2 = new RTSphere( Vec3(-0.736924,0.011211,-5.834600), 0.259830, (RTMaterial_Type) 0);
  sphere2->SetTexture( (RTTexture_Type) 1);
  AddPrimitive(sphere2);
  
  RTSphere * sphere3 = new RTSphere( Vec3(1.094089,0.357729,-6.717186), 0.380408, (RTMaterial_Type) 1);
  sphere3->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere3);
  
  RTSphere * sphere4 = new RTSphere( Vec3(0.038833,-0.338069,-6.138288), 0.116038, (RTMaterial_Type) 2);
  sphere4->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere4);
  

}

// ********************************************************
void RTScene::LoadPresetScene3(void) {
  LoadBackground("/Users/jkhust/Documents/School/CS 354/GL_Project4 (Raytracer)/snow.ppm");

  RemoveAllLights();
  RemoveAllPrimitives();
  
  Enable(SETT_AMBIENT);
  Enable(SETT_DIFFUSE);
  Enable(SETT_SPECULAR);
  Disable(SETT_REFLECTION);
  Enable(SETT_TRANSPARENCY);
  Enable(SETT_TEXTURING);
  Enable(SETT_ANTIALIAS);
  Disable(SETT_ATTENUATION);
  
  SetRayDepth(5);
  
  RTLight * light0 = new RTLight();
  light0->SetPos(-7.000000, 3.000000, 0.000000);
  light0->SetVisible(true);
  light0->SetAmbient(0.300000, 0.300000, 0.300000);
  light0->SetDiffuse(0.800000, 0.800000, 0.800000);
  light0->SetSpecular(0.800000, 0.800000, 0.800000);
  AddLight(light0);
  
  RTLight * light1 = new RTLight();
  light1->SetPos(-0.413499, 0.327672, -2.656878);
  light1->SetVisible(true);
  light1->SetAmbient(0.000002, 0.000002, 0.000002);
  light1->SetDiffuse(0.078923, 0.078923, 0.078923);
  light1->SetSpecular(0.151121, 0.151121, 0.151121);
  AddLight(light1);
  
  RTSphere * sphere0 = new RTSphere( Vec3(0.000000,0.000000,-5.500000), 0.250000, (RTMaterial_Type) 2);
  sphere0->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere0);
  
  RTPolygon * poly1 = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) 5);
  poly1->AddVertex(-2.000000,-6.000000,-3.000000);
  poly1->AddVertex(1.000000,-6.000000,-3.000000);
  poly1->AddVertex(1.000000,-6.000000,-9.000000);
  poly1->AddVertex(-2.000000,-6.000000,-9.000000);
  poly1->GenerateNormal();
  AddPrimitive(poly1);
  
  RTPolygon * poly2 = new RTPolygon( Vec3(0.0f, 0.0f, 0.0f), (RTMaterial_Type) 5);
  poly2->AddVertex(30.000000,-6.000000,-3.000000);
  poly2->AddVertex(30.000000,1.000000,-3.000000);
  poly2->AddVertex(30.000000,1.000000,-9.000000);
  poly2->AddVertex(30.000000,-6.000000,-9.000000);
  poly2->GenerateNormal();
  AddPrimitive(poly2);
  
  RTSphere * sphere3 = new RTSphere( Vec3(0.357729,0.358593,-4.738771), 0.215051, (RTMaterial_Type) 0);
  sphere3->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere3);
  
  RTSphere * sphere4 = new RTSphere( Vec3(0.661931,-0.430856,-6.713847), 0.258910, (RTMaterial_Type) 1);
  sphere4->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere4);
  
  RTSphere * sphere5 = new RTSphere( Vec3(-0.484604,-0.233169,-4.767369), 0.225246, (RTMaterial_Type) 0);
  sphere5->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere5);
  
  RTSphere * sphere6 = new RTSphere( Vec3(-0.031384,0.530676,-3.627335), 0.109281, (RTMaterial_Type) 2);
  sphere6->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere6);
  
  RTSphere * sphere7 = new RTSphere( Vec3(-1.024241,0.212660,-4.915115), 0.250006, (RTMaterial_Type) 4);
  sphere7->SetTexture( (RTTexture_Type) 3);
  AddPrimitive(sphere7);
  
}

// ********************************************************
void RTScene::ExportScript(void) {
  printf("\n\n");
  
  printf("RemoveAllLights();\n");
  printf("RemoveAllPrimitives();\n");
  printf("\n");
  
  if(IsEnabled(SETT_AMBIENT))
    printf("Enable(SETT_AMBIENT);\n");
  else
    printf("Disable(SETT_AMBIENT);\n");
  
  if(IsEnabled(SETT_DIFFUSE))
    printf("Enable(SETT_DIFFUSE);\n");
  else
    printf("Disable(SETT_DIFFUSE);\n");
  
  if(IsEnabled(SETT_SPECULAR))
    printf("Enable(SETT_SPECULAR);\n");
  else
    printf("Disable(SETT_SPECULAR);\n");
 
  if(IsEnabled(SETT_REFLECTION))
    printf("Enable(SETT_REFLECTION);\n");
  else
    printf("Disable(SETT_REFLECTION);\n");

  if(IsEnabled(SETT_TRANSPARENCY))
    printf("Enable(SETT_TRANSPARENCY);\n");
  else
    printf("Disable(SETT_TRANSPARENCY);\n");

  if(IsEnabled(SETT_TEXTURING))
    printf("Enable(SETT_TEXTURING);\n");
  else
    printf("Disable(SETT_TEXTURING);\n");

  if(IsEnabled(SETT_ANTIALIAS))
    printf("Enable(SETT_ANTIALIAS);\n");
  else
    printf("Disable(SETT_ANTIALIAS);\n");

  if(IsEnabled(SETT_ATTENUATION))
    printf("Enable(SETT_ATTENUATION);\n");
  else
    printf("Disable(SETT_ATTENUATION);\n");
  
  
  printf("\n");
  printf("SetRayDepth(%d);\n", GetRayDepth());

  for(int i=0;i<iMaxLights;i++)
    if(lights[i] != NULL)
      lights[i]->ExportCommands(i);
  
  for(int j=0;j<iMaxPrimitives;j++)
    if(prims[j] != NULL)
      prims[j]->ExportCommands(j);
  
}

// ********************************************************