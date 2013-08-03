/* PointSprite                                                 */
/* Describe "#define GL_GLEXT_PROTOTYPES" before include GLUT. */
/* e.g.                                                        */
/* #define GL_GLEXT_PROTOTYPES                                 */
/* #inclde <GL/glut.h>                                         */

#include "pointsprite.h"
#include <png.h>
#include <cstdlib>
#include <GLUT/glut.h>
#include <iostream>

const GLfloat PointSprite::distance[] = {0.0, 0.0, 1.0};

PointSprite::PointSprite(){
  printf("%s(%d)\n",__FILE__,__LINE__);
  loadTexture();
  printf("%s(%d)\n",__FILE__,__LINE__);
}

PointSprite::~PointSprite(){

  glDeleteTextures(1, &texture_name);

}


void PointSprite::drawPointSprite(GLdouble* vertices, GLdouble* color, GLsizei count){

  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  glAlphaFunc(GL_GREATER, 0.5);

  glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);

  glBindTexture(GL_TEXTURE_2D, texture_name);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SPRITE);
  glEnable(GL_ALPHA_TEST);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glPointSize(SIZE);
  printf("%s(%d)\n",__FILE__,__LINE__);

  glVertexPointer(3, GL_DOUBLE, 0, vertices);
  glColorPointer (4, GL_DOUBLE, 0, color);

  glDrawArrays(GL_POINTS, 0, count);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);


  glDisable(GL_ALPHA_TEST);
  glDisable(GL_POINT_SPRITE);
  glDisable(GL_TEXTURE_2D);


}

void PointSprite::drawPointSprite(GLdouble* vertices, GLdouble* color, GLsizei count, GLdouble* size){
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  glAlphaFunc(GL_GREATER, 0.5);

  glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);

  glBindTexture(GL_TEXTURE_2D, texture_name);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SPRITE);
  glEnable(GL_ALPHA_TEST);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_DOUBLE, 0, vertices);
  glColorPointer (3, GL_DOUBLE, 0, color);


  for(int i=0; i<count; i++){
    glPointSize(size[i]*10);
    glDrawArrays(GL_POINTS, i, 1);
  }

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glDisable(GL_ALPHA_TEST);
  glDisable(GL_POINT_SPRITE);
  glDisable(GL_TEXTURE_2D);
}



void PointSprite::loadTexture(){
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  png_uint_32  width, height;
  int bit_depth, color_type, interlace_type;
  unsigned char **pngimage;
 
  fp = fopen( "SP_W.png", "rb" );
  printf("%s(%d)\n",__FILE__,__LINE__);
  png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
    printf("%s(%d)\n",__FILE__,__LINE__);
  info_ptr = png_create_info_struct( png_ptr );
  printf("%s(%d)\n",__FILE__,__LINE__);

  png_init_io( png_ptr, fp );
  png_read_info( png_ptr, info_ptr );
  png_get_IHDR( png_ptr, info_ptr, &width, &height,
                &bit_depth, &color_type, &interlace_type,
                NULL, NULL);
  printf("%s(%d)\n",__FILE__,__LINE__);
  pngimage = ( png_bytepp )malloc( height * sizeof( png_bytep ) );
  for ( int i = 0; i < height; i++ )
    {
      pngimage[ i ] = ( png_bytep )malloc( png_get_rowbytes( png_ptr, info_ptr ) );
    }
  png_read_image( png_ptr, pngimage );
  printf("%s(%d)\n",__FILE__,__LINE__);

  GLubyte *texture;
  texture = ( unsigned char* )malloc( sizeof( unsigned char ) * width * height * 4 );
  unsigned char	*pbuff;
  printf("%s(%d)\n",__FILE__,__LINE__);
  for ( int y = 0; y < height; y++ )
    {
      pbuff = pngimage[ ( height - 1 ) - y ];
      for( int i = 0; i < width; i++ )
        {
          texture[ ( y * width + i ) * 4 + 0 ] = pbuff[ i * 4 + 0 ];
          texture[ ( y * width + i ) * 4 + 1 ] = pbuff[ i * 4 + 1 ];
          texture[ ( y * width + i ) * 4 + 2 ] = pbuff[ i * 4 + 2 ];
          texture[ ( y * width + i ) * 4 + 3 ] = pbuff[ i * 4 + 3 ];
        }
    }

  printf("%s(%d)\n",__FILE__,__LINE__);
  glGenTextures( 1, &texture_name );
  printf("%s(%d)\n",__FILE__,__LINE__);
  glBindTexture( GL_TEXTURE_2D, texture_name );
  printf("%s(%d)\n",__FILE__,__LINE__);
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

  printf("%s(%d)\n",__FILE__,__LINE__);

  gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height,
                     GL_RGBA, GL_UNSIGNED_BYTE, texture );//Segmentation Fault

  printf("%s(%d)\n",__FILE__,__LINE__);
  glTexParameterf( GL_TEXTURE_2D,
                   GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  printf("%s(%d)\n",__FILE__,__LINE__);

  glTexParameterf( GL_TEXTURE_2D,
                   GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

  printf("%s(%d)\n",__FILE__,__LINE__);

  free( texture );
  free( pngimage );
  png_destroy_read_struct( &png_ptr, &info_ptr, ( png_infopp )NULL );

  fclose(fp);

}
