#include <stdlib.h>
#include <sgx_spinlock.h>
#include "sgx_trts.h"
#include "sgx_cpuid.h"
#include "sgx_error.h"


#define PAGE_SHIFT      12
#ifdef __ASSEMBLY__
#define PAGE_SIZE       (1 << PAGE_SHIFT)
#else
#define PAGE_SIZE       (1UL << PAGE_SHIFT)
#endif
#define PAGE_MASK       (~(PAGE_SIZE-1))

sgx_status_t sgx_oc_mlock(int * int32_t, uint64_t addr,uint32_t nr_pages);
sgx_status_t sgx_oc_munlock( int * int32_t ,uint64_t addr,uint32_t nr_pages);
sgx_status_t sgx_oc_mincore( int * int32_t, uint64_t addr);

int mlock(unsigned long start_address,unsigned long size){
    int res=0;
    unsigned long end_address=start_address+size;
    unsigned int nr_pages=1;

    start_address&=PAGE_MASK;
    end_address&=PAGE_MASK;

    nr_pages=( (end_address-start_address) >> PAGE_SHIFT) +1;

    sgx_oc_mlock(&res,start_address,nr_pages);
    return res;
}
