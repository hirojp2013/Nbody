#ifndef _SNAPSHOT_H_
#define _SNAPSHOT_H_
const int  SNAPSHOT_IMAGE_MAX = 2048 * 2048;
class Snapshot {
  int       active;
  unsigned char      pic_red[SNAPSHOT_IMAGE_MAX];  
  unsigned char      pic_green[SNAPSHOT_IMAGE_MAX];
  unsigned char      pic_blue[SNAPSHOT_IMAGE_MAX];
  unsigned char      pic_rgb[SNAPSHOT_IMAGE_MAX*3];
  void      makePPMimage(char*, int, int, int, int);
public:
  Snapshot();
  void      activate() { active = 1; };
  void      inactivate() { active = 0; };
  void      button_has_pressed();
  void      save_image();
};
#endif
