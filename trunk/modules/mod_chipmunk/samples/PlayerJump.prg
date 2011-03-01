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
import "mod_draw";
import "mod_scroll";
import "mod_chipmunk"

global
	pelota;
	cpVect point,ot;
	handler;
	fondo;
	fpg;
private
	press;
	cpSegmentQueryInfo info ;
	float distancia;
	bl;
Begin
	set_mode(800,600,32);
	fondo=load_png("fondoImg.png");
	pelota=load_png("bola40.png");
	fpg=load_fpg("graficos.fpg");
	start_scroll(0,0,fondo,0,0,0);
	gphysics.gravity_Y=300;
	gphysics.damping=0.9;
	gphysics.interval=1.0/25.0;
	handler=COLLISIONHANDLERNEW(1,2);    //detecta donde colisionan los objetos con lphysics.collisionType 1 y 2	
	plano(400,440,0);
	plano(700,340,6000);
	plano(1000,640,0);
	plano(1300,740,-10000);
	caer(200,420);
	cubo(400,400);
	gphysics.bias_coef=1.0;
	mouse.graph=pelota;
	mouse.size=50;
	while (!key(_esc))
		frame;
	end
	let_me_alone();
end

process plano(x,y,angle)
begin
	lphysics.static=true;
	lphysics.mass=infinity;
	lphysics.inertia=infinity;
	lphysics.collisionType=2;
	lphysics.elasticity=1;
	lphysics.friction=0.4;
	graph=new_map(300,20,32);
	z=15;
	lphysics.ShapeType=TYPE_LINE;
	map_clear(file,graph,rgb(0,255,0));
	ctype=c_scroll;
	loop
		frame;
	end
end

process caer(x,y)
private
begin
	lphysics.static=false;
	lphysics.mass=10;
	lphysics.inertia=10;
	lphysics.collisionType=2;
	lphysics.elasticity=1;
	lphysics.friction=0.4;
	graph=new_map(100,20,32);
	z=15;
	lphysics.ShapeType=TYPE_LINE;
	map_clear(file,graph,rgb(250,0,0));
	ctype=c_scroll;
	signal(id,s_freeze);
	loop
		frame;
	end
end

process cubo(x,y)
private
	id3;
	cpvect nPiso,vel,inter,aux,pos=0,-17;
	cpContactPointSet Ct;
	int x0,y0;
	sub;
	dat[]=0,0,20;//se puede crear un arreglo con los parámetros para la creación del cuerpo físico y asignarse la dirección del arreglo a la variable local lphysics.params para crear el cuerpo de acuerdo a éstos. Los parámetros son los mismos que los que se usan en las funciones que hacen este trabajo y en el mismo orden (addCircleShape, por ejemplo).
begin
	lphysics.static=false;
	lphysics.mass=10;
	lphysics.inertia= cpMomentForCircle(lphysics.mass, 0, 10, &cpvzero);
	lphysics.params=&dat;                     //parámetros para la creación del lphysics.shape: centro 0,0 y 20 de radio.
	for (z=302;z<310;z++)
		set_center(fpg,z,17,22);
	end
	file=fpg;
	graph=302;
	lphysics.elasticity=0;
	lphysics.friction=0;
	lphysics.collisionType=1;
	priority=father.priority-2;
	lphysics.ShapeType=TYPE_circle;
	FORCECREATEBODY(); //forza la creación del cuerpo físico inmediatamente para comenzar a usarlo
	ctype=c_scroll;
	scroll.camera=id;
	loop

		if (key(_right))
			GetBody(lphysics.body,cp_c_v,&vel);
			cpvperp(&nPiso,&aux);
			cpvmult(&aux, 10,&inter);
			cpvadd(&vel, &inter,&inter);
			inter.x=cpfclamp(inter.x, -120, 120);
			DEFBODYP(lphysics.body,CP_C_V,&inter);
			graph++;
			flags=1;

		end
		if (key(_left))
			GetBody(lphysics.body,cp_c_v,&vel);
			cpvperp(&nPiso,&aux);
			cpvmult(&aux, -10,&inter);
			cpvadd(&vel, &inter,&inter);
			inter.x=cpfclamp(inter.x, -120, 120);
			DEFBODYP(lphysics.body,CP_C_V,&inter);
			graph++;
			flags=0;
		end
 	if (GETCOLLISIONINFO(handler,&ct))
			
			if (ct.points[0].normal.y>0.7)
				nPiso.x=-1.0*ct.points[0].normal.x;
				nPiso.y=-1.0*ct.points[0].normal.y;
                        end
			id3=(ct.id2==id? ct.id1 : ct.id2);
			if (id3.reserved.status<>2);
			signal(id3,s_wakeup);
			id3.flags=4;
			end
			sub=true;
		else
			sub=false;
		end

		angle=atan2(nPiso.y*1000.0,nPiso.x*1000.0)+90000;
   	       if (sub and key(_up) )

			GetBody(lphysics.body,cp_c_v,&vel);
			cpvmult(&nPiso, 600.0,&aux);
			cpvadd(&vel, &aux,&vel);
			vel.y=cpfclamp(vel.y, -600, 600);
			DEFBODYP(lphysics.body,cp_c_v,&vel);
			cpBodyActivate(lphysics.body);
		else
			cpv(0,-1,&nPiso);
		end
		if (graph>309)
			graph=302;
		end
		UpdateVelocity();
		frame;

	end
end
