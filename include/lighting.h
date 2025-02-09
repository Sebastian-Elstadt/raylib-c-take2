#ifndef LIGHTING_H
#define LIGHTING_H

void InitLighting(void);
void UpdateLighting(Camera *camera);
void DisposeLighting(void);
void ApplyLightingShader(Model *model);

#endif // LIGHTING_H