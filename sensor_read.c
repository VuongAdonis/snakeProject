#include "sensor_read.h"
void adc_Display(){
	lcd_ShowStr(10, 30, "Power:", RED, WHITE, 16, 0);
	lcd_ShowFloatNum(130, 30, Power, 5, RED, WHITE, 16);
	lcd_ShowStr(200, 30, "(mW)", RED, WHITE, 16, 0);

	lcd_ShowStr(10, 50, "Light:", RED, WHITE, 16, 0);
	lcd_ShowStr(130, 50, Light_intensity, RED, WHITE, 16, 0);

	lcd_ShowStr(10, 70, "Temperature:", RED, WHITE, 16, 0);
	lcd_ShowStr(130, 70, Temperature_intensity, RED, WHITE, 16, 0);


	lcd_ShowStr(10, 90, "Humidity:", RED, WHITE, 16, 0);
	lcd_ShowStr(130, 90, Humidity_intensity, RED, WHITE, 16, 0);

}

void adc_Update(){
	sensor_Read();
	Power = sensor_GetCurrent()*sensor_GetVoltage();
	
  	Light = sensor_GetLight();
	if(Light > 1700){
		Light_intensity = "Weak";
	}
  	else if(Light < 900){
		Light_intensity = "Strong";
	}
  	else{
		Light_intensity = "Normal";
	}
	
  	Humidity = (((float)sensor_GetPotentiometer())/4095.0)*100.0;
  	if(Humidity > 70){
		Humidity_intensity = "High";
	}
  	else if(Humidity < 40){
		Humidity_intensity = "Low";
	}
  	else{
		Humidity_intensity = "Normal";
	}

  	Temperature = sensor_GetTemperature();
  	if(Temperature > 35){
		Temperature_intensity = "Hot";
	}
  	else if(Temperature < 25){
		Temperature_intensity = "Cold";
	}
  	else{
		Temperature_intensity = "Normal";
	}
}
