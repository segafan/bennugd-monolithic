import "mod_video"
import "mod_key"
import "mod_proc"
import "mod_map"
import "mod_screen"
import "mod_wm"
import "mod_dir"
import "mod_file"
import "mod_chipmunk"
import "mod_mouse"
import "mod_say"
import "mod_time";
import "mod_scroll";
import "mod_text";
import "mod_sound";
import "mod_math";

#define ANCHO     1024
#define ALTO      768

global
f_pagina;
s_sonidos[2];
puntuaje=0;
scroll_width;
scroll_heigth;
g_circuloPeque;
pelota;

begin
     full_screen=true;
     set_mode(ancho,alto,32);
     f_pagina=load_fpg("catapulta.fpg");
     g_circuloPeque=load_png("punto_peque.png");
     pelota=load_png("pelota.png");
     
    gphysics.interval=1.0/25.0;                   //Velocidad en que el motor está actuando, normalmente se usa la inversa del valor de las imágenes por segundo
    gphysics.SLEEPTIMETHRESHOLD=infinityf();      //Time a group of bodies must remain idle in order to fall asleep
    gphysics.bias_coef=0.3;
    gphysics.gravity_Y=50;
    gphysics.damping=1;

    gphysics.collision_slop=0.0;
    gphysics.iterations=10;
    gphysics.sleepTimeThreshold=infinityf();

     catapulta();
     mano();
     addPivotJoint2(0, son, 301,857,0,0);
     addDampedRotarySpring(0, son, 0,1333333,0);
     ADDROTARYLIMITJOINT(0,son, -76000,0);
     mouseP();
     estructura(1000);
     estructura(1600);
     puntuaje=0;
     write(0,40,20,4,"puntaje");
     write_var(0,40,40,4,puntuaje);

  while (not key(_esc))
        frame;
  end
  let_me_alone();
end

process mouseP()
private
	mouseJoint;
	x0,y0;
begin
 	lphysics.static=true;
	lphysics.ShapeType=TYPE_empty;                //No crearle cuerpos
	FORCECREATEBODY();
        ctype=c_scroll;
	graph=pelota;	size=30;	priority=5;	z=-100;
	loop
		x=mouse.x+scroll.x0;
		y=mouse.y+scroll.y0;
		 if (mouse.left)
			z = SpacePointQueryFirst( x, y, CP_ALL_LAYERS, CP_NO_GROUP);        //Toma el id de algún proceso que toque el punto dado por (x,y) y cuya capa esté comprendida por CP_ALL_LAYERS y pertenezca al grupo CP_NO_GROUP
			if (z and mouseJoint==0)                                            //Si z es distinto de cero y no se ha creado el joint
				WORLD2LOCAL(z, x, y,&x0, &y0);                              //Transforma las coordenadas del ratón a coordenadas locales del proceso almacenado en z
				mouseJoint=addPivotJoint2(id, z, 0,0, x0,y0);               //crea el joint entre este proceso y el proceso apuntado por z en los puntos (0,0) de este proces y el (x0, y0) del proceso que se toca. Coordenadas locales
				DefConstraintF(mouseJoint,CP_C_MAXFORCE,80000);             //Define algunos valores del joint, véase la ayuda para más información
				DefConstraintF(mouseJoint,CP_C_BIASCOEF,0.000005822);
			end
		elseif (mouseJoint<>0)                                                      //Si no se presiona el botón izquierdo del ratón eliminar el joint
			RemoveConstraint(mouseJoint);
			mouseJoint = 0;
		end
		frame;
	end
end

process catapulta()
private
zona;
begin

  s_sonidos[0]=load_wav("sonidos/cae.wav");
  s_sonidos[1]=load_wav("sonidos/lanzarPelota.wav");
  file=f_pagina;
  graph=1;
  x=248;
  y=818;
  zona=load_png("scroll.png");
  scroll_width =graphic_info(0,zona,g_width);
  scroll_heigth =895;//graphic_info(0,zona,g_height);

   addInanimateShape(type_line, 0.0,   scroll_heigth, scroll_width,scroll_heigth, 0.0);      //Crea una línea para simular el piso y se agrega al fondo, pero no se pinta.
  addInanimateShape(type_line, 0.0,   0.0,  scroll_width,0.0,  0.0);
  addInanimateShape(type_line, 0.0,   0.0,  0.0,  scroll_heigth, 0.0);
  addInanimateShape(type_line, scroll_width, 0.0,  scroll_width,scroll_heigth, 0.0);

  ctype=c_scroll;
  start_scroll(0,0,zona,0,0,0,0,0);
  scroll.camera=id;
  scroll.speed=15;
  SPACEADDCOLLISIONHANDLER(3,3,"","","postsolveCatap","",null,null,null,null);
loop
      if (key(_left))
         scroll.camera=0;
         scroll.x0-=15;
      end
      if (key(_right))
         scroll.camera=0;
         scroll.x0+=15;
      end
      if (key(_up))
         scroll.camera=0;
         scroll.y0-=15;
      end
      if (key(_down))
         scroll.camera=0;
         scroll.y0+=15;
      end
frame;
end
onexit;
stop_scroll(0);
unload_map(0,zona);
SPACEREMOVECOLLISIONHANDLER(3,3);
end

function postsolveCatap(int arb, int * p )
private
float fx,fy,mag;
int canal;
begin
  GETARBITERTOTALIMPULSE(arb,&fx,&fy);
  mag=abs(fx)+abs(fy);
  if (mag>20)
     canal=play_wav(s_sonidos[0],0);
     SET_channel_VOLUME ( canal, mag*2 );
     puntuaje+=mag/10;
  end
end

process punto(x,y)
begin
ctype=c_scroll;
        z=-500;
        graph=pelota;
loop
frame;
end
end

process mano()
private
objeto=0;
x0,y0;
joint;
int c=3;
x1,y1;
begin
        x=301;
        y=857;
        file=f_pagina;
        graph=2;
	lphysics.mass=2;
	lphysics.ELASTICITY=1;
	lphysics.friction=0.3;
	lphysics.ShapeType=Type_line;
	lphysics.group=3;
	forceCreateBody();
	lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
        ctype=c_scroll;
        z=-300;

/*         LOCAL2WORLD(id, 0, -202, &x1, &y1);
        punto(x1,y1);
        LOCAL2WORLD(id, 0, -25, &x1, &y1);
        punto(x1,y1);
        alpha=40; */
	loop

        	        if (angle>15000 and objeto==0)
        	           if (c>0)
	                      c--;
              	              objeto=bala(x+1,y-175);
              	              WORLD2LOCAL(id,objeto.x,objeto.y,&x0, &y0);
              	              joint=addPinJoint(id,objeto, x0,y0,0,0);
              	              scroll.camera=objeto;
           	           end
        	        end
        	        if (angle<13000 and joint<>0 and not mouse.left)
        	           RemoveConstraint(joint);
        	           play_wav(s_sonidos[1],0);
        	           joint=0;
        	        end
        	        if (angle<10000 and objeto<>0)
        	           objeto=0;
        	        end
                frame;

	end
end
process bala(x,y)
begin
        graph=g_circuloPeque;
	lphysics.layers=2;
	lphysics.group=3;
        lphysics.ShapeType=TYPE_CIRCLE;
	lphysics.elasticity=0;                     //Define su elasticidad
	lphysics.friction=0.3;                         //Define su coeficiente de fricción
        forceCreateBody();                 //Se forza la creación del cuerpo
        lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
        ctype=c_scroll;
        lphysics.collisionType=3;
	from z=0 to 300;
	     frame;
	end
	onexit;
	if (scroll.camera==id)
	   scroll.camera=father;
	end
end

process ladrillos(x,y,angle)
begin
	file=f_pagina;
        graph=3;
	lphysics.layers=2;
        lphysics.ShapeType=TYPE_box;      //Le crea un cuerpo poligonal, es el más caro computacionalmente hablando, pero es el más exacto para ajustarle una forma
	lphysics.elasticity=0;                     //Define su elasticidad
	lphysics.friction=0.3;                         //Define su coeficiente de fricción
        forceCreateBody();                 //Se forza la creación del cuerpo
        lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
        ctype=c_scroll;
        lphysics.collisionType=3;
	loop
		frame;

	end
end


function estructura(x);
private
lim,c;
begin
     y=scroll_heigth-33;
     lim=200;
     from c=0 to 3;
       for(z=x-lim;z<x+lim;z+=60);
          ladrillos(z,y,0);
       end
       y-=36;
       for(z=x-lim;z<x+lim;z+=60);
          ladrillos(z,y,90000);
       end
       y-=36;
       lim-=60;
     end


end