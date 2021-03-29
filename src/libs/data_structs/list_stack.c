#include "data_structs/stack.h"

#include "data_structs/list.h"
#include "lang/memory.h"
#include "lang/assert.h"
#include "logger/log.h"

/* __________________________________________________________________________ */
/*                                                                     Local  */

struct stack {
  int count;
  List_T storage;
} empty_stack = { .count = 0,
                  .storage = NULL
                };

/* __________________________________________________________________________ */

Stack_T
Stack_new(void)
{
  Stack_T stack;
  NEW(stack);

  stack->count = 0;
  stack->storage = List_new();

  return stack;
}

bool
Stack_is_empty(Stack_T stack)
{
  Require(stack);
  return stack->count == 0;
}

void
Stack_push(Stack_T stack, Generic_T data)
{
  Require(stack);

  List_insert(&stack->storage, data);
  stack->count++;
}

bool
Stack_pop(Stack_T stack, Generic_T* p_data__)
{
  Require(stack);

  if (stack->count == 0) {
    return false;
  }

  List_delete_head(&stack->storage, p_data__);
  stack->count--;
  return true;
}

bool
Stack_peel(Stack_T stack, Generic_T* p_data__)
{
  if (!Stack_pop(stack, p_data__))
  { return false; }

  Stack_push(stack, *p_data__);
  return true;
}

void
Stack_destroy(Stack_T stack, free_data_FN free_data_fn)
{
  if (!Stack_is_empty(stack)) {
    Log_warn("Stack is not empty.");

    List_destroy(&stack->storage, free_data_fn);
    stack->count = 0;
  }

  *stack = empty_stack;

  FREE(stack);
  stack = NULL;
}

void
Stack_free(Stack_T stack)
{
  Stack_destroy(stack, NULL);
}
