#ifndef __MODULES_DEF_H
#define __MODULES_DEF_H

#include "bgddl.h"

#define MODULES_NUMBER 47

char * dliberror();
void * dlibopen(const char *soname);
void * _dlibaddr(void* library, const char *soname);

extern DLCONSTANT __bgdexport( libkey, constants_def )[];
extern char * __bgdexport( libkey, globals_def );
extern DLVARFIXUP __bgdexport( libkey, globals_fixup )[];
extern HOOK __bgdexport( libkey, handler_hooks )[];
extern void __bgdexport( libkey, module_initialize )();
extern void __bgdexport( libkey, module_finalize )();
extern char * __bgdexport( libkey, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_map, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_map, functions_exports )[];
extern char * __bgdexport( mod_map, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_time, functions_exports )[];
extern void __bgdexport( mod_time, module_initialize )();
extern void __bgdexport( mod_time, module_finalize )();

extern DLCONSTANT __bgdexport( mod_sys, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_sys, functions_exports )[];

extern DLVARFIXUP __bgdexport( mod_video, globals_fixup )[];
extern DLSYSFUNCS __bgdexport( mod_video, functions_exports )[];
extern char * __bgdexport( mod_video, modules_dependency )[];

extern char * __bgdexport( libmouse, globals_def );
extern DLVARFIXUP __bgdexport( libmouse, globals_fixup )[];
extern HOOK __bgdexport( libmouse, handler_hooks )[];
extern char * __bgdexport( libmouse, modules_dependency )[];
extern void __bgdexport( libmouse, module_initialize )();

extern DLVARFIXUP __bgdexport( mod_debug, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_debug, globals_fixup )[];
//extern HOOK __bgdexport( mod_debug, handler_hooks )[] ;
extern void __bgdexport( mod_debug, process_exec_hook )(INSTANCE * r);
extern void __bgdexport( mod_debug, module_initialize )();
extern void __bgdexport( mod_debug, module_finalize )();
extern char * __bgdexport( mod_debug, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_m7, constants_def )[];
extern char * __bgdexport( mod_m7, globals_def );
extern char * __bgdexport( mod_m7, locals_def );
extern DLVARFIXUP __bgdexport( mod_m7, globals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_m7, locals_fixup )[];
extern void __bgdexport( mod_m7, module_initialize )();
extern DLSYSFUNCS __bgdexport( mod_m7, functions_exports )[];
extern char * __bgdexport( mod_m7, modules_dependency )[];

extern char * __bgdexport( mod_mouse, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_flic, functions_exports )[];

extern DLCONSTANT __bgdexport( libblit, constants_def )[];

extern DLSYSFUNCS __bgdexport( mod_joy, functions_exports )[];
extern char * __bgdexport( mod_joy, modules_dependency )[];

extern DLCONSTANT __bgdexport( libvideo, constants_def )[];
extern char * __bgdexport( libvideo, globals_def );
extern DLVARFIXUP __bgdexport( libvideo, globals_fixup )[];
extern void __bgdexport( libvideo, module_initialize )();
extern void __bgdexport( libvideo, module_finalize )();
extern char * __bgdexport( libvideo, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_proc, constants_def )[];
extern char * __bgdexport( mod_proc, locals_def );
extern DLVARFIXUP __bgdexport( mod_proc, locals_fixup )[];
extern void __bgdexport( mod_proc, process_exec_hook )(INSTANCE * r);
extern DLSYSFUNCS __bgdexport( mod_proc, functions_exports )[];

extern DLVARFIXUP __bgdexport( mod_screen, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_screen, globals_fixup )[];
extern DLSYSFUNCS __bgdexport( mod_screen, functions_exports )[];
extern char * __bgdexport( mod_screen, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_mathi, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_mathi, functions_exports )[];

extern char * __bgdexport( libtext, globals_def );
extern DLVARFIXUP __bgdexport( libtext, globals_fixup )[];
extern char * __bgdexport( libtext, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_file, constants_def)[];
extern DLSYSFUNCS __bgdexport( mod_file, functions_exports)[];

extern DLCONSTANT __bgdexport( mod_crypt, constants_def)[];
extern DLSYSFUNCS __bgdexport( mod_crypt, functions_exports)[];

extern DLCONSTANT __bgdexport( mod_text, constants_def)[];
extern DLSYSFUNCS __bgdexport( mod_text, functions_exports)[];
extern char * __bgdexport( mod_text, modules_dependency)[];

extern DLCONSTANT __bgdexport( mod_ffi, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_ffi, functions_exports )[];

extern DLSYSFUNCS __bgdexport( mod_draw, functions_exports )[];
extern char * __bgdexport( mod_draw, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_sound, constants_def )[];
extern char * __bgdexport( mod_sound, globals_def );
extern DLVARFIXUP __bgdexport( mod_sound, globals_fixup )[];
extern DLSYSFUNCS __bgdexport( mod_sound, functions_exports )[];
extern void __bgdexport( mod_sound, module_initialize )();
extern void __bgdexport( mod_sound, module_finalize )();

extern void __bgdexport( libsdlhandler, module_initialize )();
extern void __bgdexport( libsdlhandler, module_finalize )();
extern HOOK __bgdexport( libsdlhandler, handler_hooks )[];

extern char * __bgdexport( mod_regex, globals_def );

extern DLVARFIXUP __bgdexport( mod_regex, globals_fixup)[];
extern DLSYSFUNCS __bgdexport( mod_regex, functions_exports)[];

extern DLCONSTANT __bgdexport( mod_path, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_path, functions_exports )[];

extern char * __bgdexport( mod_path, modules_dependency )[];

extern void __bgdexport( libfont, module_initialize )();
extern char * __bgdexport( libfont, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_effects, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_effects, functions_exports )[];
extern char * __bgdexport( mod_effects, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_say, functions_exports )[];

extern DLCONSTANT __bgdexport( libjoy, constants_def )[];
extern void __bgdexport( libjoy, module_initialize )();
extern void __bgdexport( libjoy, module_finalize )();
extern char * __bgdexport( libjoy, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_sort, functions_exports )[];

extern DLCONSTANT __bgdexport( libscroll, constants_def )[];
extern char * __bgdexport( libscroll, locals_def );
extern char * __bgdexport( libscroll, globals_def );
extern DLVARFIXUP __bgdexport( libscroll, locals_fixup )[];
extern DLVARFIXUP __bgdexport( libscroll, globals_fixup )[];
extern char * __bgdexport( libscroll, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_string, functions_exports )[];
extern char * __bgdexport( mod_timers, globals_def );
extern DLVARFIXUP __bgdexport( mod_timers, globals_fixup )[];
extern HOOK __bgdexport( mod_timers, handler_hooks )[];

extern DLSYSFUNCS __bgdexport( mod_blendop, functions_exports)[];
extern char * __bgdexport( mod_blendop, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_rand, functions_exports )[];

extern DLSYSFUNCS __bgdexport( mod_scroll, functions_exports )[];
extern char * __bgdexport( mod_scroll, modules_dependency )[];

extern void __bgdexport( librender, instance_create_hook )(INSTANCE * r);
extern void __bgdexport( librender, instance_destroy_hook )(INSTANCE * r);
extern DLCONSTANT __bgdexport( librender, constants_def )[];
extern char * __bgdexport( librender, globals_def );
extern char * __bgdexport( librender, locals_def );
extern DLVARFIXUP __bgdexport( librender, globals_fixup )[];
extern DLVARFIXUP __bgdexport( librender, locals_fixup )[];
extern HOOK __bgdexport( librender, handler_hooks )[];
extern char * __bgdexport( librender, modules_dependency )[];
extern void __bgdexport( librender, module_initialize )();
extern void __bgdexport( librender, module_finalize )();

extern char * __bgdexport( mod_grproc, locals_def );
extern DLVARFIXUP __bgdexport( mod_grproc, locals_fixup )[];
extern DLVARFIXUP __bgdexport( mod_grproc, globals_fixup )[];
extern void __bgdexport( mod_grproc, module_initialize )();
extern void __bgdexport( mod_grproc, process_exec_hook )(INSTANCE * r);
extern DLSYSFUNCS __bgdexport( mod_grproc, functions_exports )[];
extern char * __bgdexport( mod_grproc, modules_dependency )[];

extern DLCONSTANT __bgdexport( mod_cd, constants_def )[];
extern char * __bgdexport( mod_cd, globals_def );
extern DLVARFIXUP __bgdexport( mod_cd, globals_fixup )[];
extern DLSYSFUNCS __bgdexport( mod_cd, functions_exports )[];
extern void __bgdexport( mod_cd, module_initialize )();
extern void __bgdexport( mod_cd, module_finalize )();

extern DLSYSFUNCS __bgdexport( mod_key, functions_exports )[];
extern char * __bgdexport( mod_key, modules_dependency )[];

extern char * __bgdexport( mod_dir, globals_def );
extern DLVARFIXUP __bgdexport( mod_dir, globals_fixup)[];
extern DLSYSFUNCS __bgdexport( mod_dir, functions_exports)[];

extern void __bgdexport( libgrbase, module_initialize )();
extern char * __bgdexport( libgrbase, globals_def );
extern DLVARFIXUP __bgdexport( libgrbase, globals_fixup )[];

extern DLSYSFUNCS __bgdexport( mod_mem, functions_exports )[];

extern DLCONSTANT __bgdexport( mod_math, constants_def )[];
extern DLSYSFUNCS __bgdexport( mod_math, functions_exports )[];

extern char * __bgdexport( libwm, globals_def );
extern DLVARFIXUP __bgdexport( libwm, globals_fixup )[];
extern HOOK __bgdexport( libwm, handler_hooks )[];
extern char * __bgdexport( libwm, modules_dependency )[];

extern DLSYSFUNCS __bgdexport( mod_wm, functions_exports )[];
extern char * __bgdexport( mod_wm, modules_dependency )[];

typedef struct module_def_ {
	char name[300];
	DLCONSTANT * constants_def;
	char * globals_def;
	char * locals_def;
	char ** types_def;
	char ** modules_dependency;
	DLVARFIXUP * globals_fixup;
	DLVARFIXUP * locals_fixup;
	DLSYSFUNCS * functions_exports;
	FN_HOOK module_initialize;
	FN_HOOK module_finalize;
	INSTANCE_HOOK instance_create_hook;
	INSTANCE_HOOK instance_destroy_hook;
	INSTANCE_HOOK instance_pre_execute_hook;
	INSTANCE_HOOK instance_pos_execute_hook;
	INSTANCE_HOOK process_exec_hook;
	HOOK * handler_hooks;
} module_def;

#endif
