local ffi = require("scripts/gameapi")

local C = ffi.C
local entity = nil
local sprite = nil

local minSpeed = 16
local maxSpeed = 64

function genYPos()
	return random(0, screen.height)
end

function genSpeed()
	return random(minSpeed, maxSpeed)
end

function resetBackgroundEntity(initial)
	x = screen.width + sprite.width
	if initial then
		x = random(0, screen.width)
	end

	C.entitySetVelocity(entity, -genSpeed(), 0)
	C.entitySetPosition(entity, x, genYPos())	
end

function start()
	entity = C.getEntity(entityId)
	sprite = C.entityGetSprite(entity)
	
	resetBackgroundEntity(true)
end

function update(dt)
end

function lateUpdate(dt)
	if entity.transform.position.x < -sprite.width then
		resetBackgroundEntity(false)
	end
end

function render()
end