#include "rpncalc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

struct rpn_plugin_info *rpn_plugin_info_create(char *name, char *author, char *description, double version)
{
	struct rpn_plugin_info *pi = malloc(sizeof(struct rpn_plugin_info));
	
	if(pi == NULL)
		return NULL;
	
	pi->version = version;
	
	// Copy the strings
	
	if(name == NULL)
		return NULL;
	
	pi->name = malloc((strlen(name) + 1)*sizeof(char));
	
	if(pi->name == NULL)
		return NULL;
	
	strcpy(pi->name, name);
	
	if(author == NULL)
		return NULL;
	
	pi->author = malloc((strlen(author) + 1)*sizeof(char));
	
	if(pi->author == NULL)
		return NULL;
	
	strcpy(pi->author, author);
	
	if(description == NULL)
		return NULL;
	
	pi->description = malloc((strlen(description) + 1)*sizeof(char));
	
	if(pi->description == NULL)
		return NULL;
	
	strcpy(pi->description, description);
	
	return pi;
}

struct rpn_plugin *plugin_init(char *filename)
{
	if(filename == NULL)
		return NULL;
	
	struct rpn_plugin *plugin = malloc(sizeof(struct rpn_plugin));
	
	if(plugin == NULL)
		return NULL;
	
	plugin->handle = dlopen(filename, RTLD_LAZY);
	
	if(plugin->handle == NULL)
	{
		fprintf(stderr, "Error opening plugin at %s: %s", filename, dlerror());
		free(plugin);
		
		return NULL;
	}
	
	// Bind the plugin main function
	
	dlerror();
	
	plugin->plugin_main = (rpn_plugin_main_t)dlsym(plugin->handle, "rpn_plugin_main");
	
	char *error = dlerror();
	
	if(error != NULL)
	{
		fprintf(stderr, "Error opening plugin at %s: %s\n", filename, error);
		dlclose(plugin->handle);
		free(plugin);
		
		return NULL;
	}
	
	// Get the metadata
	
	dlerror();
	
	rpn_plugin_info_t info_func = (rpn_plugin_info_t)dlsym(plugin->handle, "rpn_plugin_info");
	
	char *error1 = dlerror();
	
	if(error1 != NULL)
	{
		fprintf(stderr, "Error opening plugin at %s: %s\n", filename, error);
		dlclose(plugin->handle);
		free(plugin);
		
		return NULL;
	}
	
	plugin->plugin_info = info_func(&rpn_plugin_info_create);
	
	if(plugin->plugin_info == NULL)
	{
		fprintf(stderr, "Error opening plugin at %s: Error getting metadata.\n", filename);
		dlclose(plugin->handle);
		free(plugin);
	}
	
	// And we're done
	
	return plugin;
}

struct rpn_plugin *plugin_destroy(struct rpn_plugin *plugin)
{
	if(plugin == NULL)
		return NULL;
	
	dlclose(plugin->handle);
	
	free(plugin->plugin_info->name);
	free(plugin->plugin_info->author);
	free(plugin->plugin_info->description);
	
	free(plugin->plugin_info);
	
	struct rpn_plugin *next = plugin->next;
	
	free(plugin);
	
	return next;
}
	
	
	
	
	
	
	
