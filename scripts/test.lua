local ffi = require("scripts/gameapi")

local C = ffi.C
local firetime = 0.1
local timer = firetime

function start()
	player = C.getEntity(1);
end

function update(dt)
	if timer > 0 then
		timer = timer - dt;
	end
end

function tryShoot()
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
