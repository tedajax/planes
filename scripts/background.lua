local ffi = require("scripts/gameapi")

local C = ffi.C
local entity = nil

function start()
	entity = C.getEntity(entityId)
	C.entitySetVelocity(entity, -64, 0)
end

function update(dt)
end

function lateUpdate(dt)
end

function render()
end