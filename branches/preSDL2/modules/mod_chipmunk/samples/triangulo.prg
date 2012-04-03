//PRG, ejemplo para el motor de física

import "mod_key";
import "mod_text";
import "mod_proc";
import "mod_grproc";
import "mod_video";
import "mod_wm";
import "mod_map";
import "mod_say";
import "mod_math";
import "mod_screen";
import "mod_chipmunk";
import "mod_draw";
import "mod_rand";


global
	pelota;
	cpVect point,ot;
tot=0;
private
	press;
	float distancia;
	bl;
Begin
	set_mode(800,600,32);
	pelota=load_png("tri.png");
	gphysics.gravity_Y=300;
	gphysics.interval=1.0/25.0;
	
	for (z=0;z<6;z++)
		plano();
	end
	write(0,400,10,4,"Mueve los triangulos con _left, _right ");
	gphysics.bias_coef=1.0;
	mouse.graph=pelota;
	mouse.size=50;
	while (!key(_esc))
if (rand(0,30)==3 and tot<30)

		triangulo();
end
		frame;

	end

	let_me_alone();

end

process plano()
private

begin

	lphysics.static=true;
	lphysics.mass=infinity;
	lphysics.inertia=infinity;
	lphysics.collisionType=2;
	lphysics.elasticity=1;
	lphysics.friction=0.4;
	graph=new_map(rand(200,400),20,32);
	x=rand(100,700);
	y=rand(300,550);
	z=15;
	angle=rand(0,360000);
	lphysics.ShapeType=TYPE_LINE;
	map_clear(file,graph,rgb(0,255,0));

	loop
		frame;
	end
end

process triangulo()
private
id3;
datos[]=0,0,3,
-20,-20,
       -20,20,
       20,0;
cpvect p[]= -20.0,-20.0
       -20.0,20.0,
       20.0,0.0;
begin
tot++;
        x=400;
	y=100;
 lphysics.params=&datos;
	lphysics.static=false;
	lphysics.mass=10;
	lphysics.inertia=CPMOMENTFORPOLY(lphysics.mass,3.0,&p,0.0,0.0);
	lphysics.ELASTICITY=0.1;
	lphysics.friction=0.3;
	lphysics.collisionType=1;
	priority=father.priority-2;
	lphysics.ShapeType=TYPE_CONVEX_POLYGON;
	graph=pelota;

	while (!key(_esc))
		if (key(_right))
			lphysics.incr_x+=5;
		end

		if (key(_left))
			lphysics.incr_x-=5;
		end
		if (out_region(id,0))
			signal(id,s_kill);
		end
		frame;

	end
onexit;
tot--;
end
