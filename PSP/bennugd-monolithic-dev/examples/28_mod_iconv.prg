import "mod_say"
import "mod_mouse"
import "mod_key"
import "mod_video"
import "mod_text"
import "mod_iconv"

Process Main()
Private
  string cadena = "Hola, güenas";
  string convertida;
  
Begin
  set_mode(640, 480);
  say(cadena);
  convertida = iconv("CP850", "ISO-8859", cadena);
  say(convertida);
  write(0, 320, 220, 4, cadena);
  write(0, 320, 240, 4, convertida);
  while(! mouse.left)
    FRAME;
  End;
End;
