--- src/session-child.c.orig	2024-12-12 03:29:47 UTC
+++ src/session-child.c
@@ -13,7 +13,6 @@
 #include <grp.h>
 #include <glib.h>
 #include <security/pam_appl.h>
-#include <utmp.h>
 #include <utmpx.h>
 #include <sys/mman.h>
 #if HAVE_SETUSERCONTEXT
@@ -196,28 +195,6 @@ read_xauth (void)
     return x_authority_new (x_authority_family, x_authority_address, x_authority_address_length, x_authority_number, x_authority_name, x_authority_data, x_authority_data_length);
 }
 
-/* GNU provides this but we can't rely on that so let's make our own version */
-static void
-updwtmpx (const gchar *wtmp_file, struct utmpx *ut)
-{
-    struct utmp u;
-    memset (&u, 0, sizeof (u));
-    u.ut_type = ut->ut_type;
-    u.ut_pid = ut->ut_pid;
-    if (ut->ut_line)
-        strncpy (u.ut_line, ut->ut_line, sizeof (u.ut_line));
-    if (ut->ut_id)
-        strncpy (u.ut_id, ut->ut_id, sizeof (u.ut_id));
-    if (ut->ut_user)
-        strncpy (u.ut_user, ut->ut_user, sizeof (u.ut_user));
-    if (ut->ut_host)
-        strncpy (u.ut_host, ut->ut_host, sizeof (u.ut_host));
-    u.ut_tv.tv_sec = ut->ut_tv.tv_sec;
-    u.ut_tv.tv_usec = ut->ut_tv.tv_usec;
-
-    updwtmp (wtmp_file, &u);
-}
-
 #if HAVE_LIBAUDIT
 static void
 audit_event (int type, const gchar *username, uid_t uid, const gchar *remote_host_name, const gchar *tty, gboolean success)
@@ -367,8 +344,6 @@ session_child_run (int argc, char **argv)
             ut.ut_tv.tv_sec = tv.tv_sec;
             ut.ut_tv.tv_usec = tv.tv_usec;
 
-            updwtmpx ("/var/log/btmp", &ut);
-
 #if HAVE_LIBAUDIT
             audit_event (AUDIT_USER_LOGIN, username, -1, remote_host_name, tty, FALSE);
 #endif
@@ -397,7 +372,7 @@ session_child_run (int argc, char **argv)
         else
         {
             /* Set POSIX variables */
-            pam_putenv (pam_handle, "PATH=/usr/local/bin:/usr/bin:/bin");
+            pam_putenv (pam_handle, "PATH=/sbin:/bin:/usr/sbin:/usr/bin:%%PREFIX%%/sbin:%%PREFIX%%/bin");
             g_autofree gchar* user_env = g_strdup_printf ("USER=%s", username);
             pam_putenv (pam_handle, user_env);
             g_autofree gchar* logname_env = g_strdup_printf ("LOGNAME=%s", username);
@@ -759,7 +734,6 @@ session_child_run (int argc, char **argv)
             if (!pututxline (&ut))
                 g_printerr ("Failed to write utmpx: %s\n", strerror (errno));
             endutxent ();
-            updwtmpx ("/var/log/wtmp", &ut);
 
 #if HAVE_LIBAUDIT
             audit_event (AUDIT_USER_LOGIN, username, uid, remote_host_name, tty, TRUE);
@@ -800,7 +774,6 @@ session_child_run (int argc, char **argv)
             if (!pututxline (&ut))
                 g_printerr ("Failed to write utmpx: %s\n", strerror (errno));
             endutxent ();
-            updwtmpx ("/var/log/wtmp", &ut);
 
 #if HAVE_LIBAUDIT
             audit_event (AUDIT_USER_LOGOUT, username, uid, remote_host_name, tty, TRUE);
