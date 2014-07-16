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

	struct sprite_t {
		struct vec2_t *position;
		struct vec2_t *scale;
		float rotation;
		int width;
		int height;
		int depth;
	};

	void entitySetPosition(struct entity_t *e, float x, float y);
	void entitySetRotation(struct entity_t *e, float r);
	void entitySetScale(struct entity_t *e, float x, float y);
	void entitySetVelocity(struct entity_t *e, float x, float y);
	void entitySetAngularVelocity(struct entity_t *e, float r);
	struct sprite_t *entityGetSprite(struct entity_t *e);
	int random_int(int min, int max);
]]

entityId = 0
function setEntityId(id)
	entityId = id
end

screen = {}
function setScreenSize(width, height)
	screen.width = width
	screen.height = height
end

function random(min, max)
	return ffi.C.random_int(min, max)
end

return ffi