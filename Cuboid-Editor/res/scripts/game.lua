
local pos1 = Vector2.new()


local size1 = Vector2.new()
size1.x = 0.45
size1.y = 0.45


for i = -1.5, 1.5, 0.25 do
    for j = -1.5, 1.5, 0.25 do
        pos1.x = math.sin(i) * (1.0 / math.cos(math.tan(j)))
        pos1.y = math.tan(j) * math.cos(1.0 / (22.0 / 7.0))
        draw_quad(pos1, size1)
    end
end

pos1.x = 0
pos1.y = 0