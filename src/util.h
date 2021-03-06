#ifndef UTIL_H
#define UTIL_H
#include "type.h"

#define car(p) ((p)->pair->car)
#define cdr(p) ((p)->pair->cdr)
#define caar(x)   (car(car(x)))
#define cadr(x)   (car(cdr(x)))
#define cdar(x)   (cdr(car(x)))
#define cddr(x)   (cdr(cdr(x)))
#define caaar(x)  (car(car(car(x))))
#define caadr(x)  (car(car(cdr(x))))
#define cadar(x)  (car(cdr(car(x))))
#define caddr(x)  (car(cdr(cdr(x))))
#define cdaar(x)  (cdr(car(car(x))))
#define cdadr(x)  (cdr(car(cdr(x))))
#define cddar(x)  (cdr(cdr(car(x))))
#define cdddr(x)  (cdr(cdr(cdr(x))))
#define caaaar(x) (car(car(car(car(x)))))
#define caaadr(x) (car(car(car(cdr(x)))))
#define caadar(x) (car(car(cdr(car(x)))))
#define caaddr(x) (car(car(cdr(cdr(x)))))
#define cadaar(x) (car(cdr(car(car(x)))))
#define cadadr(x) (car(cdr(car(cdr(x)))))
#define caddar(x) (car(cdr(cdr(car(x)))))
#define cadddr(x) (car(cdr(cdr(cdr(x)))))
#define cdaaar(x) (cdr(car(car(car(x)))))
#define cdaadr(x) (cdr(car(car(cdr(x)))))
#define cdadar(x) (cdr(car(cdr(car(x)))))
#define cdaddr(x) (cdr(car(cdr(cdr(x)))))
#define cddaar(x) (cdr(cdr(car(car(x)))))
#define cddadr(x) (cdr(cdr(car(cdr(x)))))
#define cdddar(x) (cdr(cdr(cdr(car(x)))))
#define cddddr(x) (cdr(cdr(cdr(cdr(x)))))


#define env_ref(t)   ((t)->env->ref)

#define clos_expr(t) ((t)->clos->exp)
#define clos_body(t) ((t)->clos->exp->expr->body)
#define clos_args(t) ((t)->clos->exp->expr->args)
#define clos_env(t)  ((t)->clos->env)
#define clos_tr(t)  ((t)->clos->tr)

#define mac_keys(t)  ((t)->mac->keyws)
#define mac_rules(t) ((t)->mac->rules)
#define port_fp(t)   ((t)->port->fp)
#define port_ctx(t)  ((t)->port->ctx)
#define port_ptr(t)  ((t)->port->ptr)
#define port_name(t) ((t)->port->name)
#define port_mode(t) ((t)->port->mode)
#define port_open(t) ((t)->port->open)


bool is_list(Obj pr);
bool cmp_num(Obj a , Obj b);
bool eqv(Obj a , Obj b);
bool equal(Obj a , Obj b);
int pat_num(Obj pr);
int  length(Obj pr);
void fprint_obj(FILE *s , kObj obj);
void fprint_obj_dtl(FILE *s , Obj obj);
void fprint_pair(FILE *s , kObj pr);
void fprint_symtree(FILE *s , Symtree tree);

#define print_obj(obj) fprint_obj(stdout , obj)
#define print_pair(obj) fprint_pair(stdout , obj)

Obj cons(kObj head , kObj body);

Obj zip_env(Obj syms , Obj args , Obj env);

#define zipped_env(syms , args , env) \
    zip_env(syms , args , new(ENV , env))

Obj zip_pat(Obj pat , Obj args , Obj env);
Obj lssym(Obj ls , Obj sym);
Obj lssym_rec(Obj ls , Obj sym);
Obj lsobj(Obj ls , Obj obj);
Obj prid(Obj ls);
bool is_sympr(Obj ls);

#define error(fmt , ...) \
    printf(fmt , ##__VA_ARGS__) , exit(1)

#define imode_msg(fmt , ...) \
    printf(port_fp(repl_pt) == stdin ? (fmt) : "" , ##__VA_ARGS__) , fflush(stdout)

#define falert(s , str , obj) \
    fprintf(s , str) , fprint_obj(s , obj) , fputs("" , s)

Obj alert(char *str , Obj obj);
Obj alert_dtl(char *str , Obj obj);
Obj warning(char *str);

#define msgobjc(str , obj) \
    fprintf(stdout , str) , fprint_obj_dtl(stdout , obj)

#define msgobj(str , obj) \
    fprintf(stdout , str) , fprint_obj_dtl(stdout , obj) , puts("")

#define ASSERT(expr , msg) \
    if(!(expr)) error("%s : %s %d" , msg , __FILE__ , __LINE__)

#endif
