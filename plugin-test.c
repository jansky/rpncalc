#include "rpncalc.h"
#include <string.h>

extern int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link);
struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ));

struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ))
{
	return info_link("Test Plugin", "Ian Duncan", "This is a test.", 1.0);
}

int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link)
{
	if(strcmp(token, "hello") == 0)
	{
		struct rpn_stack_element *e = link->stack_element_create_number(100);
		
		link->stack_push(stack, e);
		
		return 0;
	}
	
	return 1;
}
