/*
 * Copyright (C) 2011-2020 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "isgx_user.h"
#include "edmm_utility.h"
#include <stdint.h>
#include <sys/ioctl.h>

extern "C" int32_t sgx_oc_mlock(unsigned long addr,unsigned int nr_pages){
    static int m_hdevice=-1;
    if(m_hdevice==-1){
      if (false==open_se_device( SGX_DRIVER_OUT_OF_TREE, &m_hdevice )){ return -7;};
    }

    struct sgx_range rg;
    rg.start_addr=addr;
    rg.nr_pages=nr_pages;
    return ioctl( m_hdevice,SGX_IOC_ENCLAVE_MLOCK,&rg);
}

extern "C" int32_t sgx_oc_munlock(unsigned long addr,unsigned int nr_pages){
    static int m_hdevice=-1;
    if(m_hdevice==-1){
      if (false==open_se_device( SGX_DRIVER_OUT_OF_TREE, &m_hdevice )){ return -7;};
    }

    struct sgx_range rg;
    rg.start_addr=addr;
    rg.nr_pages=nr_pages;
    return ioctl( m_hdevice,SGX_IOC_ENCLAVE_MUNLOCK,&rg);
}

extern "C" int32_t sgx_oc_mincore(unsigned long addr){
    static int m_hdevice=-1;
    if(m_hdevice==-1){
      if (false==open_se_device( SGX_DRIVER_OUT_OF_TREE, &m_hdevice )){ return -7;};
    }

    return ioctl( m_hdevice,SGX_IOC_ENCLAVE_MINCORE,&addr);
}
