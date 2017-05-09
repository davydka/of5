#include "testApp.h"

ofImage img;
ofPlanePrimitive plane;
ofShader shader_keliedo;
ofShader shader;

bool use_kal = true;

//--------------------------------------------------------------
void testApp::setup(){
   
   std::cout<<glGetString(GL_VERSION)<<std::endl;
   
   ofDisableArbTex();
   
   img.loadImage("eyes.jpg");
   
   float planeScale = 1.;
   int planeWidth = ofGetWidth() * planeScale;
   int planeHeight = ofGetHeight() * planeScale;
   int planeGridSize = 20;
   int planeColumns = planeWidth / planeGridSize;
   int planeRows = planeHeight / planeGridSize;
   
   plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
   plane.mapTexCoordsFromTexture(img.getTextureReference());
   
   // my opengl3 shaders don't work
//   if(ofIsGLProgrammableRenderer()){
//      shader_keliedo.load("gl3/kaleidoscope");
//      shader.load("gl3/shader"); //passthrough shader
//   }else{
      shader_keliedo.load("gl2/kaleidoscope");
      shader.load("gl2/shader"); //passthrough shader
      //}
   use_kal = true;
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
   ofClear(255.0f, 255.f, 255.f);
   ofSetColor(255);
   
   GLint repeat = GL_MIRRORED_REPEAT;
   //img.getTextureReference().setTextureWrap(repeat,repeat);
    ofSetTextureWrap(repeat,repeat);

   
   //img.getTextureReference().bind();
   
   float mousePositionX = ofMap(mouseX, 0, ofGetWidth(), plane.getWidth(), -plane.getWidth(), true);
   float mousePositionY = ofMap(mouseY, 0, ofGetHeight(), plane.getHeight(), -plane.getHeight(), true);
   
   float mouseNormX =((float)mouseX)/((float)ofGetWidth());
   float mouseNormY =((float)mouseY)/((float)ofGetHeight());
   
   if (use_kal){
      shader_keliedo.begin();
      shader_keliedo.setUniform2f("mouse", mousePositionX, mousePositionY);
      shader_keliedo.setUniform1f("time", ofGetElapsedTimef());
      shader_keliedo.setUniform2f("resolution", ofGetWidth(),ofGetHeight());
      shader_keliedo.setUniform2f("uvOffset", mouseNormX, mouseNormY);
      ofPushMatrix();
      //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
      //plane.draw();
       //ofDrawPlane(0, 0, ofGetWidth(), ofGetHeight());
       img.draw(0,0, ofGetWidth(), ofGetHeight());
      ofPopMatrix();
      shader_keliedo.end();
   }else{
      shader.begin();
      shader.setUniform2f("mouse", mouseNormX, mouseNormY);
      ofPushMatrix();
      ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
      plane.draw();
      ofPopMatrix();
      shader.end();
   }
   
   //img.getTextureReference().unbind();
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
   use_kal = !use_kal;
}
