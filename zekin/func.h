#ifndef FUNC_H
#define FUNC_H
#include "type.h"
#include "mem.h"

Obj apply_source(Obj pr , Obj env);
Obj apply_senv(Obj pr , Obj env);
Obj apply_apply(Obj pr , Obj env);
Obj apply_nullq(Obj pr , Obj env);
Obj apply_not(Obj pr , Obj env);
Obj apply_car(Obj pr , Obj env);
Obj apply_cdr(Obj pr , Obj env);
Obj apply_eqnum(Obj pr , Obj env);
Obj apply_length(Obj pr , Obj env);
Obj apply_add(Obj pr , Obj env);
Obj apply_sub(Obj pr , Obj env);
Obj apply_mul(Obj pr , Obj env);
Obj apply_div(Obj pr , Obj env);
Obj apply_mod(Obj pr , Obj env);
Obj apply_cons(Obj pr , Obj env);
Obj apply_display(Obj pr , Obj env);
Obj apply_listq(Obj pr , Obj env);
Obj apply_pairq(Obj pr , Obj env);


Obj apply_clos(Obj pcr , Obj args , Obj env);
#endif
