import "mod_say";
import "mod_key";
import "mod_video";
import "mod_text";
import "mod_iconv";

Process Main()
Private
  string cadena = "Hola, güenas";
  string convertida;
  
Begin
  set_mode(640, 480);
  say(cadena);
  convertida = iconv("ISO-8859-1", "UTF8", cadena);
  say(convertida);
  write(0, 320, 220, 4, cadena);
  write(0, 320, 240, 4, convertida);
  while(!key(_esc))
    FRAME;
  End;
End;
