#ifndef FUNC_H
#define FUNC_H
#include "type.h"
#include "mem.h"
bool is_list(Cons pr);
Obj cons(kObj a , kObj b);
void print_obj(kObj obj);
void print_pair(kObj pr);
void print_cons(Cons kons);


Obj apply_car(Cons pr , Obj env);
Obj apply_cdr(Cons pr , Obj env);
Obj apply_eqnum(Cons pr , Obj env);
Obj apply_length(Cons pr , Obj env);
Obj apply_add(Cons pr , Obj env);
Obj apply_sub(Cons pr , Obj env);
Obj apply_mul(Cons pr , Obj env);
Obj apply_div(Cons pr , Obj env);
Obj apply_cons(Cons pr , Obj env);
Obj apply_print(Cons pr , Obj env);
Obj apply_listq(Cons pr , Obj env);
Obj apply_pairq(Cons pr , Obj env);
#endif
