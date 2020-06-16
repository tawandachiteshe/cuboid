
local pos1 = Vector2.new()


local size1 = Vector2.new()
size1.x = 1.0
size1.y = 1.0


for i = 1, 100, 1 do
    for j = 1, 100, 1 do
        pos1.x = pos1.x + i
        pos1.y = pos1.y + j
        draw_quad(pos1, size1)
    end
end

pos1.x = 0
pos1.y = 0