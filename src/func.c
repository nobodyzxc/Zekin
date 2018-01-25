#include "mem.h"
#include "func.h"
#include "util.h"
#include "eval.h"
#include "main.h"
#include "parse.h"
#include "token.h"

#include <math.h>
#include <readline/readline.h>
#include <readline/history.h>

/* predictors */
Obj apply_eqq(Obj args , Obj env){
    if(length(args) != 2)
        alert("eq? : only accepts 2 args , got " , args);
    else
        return new(BOOLEAN , car(args) == cadr(args));
    return (Obj)err;
}

Obj apply_eqvq(Obj args , Obj env){
    if(length(args) != 2)
        alert("eqv? : only accepts 2 args , got " , args);
    else
        return new(BOOLEAN , eqv(car(args) , cadr(args)));
    return (Obj)err;
}

Obj apply_equalq(Obj args , Obj env){
    if(length(args) != 2)
        alert("equal? : only accepts 2 args , got " , args);
    else
        return new(BOOLEAN , equal(car(args) , cadr(args)));
    return (Obj)err;
}

Obj apply_nullq(Obj args , Obj env){
    if(length(args) != 1)
        alert("null? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_nil(car(args)));
    return (Obj)err;
}

Obj apply_listq(Obj args , Obj env){
    if(length(args) != 1)
        alert("list? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_list(car(args)));
    return (Obj)err;
}

Obj apply_pairq(Obj args , Obj env){
    if(length(args) != 1)
        alert("pair? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , car(args)->type == PAIR);
    return (Obj)err;
}

Obj apply_booleanq(Obj args , Obj env){
    if(length(args) != 1)
        alert("boolean? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_bool(car(args)));
    return (Obj)err;
}

Obj apply_numberq(Obj args , Obj env){
    if(length(args) != 1)
        alert("number? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_num(car(args)));
    return (Obj)err;
}

Obj apply_exactq(Obj args , Obj env){
    if(length(args) != 1)
        alert("exact? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_exact(car(args)));
    return (Obj)err;
}

Obj apply_integerq(Obj args , Obj env){
    if(length(args) != 1)
        alert("integer? : only accepts 1 arg , got " , args);
    else if(is_num(car(args)))
        return new(BOOLEAN ,
                is_exact(car(args))
                || floor(num_of(car(args))) == num_of(car(args)));
    else
        alert("integer? : only accepts number , got " , args);
    return (Obj)err;
}

Obj apply_stringq(Obj args , Obj env){
    if(length(args) != 1)
        alert("string? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_str(car(args)));
    return (Obj)err;
}

Obj apply_closureq(Obj args , Obj env){
    if(length(args) != 1)
        alert("closure? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_clos(car(args)));
    return (Obj)err;
}

Obj apply_envq(Obj args , Obj env){
    if(length(args) != 1)
        alert("env? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_env(car(args)));
    return (Obj)err;
}
/* precedures */
Obj apply_exit(Obj args , Obj env){
    if(length(args) > 0 &&
            car(args)->type == INTEGER)
        exit((int)(car(args)->integer));
    exit(0);
    return NULL;
}

Obj apply_clos(Obj pcr , Obj args , Obj env){
    Obj iter = clos_body(pcr) , val = NULL;
    env = zipped_env(clos_args(pcr) , args , clos_env(pcr));
    while(not_nil(iter))
        val = eval(car(iter) , env) , iter = cdr(iter);
    return val;
}

Obj apply_gc(Obj args , Obj env){
    gc();
    return NULL;
}

Obj apply_source(Obj args , Obj env){
    if(length(args) != 1)
        alert("source : only accepts 1 arg , got " , args);
    else if(car(args)->type != STRING)
        puts("source file name must be string");
    else if(load_script(car(args)->str , true)){
        stdin_printf("ok , \"%s\" loaded\n" , car(args)->str);
        return NULL;
    }
    return (Obj)err;
}

Obj apply_system(Obj args , Obj env){
    if(length(args) != 1)
        alert("system : only accepts 1 arg , got " , args);
    else if(car(args)->type != STRING)
        puts("system : command must be string");
    else if(!system(car(args)->str))
            return NULL;
    return (Obj)err;
}

Obj apply_apply(Obj args , Obj env){
    if(length(args) != 2)
        alert("apply : only accepts 2 args , got " , args);
    else if(car(args)->type == CLOSURE)
        return apply_clos(car(args) ,
                cadr(args) , env);
    else if(car(args)->type == FUNCTION)
        return car(args)->proc->apply(
                cadr(args) , env);
    else{
        printf("cannot apply ");
        print_obj(car(args));
        alert(" on " , cadr(args));
    }
    return (Obj)err;
}

Obj apply_get_env(Obj args , Obj env){
    if(length(args) != 1)
        alert("get-env : only accepts 1 arg , got " , args);
    else if(!car(args) || car(args)->type != CLOSURE)
        puts("get-env only accepts closure");
    else
        return clos_env(car(args));
    return (Obj)err;
}

Obj apply_get_curenv(Obj args , Obj env){
    return env;
}

Obj apply_lookup_symbol(Obj args , Obj env){
    if(length(args) != 2)
        alert("lookup-env : only accepts 2 arg , got " , args);
    else if(!car(args) || car(args)->type != SYMBOL)
        alert("lookup-env's 1st arg should be symbol , got " , car(args));
    else if(!cadr(args) || cadr(args)->type != ENV)
        alert("lookup-env's 2nd arg should be environment , got " , cadr(args));
    else{
        Obj res = search_symbol(car(args)->str , cadr(args));
        if(res != err)
            return res;
        else
            alert("lookup-symbol : cannot found symbol " , car(args));
    }
    return (Obj)err;
}

Obj apply_flush_output(Obj args , Obj env){
    fflush(stdout);
    return NULL;
}

Obj apply_display(Obj args , Obj env){
    /* todo : extend arity up to 2
     * to support output-port? */
    if(length(args) != 1)
        alert("display : only accepts 1 arg , got " , args);
    else{
        if(!car(args)) /* handle void */
            print_obj(args);
        else if(car(args)->type == STRING)
            printf(car(args)->str);
        else if(car(args)->type == CLOSURE)
            detail(car(args));
        else if(car(args)->type == ENV)
            detail(car(args));
        else if(car(args)->type == MACRO)
            detail(car(args));
        else
            print_obj(car(args));
        return NULL;
    }
    return (Obj)err;
}

Obj apply_length(Obj args , Obj env){
    int len = 0;
    if(length(args) != 1)
        alert("length : only accepts 1 arg , got " , args);
    else if(!is_pair(car(args)))
        alert("cannot apply length on " , car(args));
    else if((len = length(car(args))) >= 0)
        return new(INTEGER , len);
    else
        alert("cannot apply length on pr : " , car(args));
    return (Obj)err;
}

Obj apply_car(Obj args , Obj env){
    if(length(args) != 1)
        alert("car : only accepts 1 arg , got " , args);
    else if(car(args) && car(args)->type == PAIR)
        return caar(args);
    else
        alert("cannot apply car on " , car(args));
    return (Obj)err;
}

Obj apply_cdr(Obj args , Obj env){
    if(length(args) != 1)
        alert("cdr : only accepts 1 arg , got " , args);
    else if(car(args)->type == PAIR)
        return cdar(args);
    else
        alert("cannot apply cdr on " , car(args));
    return (Obj)err;
}

Obj apply_cons(Obj args , Obj env){
    // assert arity == 2
    if(length(args) != 2)
        alert("cons : only accepts 2 args , got " , args);
    else
        return new(PAIR , new_cons(car(args) , cadr(args)));
    return (Obj)err;
}

Obj apply_eqnum(Obj args , Obj env){
    // assert arity > 1
    if(length(args) < 2)
        alert("= : accepts at least 2 args , got " , args);
    else{
        bool rtn = true;
        Obj head = car(args);
        while(args->type == PAIR)
            if(is_num(car(args)))
                rtn &= cmp_num(head , car(args)) , args = cdr(args);
            else
                return alert("apply = on non-number obj " , car(args));
        return new(BOOLEAN , rtn);
    }
    return (Obj)err;
}

#define apply_cmp(name , op) \
    Obj apply_ ## name (Obj args , Obj env){ \
        if(length(args) < 2) \
        alert(str(op) " : accepts at least 2 args , got " , args); \
        else{ \
            for( ; iterable(args) && not_nil(cdr(args)) ; \
                    args = cdr(args)) \
            if(!(num_of(car(args)) op num_of(cadr(args)))) \
                return (Obj)false_obj; \
            return (Obj)true_obj; \
        } \
        return (Obj)err; \
    }

apply_cmp(lt , <);
apply_cmp(gt , >);
apply_cmp(let , <=);
apply_cmp(get , >=);

Obj apply_not(Obj args , Obj env){
    //assert airth == 1
    if(length(args) != 1)
        alert("not : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , is_false(car(args)));
    return (Obj)err;
}

Obj apply_void(Obj args , Obj env){
    return NULL;
}

Obj apply_voidq(Obj args , Obj env){
    if(length(args) != 1)
        alert("void? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , car(args) == NULL);
    return (Obj)err;
}

Obj apply_symbolq(Obj args , Obj env){
    if(length(args) != 1)
        alert("symbol? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , car(args)->type == SYMBOL);
    return (Obj)err;
}

Obj apply_procedureq(Obj args , Obj env){
    if(length(args) != 1)
        alert("procedure? : only accepts 1 arg , got " , args);
    else
        return new(BOOLEAN , car(args)
                && (car(args)->type == CLOSURE
                    || car(args)->type == FUNCTION));
    return (Obj)err;
}

Obj apply_read(Obj args , Obj env){
    /* todo : input-port ? */
    /* disable up down arrow key in read func */
    rl_bind_keyseq("\\e[A" , rl_abort);
    rl_bind_keyseq("\\e[B" , rl_abort);

    FILE *prev_stream = stream;
    stream = stdin;
    Token tok = NULL;
    while(is_blank(*ctx_p)) ctx_p++;
    if(!*ctx_p) ctx_p = NULL;
    ctx_p = tokenize(get_non_blank(ctx_p) , &tok);
#ifdef PURE_READ
    clear_buffer();
#endif
    Obj val = parse(tok);
    free_token(tok);
    stream = prev_stream;

    /* enable up down arrow key after read func */
    rl_bind_keyseq("\\e[A" , rl_get_previous_history);
    rl_bind_keyseq("\\e[B" , rl_get_next_history);
    return val;
}

#define arith(args , rtn , op , base) \
    Obj rtn = new(INTEGER , base); \
    int pr_len = length(args); \
    int chk = 6 op 2; \
    if((6 op 2 > 5 && pr_len) || pr_len > 1){ \
        if(car(args)->type == INTEGER){ \
            rtn->integer = car(args)->integer; \
        } \
        else if(car(args)->type == DECIMAL){ \
            rtn->type = DECIMAL; \
            rtn->decimal = car(args)->decimal; \
        } \
        else{ \
            printf("cannot apply " xstr(op) " on non-number obj "); \
            return alert("" , car(args)); \
        } \
        args = cdr(args); \
    } \
    for( ; args ; args = cdr(args)){ \
        if(is_nil(args)) \
        break; \
        if(6 op 3 == 2 || 6 op 3 == 0){ \
            if(num_of(car(args)) == 0){ \
            printf(6 op 3 ? "/" : "%%");    \
            return alert(" : arg cannot be zero , got " , car(args)); \
            } \
        } \
        if(!is_num(car(args))){ \
            printf("cannot apply " xstr(op) " on non-number obj "); \
            return alert("" , car(args)); \
        } \
        else if(rtn->type == DECIMAL){ \
            HANDEL_DEC1(args , rtn , op , base) \
        } \
        else if(rtn->type == INTEGER){ \
            if(car(args)->type == INTEGER) \
            rtn->integer op ## = car(args)->integer; \
            HANDEL_DEC2(args , rtn , op , base) \
        } \
    }

#define apply_opr(op_name , op , base) \
    Obj apply_ ## op_name(Obj args , Obj env){ \
        arith(args , rtn , op , base); \
        return rtn; \
    }

#define HANDEL_DEC1(args , rtn , op , base) \
    if(car(args)->type == INTEGER) \
    rtn->decimal op ## = (double) car(args)->integer; \
    else if(car(args)->type == DECIMAL) \
    rtn->decimal op ## = car(args)->decimal; \

#define HANDEL_DEC2(args , rtn , op , base) \
    else if(car(args)->type == DECIMAL){ \
        rtn->type = DECIMAL; \
        rtn->decimal = rtn->integer; \
        rtn->decimal op ## = car(args)->decimal; \
    }

apply_opr(add , + , 0);
apply_opr(mul , * , 1);
apply_opr(sub , - , 0);
apply_opr(div , / , 1);

#undef HANDEL_DEC1
#undef HANDEL_DEC2
#define HANDEL_DEC1(args , rtn , op , base) \
    { \
        printf("cannot apply %% on decimal\n"); \
        return (Obj) err; \
    }
#define HANDEL_DEC2(args , rtn , op , base) \
    else if(car(args)->type == DECIMAL){ \
        printf("cannot apply %% on decimal\n"); \
        return (Obj) err; \
    }
#define MOD
apply_opr(mod , % , 1);
