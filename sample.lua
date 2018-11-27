stone = gr.material({0.8, 0.7, 0.7}, {0.0, 0.0, 0.0}, 0)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
hide = gr.material({0.84, 0.6, 0.53}, {0.3, 0.3, 0.3}, 20)
mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
mat4 = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25)
gold = gr.material({0.9, 0.8, 0.4}, {0.8, 0.8, 0.4}, 25)
blue = gr.material({0.7, 0.6, 1}, {0.5, 0.4, 0.8}, 25)
brown = gr.material({0.5, 0.3, 0.2}, {0.0, 0.0, 0.0}, 0)
green = gr.material({0.1, 0.5, 0.1}, {0.0, 0.0, 0.0}, 0)

scene = gr.node('scene')
scene:rotate('x', 10.0)
-- scene:scale(2, 2, 2)

inst = gr.node('inst')

arc = gr.node('arc')
inst:add_child(arc)
arc:translate(0, 0, -10)

p1 = gr.cylinder('p1')
arc:add_child(p1)
p1:set_material(stone)
p1:scale(0.5, 4, 0.5)
p1:translate(-2.4, 0, -0.4)

p2 = gr.cylinder('p2')
arc:add_child(p2)
p2:set_material(stone)
p2:scale(0.5, 4, 0.5)
p2:translate(1.6, 0, -0.4)

s = gr.sphere('s')
arc:add_child(s)
s:set_material(stone)
s:scale(3, 0.5, 0.5)
s:translate(-0.3, 4, -0.4)

tree = gr.node('tree')
tree:translate(0, 0, -7.5)

t1 = gr.cylinder('t1')
tree:add_child(t1)
t1:set_material(brown)
t1:scale(0.11, 0.5, 0.11)

t2 = gr.sphere('t2')
tree:add_child(t2)
t2:set_material(green)
t2:scale(0.5, 0.8, 0.5)
t2:translate(0, 1.3, 0)



for i = 1, 6 do
   an_tree = gr.node('tree' .. tostring(i))
   an_tree:rotate('Y', (i-1) * 60)
   scene:add_child(an_tree)
   an_tree:add_child(tree)
end

for i = 1, 4 do
	if i == 3 then goto continue end
	   an_arc = gr.node('arc' .. tostring(i))
	   an_arc:rotate('Y', (i-1) * 90)
	   scene:add_child(an_arc)
	   an_arc:add_child(arc)
	::continue::
end

-- the floor

plane = gr.mesh('plane', 'plane.obj' )
scene:add_child(plane)
plane:set_material(grass)
plane:scale(30, 30, 30)

-- cow model
cow_poly = gr.mesh('cow', 'cow.obj')
factor = 2.0/(2.76+3.637)

cow_poly:set_material(gold)

cow_poly:translate(0.0, 3.637, 0.0)
cow_poly:scale(factor, factor, factor)
cow_poly:translate(0.0, -1.0, 0.0)

-- cow instance
cow1 = gr.node('cow1')
scene:add_child(cow1)
cow1:add_child(cow_poly)
cow1:scale(1.11, 1.1, 1.1)
cow1:translate(-3.7, 0.8, 0)

cow2 = gr.node('cow2')
scene:add_child(cow2)
cow2:add_child(cow_poly)
cow2:rotate('y', 180)
cow2:scale(1.1, 1.1, 1.1)
cow2:translate(3.7, 0.8, 0)

c1 = gr.sphere('c1')
scene:add_child(c1)
c1:set_material(mat1)
c1:scale(1.5, 1.5, 1.5)
c1:translate(0, 1, 0)

gr.render(scene,
	  'sample.png', 500, 500,
	  {0, 2, 30}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.4, 0.4, 0.4}, {gr.light({200, 202, 430}, {0.8, 0.8, 0.8}, {1, 0, 0})})

-- A simple scene with some miscellaneous geometry.
