#include "e_mod_main.h"

/* gadcon requirements */
static E_Gadcon_Client *_gc_init(E_Gadcon * gc, const char *name, const char *id, const char *style);
static void             _gc_shutdown(E_Gadcon_Client * gcc);
static void             _gc_orient(E_Gadcon_Client * gcc, E_Gadcon_Orient orient);
static const char      *_gc_label(const E_Gadcon_Client_Class *client_class);
static                  Evas_Object *_gc_icon(const E_Gadcon_Client_Class *client_class, Evas * evas);
static const char      *_gc_id_new(const E_Gadcon_Client_Class *client_class);

/* and actually define the gadcon class that this module provides (just 1) */
static const E_Gadcon_Client_Class _gadcon_class = {
   GADCON_CLIENT_CLASS_VERSION,
   "comptonmod",
   {
      _gc_init, _gc_shutdown, _gc_orient, _gc_label, _gc_icon, _gc_id_new, NULL,
      e_gadcon_site_is_not_toolbar
   },
   E_GADCON_CLIENT_STYLE_PLAIN
};

/* actual module specifics */
typedef struct _Instance Instance;
struct _Instance
{
   E_Gadcon_Client *gcc;
   Evas_Object *o_button;
};

static void _button_cb_mouse_down(void *data, Evas * e, Evas_Object * obj, void *event_info);

static E_Module *comp_module = NULL;

static E_Gadcon_Client *
_gc_init(E_Gadcon *gc, const char *name, const char *id, const char *style)
{
   Evas_Object *o;
   E_Gadcon_Client *gcc;
   Instance *inst;
   char buf[PATH_MAX];

   inst = E_NEW(Instance, 1);

   snprintf(buf, sizeof(buf), "%s/e-module-comptonmod.edj", e_module_dir_get(comp_module));
   
   o = edje_object_add(gc->evas);
   if (!e_theme_edje_object_set(o, "base/theme/modules/comptonmod", "modules/comptonmod/main"))
     edje_object_file_set(o, buf, "modules/comptonmod/main");

   evas_object_show(o);
   edje_object_signal_emit(o, "passive", "");

   gcc = e_gadcon_client_new(gc, name, id, style, o);
   gcc->data = inst;

   inst->gcc = gcc;
   inst->o_button = o;

   e_gadcon_client_util_menu_attach(gcc);

   return gcc;
}

static void
_gc_shutdown(E_Gadcon_Client *gcc)
{
   Instance *inst;

   inst = gcc->data;

   evas_object_del(inst->o_button);
   E_FREE(inst);
}

static void
_gc_orient(E_Gadcon_Client *gcc, E_Gadcon_Orient orient)
{
   e_gadcon_client_aspect_set (gcc, 16, 16);
   e_gadcon_client_min_size_set (gcc, 16, 16);
}

static const char *
_gc_label (const E_Gadcon_Client_Class *client_class)
{
   return "ComptonMod";
}

static Evas_Object *
_gc_icon(const E_Gadcon_Client_Class *client_class, Evas * evas)
{
   Evas_Object *o;
   char buf[PATH_MAX];

   o = edje_object_add(evas);
   snprintf (buf, sizeof(buf), "%s/e-module-comptonmod.edj", e_module_dir_get(comp_module));
   edje_object_file_set(o, buf, "icon");
   return o;
}

static const char *
_gc_id_new (const E_Gadcon_Client_Class *client_class)
{
   return _gadcon_class.name;
}


/* module setup */
EAPI E_Module_Api e_modapi = {
  E_MODULE_API_VERSION,
  "ComptonMod"
};

EAPI void *
e_modapi_init (E_Module * m)
{
   Ecore_Exe *exe;
   comp_module = m;
   //~ e_gadcon_provider_register(&_gadcon_class);
      
   char cmd[PATH_MAX+20];
   char buf[PATH_MAX];
   snprintf(buf, sizeof(buf), "%s/compton.conf",
                 efreet_config_home_get());
   if (ecore_file_can_read(buf))
      snprintf(cmd, sizeof(cmd), "picom --config %s -b &", buf);
   else
      if (ecore_file_can_read("/etc/compton.conf"))
         snprintf(cmd, sizeof(cmd), "picom --config %s -b &", "/etc/compton.conf");
      else
         snprintf(cmd, sizeof(cmd), "picom --config %s -b &", "picom --config /dev/null");
   exe = e_util_exe_safe_run(cmd, NULL);
   return comp_module;
}

EAPI int
e_modapi_shutdown (E_Module * m)
{
   Ecore_Exe *exe;
   comp_module = NULL;
   //~ e_gadcon_provider_unregister(&_gadcon_class);

   char cmd[200];
   snprintf(cmd, sizeof(cmd), "%s", "killall picom");
   exe = e_util_exe_safe_run(cmd, NULL);
   return 1;
}

EAPI int
e_modapi_save(E_Module * m)
{
   return 1;
}
