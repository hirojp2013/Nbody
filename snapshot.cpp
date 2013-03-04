//
// vfive: Vector Field Interactive Visualization Environment
//
//
// snapshot.c++
//
//                by Kageyama, Akira  (kage@nifs.ac.jp)  2000.04.24
//  		  Modified by Ohno (AVS file -> PPM file)
//
// Please read the file "LICENCE_ja.txt"(in Japanese) or "LICENCE_en.txt" (in English)
// before you use this software. 

#include "snapshot.hpp"

Snapshot::Snapshot()
{
  active = 0;     // When this is 1, you cave save image to a file
                  // by pushing wand's middle button.
}

/*
 *---------------------------------------------------------------------
 > makeAVSimage
 *---------------------------------------------------------------------
 * 
\*
     An OpenGL sample program.
	- Read the color buffer and make an AVS image file (*.x) from it 
	  by "glReadPixels" command.
	- An AVS image file named "picture.x" is automatically generated.
	- AVS image file has a simple data structure;
		    int  width
		    int  height
		    char alpha <-+  1st pixel
		    char red     |
		    char green   |   
		    char blue  <-+
		    char alpha <-+  2nd pixel
		    char red     |
		    char green   |   
		    char blue  <-+
		    char alpha <-+  3rd pixel
		    char red     |
		    char green   |   
		    char blue  <-+
		       .
		       .
		       .
		       .
                              by Akira Kageyama              <98.07.21>
				 Theory and Computer Simulation Center,
				 National Institute for Fusion Science.
*/


void 
Snapshot::makePPMimage(char *file1, int org_x, int org_y, 
		       int width, int height) 
{
    FILE  *fp;

    // printf(" debug... width = %d height = %d\n", width, height);
    
    // We cannot use the following (simpler) command, since the
    // each element of RGBA in the color buffer isn't always the same as 
    // that in the AVS-X image file (which is "A-R-G-B").
    //
    // glReadPixels(org_x, org_y, width, height, 
    //   	    GL_RGBA, GL_UNSIGNED_BYTE, pic_rgba);

    // AVS file -> PPM file
    // Revised 2006.6 by N.Ohno

    glReadPixels(org_x, org_y, width, height, 
	         GL_RED,   GL_UNSIGNED_BYTE, pic_red);
    glReadPixels(org_x, org_y, width, height, 
                 GL_GREEN, GL_UNSIGNED_BYTE, pic_green);
    glReadPixels(org_x, org_y, width, height, 
                 GL_BLUE,  GL_UNSIGNED_BYTE, pic_blue);

    int ctr, i, j, anti_j, k;
    for (ctr = 0, j = 0; j < height; j++) {
	anti_j = height - j - 1;

	for (i = 0; i < width; i++, ctr += 3) {
	    k = anti_j * width + i;

	    pic_rgb[ctr + 0] = pic_red[k];
	    pic_rgb[ctr + 1] = pic_green[k];
	    pic_rgb[ctr + 2] = pic_blue[k];

	}
    }


    fp = fopen(file1, "wb");
    if (fp == NULL)
	v5_error("File open error: image save.");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    fwrite(pic_rgb, width * height * 3, 1, fp);

    fclose(fp);
}

static void
flush_white()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}


void
Snapshot::save_image()
  //
  // Save image on the master screen into disk.
  //
{
  if ( CAVEMasterDisplay()==0 ) return;
	  // Do nothing when the child process is not for the master.

  if ( !active ) return;

  static int counter=0;

  char file[100];
  
  sprintf(file,"./snapshot%03d.ppm",counter);
  printf("  file = %s\n", file);
  int org_x, org_y, width, height;
  CAVEGetWindowGeometry(&org_x, &org_y, &width, &height);
  printf("saveimage: %s: %d x %d + %d + %d\n", 
	 file, width, height, org_x, org_y);
  if ( width * height >= SNAPSHOT_IMAGE_MAX ) 
    v5_error("The screen size is too large. Increase SNAPSHOT_IMAGE_MAX");
  glReadBuffer(GL_FRONT_RIGHT);
  makePPMimage(file, org_x, org_y, width, height);
  
  counter++;
  inactivate();
  flush_white();     // Notify the user that the picture was taken.
}

void
Snapshot::button_has_pressed()
{
  activate();
}
  

