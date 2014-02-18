local ffi = require("ffi")

ffi.cdef[[
	void spawnBullet(float x, float y, float angle);
]]

local C = ffi.C
local firetime = 0.1
local timer = firetime

function start()
end

function update(dt)
	timer = timer - dt;
	if (timer <= 0) then
		timer = firetime
		C.spawnBullet(50, 350, -10)
		C.spawnBullet(50, 360, 0)
		C.spawnBullet(50, 370, 10)
	end
end

function lateUpdate(dt)
end

function render()
end
