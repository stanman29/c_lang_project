#ifndef COMMON_LANG_ASSERT_H
#define COMMON_LANG_ASSERT_H

#ifdef  NDEBUG
#define Assert(exp) ((void)0)

#define Require(exp) ((void)0)
#define Ensure(exp) ((void)0)
#define Invariant(exp) ((void)0)

#else

#include "except.h"

extern void Assert(int exp);
extern void Fail(void);

extern void Require(int exp);
extern void Ensure(int exp);
extern void Invariant(int exp);

#define Assert(exp)     ( (void)((exp) || (THROW(Assert_Failed), 0)) )

#define Require(exp)    ( (void)((exp) || (THROW(Precondition_Failed), 0)) )
#define Ensure(exp)     ( (void)((exp) || (THROW(Postcondition_Failed), 0)) )
#define Invariant(exp)  ( (void)((exp) || (THROW(Invariant_Error), 0)) )

#endif  /* NDEBUG */
#endif  /* COMMON_LANG_ASSERT_H */