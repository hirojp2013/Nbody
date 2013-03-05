/* PointSprite                                                 */
/* Describe "#define GL_GLEXT_PROTOTYPES" before include GLUT. */
/* e.g.                                                        */
/* #define GL_GLEXT_PROTOTYPES                                 */
/* #inclde <GL/glut.h>                                         */

#include "pointsprite.hpp"
#include "myPng.hpp"
#include <cstdlib>
#include <iostream>

const GLfloat PointSprite::distance[] = {0.0, 0.0, 1.0};

PointSprite::PointSprite(){
  glGenTextures( 1, &texture_name );
  myPng pngObj;
  if(!pngObj.loadpng("SP_W.png")){
    std::cout << "The file does not exit." << std::endl;
    exit(1);
  }
  glGenTextures( 1, &texture_name );
  glBindTexture( GL_TEXTURE_2D, texture_name );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
  gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, pngObj.getWidth(), pngObj.getHeight(),
		     GL_RGBA, GL_UNSIGNED_BYTE, pngObj.getTexture() );//Segmentation Fault

  glTexParameterf( GL_TEXTURE_2D,
		   GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glTexParameterf( GL_TEXTURE_2D,
		   GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  buildVBO();
}

PointSprite::~PointSprite(){
  glDeleteTextures(1, &texture_name);
  glDeleteTextures(1, &vertexBuf_name);
}

void PointSprite::buildVBO(){
  stride = sizeof( MY_VERTEX );
  glGenBuffers(1, &vertexBuf_name);
}


void PointSprite::drawPointSprite(MY_VERTEX* vertices,  GLsizei count){
  set_vbo(vertices,count,GL_STREAM_DRAW);
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  glAlphaFunc(GL_GREATER, 0.1);
  glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
  glBindTexture(GL_TEXTURE_2D, texture_name);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SPRITE);
  glEnable(GL_ALPHA_TEST);
  glPointSize(1000);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuf_name);
  glVertexPointer(3, GL_DOUBLE, stride, 0);
  glColorPointer (4,GL_DOUBLE,stride,BUFFER_OFFSET(sizeof(double)*3));
  glDrawArrays(GL_POINTS,0,100);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisable(GL_TEXTURE_2D);
  
}

void PointSprite::drawPointSprite(MY_VERTEX* vertices, GLsizei count, GLdouble* size){
  set_vbo(vertices,count,GL_STREAM_DRAW);

  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  glAlphaFunc(GL_GREATER, 0.1);
  glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
  glBindTexture(GL_TEXTURE_2D, texture_name);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SPRITE);
  glEnable(GL_ALPHA_TEST);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuf_name);
  glVertexPointer(3, GL_DOUBLE, stride, 0);
  glColorPointer (4,GL_DOUBLE,stride,BUFFER_OFFSET(sizeof(double)*3));
  for(int i=0; i<count; i++){
    glPointSize(size[i]);
    glDrawArrays(GL_POINTS, i, 1);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisable(GL_TEXTURE_2D);
}

void PointSprite::set_vbo(MY_VERTEX vertexBuf[],int count,GLenum usage){
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuf_name);
  glBufferData(GL_ARRAY_BUFFER, stride*count, vertexBuf, usage);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}





