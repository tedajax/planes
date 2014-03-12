local ffi = require("scripts/gameapi")

local C = ffi.C
local entity = nil
local sprite = nil

function start()
	entity = C.getEntity(entityId)
	C.entitySetVelocity(entity, -32, 0)
	sprite = C.entityGetSprite(entity)
end

function update(dt)
end

function lateUpdate(dt)
	if entity.transform.position.x < -sprite.width then
		C.entitySetPosition(entity, 1280 + sprite.width, entity.transform.position.y)
	end
end

function render()
end