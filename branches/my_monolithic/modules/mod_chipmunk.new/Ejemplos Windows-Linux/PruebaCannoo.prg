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
import "mod_file";

#include "jkeys.lib"


global
	pelota,barra,barraND;
	mass=1,inerty;
	fich;
private
	press;
	float distancia;
	bl;
	cpVect l[]=-30.0,-5.0,
        -30.0,5.0,
        30.0,5.0,
        30.0,-5.0;
Begin
	set_mode(320,240,8);
	set_fps(25,0);
	fich=fopen("salida.txt",o_write);
	jkeys_set_default_keys();
	jkeys_init();
	pelota=new_map(15,15,8);
	drawing_map(0,pelota);
	drawing_color(rgb(255,0,0));
	draw_fcircle(7,7,7);
	gphysics.gravity_Y=70;
	gphysics.interval=1.0/25.0;
	gphysics.phresolution=1;
	barra=new_map(60,10,8);
        barraND=new_map(60,10,8);
	map_clear(0,barra,rgb(50,200,20));
	map_clear(0,barraND,rgb(180,0,130));
	inerty=cpMomentForSegment(mass,-30.0,0.0,30.0,0.0);

        addInanimateShape(type_line, 0.0  ,0.0,  0.0,240.0,0.0);
        addInanimateShape(type_line, 319.0,0.0,319.0,240.0,0.0);
        addInanimateShape(type_line, 0.0  ,0.0,319.0,  0.0,0.0);

        creaZona();

	write(0,10,10,0,"Deja caer la pelota al agua");

        graph=new_map(320,10,8);
        map_clear(file,graph,rgb(0,0,255));
        x=160;
        y=235;
        mouse.graph=pelota;
	while (!jkeys_state[_JKEY_MENU])
		frame;

	end
        jkeys_exit();
	let_me_alone();
	fclose(fich);

end

function creaZona();
begin
signal(type plano,s_kill);
        bol();
        plano(160,28,barra, "sin movimiento arriba");

        z=plano(140,50,barraND, "resorte");
       	addPivotJoint(z,0,110,50);
	addDampedRotarySpring(z, 0, 0,95000,2);

        z=plano(200,90,barraND,"motor");
       	addPivotJoint(z,0,230,90);
        addSimpleMotor(z,0,80000);

	z=plano(58,135,barraND,"oscilacion");
       	addPinJoint(z,0,0,0,150,120);

       	plano(160,165,barra,"sin movimiento abajo");

end

process plano(x,y,graph, string nombre)
private
cpvect v,f,r;
int id3;
begin
        if (graph==barra)
	lphysics.static=true;
	 lphysics.mass=infinityf();
	lphysics.inertia=infinityf();
	else
	lphysics.static=false;
        lphysics.mass=mass;
	lphysics.inertia=inerty;
	end

	lphysics.elasticity=1;
	lphysics.friction=1;
	lphysics.ShapeType=TYPE_line;
	fputs(fich,nombre+" comienzo "+x+ " " + y + " "+ angle);
	FORCECREATEBODY();
	loop
	getBody(lphysics.body,cp_c_v,&v);
	getBody(lphysics.body,cp_c_f,&f);
	getBody(lphysics.body,cp_c_rot,&r);
	fputs(fich,nombre+" "+x+ " " + y + " "+ angle+" "+cpvstr(v)+" "+cpvstr(f)+" "+cpvstr(r));
	while (id3=GETCONSTRAINTS(id))       //no tienen constraints, no debe salir en consola nada
	fputs(fich,"impulso "+CONSTRAINTGETIMPULSE(id3));
	end
	if (mouse.left and graph==barra and collision(type mouse))
	   signal(id,s_kill);
	end
		frame;
	end
end

process bol()
private
cpvect v,f,r;
int id3;
string nombre ="bola";
begin
        x=160;
	y=20;
	lphysics.static=false;
	lphysics.mass=10;
	lphysics.inertia=CPMOMENTFORCIRCLE(lphysics.mass,0.0,10.0,0.0,0.0);
	lphysics.ELASTICITY=0.1;
	lphysics.friction=0.9;
	lphysics.collisionType=1;
	lphysics.ShapeType=TYPE_CIRCLE;
	graph=pelota;
        FORCECREATEBODY();
	loop
	getBody(lphysics.body,cp_c_v,&v);
	getBody(lphysics.body,cp_c_f,&f);
	getBody(lphysics.body,cp_c_rot,&r);
	fputs(fich,nombre+" "+x+ " " + y + " "+ angle+" "+cpvstr(v)+" "+cpvstr(f)+" "+cpvstr(r));
		if (out_region(id,0))
                        z=write(0,100,100,4,"Felicidades!!, reiniciando...");
                        frame(4500);
                        delete_text(z);
			creaZona();
			signal(id,s_kill);
		end
		frame;

	end
end
