Program pptls;

import "mod_video"
import "mod_key"
import "mod_draw"
import "mod_proc"
import "mod_map"
import "mod_screen"
import "mod_time"
import "mod_text"
import "mod_grproc"
import "mod_rand"
import "mod_time"
import "mod_joy"


#define PSP_TRIANGLE_BUTTON 0
#define PSP_CIRCLE_BUTTON 1
#define PSP_X_BUTTON 2
#define PSP_SQUARE_BUTTON 3
#define PSP_L_BUTTON 4
#define PSP_R_BUTTON 5
#define PSP_DOWN_BUTTON 6
#define PSP_LEFT_BUTTON 7
#define PSP_UP_BUTTON 8
#define PSP_RIGHT_BUTTON 9
#define PSP_SELECT_BUTTON 10
#define PSP_START_BUTTON 11
#define PSP_LEFT_RIGHT_AXIS 0
#define PSP_UP_DOWN_AXIS 1


Global
	comenzar;
	id_texto;
	id_texto2;
	tiempo =200;
	i_tiempo =100;
	jugador id_jugador;
	ordenador id_ordenador;
End

function keyjoy(int keyid)
begin
	if (key(keyid))
		return 1;
	end
	if (NUMBER_JOY()>0)
		if (keyid==_UP && get_joy_button(0,PSP_UP_BUTTON))
			return 1;
		end
		if (keyid==_DOWN && get_joy_button(0,PSP_DOWN_BUTTON))
			return 1;		
		end
		if (keyid==_LEFT && get_joy_button(0,PSP_LEFT_BUTTON))
			return 1;
		end
		if (keyid==_RIGHT && get_joy_button(0,PSP_RIGHT_BUTTON))
			return 1;
		end

		if (keyid==_esc && get_joy_button(0,PSP_SELECT_BUTTON))
			return 1;
		end

		if (keyid==_enter && get_joy_button(0,PSP_START_BUTTON))
			return 1;
		end
	end
	
	return 0;
end

process chuleta(x,y)
private
begin
	size = 50;
	graph = load_png("recursos/chuleta.png");
	while (!keyjoy(_esc) )
		Frame; 
	end
	unload_map(0,graph);
end

process jugador(x,y)
public
	seleccion;
	ganadas;
private
	imagenes[5];
	id_text_g;
begin
	size = 50;
	imagenes[0]=load_png("recursos/p1_1p.png");
	imagenes[1]=load_png("recursos/p1_2a.png");
	imagenes[2]=load_png("recursos/p1_3t.png");
	imagenes[3]=load_png("recursos/p1_4l.png");
	imagenes[4]=load_png("recursos/p1_5s.png");
	id_text_g = write_var(0,10,200,0,ganadas);
	while (!keyjoy(_esc) )
		graph = imagenes[seleccion];
		if (comenzar ==1)
			if (keyjoy(_right))
				while (keyjoy(_right) ) frame;end;
				seleccion ++;
				seleccion%=5;
			end
			if (keyjoy(_left))
				while (keyjoy(_left) ) frame;end;
				seleccion --;
				if (seleccion < 0)
				   seleccion = 4;
				end
			end
		end
	        Frame;
	end
	for (x=0;x<5;x++)
		unload_map(0,imagenes[x]);
	end
	delete_text(id_text_g);
end

process ordenador(x,y)
public
	seleccion;
	ganadas;
private
	imagenes[5];
	comprobar = 50;
	i_comprobar;
	v_rand;
	id_text_g;
begin
	size = 50;
	imagenes[0]=load_png("recursos/p2_1p.png");
	imagenes[1]=load_png("recursos/p2_2a.png");
	imagenes[2]=load_png("recursos/p2_3t.png");
	imagenes[3]=load_png("recursos/p2_4l.png");
	imagenes[4]=load_png("recursos/p2_5s.png");
	id_text_g = write_var(0,310,200,0,ganadas);
	while (!keyjoy(_esc) )
		graph = imagenes[seleccion];
		if (comenzar ==1)
			if (i_comprobar>comprobar)
				i_comprobar = 0;
				v_rand = rand(1,3);
				if (v_rand==1)
					seleccion ++;
					seleccion%=5;
				end
				if (v_rand==2)
				seleccion --;
					if (seleccion < 0)
					   seleccion = 4;
					end
				end
			else
				i_comprobar++;
			end
		end
	        Frame;
	end
	for (x=0;x<5;x++)
		unload_map(0,imagenes[x]);
	end
	delete_text(id_text_g);
end

Begin
	rand_seed(time());
	set_mode(320,240,32);
	set_fps(25,0);
	chuleta(157,63);
	id_jugador=jugador(50,170);
	id_ordenador=ordenador(270,170);
    	id_texto = write(0,140,180,0,"Start");
    	while (!keyjoy(_esc))
		if (keyjoy(_f))
		    	full_screen = !full_screen;
		    	set_mode(640,480,16);
		end
		if (keyjoy(_enter) && comenzar ==0)
			while (keyjoy(_enter) ) frame;end;
			comenzar = 1;
			if (id_texto2!=0)		
				delete_text(id_texto2);
			end
			delete_text(id_texto);
			i_tiempo=tiempo;
			id_texto = write_var(0,140,180,0,i_tiempo);
			id_jugador.seleccion = 0;
			id_ordenador.seleccion = 0;
		end
		if (i_tiempo<0 && comenzar == 1)
			delete_text(id_texto);
			if (
				(id_jugador.seleccion == 0 && (id_ordenador.seleccion == 2 || id_ordenador.seleccion == 3)) ||
				(id_jugador.seleccion == 1 && (id_ordenador.seleccion == 0 || id_ordenador.seleccion == 4)) ||
				(id_jugador.seleccion == 2 && (id_ordenador.seleccion == 1 || id_ordenador.seleccion == 3)) ||
				(id_jugador.seleccion == 3 && (id_ordenador.seleccion == 1 || id_ordenador.seleccion == 4)) ||
				(id_jugador.seleccion == 4 && (id_ordenador.seleccion == 0 || id_ordenador.seleccion == 2)) 
			)
				id_texto2 = write(0,140,180,0,"winner");
				id_jugador.ganadas++;
			else
				if (id_jugador.seleccion == id_ordenador.seleccion)
					id_texto2 = write(0,140,180,0,"draw");
				else
					id_texto2 = write(0,140,180,0,"looser");
					id_ordenador.ganadas++;
				end
			end
		    	id_texto = write(0,140,200,0,"Start");
			comenzar = 0;
		end
		i_tiempo--;
	        frame;
	end
	let_me_alone();
end

