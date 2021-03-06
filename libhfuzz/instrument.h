/*
 *
 * honggfuzz - compiler instrumentation
 * -----------------------------------------
 *
 * Author: Robert Swiecki <swiecki@google.com>
 *
 * Copyright 2010-2015 by Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 */

#ifndef _HF_LIBHFUZZ_INSTRUMENT_H_
#define _HF_LIBHFUZZ_INSTRUMENT_H_

#include "../libcommon/common.h"
#include "../libcommon/util.h"

extern feedback_t *feedback;
extern uint32_t my_thread_no;

__attribute__ ((always_inline))
static inline void instrumentUpdateCmpMap(void *addr, unsigned int n)
{
    uintptr_t pos = (uintptr_t) addr % _HF_PERF_BITMAP_SIZE_16M;
    uint8_t v = n > 254 ? 254 : n;
    uint8_t prev = ATOMIC_GET(feedback->bbMapCmp[pos]);
    if (prev < v) {
        ATOMIC_SET(feedback->bbMapCmp[pos], v);
        ATOMIC_POST_ADD(feedback->pidFeedbackCmp[my_thread_no], v - prev);
    }
}

#endif
