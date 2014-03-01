local ffi = require("ffi")

ffi.cdef[[
	void spawnBullet(float x, float y, float angle);

	typedef enum component_type_e {
		C_TRANSFORM,
		C_SPRITE_RENDERER,
		C_PLAYER_CONTROLLER,
		C_BULLET_CONTROLLER,
		C_LUA_COMPONENT,
		COMPONENT_COUNT //make sure this is always the last element in the enum
	} ComponentType;

	typedef struct component_t {
		ComponentType type;
		bool enabled;
		struct entity_t *entity;
		void *component;
	} Component;

	typedef struct vec2_t {
		float x, y;
	} Vec2;

	typedef struct ctransform_t {
		Component *super;
		Vec2 *position;
		Vec2 *scale;
		float rotation;

		Vec2 *velocity;
		float angularVelocity;
	} CTransform;

	typedef struct entity_t {
		int32_t id;
		bool enabled;
		bool destroy;
		CTransform *transform;
	} Entity;
	Entity *getEntity(int32_t id);
	void entitySetPosition(struct entity_t *e, float x, float y);
	void entitySetRotation(struct entity_t *e, float r);
	void entitySetScale(struct entity_t *e, float x, float y);
	void entitySetVelocity(struct entity_t *e, float x, float y);
	void entitySetAngularVelocity(struct entity_t *e, float r);
]]

return ffi