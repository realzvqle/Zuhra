local RED = 0xFF0000FF
local GREEN = 0x00FF00FF
local BLUE = 0x0000FFFF
local WHITE = 0xFFFFFFFF


change_background(GREEN);


local color = create_color(0, 0,3,255);
local state = draw_button("Click Me", 200, 200, 200, 50, color, WHITE, GREEN, 20)

draw_rect(900, 900, 90, 80, RED);

draw_circle(100, 100, 90, BLUE);

if state == 2 then 
    draw_text("Hello", 10, 10, 90, BLUE);
elseif state == 3 then 
    draw_text("Bello", 10, 10, 90, BLUE);
elseif state == 4 then 
    draw_text("Tello", 10, 10, 90, BLUE);
end