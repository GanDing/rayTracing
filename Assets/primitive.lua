-- mat1 = gr.material({0.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, {0.2, 0.0, 0.8}, 25, 0.0, 1.5)
-- mat2 = gr.material({0.9, 0.9, 0.9}, {0.5, 0.7, 0.5}, {1.0, 0.0, 0.0}, 25, 0.0, 1.0)
-- mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, {1.0, 0.0, 0.0}, 25, 0.0, 1.0)
-- mat4 = gr.material({1.0, 1.0, 1.0}, {0.5, 0.4, 0.8}, {1.0, 0.0, 0.0}, 25, 0.0, 1.0)
mat1 = gr.material({0.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, 25, 0.8)
mat2 = gr.material({0.9, 0.9, 0.9}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
mat4 = gr.material({0.8, 0.8, 0.8}, {0.5, 0.4, 0.8}, 25, 0)
blue = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25, 0)
green = gr.material({0.1, 0.5, 0.1}, {0.5, 0.4, 0.8}, 25, 0)
brown = gr.material({0.5, 0.3, 0.2}, {0.0, 0.0, 0.0}, 25, 0)
m_mat3 = gr.material({1.0, 0.6, 0.1}, {0.0, 0.0, 0.0}, 25, 0)
glass = gr.material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 25, 1)
mirrow = gr.material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 25, 0)


scene_root = gr.node('root')

-- s2 = gr.nh_sphere('s2', {-20, -15, -20}, 15)
s2 = gr.torus('s2', 15, 5)
-- s2:translate(-200, 0, -200)
scene_root:add_child(s2)
s2:set_material(mat2)

-- s2 = gr.nh_sphere('s2', {0, -19, -0}, 11)
-- s2:translate(-200, 0, -200)
-- scene_root:add_child(s2)
-- s2:set_material(green)

s3 = gr.nh_box('s3', {-60, -120, -60}, 120)
s3:translate(0, -30, 0)
scene_root:add_child(s3)
s3:set_material(brown)

s4 = gr.nh_box('s4', {-60, 0, -120}, 120)
s4:translate(0, -30, -60)
s4:scale(1, 1.5, 1)
scene_root:add_child(s4)
s4:set_material(blue)

s5 = gr.nh_box('s5', {-60, 0, -60}, 120)
s5:translate(100, -30, 0)
s5:scale(1, 1.5, 1)
scene_root:add_child(s5)
-- s5:set_material(blue)
s5:set_material(blue)

s6 = gr.nh_box('s6', {-60, 0, -60}, 120)
s6:translate(-100, -30, 0)
s6:scale(1, 1.5, 1)
scene_root:add_child(s6)
-- s6:set_material(green)
s6:set_material(blue)

white_light = gr.light({10.0, 40.0, 10.0}, {0.9, 0.9, 0.9}, {1, 1, 1})

gr.render(scene_root, 'primitive.png', 512, 512,
    {0, 0, 120}, {0, 0, -1}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, {white_light})
