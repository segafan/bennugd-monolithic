#include <string.h>
#include <stdlib.h>
#include "sim_loadlib.h"

module_def modules[MODULES_NUMBER] = { };
char str_error[1024] = { };
int modules_count;

void initialize_modules_table() {
	int i = 0;
	memset(&modules[0], 0, sizeof(module_def) * MODULES_NUMBER);

	// mod_say
	strcpy(modules[i].name, "mod_say");
	modules[i].functions_exports = __bgdexport(mod_say,functions_exports);
	i++;

#if !defined(__LITE__) || __LITE__>1

	// libsdlhandler
	strcpy(modules[i].name, "libsdlhandler");
	modules[i].module_initialize = __bgdexport(libsdlhandler,module_initialize);
	modules[i].module_finalize = __bgdexport(libsdlhandler,module_finalize);
	modules[i].handler_hooks = __bgdexport(libsdlhandler,handler_hooks);
	i++;

	// libjoy
	strcpy(modules[i].name, "libjoy");
	modules[i].constants_def = __bgdexport(libjoy,constants_def);
	modules[i].module_initialize = __bgdexport(libjoy,module_initialize);
	modules[i].module_finalize = __bgdexport(libjoy,module_finalize);
	modules[i].modules_dependency = __bgdexport(libjoy,modules_dependency);
	i++;

	// mod_joy
	strcpy(modules[i].name, "mod_joy");
	modules[i].functions_exports = __bgdexport(mod_joy,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_joy,modules_dependency);
	i++;

#endif
#if !defined(__LITE__) || __LITE__>2

	// libgrbase
	strcpy(modules[i].name, "libgrbase");
	modules[i].module_initialize = __bgdexport(libgrbase,module_initialize);
	modules[i].globals_def = __bgdexport(libgrbase,globals_def);
	modules[i].globals_fixup = __bgdexport(libgrbase,globals_fixup);
	i++;

	// libblit
	strcpy(modules[i].name, "libblit");
	modules[i].constants_def = __bgdexport(libblit,constants_def);
	i++;

	// libfont
	strcpy(modules[i].name, "libfont");
	modules[i].module_initialize = __bgdexport(libfont,module_initialize);
	modules[i].modules_dependency = __bgdexport(libfont,modules_dependency);
	i++;

	// libtext
	strcpy(modules[i].name, "libtext");
	modules[i].globals_def = __bgdexport(libtext,globals_def);
	modules[i].globals_fixup = __bgdexport(libtext,globals_fixup);
	modules[i].modules_dependency = __bgdexport(libtext,modules_dependency);
	i++;

	// libvideo
	strcpy(modules[i].name, "libvideo");
	modules[i].constants_def = __bgdexport(libvideo,constants_def);
	modules[i].globals_def = __bgdexport(libvideo,globals_def);
	modules[i].globals_fixup = __bgdexport(libvideo,globals_fixup);
	modules[i].module_initialize = __bgdexport(libvideo,module_initialize);
	modules[i].module_finalize = __bgdexport(libvideo,module_finalize);
	modules[i].modules_dependency = __bgdexport(libvideo,modules_dependency);
	i++;

	// librender
	strcpy(modules[i].name, "librender");
	modules[i].instance_create_hook
			= __bgdexport(librender,instance_create_hook);
	modules[i].instance_destroy_hook
			= __bgdexport(librender,instance_destroy_hook);
	modules[i].constants_def = __bgdexport(librender,constants_def);
	modules[i].globals_def = __bgdexport(librender,globals_def);
	modules[i].locals_def = __bgdexport(librender,locals_def);
	modules[i].globals_fixup = __bgdexport(librender,globals_fixup);
	modules[i].locals_fixup = __bgdexport(librender,locals_fixup);
	modules[i].handler_hooks = __bgdexport(librender,handler_hooks);
	modules[i].modules_dependency = __bgdexport(librender,modules_dependency);
	modules[i].module_initialize = __bgdexport(librender,module_initialize);
	modules[i].module_finalize = __bgdexport(librender,module_finalize);
	i++;

	// mod_text
	strcpy(modules[i].name, "mod_text");
	modules[i].constants_def = __bgdexport(mod_text,constants_def);
	modules[i].functions_exports = __bgdexport(mod_text,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_text,modules_dependency);
	i++;

#endif
#if !defined(__LITE__) || __LITE__>3

	// mod_video
	strcpy(modules[i].name, "mod_video");
	modules[i].globals_fixup = __bgdexport(mod_video,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_video,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_video,modules_dependency);
	i++;

	// mod_proc
	strcpy(modules[i].name, "mod_proc");
	modules[i].constants_def = __bgdexport(mod_proc,constants_def);
	modules[i].locals_def = __bgdexport(mod_proc,locals_def);
	modules[i].locals_fixup = __bgdexport(mod_proc,locals_fixup);
	modules[i].process_exec_hook = __bgdexport(mod_proc,process_exec_hook);
	modules[i].functions_exports = __bgdexport(mod_proc,functions_exports);
	i++;

	// libkey
	strcpy(modules[i].name, "libkey");
	modules[i].constants_def = __bgdexport(libkey,constants_def);
	modules[i].globals_def = __bgdexport(libkey,globals_def);
	modules[i].globals_fixup = __bgdexport(libkey,globals_fixup);
	modules[i].handler_hooks = __bgdexport(libkey,handler_hooks);
	modules[i].module_initialize = __bgdexport(libkey,module_initialize);
	modules[i].module_finalize = __bgdexport(libkey,module_finalize);
	modules[i].modules_dependency = __bgdexport(libkey,modules_dependency);
	i++;

	// mod_key
	strcpy(modules[i].name, "mod_key");
	modules[i].functions_exports = __bgdexport(mod_key,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_key,modules_dependency);
	i++;

#endif
#if !defined(__LITE__) || __LITE__>4

	// libmouse
	strcpy(modules[i].name, "libmouse");
	modules[i].globals_def = __bgdexport(libmouse,globals_def);
	modules[i].globals_fixup = __bgdexport(libmouse,globals_fixup);
	modules[i].handler_hooks = __bgdexport(libmouse,handler_hooks);
	modules[i].modules_dependency = __bgdexport(libmouse,modules_dependency);
	modules[i].module_initialize = __bgdexport(libmouse,module_initialize);
	i++;

	// mod_mouse
	strcpy(modules[i].name, "mod_mouse");
	modules[i].modules_dependency = __bgdexport(mod_mouse,modules_dependency);
	i++;

	// mod_map
	strcpy(modules[i].name, "mod_map");
	modules[i].constants_def = __bgdexport(mod_map,constants_def);
	modules[i].functions_exports = __bgdexport(mod_map,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_map,modules_dependency);
	i++;

	// mod_time
	strcpy(modules[i].name, "mod_time");
	modules[i].functions_exports = __bgdexport(mod_time,functions_exports);
	modules[i].module_initialize = __bgdexport(mod_time,module_initialize);
	modules[i].module_finalize = __bgdexport(mod_time,module_finalize);
	i++;

	// libdraw
	strcpy(modules[i].name, "libdraw");
	i++;

	// mod_draw
	strcpy(modules[i].name, "mod_draw");
	modules[i].functions_exports = __bgdexport(mod_draw,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_draw,modules_dependency);
	i++;

	// mod_sound
	strcpy(modules[i].name, "mod_sound");
	modules[i].constants_def = __bgdexport(mod_sound,constants_def);
	modules[i].globals_def = __bgdexport(mod_sound,globals_def);
	modules[i].globals_fixup = __bgdexport(mod_sound,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_sound,functions_exports);
	modules[i].module_initialize = __bgdexport(mod_sound,module_initialize);
	modules[i].module_finalize = __bgdexport(mod_sound,module_finalize);
	i++;

	// mod_grproc
	strcpy(modules[i].name, "mod_grproc");
	modules[i].locals_def = __bgdexport(mod_grproc,locals_def);
	modules[i].locals_fixup = __bgdexport(mod_grproc,locals_fixup);
	modules[i].globals_fixup = __bgdexport(mod_grproc,globals_fixup);
	modules[i].module_initialize = __bgdexport(mod_grproc,module_initialize);
	modules[i].process_exec_hook = __bgdexport(mod_grproc,process_exec_hook);
	modules[i].functions_exports = __bgdexport(mod_grproc,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_grproc,modules_dependency);
	i++;

#endif
#if !defined(__LITE__) || __LITE__>5

	// libscroll
	strcpy(modules[i].name, "libscroll");
	modules[i].constants_def = __bgdexport(libscroll,constants_def);
	modules[i].locals_def = __bgdexport(libscroll,locals_def);
	modules[i].globals_def = __bgdexport(libscroll,globals_def);
	modules[i].locals_fixup = __bgdexport(libscroll,locals_fixup);
	modules[i].globals_fixup = __bgdexport(libscroll,globals_fixup);
	modules[i].modules_dependency = __bgdexport(libscroll,modules_dependency);
	i++;

	// mod_scroll
	strcpy(modules[i].name, "mod_scroll");
	modules[i].functions_exports = __bgdexport(mod_scroll,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_scroll,modules_dependency);
	i++;

	// mod_sort
	strcpy(modules[i].name, "mod_sort");
	modules[i].functions_exports = __bgdexport(mod_sort,functions_exports);
	i++;

	// mod_sys
	strcpy(modules[i].name, "mod_sys");
	modules[i].constants_def = __bgdexport(mod_sys,constants_def);
	modules[i].functions_exports = __bgdexport(mod_sys,functions_exports);
	i++;

	// mod_debug
	strcpy(modules[i].name, "mod_debug");
	modules[i].locals_fixup = __bgdexport(mod_debug,locals_fixup);
	modules[i].globals_fixup = __bgdexport(mod_debug,globals_fixup);
	//modules[i].handler_hooks = __bgdexport(mod_debug,handler_hooks);
	modules[i].process_exec_hook = __bgdexport(mod_debug,process_exec_hook);
	modules[i].module_initialize = __bgdexport(mod_debug,module_initialize);
	modules[i].module_finalize = __bgdexport(mod_debug,module_finalize);
	modules[i].modules_dependency = __bgdexport(mod_debug,modules_dependency);
	i++;

	// mod_m7
	strcpy(modules[i].name, "mod_m7");
	modules[i].constants_def = __bgdexport(mod_m7,constants_def);
	modules[i].globals_def = __bgdexport(mod_m7,globals_def);
	modules[i].locals_def = __bgdexport(mod_m7,locals_def);
	modules[i].globals_fixup = __bgdexport(mod_m7,globals_fixup);
	modules[i].locals_fixup = __bgdexport(mod_m7,locals_fixup);
	modules[i].module_initialize = __bgdexport(mod_m7,module_initialize);
	modules[i].functions_exports = __bgdexport(mod_m7,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_m7,modules_dependency);
	i++;

	// mod_flic
	strcpy(modules[i].name, "mod_flic");
	modules[i].functions_exports = __bgdexport(mod_flic,functions_exports);
	i++;

	// mod_screen
	strcpy(modules[i].name, "mod_screen");
	modules[i].locals_fixup = __bgdexport(mod_screen,locals_fixup);
	modules[i].globals_fixup = __bgdexport(mod_screen,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_screen,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_screen,modules_dependency);
	i++;

	// mod_mathi
	strcpy(modules[i].name, "mod_mathi");
	modules[i].constants_def = __bgdexport(mod_mathi,constants_def);
	modules[i].functions_exports = __bgdexport(mod_mathi,functions_exports);
	i++;

	// mod_file
	strcpy(modules[i].name, "mod_file");
	modules[i].constants_def = __bgdexport(mod_file,constants_def);
	modules[i].functions_exports = __bgdexport(mod_file,functions_exports);
	i++;

	// mod_crypt
	strcpy(modules[i].name, "mod_crypt");
	modules[i].constants_def = __bgdexport(mod_crypt,constants_def);
	modules[i].functions_exports = __bgdexport(mod_crypt,functions_exports);
	i++;

	// mod_regex
	strcpy(modules[i].name, "mod_regex");
	modules[i].globals_def = __bgdexport(mod_regex,globals_def);
	modules[i].globals_fixup = __bgdexport(mod_regex,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_regex,functions_exports);
	i++;

	// mod_path
	strcpy(modules[i].name, "mod_path");
	modules[i].constants_def = __bgdexport(mod_path,constants_def);
	modules[i].functions_exports = __bgdexport(mod_path,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_path,modules_dependency);
	i++;

	// mod_effects
	strcpy(modules[i].name, "mod_effects");
	modules[i].constants_def = __bgdexport(mod_effects,constants_def);
	modules[i].functions_exports = __bgdexport(mod_effects,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_effects,modules_dependency);
	i++;

	// mod_string
	strcpy(modules[i].name, "mod_string");
	modules[i].functions_exports = __bgdexport(mod_string,functions_exports);
	i++;

	// mod_timers
	strcpy(modules[i].name, "mod_timers");
	modules[i].globals_def = __bgdexport(mod_timers,globals_def);
	modules[i].globals_fixup = __bgdexport(mod_timers,globals_fixup);
	modules[i].handler_hooks = __bgdexport(mod_timers,handler_hooks);
	i++;

	// mod_blendop
	strcpy(modules[i].name, "mod_blendop");
	modules[i].functions_exports = __bgdexport(mod_blendop,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_blendop,modules_dependency);
	i++;

	// mod_rand
	strcpy(modules[i].name, "mod_rand");
	modules[i].functions_exports = __bgdexport(mod_rand,functions_exports);
	i++;

	// mod_cd
	strcpy(modules[i].name, "mod_cd");
	modules[i].constants_def = __bgdexport(mod_cd,constants_def);
	modules[i].globals_def = __bgdexport(mod_cd,globals_def);
	modules[i].globals_fixup = __bgdexport(mod_cd,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_cd,functions_exports);
	modules[i].module_initialize = __bgdexport(mod_cd,module_initialize);
	modules[i].module_finalize = __bgdexport(mod_cd,module_finalize);
	i++;

	// mod_dir
	strcpy(modules[i].name, "mod_dir");
	modules[i].globals_def = __bgdexport(mod_dir,globals_def);
	modules[i].globals_fixup = __bgdexport(mod_dir,globals_fixup);
	modules[i].functions_exports = __bgdexport(mod_dir,functions_exports);
	i++;

	// mod_mem
	strcpy(modules[i].name, "mod_mem");
	modules[i].functions_exports = __bgdexport(mod_mem,functions_exports);
	i++;

	// mod_math
	strcpy(modules[i].name, "mod_math");
	modules[i].constants_def = __bgdexport(mod_math,constants_def);
	modules[i].functions_exports = __bgdexport(mod_math,functions_exports);
	i++;

	// libwm
	strcpy(modules[i].name, "libwm");
	modules[i].globals_def = __bgdexport(libwm,globals_def);
	modules[i].globals_fixup = __bgdexport(libwm,globals_fixup);
	modules[i].handler_hooks = __bgdexport(libwm,handler_hooks);
	modules[i].modules_dependency = __bgdexport(libwm,modules_dependency);
	i++;

	// mod_wm
	strcpy(modules[i].name, "mod_wm");
	modules[i].functions_exports = __bgdexport(mod_wm,functions_exports);
	modules[i].modules_dependency = __bgdexport(mod_wm,modules_dependency);
	i++;
#endif
	modules_count = i;

}

char * dliberror() {
	return (char*) str_error;
}

void * dlibopen(const char *soname) {
	static int first_time = 1;
	int i;
	char no_ext[255];
	void * ret =  0;
	strcpy(no_ext, soname);
	if (first_time) {
		initialize_modules_table();
		first_time = 0;
	}
#ifdef WIN32
	no_ext[strlen(soname)-4]=0;
#else
	no_ext[strlen(soname) - 3] = 0;
#endif
	for (i = 0; i < modules_count; i++) {
		if (strcmp(no_ext, modules[i].name) == 0) {
			ret = &modules[i];
			return ret;
		}
	}
	strcpy(str_error, "Unsupported module: ");
	strcat(str_error, soname);
	return ret;
}

void * _dlibaddr(void* library, const char *soname) {
	module_def * module = 0;
	module = library;
	if (module == 0)
		return NULL;
	if (strcmp(soname, "constants_def") == 0)
		return module->constants_def;
	if (strcmp(soname, "globals_def") == 0)
		return &module->globals_def;
	if (strcmp(soname, "locals_def") == 0)
		return &module->locals_def;
	if (strcmp(soname, "types_def") == 0)
		return module->types_def;
	if (strcmp(soname, "modules_dependency") == 0)
		return module->modules_dependency;
	if (strcmp(soname, "globals_fixup") == 0)
		return module->globals_fixup;
	if (strcmp(soname, "locals_fixup") == 0)
		return module->locals_fixup;
	if (strcmp(soname, "functions_exports") == 0)
		return module->functions_exports;
	if (strcmp(soname, "module_initialize") == 0)
		return module->module_initialize;
	if (strcmp(soname, "module_finalize") == 0)
		return module->module_finalize;
	if (strcmp(soname, "instance_create_hook") == 0)
		return module->instance_create_hook;
	if (strcmp(soname, "instance_destroy_hook") == 0)
		return module->instance_destroy_hook;
	if (strcmp(soname, "instance_pre_execute_hook") == 0)
		return module->instance_pre_execute_hook;
	if (strcmp(soname, "instance_pos_execute_hook") == 0)
		return module->instance_pos_execute_hook;
	if (strcmp(soname, "process_exnoextec_hook") == 0)
		return module->process_exec_hook;
	if (strcmp(soname, "handler_hooks") == 0)
		return module->handler_hooks;

	return 0;
}

