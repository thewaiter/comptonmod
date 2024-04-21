#include "e_mod_main.h"

/* actual module specifics */
static E_Module *comp_module = NULL;


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
      
   char cmd[PATH_MAX+20];
   char buf[PATH_MAX];
   snprintf(buf, sizeof(buf), "%s/picom.conf",
                 efreet_config_home_get());
   if (ecore_file_can_read(buf))
      snprintf(cmd, sizeof(cmd), "picom --config %s -b &", buf);
   else
      if (ecore_file_can_read("/etc/picom.conf"))
         snprintf(cmd, sizeof(cmd), "picom --config %s -b &", "/etc/picom.conf");
      else
         snprintf(cmd, sizeof(cmd), "picom --config %s -b &", "picom --config /dev/null");
   exe = e_util_exe_safe_run(cmd, NULL);
   if (exe) ecore_exe_free(exe);
   return comp_module;
}

EAPI int
e_modapi_shutdown (E_Module * m __UNUSED__)
{
   Ecore_Exe *exe;
   comp_module = NULL;

   char cmd[200];
   snprintf(cmd, sizeof(cmd), "%s", "killall picom");
   exe = e_util_exe_safe_run(cmd, NULL);
   if (exe) ecore_exe_free(exe);
   return 1;
}

EAPI int
e_modapi_save(E_Module * m  __UNUSED__)
{
   return 1;
}
