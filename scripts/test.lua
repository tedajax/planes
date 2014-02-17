local ffi = require("ffi")
ffi.cdef[[
	typedef	int8_t		i8;
	typedef	int16_t		i16;
	typedef	int32_t		i32;
	typedef	int64_t		i64;

	typedef uint8_t		u8;
	typedef	uint16_t	u16;
	typedef	uint32_t	u32;
	typedef	uint64_t	u64;

	typedef	float		f32;
	typedef	double		f64;

	typedef struct vec2_t {
		f32 x, y;
	} Vec2;

	typedef void(*free_func)(void *);

	typedef struct dynarr_t {
		u32 size;
		u32 capacity;
		free_func freeFunc;
		void **data;
	} DynArr;

	typedef enum component_type_e {
		C_TRANSFORM,
		C_SPRITE_RENDERER,
		C_PLAYER_CONTROLLER,
		C_BULLET_CONTROLLER,
		C_LUA_COMPONENT,
		COMPONENT_COUNT
	} ComponentType;

	typedef struct component_t {
		ComponentType type;
		bool enabled;
		struct entity_t *entity;
		void *component;
	} Component;

	typedef struct ctransform_t {
		Component *super;
		Vec2 *position;
		Vec2 *scale;
		f32 rotation;

		Vec2 *velocity;
		f32 angularVelocity;
	} CTransform;

	typedef struct entity_t {
		i32 id;
		bool enabled;
		bool destroy;
		CTransform *transform;
		DynArr *components;
	} Entity;

	void *entity_getComponent(Entity *self, ComponentType type);
	void entity_start(Entity *self);
	void entity_update(Entity *self, f32 dt);
	void entity_lateUpdate(Entity *self, f32 dt);
	void entity_render(Entity *self);

	void *entity_addComponent(Entity *self, ComponentType type);
	void *entity_getComponent(Entity *self, ComponentType type);
	bool entity_removeComponent(Entity *self, Component *component);

	Entity *entity_new();

	typedef struct csprite_renderer_t {
		struct component_t *super;
		Sprite *sprite;
	} CSpriteRenderer;

	void *c_spriteRenderer_new(struct component_t *super);
	void c_spriteRenderer_start(void *pself);
	void c_spriteRenderer_update(void *pself, f32 dt);
	void c_spriteRenderer_lateUpdate(void *pself, f32 dt);
	void c_spriteRenderer_render(void *pself);

	
]]

local C = ffi.C

function start()
	local e = ffi.C.entity_new()
	print(e["id"])
end

function update(dt)
end

function lateUpdate(dt)
end

function render()
end
