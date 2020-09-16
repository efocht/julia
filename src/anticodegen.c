// This file is a part of Julia. License is MIT: https://julialang.org/license

#include "julia.h"
#include "julia_internal.h"
//#include "jitlayers.h"

#include "intrinsics.h"

#define UNAVAILABLE { jl_errorf("%s: not available in this build of Julia", __func__); }

void jl_dump_native(void *native_code, const char *bc_fname, const char *unopt_bc_fname, const char *obj_fname, const char *asm_fname, const char *sysimg_data, size_t sysimg_len) UNAVAILABLE
int32_t jl_get_llvm_gv(void *native_code, jl_value_t *p) UNAVAILABLE
void jl_write_malloc_log(void) UNAVAILABLE
void jl_write_coverage_data(const char *x) UNAVAILABLE

JL_DLLEXPORT void jl_clear_malloc_data(void) UNAVAILABLE
JL_DLLEXPORT void jl_extern_c(jl_function_t *f, jl_value_t *rt, jl_value_t *argt, char *name) UNAVAILABLE
JL_DLLEXPORT void *jl_function_ptr(jl_function_t *f, jl_value_t *rt, jl_value_t *argt) UNAVAILABLE
JL_DLLEXPORT jl_value_t *jl_dump_method_asm(jl_method_instance_t *linfo, size_t world, int raw_mc, char getwrapper, const char* asm_variant, const char *debuginfo) UNAVAILABLE
JL_DLLEXPORT jl_value_t *jl_dump_function_ir(void *f, char strip_ir_metadata, char dump_module, const char *debuginfo) UNAVAILABLE
JL_DLLEXPORT void *jl_get_llvmf_defn(jl_method_instance_t *linfo, size_t world, char getwrapper, char optimize, const jl_cgparams_t params) UNAVAILABLE

JL_DLLEXPORT void *jl_LLVMCreateDisasm(const char *TripleName, void *DisInfo, int TagType, void *GetOpInfo, void *SymbolLookUp) UNAVAILABLE
JL_DLLEXPORT size_t jl_LLVMDisasmInstruction(void *DC, uint8_t *Bytes, uint64_t BytesSize, uint64_t PC, char *OutString, size_t OutStringSize) UNAVAILABLE

int32_t jl_assign_functionID(const char *fname) UNAVAILABLE

void jl_init_codegen(void) { }

int jl_getFunctionInfo(jl_frame_t **frames, uintptr_t pointer, int skipC, int noInline)
{
    return 0;
}

void jl_register_fptrs(uint64_t sysimage_base, const struct _jl_sysimg_fptrs_t *fptrs,
                       jl_method_instance_t **linfos, size_t n)
{
    (void)sysimage_base; (void)fptrs; (void)linfos; (void)n;
}

#if 0
// who is missing this?
jl_functions_t jl_compile_linfo(jl_method_instance_t **pli, jl_code_info_t *src, size_t world, const jl_cgparams_t *params)
{
    jl_method_instance_t *li = *pli;
    jl_functions_t decls = {};

    if (jl_is_method(li->def.method)) {
        jl_printf(JL_STDERR, "code missing for ");
        jl_static_show(JL_STDERR, (jl_value_t*)li);
        jl_printf(JL_STDERR, " : sysimg may not have been built with --compile=all\n");
    }
    else {
        jl_printf(JL_STDERR, "top level expression cannot be compiled in this build of Julia");
    }
    return decls;
}
#endif

//jl_value_t *jl_fptr_interpret_call(jl_method_instance_t *lam, jl_value_t **args, uint32_t nargs);
jl_code_instance_t *jl_generate_fptr(jl_method_instance_t *pli, size_t world)
{
    return (jl_code_instance_t *)&jl_fptr_interpret_call;
}

JL_DLLEXPORT uint32_t jl_get_LLVM_VERSION(void)
{
    return 0;
}

// from debuginfo

// Any function that acquires this lock must be either a unmanaged thread
// or in the GC safe region and must NOT allocate anything through the GC
// while holding this lock.
// Certain functions in this file might be called from an unmanaged thread
// and cannot have any interaction with the julia runtime
static uv_rwlock_t threadsafe;

void jl_init_debuginfo(void)
{
  uv_rwlock_init(&threadsafe);
}

void jl_lock_profile(void)
{
  uv_rwlock_rdlock(&threadsafe);
}

void jl_unlock_profile(void)
{
  uv_rwlock_rdunlock(&threadsafe);
}
