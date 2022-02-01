

void copyDMXToOutput(void) {
  xSemaphoreTake( ESP32DMX.lxDataLock, portMAX_DELAY );
	for (int i=1; i<=512; i++) {
    	ESP32DMX.setSlot(i , output[i]);
   }
   xSemaphoreGive( ESP32DMX.lxDataLock );
}