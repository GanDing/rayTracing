mat1 = gr.material({0.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, 25, 0.8)
mat2 = gr.material({0.9, 0.9, 0.9}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
mat4 = gr.material({0.8, 0.8, 0.8}, {0.5, 0.4, 0.8}, 25, 0)
blue = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25, 0)
red = gr.material({1, 0.2, 0.2}, {0.5, 0.4, 0.5}, 25, 0)
pink = gr.material({1, 0.2, 0.8}, {0.5, 0.4, 0.5}, 25, 0)
green = gr.material({0.1, 0.5, 0.1}, {0.5, 0.4, 0.8}, 25, 0)
brown = gr.material({0.5, 0.3, 0.2}, {0.0, 0.0, 0.0}, 25, 0)
m_mat3 = gr.material({1.0, 0.6, 0.1}, {0.0, 0.0, 0.0}, 25, 0)
glass = gr.material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 25, 1)
mirrow = gr.material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 25, 0)
wall = gr.texture("texture/wall.png", {0.1, 0.1, 0.1}, 25, 0)
rock = gr.texture("texture/rock.png", {0.2, 0.2, 0.2}, 25, 0)
wood = gr.texture("texture/wood.png", {0.1, 0.1, 0.1}, 25, 0)
earth = gr.texture("texture/earthmap.png", {0.3, 0.3, 0.3}, 25, 0)
floor = gr.texture("texture/floor.png", {0.2, 0.2, 0.2}, 25, 0)
zuocang = gr.texture("texture/zuocang.png", {0, 0, 0}, 25, 0)
earthbump = gr.bump("texture/earthbump.png")
zuocangbump = gr.bump("texture/zuocangbump2.png")
earth:set_bump(earthbump)
-- zuocang:set_bump(zuocangbump)

scene_root = gr.node('root')

table = gr.nh_box('table', {-40, -60, -30}, 60)
scene_root:add_child(table)
table:set_material(rock)

glassball1 = gr.nh_sphere('glassball1', {0, 2, 0}, 2)
table:add_child(glassball1)
glassball1:set_material(glass)

glassball2 = gr.nh_sphere('glassball2', {-7, 2, 25}, 2)
table:add_child(glassball2)
glassball2:set_material(glass)

glassball3 = gr.nh_sphere('glassball3', {6, 2, -3}, 2)
table:add_child(glassball3)
glassball3:set_material(glass)

box1 = gr.nh_box('box1', {-20, 0, -15}, 6)
-- box1:rotate('x', 90)
table:add_child(box1)
box1:set_material(pink)

box2 = gr.nh_box('box2', {-20, 6, -15}, 6)
-- box1:rotate('x', 90)
table:add_child(box2)
box2:set_material(green)

box3 = gr.nh_box('box3', {-20, 12, -15}, 6)
-- box1:rotate('x', 90)
table:add_child(box3)
box3:set_material(floor)

box4 = gr.nh_box('box4', {-10, 0, 10}, 6)
-- box1:rotate('x', 90)
box4:rotate('y', 20)
box4:translate(-7, 0, 0)
table:add_child(box4)
box4:set_material(wood)

box5 = gr.nh_box('box5', {-20, 0, -9}, 6)
-- box1:rotate('x', 90)
table:add_child(box5)
box5:set_material(red)

-- cylinder1 = gr.cylinder('cylinder1')
-- cylinder1:translate(-8,0,20)
-- -- cylinder1:scale()
-- scene_root:add_child(cylinder1)
-- cylinder1:set_material(mat2)

earth1 = gr.nh_sphere('earth', {0,0,0}, 3)
earth1:rotate('x', 30)
earth1:translate(6, 3, 20)
table:add_child(earth1)
earth1:set_material(earth)

mirrow1 = gr.nh_box('mirrow1', {0,0,0}, 15)
-- mirrow1:scale(1, 1, 0.05)
-- mirrow1:rotate('y', -30)
-- mirrow1:rotate('y', -30)
mirrow1:scale(1, 1, 0.05);
mirrow1:rotate('x', -5)
mirrow1:rotate('y', -35)
mirrow1:translate(6, 0, -15);
table:add_child(mirrow1)
mirrow1:set_material(mirrow)

wall1 = gr.nh_box('wall1', {-40, -30, -150}, 100)
scene_root:add_child(wall1)
wall1:set_material(wall)

wall2 = gr.nh_box('wall2', {-140, -30, -50}, 100)
scene_root:add_child(wall2)
wall2:set_material(wall)

-- wall3 = gr.nh_box('wall3', {-140, -30, -50}, 100)
-- scene_root:add_child(wall3)
-- wall2:set_material(wall)

zuocang1 = gr.nh_box('zuocang1', {-5, 20, -59.95}, 15)
zuocang1:scale(1, 1.5, 1)
wall1:add_child(zuocang1)
zuocang1:set_material(zuocang)

white_light = gr.light({10.0, 40.0, 10.0}, {0.9, 0.9, 0.9}, {1, 1, 1})

gr.render(scene_root, 'finalscene.png', 512, 512,
    {0, 15, 60}, {0, 0, -1}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, {white_light})
