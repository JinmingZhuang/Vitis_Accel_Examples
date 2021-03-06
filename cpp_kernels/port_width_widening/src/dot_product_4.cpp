/**********
Copyright (c) 2020, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

#include <stdint.h>
#define DATA_WIDTH 16

extern "C" {
void dot_product_4(const uint32_t* a, const uint32_t* b, uint64_t* res, const int size, const int reps) {
// Using HLS_INERFACE pragma to place each buffer in a different bank
// Using hls_config.tcl to set port width
// i.e. 2 bundles with each port having a width of 512

#pragma HLS INTERFACE m_axi port = a bundle = gmem0
#pragma HLS INTERFACE m_axi port = b bundle = gmem1
#pragma HLS INTERFACE m_axi port = res bundle = gmem0

loop_reps:
    for (int i = 0; i < reps; i++) {
    dot_product_outer:
        for (int j = 0; j < size; j += DATA_WIDTH) {
        dot_product_inner:
            for (int k = 0; k < DATA_WIDTH; k++) {
                res[j + k] = a[j + k] * b[j + k];
            }
        }
    }
}
}
