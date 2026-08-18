// Code made by Srdjan Crnjanski 2026 2026
// This is demo application showing advanced usage of bitscrambler potential
// It uses specialy designed component (also written by me) 
// to simulate ALU bitwise computation among ant two 8 bit channels
// by bitwise function deffined within 3rd channel
// so it is cappable to perform different bitwise operations per pixel in single bitscrambler program

#include <inttypes.h>
#include <stdint.h>
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "advanced_bitscrambler.h"


void app_main(void){
  init_bitscrambler();

  // this bitscrambler code expects 32 bit input buffer ie RGBA8888
  // so we create one of 256 elemnts in size for testing purposes
  uint32_t* buf_in = (uint32_t*)heap_caps_aligned_alloc(256, 256 * 4, MALLOC_CAP_32BIT | MALLOC_CAP_DMA | MALLOC_CAP_CACHE_ALIGNED);
  if(buf_in == NULL){
    ESP_LOGE("alloc", "Failed to allocate in buffer!");
    return;
  }

  // Here we populate RGBA buffer for testing bitwise operation is stored in alpha channel
  // green channel is populated by counter value
  // blue channel is setup to 0xFF 
  // ofcourse, you can change values ie. function variation in alpha can be determined by counter in this demo
  // also content of blue or green channel can be anything
  uint32_t alpha = BITWISE_A_XOR_B << 24; // chosen function is shifted to alpha position
  for(uint16_t i=0; i<256; i++){
    buf_in[i] = ((i << 8) | 0x000000FF | alpha); // counter stored in green channel, const 255 in blue channel
  }


 // resulting buffer is 8 bits containing bitwise opperation performed over blue and green channels by function determined in alpha content
  uint8_t* buf_out = (uint8_t*)heap_caps_aligned_alloc(256, 256, MALLOC_CAP_8BIT | MALLOC_CAP_DMA | MALLOC_CAP_CACHE_ALIGNED);
  if(buf_out == NULL){
    ESP_LOGE("alloc", "Failed to allocate out buffer!");
    return;
  }
  
 size_t written = run_bitscrambler(buf_in, 256 * 4, buf_out, 256, advanced_alu_sim_bga);
  
  ESP_LOGI("scramble", "Successful finished.  processed  %zu elements", written);
  printf("Out data: ");
  for(uint16_t i=0; i<256; i++){
    printf("0x%"PRIX8" ",buf_out[i]);
  }
  printf("\n");


 deinit_bitscrambler();

 free(buf_in);
 free(buf_out); 
 
}

