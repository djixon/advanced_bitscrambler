// Designed and programed by Srdjan Crnjanski 2026 V1.0
// all rights reserved
// you can use the code for free, but author name, year, version and all comments must be preserved within
// your source files

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/bitscrambler.h"
#include "driver/bitscrambler_loopback.h"
#include "advanced_bitscrambler.h"

static bitscrambler_handle_t bs_handle = NULL;

void init_bitscrambler(void){
 esp_err_t ret;
 ret = bitscrambler_loopback_create(&bs_handle, SOC_BITSCRAMBLER_ATTACH_I2S2, 1024);
 if(ret != ESP_OK){
  ESP_LOGI("scramble", "Failed to create loop back");
 }
}

void deinit_bitscrambler(void){
 if(bs_handle != NULL){
   bitscrambler_disable(bs_handle);
   bitscrambler_free(bs_handle);
   ESP_LOGI("scramble", " succ freed");
 }
}

size_t run_bitscrambler(void* in_buffer, uint32_t in_size_bytes, void* out_buffer, uint32_t out_size_bytes, const void *program_bin){
 esp_err_t ret = bitscrambler_enable(bs_handle);
 if(ret != ESP_OK){
  ESP_LOGI("scramble", "Failed to enable bitscramble");
  deinit_bitscrambler();
  return 0;
 }

 ret = bitscrambler_load_program(bs_handle, program_bin); 
 if(ret != ESP_OK){
  ESP_LOGE("scrambler", " Failed to load program %s",esp_err_to_name(ret));
  deinit_bitscrambler();
  return 0;
 }
 
 size_t written=0;
 ret = bitscrambler_loopback_run(bs_handle,  in_buffer, in_size_bytes, out_buffer, out_size_bytes, &written);
 
 if(ret != ESP_OK){
  ESP_LOGE("scrambler", " Failed running program %s",esp_err_to_name(ret));
  deinit_bitscrambler();
 }

 ret = bitscrambler_disable(bs_handle);
 if(ret != ESP_OK){
  ESP_LOGI("scramble", "Failed to disable bitscramble");
  deinit_bitscrambler();
 }
  return written; 
}


