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
import "mod_rand";
import "mod_chipmunk";

global
	float u = 0.6;       //fricción para algunos cuerpos

	pelota;              //Gráfico para las pelotas
private
	press;               //Se usa en las pulsaciones de espacio

Begin
if (mode_is_ok(1280,800,32,MODE_FULLSCREEN ))            //Si el modo de video está soportado
	set_mode(1280,800,32,MODE_FULLSCREEN );          //Lo define
elseif (mode_is_ok(1280,800,32,0))
	set_mode(1280,800,32);
else
exit("El modo de video no está soportado, intenta cambiarlo");
end

	pelota=load_png("pelota.png");

	gphysics.gravity_y=300;           //Define gravedad
        gphysics.iterations=30;           //Aumenta el número de iteraciones para cada cuerpo, mejorando la simulación pero haciéndola más tardada. El número de iteraciones por frame será este valor multiplicado por phresolution, por lo general x3

        //Estas funciones mejoran el rendimiento del motor, vésase la descripción de cada una en la ayuda para más información
        gphysics.sleepTimeThreshold=0.5;
        gphysics.collision_slop=0.5;
//	SpaceResizeActiveHash( 30.0, 2999);
//	SpaceResizeStaticHash( 30.0, 999);

	plano();               //Se pone el piso
	creaPiramide();        //Se crea la pirámide de dominós

	write(0,400,10,4,"Presiona _space");

	while (!key(_esc))
		if (key(_space))
			if (not press)               //si presiona espacio, se arroja una pelota para tumbar los dominós
				cubo();
				press=true;
			end
		else
			press=false;
		end
		frame;

	end
	let_me_alone();
end

process plano()                                      //Crea el plano donde se sienta la pirámide
begin
	lphysics.static=true;                        //Que sea un cuerpo estático (Nada lo mueve excepto tú con x o incr_x)
	lphysics.ShapeType=TYPE_LINE;                //Le agrega un cuerpo tipo línea

	graph=new_map(1200,20,32);
	map_clear(file,graph,rgb(0,255,0));
	x=640;	y=780;	z=15;
	loop
		frame;
	end
end


process dominos(x,y,angle)
begin
	graph=new_map(6,40,32);
	map_clear(file,graph,rgb(100,255,255));
        priority=father.priority;

	lphysics.ShapeType=TYPE_box;      //Le crea un cuerpo poligonal, es el más caro computacionalmente hablando, pero es el más exacto para ajustarle una forma
	lphysics.elasticity=0;                     //Define su elasticidad
	lphysics.friction=u;                         //Define su coeficiente de fricción

        forceCreateBody();                 //Se forza la creación del cuerpo

        //Antes de llamar a getOptimalInertia hay que actualizar el cuerpo, ya sea forzando su creación (cuando éste aún no existe) o haciendo un frame(v) antes, con v igual a cualquier valor o sin v.
	lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
	loop
		frame;

	end
end

#define reajuste 770
#define n 9

//Crea la pirámide, por se código bennu no comentaré nada
function creaPiramide()
private
cpVect offs,pos,aux;
begin

for(x=n; x>0; x--)
		cpv(-x*60/2.0, (n - x)*52 +240,&offs);
		for(y=x-1; y>=0; y--)
                        cpvadd(cpv(y*60, -220,aux), &offs,&pos);
			dominos(640+pos.x,reajuste-pos.y,0);

                        cpvadd(cpv(y*60, -197,aux), &offs,&pos);
			dominos(640+pos.x,reajuste-pos.y,PI/2.0);


			if(y == (x - 1)) continue;  end
                        cpvadd(cpv(y*60 + 30, -191,aux), &offs,&pos);
			dominos(640+pos.x,reajuste-pos.y,PI/2.0);

                end
                cpvadd(cpv(-17, -174,aux), &offs,&pos);
		dominos(640+pos.x,reajuste-pos.y,0);

                cpvadd(cpv((x - 1)*60 + 17, -174,aux), &offs,&pos);
		dominos(640+pos.x,reajuste-pos.y,0);
        end

end

process cubo()
begin
	x=400;	y=100;
        graph=pelota;

	lphysics.mass=10;
	lphysics.inertia= cpMomentForCircle(10.0, 0.0, 10.0, 0.0,0.0);
	lphysics.ShapeType=TYPE_circle;
	lphysics.elasticity=0.1;
	lphysics.friction=0.6;

        FORCECREATEBODY(); //forza la creación del cuerpo físico inmediatamente para comenzar a usarlo
        Slew( rand(300,900),500, 1);  //Mueve la pelóta hacia el punto ( rand[300,900] ,500)
	loop
                if (out_region(id,0))
			signal(id,s_kill);
		end
		frame;

	end
end
