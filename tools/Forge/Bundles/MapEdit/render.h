#ifndef render_h
#define render_h

#include "SetBrush.h"

typedef enum {dr_wire, dr_flat, dr_texture}  drawmode_t;

extern int          r_width, r_height;
extern unsigned     *r_picbuffer;
extern float        *r_zbuffer;

extern vec3_t   r_origin, r_matrix[3];
extern BOOL     r_drawflat;

void REN_ClearBuffers (void);
void REN_DrawCameraFace (face_t * idpol);
void REN_DrawXYFace (face_t * idpol);
void REN_BeginCamera (void);
void REN_BeginXY (void);

#endif // render_h
