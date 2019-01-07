/*
 *
 * Build Order: You are given a list of projects and a list of dependencies (which is a list of pairs of
 * projects, where the second project is dependent on the first project). All of a project's dependencies
 * must be built before the project is. Find a build order that will allow the projects to be built. If there
 * is no valid build order, return an error.
 * EXAMPLE
 * Input:
 * projects: a, b, c, d, e, f
 * dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
 * Output: f, e, a, b, d, c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"

/* for each project, the build tree will have a list of dependent tasks*/
/* the build order will be the depth first tree traversal */
typedef struct build_tasks
{
	int task;		/* the task number */
	bool marked;	/* to be used during breadth first traversal */

	/* this is a C project, so we don't have access to C++ STL (for ex. std::vector) */
	/* so we have to manage the array of dependent_tasks ourselves */
	int dep_tasks_count;
	int dep_tasks_arr_sz;
	
	/* the array of dependent tasks */
	struct build_tasks ** dependent_tasks;
} build_task;

/* a list of build_tree */
typedef struct build_trees
{
	build_task * head;
	struct build_trees * next;
} build_tree;

/* the function for this exercise */
build_tree * process_dependencies(build_tree ** input_task_list);
build_task * find_build_task(build_tree * t, int task);
build_task * find_dependent_build_task(build_task * t, int task);

/* some "administrative" functions */
build_task * create_build_task(int project);
void add_dependent_task(build_task *t, build_task * dep_task);
void add_dependent_task_number(build_task *t, int task);
build_tree * remove_top_level_task_from_tree(build_tree ** t, int task);
void print_build_tree(build_tree * t);
void print_build_task(build_task * t);
void free_build_task(build_task * t);
void free_build_tree(build_tree *t);
build_tree * read_task_list();


int main()
{
	build_tree * input = read_task_list();
	if (!input || !(input->head))
	{
		printf("empty task list. Exiting.\n");
		return 0;
	}

	build_tree * output = process_dependencies(&input);
	if (!output)
	{
		printf("there is a cycle in the dependency list. Exiting.\n");
		free_build_tree(input);
		return 0;
	}
	
	/* output the results */
	printf("Output: ");
	
	/* If the input list is not empty that means there are some tasks which are not involved in the depedency graph */
	/* print these first */
	build_tree * tmp = input;
	if (tmp)
	{
		printf("%d",tmp->head->task);
		tmp = tmp->next;
	}

	while (tmp)
	{
		printf(", %d", tmp->head->task);
		tmp = tmp->next;
	}
	
	print_build_tree(output);
	printf("\n");

	free_build_tree(input);
	free_build_tree(output);
	
	return 0;
}

/* given a list of tasks, this function will read the dependencies */
/* for each dependency will check if it creates a cycle in the build_tree */
/* if there are no cycles, the new dependency will be added to the tree */
/* if a cycle is created, the build_tree being created will be destroyed */
/* and the function will return NULL i*/
build_tree * process_dependencies(build_tree ** input_task_list)
{
	char * line = NULL;
	size_t size;
	getline(&line, &size, stdin);
	
	/* the format is "dependencies: (task_no_1, task_no_2)" */
	/* to keep it simple, assume input is correct */
	build_tree * res = NULL;
	
	char *token;
	char delim[4]=" ,()";
	token = strtok(line, delim);
	int master = atoi(token);
	while (token)
	{
		token = strtok(NULL, delim);
		int dependent = atoi(token);
		if (dependent == master)
		{
			/* self referential rule - (1,1) */
			token = strtok(NULL, delim);
			master = atoi(token);
			continue;
		}

		build_task * master_task = find_build_task(res, master);
		if (master_task)
		{
			build_task * dep_task = find_build_task(res, dependent);
			if (dep_task)
			{
				/* both master and dependent tasks are in the tree */
				/* check if adding the new edge would create a cycle */
				build_task * cycle_check = find_dependent_build_task(dep_task, master);
				if (cycle_check)
				{
					/* cycle found.... */
					free_build_tree(res);
					res = NULL;
					break;
				}
				else
				{
					/* if dep_task does not depend on any other tasks (i.e. is it a top leve node in build_tree) */
					/* it should be removed from the top level in the build_tree */
					/* add this edge to the graph */
					remove_top_level_task_from_tree(&res, dependent	);
					add_dependent_task(master_task, dep_task);
				}
			}
			else
			{
				add_dependent_task_number(master_task, dependent);
			}
		}
		else
		{
			/* add the new master - dependent edge to the build tree */
			build_tree * prev = res;
			build_task * new_task = create_build_task(master);
			build_task * dependent_task = find_build_task(res, dependent);
			if (!dependent_task)
			{
				add_dependent_task_number(new_task, dependent);
			}
			else
			{
				add_dependent_task(new_task, dependent_task);
			}
			res = (build_tree *) malloc(sizeof(build_tree));
			res->head = new_task;
			res->next = prev;
		}
		
		/* remove the two tasks read from the dependency list as they are in the dependency build tree now */
		build_tree * input_list_task = remove_top_level_task_from_tree(input_task_list, master);
		free(input_list_task);
		input_list_task = remove_top_level_task_from_tree(input_task_list, dependent);
		free(input_list_task);
		
		/* next depedency on the input */
		token = strtok(NULL, delim);
		master = atoi(token);
	}

	return res;

	free(line);
}

/* assume no cycles */
build_task * find_dependent_build_task(build_task *t, int task)
{
	if (!t)
	{
		return NULL;
	}
	
	if (t->task == task)
	{
		return t;
	}
	for (int i = 0; i < t->dep_tasks_count; i ++)
	{
		build_task * res = find_dependent_build_task(t->dependent_tasks[i], task);
		if (res)
		{
			return res;
		}
	}

	return NULL;
}

/* assume no cycles */
build_task * find_build_task(build_tree * t, int task)
{
	while (t)
	{
		build_task * res = find_dependent_build_task( t->head, task);
		if (res)
		{
			return res;
		}
		t = t->next;
	}
	return NULL;
}

build_task * create_build_task(int task)
{
	build_task * res = (build_task *) malloc(sizeof(build_task));
	memset(res /*dest*/, 0 /*value*/, sizeof(build_task) /*num*/);
	res->task = task;
	return res;
}

void add_dependent_task(build_task *t, build_task *dep_task)
{
	if (t->dep_tasks_arr_sz == t->dep_tasks_count)
	{
		/* we have to grow the task array */
		t->dep_tasks_arr_sz += 32;
		t->dependent_tasks = (build_task **) realloc(t->dependent_tasks, t->dep_tasks_arr_sz * sizeof(build_task*));
	}
	
	t->dependent_tasks[t->dep_tasks_count] = dep_task;

	t->dep_tasks_count ++;
}

void add_dependent_task_number(build_task *t, int task)
{
	build_task * node = (build_task *) malloc(sizeof(build_task));
	memset(node /*dest*/, 0 /*value*/, sizeof(build_task) /*num*/);
	node->task = task;
	add_dependent_task(t, node);
}

/* will remove a task from the top tasks */
/* i.e. will not descent  into the dependent tasks */
build_tree * remove_top_level_task_from_tree(build_tree ** t, int task)
{
	/* some base cases */
	if (!t || !(*t))
	{
		return NULL;
	}
	if ( (*t)->head->task == task)
	{
		build_tree * del_node = (*t);
		*t = (*t)->next;
		return del_node;
	}
	
	/* now traverse the list of top tasks looking for "target" task */
	build_tree * prev = (*t), *curr = (*t)->next;
	while (curr && curr->head->task != task)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr && curr->head->task == task)
	{
		prev->next = curr->next;
		return curr;
	}
	else
	{
		return NULL;
	}
}

void print_build_tree(build_tree * t)
{
	while (t)
	{
		print_build_task(t->head);
		t = t->next;
	}
}

/* the build order will be the breadth first traversal */
void print_build_task(build_task * t)
{
	queue * q = create_empty_queue();
	t->marked = true;
	enqueue(q, t);
	while (!isEmpty(q))
	{
		build_task * bd = (build_task *) dequeue(q);
		printf(", %d", bd->task);
		for (int i = 0; i < bd->dep_tasks_count; i++)
		{
			build_task * child = bd->dependent_tasks[i];
			if (!child->marked)
			{
				child->marked = true;
				enqueue(q, bd->dependent_tasks[i]);
			}
		}
	}
}


/* assume no cycles */
/* with a breath first traversal */
void free_build_task(build_task * t)
{
}

/* assume no cycles */
void free_build_tree(build_tree * t)
{
}

/* will read the project list from stdin */
/* the project list will be the words: "projects: " followed by a series of integers */
build_tree * read_task_list()
{
	char * line = NULL;
	size_t size;
	getline(&line, & size, stdin);
	if (strncmp(line, "projects: ", strlen("projects: ")) != 0)
	{
		printf("usage is : \"projects: \" followed by a list of project numbers.\n.Exiting program.\n");
		free(line);
		return NULL;
	}
	
	build_tree * res = NULL;
	
	char * token, *start = line + strlen("projects: ");
	char delim[3] = " \t,";
	token = strtok(start, delim);
	while (token)
	{
		int i = atoi(token);
		build_tree * prev = res;
		res = (build_tree *) malloc(sizeof(build_tree));
		res->head = create_build_task(i);
		res->next = prev;
		
		token = strtok(NULL, delim);
	}
	
	free(line);
	return res;
}