#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef int32_t dim_t;
typedef int32_t inc_t;

typedef void cntx_t;

typedef struct
{
	void*  a_next;
	void*  b_next;
} auxinfo_t;

typedef enum
{
    BLIS_NO_TRANSPOSE,
    BLIS_TRANSPOSE,
    BLIS_CONJ_NO_TRANSPOSE,
    BLIS_CONJ_TRANSPOSE
} trans_t;

#define PASTEMAC0_(op)             bli_ ## op
#define PASTEMAC0(op)              PASTEMAC0_(op)

#define PASTEMAC_(ch,op)           bli_ ## ch  ## op
#define PASTEMAC(ch,op)            PASTEMAC_(ch,op)

#define GEMM_UKR_PROT2( ctype_in, ctype_out, ch, opname ) \
\
void PASTEMAC(ch,opname) \
     ( \
       dim_t               k, \
       ctype_out* restrict alpha, \
       ctype_in*  restrict a, \
       ctype_in*  restrict b, \
       ctype_out* restrict beta, \
       ctype_out* restrict c, inc_t rs_c, inc_t cs_c, \
       auxinfo_t* restrict data, \
       cntx_t*    restrict cntx  \
     );

#define bli_min( a, b )  ( (a) < (b) ? (a) : (b) )
#define bli_max( a, b )  ( (a) > (b) ? (a) : (b) )
#define bli_abs( a )     ( (a) <= 0 ? -(a) : (a) )

#define bli_auxinfo_next_a(ai) ( (ai)->a_next )
#define bli_auxinfo_next_b(ai) ( (ai)->b_next )

#define bli_auxinfo_set_next_a(p,ai) ( (ai)->a_next = (p) )
#define bli_auxinfo_set_next_b(p,ai) ( (ai)->b_next = (p) )
