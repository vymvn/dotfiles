#ifndef _UTILS_H_
#define _UTILS_H_

#include <dbus-1.0/dbus/dbus.h>

/**
 * Get the string pointed to by a DBusMessageIter
 *
 * @param DBusMessageIter* The iterator pointing to the string
 *
 * @returns wchar_t* The string pointed to by the iter if it is pointing at a
 *                string. Otherwise, it returns a NULL pointer. This pointer
 *                must be freed by the caller.
 */
wchar_t *iter_get_string(DBusMessageIter *iter);

/**
 * Prints the string pointed to by a DBusMessageIter
 *
 * @param DBusMessage* iter The iterator pointing to a string
 */
void print_string_iter(DBusMessageIter *iter);

/**
 * Initialize subiter inside the container pointed to be iter if it is of the
 * specified type.
 *
 * @param DBusMessageIter* iter The iterator pointing at a container
 * @param DBusMessageIter* subiter The iterator to initialize inside the
 *                                 container.
 * @param int type The exptected type of the container
 *
 * @returns dbus_bool_t Returns TRUE if the specified type matches the type of
 *                      the container and the subiter is successfully
 *                      initialized, otherwise returns FALSE.
 */
dbus_bool_t recurse_iter_of_type(DBusMessageIter *iter,
                                 DBusMessageIter *subiter, const int type);

/**
 * Initialize subiter inside the container pointed to be iter if it is of the
 * specified signature.
 *
 * @param DBusMessageIter* iter The iterator pointing at a container
 * @param DBusMessageIter* subiter The iterator to initialize inside the
 *                                 container.
 * @param const wchar_t* signature The exptected signature of the container
 *
 * @returns dbus_bool_t Returns TRUE if the specified signature matches the
 *                      signature of the container and the subiter is
 *                      successfully initialized, otherwise returns FALSE.
 */
dbus_bool_t recurse_iter_of_signature(DBusMessageIter *iter,
                                      DBusMessageIter *subiter,
                                      const wchar_t *signature);

/**
 * Initialize entry_iter at an array dict element matching the specified key.
 *
 * @param DBusMessageIter* array_iter The iterator pointing at an array of
 *                                    dictionary entries.
 * @param DBusMessageIter* entry_iter The iterator to initialize at the value of
 *                                    the dictionary entry.
 * @param const wchar_t* key The key of the dictionary entry.
 *
 * @returns dbus_bool_t Returns TRUE if a dictionary entry with the specified
 *                      key is found and the entry_iter is successfully
 *                      initialized, otherwise returns FALSE.
 */
dbus_bool_t iter_go_to_key(DBusMessageIter *array_iter,
                           DBusMessageIter *entry_iter, const wchar_t *key);

/**
 * Try to recurse the iter into a container that it is pointing at with the
 * specified type. This points the iter to the first element of the container,
 * rather than initializing a new subiter.
 *
 * @param DBusMessageIter* iter The iterator pointing at a container
 * @param int type The exptected type of the container
 *
 * @returns dbus_bool_t Returns TRUE if the specified type matches the type of
 *                      the container and the iter is successfully inside the
 *                      container, otherwise returns FALSE.
 */
dbus_bool_t iter_try_step_into_type(DBusMessageIter *iter, const int type);

/**
 * Try to recurse the iter into a container that it is pointing at with the
 * specified signature. This points the iter to the first element of the
 * container, rather than initializing a new subiter.
 *
 * @param DBusMessageIter* iter The iterator pointing at a container
 * @param const wchar_t* signature The exptected signature of the container
 *
 * @returns dbus_bool_t Returns TRUE if the specified signature matches the
 *                      signature of the container and the iter is successfully
 *                      initialized inside the container, otherwise returns
 *                      FALSE.
 */
dbus_bool_t iter_try_step_into_signature(DBusMessageIter *iter,
                                         const wchar_t *signature);

/**
 * Try to recurse the iter into an array of dictionary entries and set the iter
 * to point at the value of a dictionary entry of the specified key. This points
 * the iter to the value of the dictionary entry, rather than initializing a new
 * subiter.
 *
 * @param DBusMessageIter* iter The iterator pointing at an array of dictionary
 *                              entries.
 * @param const wchar_t* key The key of desired dictionary entry
 *
 * @returns dbus_bool_t Returns TRUE if a dictionary entry is found with the
 *                      specified key and the iter is successfully initialized
 *                      at the value of this dictionary entry, otherwise
 *                      returns FALSE.
 */
dbus_bool_t iter_try_step_to_key(DBusMessageIter *element_iter,
                                 const wchar_t *key);

/**
 * Sleep milliseconds
 *
 * @param long milliseconds The number of milliseconds to sleep
 *
 * @returns dbus_bool_t Returns TRUE if the function is able to sleep,
 *                      successfully, otherwise FALSE.
 */
dbus_bool_t msleep(const long milliseconds);

/**
 * Get an array of paths to polybar's IPC files in the specified directory.
 *
 * @param const wchar_t* ipc_path The directory in which to search for IPC files
 * @param wchar_t*** ptr_paths A pointer to a pointer to an array of paths that
 *                          will be populated with the paths to the found IPC
 *                          files.
 * @param size_t* num_of_paths The number of paths found by the function (i.e.
 *                             the number of elements in **ptr_paths).
 *
 * @returns dbus_bool_t Returns TRUE if the directory is successfully searched
 *                      for paths, otherwise FALSE.
 */
dbus_bool_t get_polybar_ipc_paths(const wchar_t *ipc_path, wchar_t **ptr_paths[],
                                  size_t *num_of_paths);

/**
 * Join two paths together. This function takes into account if the first path
 * ends in a '/' and concatenates the two paths together.
 * TODO: normalize paths instead of checking for '/'
 *
 * @param const wchar_t* p1 The first path
 * @param const wchar_t* p2 The second path (i.e. the path to concatenate)
 *
 * @returns wchar_t* The path with p1 and p2 joined together and NULL on error.
 *                This pointer must be freed by the caller.
 */
wchar_t *join_path(const wchar_t *p1, const wchar_t *p2);

/**
 * Replace all instances of a given string in a source string with another
 * string. This works from left-to-right, replacing 'strstr' with 'test' in the
 * string 'strstrstrstr' would result in 'testtest'.
 *
 * @param wchar_t* str The string to make the replacements in
 * @param wchar_t* find The string to look for
 * @param wchar_t* repl The string to replace `find` with in `str`
 *
 * @returns wchar_t* A new string with the replacements made if any.
 */
wchar_t* str_replace_all(const wchar_t *str, const wchar_t *find, const wchar_t *repl);

/**
 * Truncate the specified string if it longer than the specified maximum length
 * and end the string with trunc while satisfying the max length constraint.
 *
 * @param wchar_t* str The string to truncate
 * @param const int max_len The maximum length that this string should be
 * @param wchar_t* trunc The string to end str with if its being truncated.
 *
 * @returns wchar_t* The truncated string. If str is longer than max_len, str will
 * be cut off at max_len, and the end of the string will be replaced with trunc.
 */
wchar_t* str_trunc(const wchar_t *str, const int max_len, const wchar_t *trunc);

/**
 * Find the number of matches of a given string in another string. This works
 * from left-to-right using similar logic to the str_replace_all function. As a
 * result, searching for 'strstr' in 'strstrstrstr' would result in 2 matches,
 * not 3 (the middle strstr).
 *
 * @param wchar_t* str The source string to search in
 * @param wchar_t* find The string to search for
 *
 * @returns int The number of matches found
 */
int num_of_matches(const wchar_t *str, const wchar_t *find);

#endif
