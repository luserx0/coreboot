/* Stubs of KASAN Implementation to reach us through compilation */

#include <stdint.h>
#include <console/console.h>
#include "kasan.h"
/*
 * *  Keep the compiler happy -- it wants prototypes but nobody
 * *  except the compiler should be touching these functions.*
*/
#pragma GCC diagnostic ignored "-Wmissing-prototypes"

//#define size_t uint32_t

void __asan_register_globals(struct kasan_global *globals, size_t size)
{
	/* STUB */
}
void __asan_unregister_globals(struct kasan_global *globals, size_t size)
{
	/* STUB */
}
void __asan_loadN(unsigned long addr, size_t size)
{
	/* STUB */
}
void __asan_storeN(unsigned long addr, size_t size)
{
	/* STUB */
}
void __asan_handle_no_return(void)
{
	/* STUB */
}
void __asan_alloca_poison(unsigned long addr, size_t size)
{
	/* STUB */
}
void __asan_allocas_unpoison(const void *stack_top, const void *stack_bottom)
{
	/* STUB */
}

void __asan_load1(unsigned long addr)
{
	/* STUB */
}
void __asan_store1(unsigned long addr)
{
	/* STUB */
}
void __asan_load2(unsigned long addr)
{
	/* STUB */
}
void __asan_store2(unsigned long addr)
{
	/* STUB */
}
void __asan_load4(unsigned long addr)
{
	/* STUB */
}
void __asan_store4(unsigned long addr)
{
	/* STUB */
}
void __asan_load8(unsigned long addr)
{
	/* STUB */
}
void __asan_store8(unsigned long addr)
{
	/* STUB */
}
void __asan_load16(unsigned long addr)
{
	/* STUB */
}
void __asan_store16(unsigned long addr)
{
	/* STUB */
}

void __asan_loadN_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_storeN_noabort(unsigned long addr)
{
	/* STUB */
}

void __asan_load1_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_store1_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_load2_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_store2_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_load4_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_store4_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_load8_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_store8_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_load16_noabort(unsigned long addr)
{
	/* STUB */
}
void __asan_store16_noabort(unsigned long addr)
{
	/* STUB */
}

void __asan_set_shadow_00(const void *addr, size_t size)
{
	/* STUB */
}
void __asan_set_shadow_f1(const void *addr, size_t size)
{
	/* STUB */
}
void __asan_set_shadow_f2(const void *addr, size_t size)
{
	/* STUB */
}
void __asan_set_shadow_f3(const void *addr, size_t size)
{
	/* STUB */
}
void __asan_set_shadow_f5(const void *addr, size_t size)
{
	/* STUB */
}
void __asan_set_shadow_f8(const void *addr, size_t size)
{
	/* STUB */
}




