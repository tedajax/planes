#ifndef _SCRIPT_API_H_
#define _SCRIPT_API_H_

void spawnBullet(float x, float y, float angle);

struct entity_t;
struct entity_t *getEntity(int id);
void entitySetPosition(struct entity_t *e, float x, float y);
void entitySetRotation(struct entity_t *e, float r);
void entitySetScale(struct entity_t *e, float x, float y);
void entitySetVelocity(struct entity_t *e, float x, float y);
void entitySetAngularVelocity(struct entity_t *e, float r);

#endif