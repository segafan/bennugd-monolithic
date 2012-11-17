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
import "mod_chipmunk"

global
	pelota;
	cpVect verts[]=
	-25,-25,
	-25,25,
	25,25,
	25,-25;
	cuadro;
	bola;
	bomba;

Begin
	set_mode(800,600,32);
	cuadro=load_png("cuadro.png");
	bola=load_png("bola40.png");
	bomba=load_png("bomba.png");
 	gphysics.damping=1;
 	for (z=0;z<15;z++)
		cuadro(z*50+50,50);
	end
	for (z=0;z<15;z++)
		cuadro(z*50+50,550);
	end
	for (y=0;y<4;y++)
		for (z=0;z<6;z++)
			cuadro(z*100+150,y*100+150);
		end
	end

	for (z=0;z<9;z++)
		cuadro(50,z*50+100);
	end

	for (z=0;z<9;z++)
		cuadro(750,z*50+100);
	end
	bomberman(150,150);
	gphysics.bias_coef=1;
	write(0,400,10,4,"Presiona v para dejar una bomba que se empuja");
	write(0,400,20,4,"Presiona space para dejar una bomba que NO se empuja");
	while (!key(_esc))
		frame;

	end
	let_me_alone();
end

process cuadro(x,y)
begin
	lphysics.static=true;
	lphysics.mass=infinity;
	lphysics.inertia=infinity;
	lphysics.elasticity=1;
	lphysics.friction=1;
	lphysics.group=1;
	lphysics.ShapeType=TYPE_CONVEX_POLYGON;
	graph=cuadro;
	z=-15;
	loop
		frame;
	end
end
      #define vel 8
process bomberman(x,y)
private
	cpVect pos;
	press,press1;
	id2;
begin
	x=400;
	y=100;
	lphysics.mass=10;
	lphysics.inertia=10;
	priority=father.priority-2;
	lphysics.elasticity=0;
	lphysics.friction=0;                 //para que no gire al friccionar con otros objetos
	lphysics.group=2;
	lphysics.ShapeType=TYPE_CIRCLE;
	graph=bola;
	while (!key(_esc))
		if (key(_right))
			lphysics.incr_x=vel;
                        angle=0;
		end

		if (key(_left))
			lphysics.incr_x=-vel;
			angle=180000;
		end

		if (key(_up))
			lphysics.incr_y=-vel;
			angle=90000;
		end

		if (key(_down))
			lphysics.incr_y=vel;
			angle=270000;
		end

		if (key(_space))
			if (press)
				bomba(x,y,20000.0);
				press=false;
			end
		else
			press=true;
		end

		if (key(_v))
			if (press1)
				bomba(x,y,1.0);
				press1=false;
			end
		else
			press1=true;
		end

		frame;

	end
end

process bomba(x,y,float masa)
private
	cpVect pos;
	pego=true;

begin
        lphysics.mass=masa;
	priority=father.priority-2;
	lphysics.group=2;
	lphysics.elasticity=0.3;
	lphysics.friction=0;
	graph=bomba;
	lphysics.ShapeType=TYPE_CIRCLE;
	while (!key(_esc))
		if (pego and not collision(father))
			lphysics.group=CP_NO_GROUP;
			pego=false;
		end
		frame;

	end
end

