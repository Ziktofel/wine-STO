/*
 * Copyright 2010 Piotr Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "config.h"

#include <stdarg.h>

#include "msvcp90.h"

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
WINE_DEFAULT_DEBUG_CHANNEL(msvcp90);

/* dlls/msvcrt/cppexcept.h */
typedef void (*cxx_copy_ctor)(void);

/* complete information about a C++ type */
typedef struct __cxx_type_info
{
    UINT             flags;        /* flags (see CLASS_* flags below) */
    const type_info *type_info;    /* C++ type info */
    this_ptr_offsets offsets;      /* offsets for computing the this pointer */
    unsigned int     size;         /* object size */
    cxx_copy_ctor    copy_ctor;    /* copy constructor */
} cxx_type_info;
#define CLASS_IS_SIMPLE_TYPE          1
#define CLASS_HAS_VIRTUAL_BASE_CLASS  4

/* table of C++ types that apply for a given object */
typedef struct __cxx_type_info_table
{
    UINT                 count;     /* number of types */
    const cxx_type_info *info[3];   /* variable length, we declare it large enough for static RTTI */
} cxx_type_info_table;

/* type information for an exception object */
typedef struct __cxx_exception_type
{
    UINT                       flags;            /* TYPE_FLAG flags */
    void                     (*destructor)(void);/* exception object destructor */
    void* /*cxx_exc_custom_handler*/ custom_handler;   /* custom handler for this exception */
    const cxx_type_info_table *type_info_table;  /* list of types for this exception object */
} cxx_exception_type;

void CDECL _CxxThrowException(exception*,const cxx_exception_type*);

/* vtables */

#ifdef _WIN64

#define __ASM_VTABLE(name,funcs) \
    __asm__(".data\n" \
            "\t.align 8\n" \
            "\t.quad " __ASM_NAME(#name "_rtti") "\n" \
            "\t.globl " __ASM_NAME("MSVCP_" #name "_vtable") "\n" \
            __ASM_NAME("MSVCP_" #name "_vtable") ":\n" \
            "\t.quad " THISCALL_NAME(MSVCP_ ## name ## _vector_dtor) "\n" \
            funcs "\n\t.text");

#define __ASM_EXCEPTION_VTABLE(name) \
    __ASM_VTABLE(name, "\t.quad " THISCALL_NAME(MSVCP_what_exception) )

#define __ASM_EXCEPTION_STRING_VTABLE(name) \
    __ASM_VTABLE(name, "\t.quad " THISCALL_NAME(MSVCP_logic_error_what) )

#else

#define __ASM_VTABLE(name,funcs) \
    __asm__(".data\n" \
            "\t.align 4\n" \
            "\t.long " __ASM_NAME(#name "_rtti") "\n" \
            "\t.globl " __ASM_NAME("MSVCP_" #name "_vtable") "\n" \
            __ASM_NAME("MSVCP_" #name "_vtable") ":\n" \
            "\t.long " THISCALL_NAME(MSVCP_ ## name ## _vector_dtor) "\n" \
            funcs "\n\t.text");

#define __ASM_EXCEPTION_VTABLE(name) \
    __ASM_VTABLE(name, "\t.long " THISCALL_NAME(MSVCP_what_exception) )

#define __ASM_EXCEPTION_STRING_VTABLE(name) \
    __ASM_VTABLE(name, "\t.long " THISCALL_NAME(MSVCP_logic_error_what) )

#endif /* _WIN64 */

extern const vtable_ptr MSVCP_bad_alloc_vtable;
extern const vtable_ptr MSVCP_logic_error_vtable;

/* exception class data */
static type_info exception_type_info = {
    NULL, /* set by set_exception_vtable */
    NULL,
    ".?AVexception@std@@"
};

DEFINE_THISCALL_WRAPPER(MSVCP_exception_ctor, 8)
exception* __stdcall MSVCP_exception_ctor(exception *this, const char **name)
{
    TRACE("(%p %s)\n", this, *name);

    this->vtable = exception_type_info.vtable;
    if(*name) {
        unsigned int name_len = strlen(*name) + 1;
        this->name = malloc(name_len);
        memcpy(this->name, *name, name_len);
        this->do_free = TRUE;
    } else {
        this->name = NULL;
        this->do_free = FALSE;
    }
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_exception_copy_ctor,8)
exception* __stdcall MSVCP_exception_copy_ctor(exception *this, const exception *rhs)
{
    TRACE("(%p,%p)\n", this, rhs);

    if(!rhs->do_free) {
        this->vtable = exception_type_info.vtable;
        this->name = rhs->name;
        this->do_free = FALSE;
    } else
        MSVCP_exception_ctor(this, (const char**)&rhs->name);
    TRACE("name = %s\n", this->name);
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_exception_dtor,4)
void __stdcall MSVCP_exception_dtor(exception *this)
{
    TRACE("(%p)\n", this);
    this->vtable = exception_type_info.vtable;
    if(this->do_free)
        free(this->name);
}

static const rtti_base_descriptor exception_rtti_base_descriptor = {
    &exception_type_info,
    0,
    { 0, -1, 0 },
    0
};

static const cxx_type_info exception_cxx_type_info = {
    0,
    &exception_type_info,
    { 0, -1, 0 },
    sizeof(exception),
    (cxx_copy_ctor)THISCALL(MSVCP_exception_dtor)
};

static const cxx_type_info_table exception_cxx_type_table = {
    1,
    {
        &exception_cxx_type_info,
        NULL,
        NULL
    }
};

static const cxx_exception_type exception_cxx_type = {
    0,
    (cxx_copy_ctor)THISCALL(MSVCP_exception_copy_ctor),
    NULL,
    &exception_cxx_type_table
};

void set_exception_vtable(void)
{
    HMODULE hmod = GetModuleHandleA("msvcrt.dll");
    exception_type_info.vtable = (void*)GetProcAddress(hmod, "??_7exception@@6B@");
}

/* bad_alloc class data */
typedef exception bad_alloc;

DEFINE_THISCALL_WRAPPER(MSVCP_bad_alloc_ctor, 8)
bad_alloc* __stdcall MSVCP_bad_alloc_ctor(bad_alloc *this, const char **name)
{
    TRACE("%p %s\n", this, *name);
    MSVCP_exception_ctor(this, name);
    this->vtable = &MSVCP_bad_alloc_vtable;
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_bad_alloc_copy_ctor, 8)
bad_alloc* __stdcall MSVCP_bad_alloc_copy_ctor(bad_alloc *this, const bad_alloc *rhs)
{
    TRACE("%p %p\n", this, rhs);
    MSVCP_exception_copy_ctor(this, rhs);
    this->vtable = &MSVCP_bad_alloc_vtable;
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_bad_alloc_dtor, 4)
void __stdcall MSVCP_bad_alloc_dtor(bad_alloc *this)
{
    TRACE("%p\n", this);
    MSVCP_exception_dtor(this);
}

DEFINE_THISCALL_WRAPPER(MSVCP_bad_alloc_vector_dtor, 8)
void * __stdcall MSVCP_bad_alloc_vector_dtor(bad_alloc *this, unsigned int flags)
{
    TRACE("%p %x\n", this, flags);
    if(flags & 2) {
        /* we have an array, with the number of elements stored before the first object */
        int i, *ptr = (int *)this-1;

        for(i=*ptr-1; i>=0; i--)
            MSVCP_bad_alloc_dtor(this+i);
        MSVCRT_operator_delete(ptr);
    } else {
        MSVCP_bad_alloc_dtor(this);
        if(flags & 1)
            MSVCRT_operator_delete(this);
    }

    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_what_exception,4)
const char* __stdcall MSVCP_what_exception(exception * this)
{
    TRACE("(%p) returning %s\n", this, this->name);
    return this->name ? this->name : "Unknown exception";
}

static const type_info bad_alloc_type_info = {
    &MSVCP_bad_alloc_vtable,
    NULL,
    ".?AVbad_alloc@std@@"
};

static const rtti_base_descriptor bad_alloc_rtti_base_descriptor = {
    &bad_alloc_type_info,
    1,
    { 0, -1, 0 },
    64
};

static const rtti_base_array bad_alloc_rtti_base_array = {
    {
        &bad_alloc_rtti_base_descriptor,
        &exception_rtti_base_descriptor,
        NULL
    }
};

static const rtti_object_hierarchy bad_alloc_type_hierarchy = {
    0,
    0,
    2,
    &bad_alloc_rtti_base_array
};

const rtti_object_locator bad_alloc_rtti = {
    0,
    0,
    0,
    &bad_alloc_type_info,
    &bad_alloc_type_hierarchy
};

static const cxx_type_info bad_alloc_cxx_type_info = {
    0,
    &bad_alloc_type_info,
    { 0, -1, 0 },
    sizeof(bad_alloc),
    (cxx_copy_ctor)THISCALL(MSVCP_bad_alloc_copy_ctor)
};

static const cxx_type_info_table bad_alloc_cxx_type_table = {
    2,
    {
        &bad_alloc_cxx_type_info,
        &exception_cxx_type_info,
        NULL
    }
};

static const cxx_exception_type bad_alloc_cxx_type = {
    0,
    (cxx_copy_ctor)THISCALL(MSVCP_bad_alloc_dtor),
    NULL,
    &bad_alloc_cxx_type_table
};

/* logic_error class data */
typedef struct _logic_error {
    exception e;
    basic_string_char str;
} logic_error;

DEFINE_THISCALL_WRAPPER(MSVCP_logic_error_ctor, 8)
logic_error* __stdcall MSVCP_logic_error_ctor(
        logic_error *this, const char **name)
{
    TRACE("%p %s\n", this, *name);
    this->e.vtable = &MSVCP_logic_error_vtable;
    this->e.name = NULL;
    this->e.do_free = FALSE;
    MSVCP_basic_string_char_ctor_cstr(&this->str, *name);
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_logic_error_copy_ctor, 8)
logic_error* __stdcall MSVCP_logic_error_copy_ctor(
        logic_error *this, logic_error *rhs)
{
    TRACE("%p %p\n", this, rhs);
    MSVCP_exception_copy_ctor(&this->e, &rhs->e);
    MSVCP_basic_string_char_copy_ctor(&this->str, &rhs->str);
    this->e.vtable = &MSVCP_logic_error_vtable;
    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_logic_error_dtor, 4)
void __stdcall MSVCP_logic_error_dtor(logic_error *this)
{
    TRACE("%p\n", this);
    MSVCP_exception_dtor(&this->e);
    MSVCP_basic_string_char_dtor(&this->str);
}

DEFINE_THISCALL_WRAPPER(MSVCP_logic_error_vector_dtor, 8)
void* __stdcall MSVCP_logic_error_vector_dtor(
        logic_error *this, unsigned int flags)
{
    TRACE("%p %x\n", this, flags);
    if(flags & 2) {
        /* we have an array, with the number of elements stored before the first object */
        int i, *ptr = (int *)this-1;

        for(i=*ptr-1; i>=0; i--)
            MSVCP_logic_error_dtor(this+i);
        MSVCRT_operator_delete(ptr);
    } else {
        MSVCP_logic_error_dtor(this);
        if(flags & 1)
            MSVCRT_operator_delete(this);
    }

    return this;
}

DEFINE_THISCALL_WRAPPER(MSVCP_logic_error_what, 4)
const char* __stdcall MSVCP_logic_error_what(logic_error *this)
{
    TRACE("%p\n", this);
    return MSVCP_basic_string_char_c_str(&this->str);
}

static const type_info logic_error_type_info = {
    &MSVCP_logic_error_vtable,
    NULL,
    ".?AVlogic_error@std@@"
};

static const rtti_base_descriptor logic_error_rtti_base_descriptor = {
    &logic_error_type_info,
    1,
    { 0, -1, 0 },
    64
};

static const rtti_base_array logic_error_rtti_base_array = {
    {
        &logic_error_rtti_base_descriptor,
        &exception_rtti_base_descriptor,
        NULL
    }
};

static const rtti_object_hierarchy logic_error_type_hierarchy = {
    0,
    0,
    2,
    &logic_error_rtti_base_array
};

const rtti_object_locator logic_error_rtti = {
    0,
    0,
    0,
    &logic_error_type_info,
    &logic_error_type_hierarchy
};

static const cxx_type_info logic_error_cxx_type_info = {
    0,
    &logic_error_type_info,
    { 0, -1, 0 },
    sizeof(logic_error),
    (cxx_copy_ctor)THISCALL(MSVCP_logic_error_copy_ctor)
};

static const cxx_type_info_table logic_error_cxx_type_table = {
    2,
    {
        &logic_error_cxx_type_info,
        &exception_cxx_type_info,
        NULL
    }
};

static const cxx_exception_type logic_error_cxx_type = {
    0,
    (cxx_copy_ctor)THISCALL(MSVCP_logic_error_dtor),
    NULL,
    &logic_error_cxx_type_table
};

#ifndef __GNUC__
void __asm_dummy_vtables(void) {
#endif
    __ASM_EXCEPTION_VTABLE(bad_alloc)
    __ASM_EXCEPTION_STRING_VTABLE(logic_error)
#ifndef __GNUC__
}
#endif

/* Internal: throws selected exception */
void throw_exception(exception_type et, const char *str)
{
    const char *addr = str;

    switch(et) {
    case EXCEPTION: {
        exception e;
        MSVCP_exception_ctor(&e, &addr);
        _CxxThrowException(&e, &exception_cxx_type);
        return;
    }
    case EXCEPTION_BAD_ALLOC: {
        bad_alloc e;
        MSVCP_bad_alloc_ctor(&e, &addr);
        _CxxThrowException(&e, &bad_alloc_cxx_type);
        return;
    }
    case EXCEPTION_LOGIC_ERROR: {
        logic_error e;
        MSVCP_logic_error_ctor(&e, &addr);
        _CxxThrowException((exception*)&e, &logic_error_cxx_type);
        return;
    }
    }
}
