#Titulo a mostrar en pantalla de seleccion de juegos, nota hay que poner comillas dobles y comillas simples
PSP_EBOOT_TITLE="TETRIS"

#Icono a mostrar en pantalla de seleccion de juegos, resolución: 144x80
PSP_EBOOT_ICON=logo.png

#Fondo a mostrar en pantalla de seleccion de juegos, resolución: 480x272
PSP_EBOOT_PIC1=NULL

#Sonido a escuchar en pantalla de seleccion de juegos, formato: at3
PSP_EBOOT_SND0=NULL

../../psp-strip ../../bgdi.elf -o ../../bgdi_strip.elf
PATH=$PATH:.
../../mksfo $PSP_EBOOT_TITLE PARAM.SFO
../../pack-pbp ../EBOOT.PBP PARAM.SFO ${PSP_EBOOT_ICON}  \
                NULL NULL ${PSP_EBOOT_PIC1}  \
                ${PSP_EBOOT_SND0}  ../../bgdi_strip.elf NULL
