/******************************************************************/
/*         Main raytracer file                                    */
/*                                                                */
/* Justin Hust (jkh2367)                                          */
/******************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "raytrace.h"
#include "VecMath.h"
#include "RTScene.h"
#include "RTCanvas.h"
#include "RTCamera.h"
#include "RTLight.h"

// random number seed
int iRandomSeed = 0;

// heap-allocated globals
RTCamera *cam;
RTCanvas *canvas;
RTScene *scene;

// **************************************************
enum ControlMode {
  ControlMode_None = 0,
  ControlMode_Prims = 1,
  ControlMode_Lights = 2,
  
};

// **************************************************
// control mode and control index.
ControlMode cmode;
int cindex;

// **************************************************
void display() {
  glClearColor(0.0, 0.0, 0.0, 0.0);  
  glClear(GL_COLOR_BUFFER_BIT);
  
  // render the scene from the camera onto the canvas.
  canvas->ClearToGray();
  scene->RenderToCanvas(cam, canvas);
  canvas->SendToFrameBuffer();
  
  glFlush();
  
}

// **************************************************
void UserInit(void) {
  // init camera
  cam = new RTCamera();
  cam->vEye.Set(0.0f, 0.0f, 0.0f);
  cam->pnear = 1.0f;
  cam->fovx = (GLfloat) PI / 6.0f;
  

  // init canvas
  canvas = new RTCanvas(iScreenWidth, iScreenHeight);
  canvas->SetCanvasProjection();
  
  // init scene
  scene = new RTScene();
  scene->LoadPresetScene1();
  
  // index of object to manipulate.
  cmode = ControlMode_Prims;
  cindex = 0;
  
}

// **************************************************
void UserCleanup() {
  if(cam != NULL) delete cam;
  cam = NULL;
  
  if(canvas != NULL) delete canvas;
  canvas = NULL;
  
  if(scene != NULL) delete scene;
  scene = NULL;
  
}

// **************************************************
void TryToggleVisibility() {
  // *** TRYING TO TOGGLE A LIGHT ***
  if(cmode == ControlMode_Lights) {
    RTLight *l = scene->GetLightWithIndex(cindex);
    
    if(l == NULL) {
      printf("Cannot toggle visibility. No light at index %d.\n", cindex);
      
    } else {
      if(l->ToggleShow()) {
        printf("Light %d turned on.\n", cindex);
        
      } else {
        printf("Light %d turned off.\n", cindex);
        
      }
      
    }
    
    // **** TRYING TO MOVE A PRIMITIVE ***
  } else {
    RTPrimitive *p = scene->GetPrimitiveWithIndex(cindex);
    
    if(p == NULL) {
      printf("Cannot toggle visibility. No primitive at index %d.\n", cindex);
      
    } else {
      if( p->ToggleShow() )
        printf("Primitive %d now showing.\n", cindex);
      else
        printf("Primitive %d now hidden.\n", cindex);

    }
    
  }
  
  
}

// **************************************************
void TryCycleMaterial() {
  RTPrimitive *p = scene->GetPrimitiveWithIndex(cindex);
  
  if(p == NULL) {
    printf("Cannot cycle material. No primitive at index %d.\n", cindex);
    
  } else {
    p->CycleMaterial();
        
  }

}

// **************************************************
void TryCycleTexture() {
  RTPrimitive *p = scene->GetPrimitiveWithIndex(cindex);
  
  if(p == NULL) {
    printf("Cannot cycle texture. No primitive at index %d.\n", cindex);
    
  } else {
    p->CycleTexture();
    
  }
  
}

// **************************************************
void TryMove(GLfloat x, GLfloat y, GLfloat z) {
  // *** TRYING TO MOVE A LIGHT ***
  if(cmode == ControlMode_Lights) {
    RTLight *l = scene->GetLightWithIndex(cindex);
    
    if(l == NULL) {
      printf("Cannot move. No light at index %d.\n", cindex);
      
    } else {
      l->Move(x, y, z);
      printf("Light %d moved to (%0.2f, %0.2f, %0.2f).\n", 
             cindex,
             l->vPos.x, 
             l->vPos.y, 
             l->vPos.z); 
      
    }

  // **** TRYING TO MOVE A PRIMITIVE ***
  } else {
    RTPrimitive *p = scene->GetPrimitiveWithIndex(cindex);
    
    if(p == NULL) {
      printf("Cannot move. No primitive at index %d.\n", cindex);
      
    } else {
      p->Move(x / 4.0f, y / 4.0f, z / 4.0f);
      printf("Primitive %d moved to (%0.2f, %0.2f, %0.2f).\n", 
             cindex,
             p->GetPos().x, 
             p->GetPos().y, 
             p->GetPos().z); 
      
    }
    
  }

}

// ***********************************************************
void ToggleAmbient() {
  if(scene->Toggle(SETT_AMBIENT))
    printf("Ambient Lighting Enabled.\n");
  else
    printf("Ambient Lighting Disabled.\n");
    
  glutPostRedisplay();
  
}


// ***********************************************************
void ToggleDiffuse() {
  if(scene->Toggle(SETT_DIFFUSE))
    printf("Diffuse Lighting Enabled.\n");
  else
    printf("Diffuse Lighting Disabled.\n");

  glutPostRedisplay();
  
}

// ***********************************************************
void ToggleSpecular() {
  if(scene->Toggle(SETT_SPECULAR))
    printf("Specular Lighting Enabled.\n");
  else
    printf("Specular Lighting Disabled.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ToggleReflections() {
  if(scene->Toggle(SETT_REFLECTION))
    printf("Ray Reflection Enabled.\n");
  else
    printf("Ray Reflection Disabled.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ToggleTexturing() {
  if(scene->Toggle(SETT_TEXTURING))
    printf("Texturing Enabled.\n");
  else
    printf("Texturing Disabled.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ToggleTransparency() {
  if(scene->Toggle(SETT_TRANSPARENCY))
    printf("Transparency Enabled.\n");
  else 
    printf("Transparency Disabled.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ToggleAntiAliasing() {
  if(scene->Toggle(SETT_ANTIALIAS))
    printf("Anti-aliasing Enabled.\n");
  else
    printf("Anti-aliasing Disabled.\n");
  
  glutPostRedisplay();
  
}


// ***********************************************************
void ToggleAttenuation() {
  if(scene->Toggle(SETT_ATTENUATION))
    printf("Light Attenuation Enabled.\n");
  else
    printf("Light Attenuation Disabled.\n");

  glutPostRedisplay();
  
}

// ***********************************************************
void AddRandomPrimitive(void) {
  scene->AddRandomPrimitive();
  printf("Added primitive. Scene now has %d primtives.\n", scene->GetNumPrimitives());
  
  glutPostRedisplay();
}


// ***********************************************************
void AddRandomLight(void) {
  scene->AddRandomLight();
  printf("Added light. Scene now has %d lights.\n", scene->GetNumLights());
  
  glutPostRedisplay();
  
}

// ***********************************************************
void LoadPresetScene1(void) {
  scene->LoadPresetScene1();
  printf("Preset Scene 1 Loaded.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void LoadPresetScene2(void) {
  scene->LoadPresetScene2();
  printf("Preset Scene 2 Loaded.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void LoadPresetScene3(void) {
  scene->LoadPresetScene3();
  printf("Preset Scene 3 Loaded.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ResetScene(void) {
  // move to a new random scene.
  iRandomSeed++;
  srand(iRandomSeed);
  
  scene->CreateRandomScene();
  printf("Random scene created.\n");
  
  glutPostRedisplay();
  
}

// ***********************************************************
void ExportScene(void) {
  scene->ExportScript();
  
}

// ***********************************************************
// custom keyFunc with preset keys
void keyFunc(unsigned char ch, int x, int y) {
  bool bPostRedisplay = false;
  
	switch(ch) {
		case 'q':
    case 'Q':
      bPostRedisplay = false;
			exit(0);
			break;
      
    case '`':
      cindex = 0;
      
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 0.\n");
      else
        printf("Now controlling Primitive 0.\n");        
  
      break;
      
    case '1':
      cindex = 1;
        
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 1.\n");
      else
        printf("Now controlling Primitive 1.\n");  
          
      break;
      
    case '2':
      cindex = 2;
          
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 2.\n");
      else
        printf("Now controlling Primitive 2.\n");  
            
      break;
      
    case '3':
      cindex = 3;
        
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 3.\n");
      else
        printf("Now controlling Primitive 3.\n");  
          
      break;
      
    case '4':
      cindex = 4;
        
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 4.\n");
      else
        printf("Now controlling Primitive 4.\n");  
          
      break;
      
    case '5':
      cindex = 5;
        
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 5.\n");
      else
        printf("Now controlling Primitive 5.\n");  
          
      break;

    case '6':
      cindex = 6;
        
      if(cmode == ControlMode_Lights)
        printf("Now controlling Light 6.\n");
      else
        printf("Now controlling Primitive 6.\n");  
          
      break;
      
    case '7':
      LoadPresetScene1();
      break;

    case '8':
      LoadPresetScene2();
      break;

    case '9':
      LoadPresetScene3();
      break;
      
    case 'A':
    case 'a':
      ToggleAmbient();
      break;
      
    case 'S':
    case 's':
      ToggleSpecular();
      break;
      
    case 'D':
    case 'd':
      ToggleDiffuse();
      break;
            
    case 'R':
    case 'r':
      ToggleReflections();
      break;

    case 'T':
    case 't':
      ToggleTransparency();
      break;
         
    case 'E':
    case 'e':
      ToggleTexturing();
      break;
      
    case 'J':
    case 'j':
      ToggleAntiAliasing();
      break;
      
    case 'U':
    case 'u':
      ToggleAttenuation();
      break;
      
    case 'L':
    case 'l':
      cmode = ControlMode_Lights;
      printf("Control Mode: LIGHTS.\n");
      break;
            
    case 'P':
    case 'p':
      cmode = ControlMode_Prims;
      printf("Control Mode: PRIMITIVES.\n");
      break;
 
    case 'V':
    case 'v':
      TryToggleVisibility();
      
      bPostRedisplay = true;
      break;
      
    case 'M':
    case 'm':
      TryCycleMaterial();
      
      bPostRedisplay = true;
      break;
      
    case 'X':
    case 'x':
      TryCycleTexture();
      
      bPostRedisplay = true;
      break;
        
    // move controlled object left
    case '[':
      TryMove(-2.0f, 0.0f, 0.0f);
      
      bPostRedisplay = true;
      break;
      
    // move controlled object right
    case ']':
      TryMove(2.0f, 0.0f, 0.0f);
      
      bPostRedisplay = true;
      break;
      
    // move controlled object down
    case '-':
      TryMove(0.0f, -2.0f, 0.0f);
      
      bPostRedisplay = true;
      break;
 
    // move controlled object up
    case '=':
      TryMove(0.0f, 2.0f, 0.0f);
      
      bPostRedisplay = true;
      break;
        
    case ';':
      TryMove(0.0f, 0.0f, -2.0f);
      
      bPostRedisplay = true;
      break;
      
    case '\'':
      TryMove(0.0f, 0.0f, 2.0f);
      
      bPostRedisplay = true;
      break;
      
    case '.':
      if( scene->DecreaseRayDepth())
        printf("Ray depth decreased to %d.\n", scene->GetRayDepth());
      else
        printf("Ray depth already at 1.\n");
      
      bPostRedisplay = true;
      break;
      
    case ',':
      if( scene->IncreaseRayDepth())
        printf("Ray depth increased to %d.\n", scene->GetRayDepth());
      else
        printf("Ray depth already at max.\n");
      
      
      bPostRedisplay = true;
      break;
      
    case 'B':
    case 'b':
      ExportScene();
      break;
      
    case 'Z':
    case 'z':
      ResetScene();
      break;
      
    case 'O':
    case 'o':
      if(cmode == ControlMode_Lights) {
        AddRandomLight();

      } else {
        AddRandomPrimitive();
      }
      
      break;

		default:
			/* Unrecognized keypress */
      return;
	}
  
  if(bPostRedisplay)
    glutPostRedisplay();
    
}

// **************************************************
// Menu items
enum MENU_TYPE
{
  MENU_NONE,
  MENU_HOWDOI,
  MENU_TOGGLE,
  MENU_TOGGLE_AMBIENT,
  MENU_TOGGLE_DIFFUSE,
  MENU_TOGGLE_SPECULAR,
  MENU_TOGGLE_REFLECTIONS,
  MENU_TOGGLE_TRANSPARENCY,
  MENU_TOGGLE_TEXTURING,
  MENU_TOGGLE_ANTIALIAS,
  MENU_TOGGLE_ATTENUATION,
  
  MENU_ADD_PRIMITIVE,
  MENU_ADD_LIGHT,
  
  MENU_PRESET_1,
  MENU_PRESET_2,
  MENU_PRESET_3,
  MENU_PRESET_4,
  MENU_RESET_SCENE,
  
  MENU_EXPORT_SCENE
  
};

// **************************************************
void menuFunc(int m) {
  switch(m) {
    case MENU_TOGGLE_AMBIENT:
      ToggleAmbient();
      break;
      
    case MENU_TOGGLE_DIFFUSE:
      ToggleDiffuse();
      break;
      
    case MENU_TOGGLE_SPECULAR:
      ToggleSpecular();
      break;
      
    case MENU_TOGGLE_REFLECTIONS:
      ToggleReflections();
      break;
      
    case MENU_TOGGLE_TRANSPARENCY:
      ToggleTransparency();
      break;
      
    case MENU_TOGGLE_TEXTURING:
      ToggleTexturing();
      break;
      
    case MENU_TOGGLE_ANTIALIAS:
      ToggleAntiAliasing();
      break;
      
    case MENU_TOGGLE_ATTENUATION:
      ToggleAttenuation();
      break;
      
    case MENU_ADD_PRIMITIVE:
      AddRandomPrimitive();
      break;
      
    case MENU_ADD_LIGHT:
      AddRandomLight();
      break;
      
    case MENU_PRESET_1:
      LoadPresetScene1();
      break;
      
    case MENU_PRESET_2:
      LoadPresetScene2();
      break;
      
    case MENU_PRESET_3:
      LoadPresetScene3();
      break;
            
    case MENU_RESET_SCENE:
      ResetScene();
      break;
      
    case MENU_EXPORT_SCENE:
      ExportScene();
      break;
      
    default:
      break;
      
  }
  
}

// **************************************************
void SetupMenu(void) {
  // *** toggle menu ***
  int menuToggle;
  menuToggle = glutCreateMenu(menuFunc);
  
  glutAddMenuEntry("Ambient Lighting ('A')", MENU_TOGGLE_AMBIENT);
  glutAddMenuEntry("Diffuse Lighting ('D')", MENU_TOGGLE_DIFFUSE);
  glutAddMenuEntry("Specular Lighting ('S')", MENU_TOGGLE_SPECULAR);
  glutAddMenuEntry("Reflection Rays ('R')", MENU_TOGGLE_REFLECTIONS);
  glutAddMenuEntry("Object Transparency ('T')", MENU_TOGGLE_TRANSPARENCY);
  glutAddMenuEntry("Texturing ('E')", MENU_TOGGLE_TEXTURING);
  glutAddMenuEntry("Anti-Aliasing ('J')", MENU_TOGGLE_ANTIALIAS);
  glutAddMenuEntry("Light Attenuation ('U')", MENU_TOGGLE_ATTENUATION);
  
  // **** add menu ****
  int menuAdd;
  menuAdd = glutCreateMenu(menuFunc);
  
  glutAddMenuEntry("Add Random Primitive ('P' then 'O')", MENU_ADD_PRIMITIVE);
  glutAddMenuEntry("Add Random Light ('L' then 'O')", MENU_ADD_LIGHT);
  
  // **** preset scene menu *****
  int menuPreset;
  menuPreset = glutCreateMenu(menuFunc);
  
  glutAddMenuEntry("Preset Scene 1 ('7')", MENU_PRESET_1);
  glutAddMenuEntry("Preset Scene 2 ('8')", MENU_PRESET_2);
  glutAddMenuEntry("Preset Scene 3 ('9')", MENU_PRESET_3);
  glutAddMenuEntry("Reset Scene ('Z')", MENU_RESET_SCENE); 
  
  
  // **** preset scene menu *****
  int menuEditScene;
  menuEditScene = glutCreateMenu(menuFunc);
  
  glutAddMenuEntry("Editing The Scene:", MENU_NONE);
  glutAddMenuEntry("------------------", MENU_NONE);
  glutAddMenuEntry("Switch between light/primitive mode with 'L' and 'P.'", MENU_NONE);
  glutAddMenuEntry("In light mode, 'O' adds a random light.", MENU_NONE);
  glutAddMenuEntry("In prim mode, 'O' adds a random primitive.", MENU_NONE);
  glutAddMenuEntry("------------------", MENU_NONE);
  glutAddMenuEntry("`,1,2,3,4,5,6 selects light or prim at that index.", MENU_NONE);
  glutAddMenuEntry("------------------", MENU_NONE);
  glutAddMenuEntry("Once selected, the following keys apply:", MENU_NONE);
  glutAddMenuEntry("- and +  for move down/up", MENU_NONE);
  glutAddMenuEntry("[ and ]  for move left/right", MENU_NONE);
  glutAddMenuEntry("; and '  for move in/out", MENU_NONE);
  glutAddMenuEntry("v        to toggle visibility", MENU_NONE);
  glutAddMenuEntry("x        to cycle primitive texture", MENU_NONE);
  glutAddMenuEntry("m        to cycle primitive material", MENU_NONE);
  
  
  // *** main menu ***
  int menuMain;
  menuMain = glutCreateMenu(menuFunc);
  
  glutAddMenuEntry("How do I?", MENU_HOWDOI);
  glutAddMenuEntry("---------", MENU_NONE);
    glutAddSubMenu("Toggle Settings...", menuToggle);
    glutAddSubMenu("Add..", menuAdd);
    glutAddSubMenu("Preset Scene...", menuPreset);
    glutAddSubMenu("Edit Scene...", menuEditScene);
    glutAddMenuEntry("Export Scene Script ('B')", MENU_EXPORT_SCENE);
  
  // Associate a mouse button with menu
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
}

// **************************************************
int main (int argc, char** argv) {
  srand(iRandomSeed);
  
  glutInit(&argc,argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(iScreenWidth,iScreenHeight);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  int win = glutCreateWindow("Project 4 - Raytracer");
  glutSetWindow(win);
  glutKeyboardFunc(keyFunc);
  glutDisplayFunc(display); 
  
  SetupMenu();
  UserInit();
  
  glutMainLoop();
  
  UserCleanup();
  
  return 0;
  
}



