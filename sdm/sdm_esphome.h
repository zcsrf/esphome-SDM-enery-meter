#include "esphome.h"

class SDMComponent : public PollingComponent {
public:
  SDM sdm = SDM(Serial, 9600, NOT_A_PIN, SERIAL_8N1, false);

  Sensor *voltage_sensor = new Sensor();
  Sensor *current_sensor = new Sensor();
  Sensor *power_sensor = new Sensor();
  Sensor *apparent_power_sensor = new Sensor();
  Sensor *power_factor_sensor = new Sensor();
  Sensor *phase_angle_sensor = new Sensor();
  Sensor *line_frequency_sensor = new Sensor();
  Sensor *energy_import_sensor = new Sensor();
  
  // remove when no longer debugging the implementation
  Sensor *read_error_count_sensor = new Sensor();

  // Adjust your polling component to your needs, value is in ms, 5 seconds = 5000 ms
  SDMComponent() : PollingComponent(5000) {}

  void setup() override {
    ESP_LOGD("SDM", "Setup completed");
  }

  void update() override {
    ESP_LOGD("SDM", "Start reading");
    // Voltage Reading
    float voltage = sdm.readVal(SDM230_VOLTAGE);
    voltage_sensor->publish_state((voltage);
    
    //  Current Reading
    float current = sdm.readVal(SDM230_CURRENT);
    current_sensor->publish_state(current);

    // Power Reading
    float power = sdm.readVal(SDM230_POWER);
    power_sensor->publish_state(power);

    // Apparent Power Reading
    float apparent_power = sdm.readVal(SDM230_ACTIVE_APPARENT_POWER);
    apparent_power_sensor->publish_state(apparent_power);        
    
    // Power Factor reading                              
    float power_factor = sdm.readVal(SDM230_POWER_FACTOR);
    power_factor_sensor->publish_state(power_factor);      
                                  
    // Phase angle reading
    float phase_angle = sdm.readVal(SDM230_PHASE_ANGLE);
    phase_angle_sensor->publish_state(phase_angle);     
    
    // Line frequency reading
    float frequency = sdm.readVal(SDM230_FREQUENCY);
    line_frequency_sensor->publish_state(frequency);     

    // Total active energy reading
    float total_active_energy = sdm.readVal(SDM230_TOTAL_ACTIVE_ENERGY);
    energy_import_sensor->publish_state(total_active_energy);

    // Number of errros while reading, remove when no longer debugging the implementation
    int error_count = sdm.getErrCount();
    read_error_count_sensor->publish_state(error_count);
                                  
    ESP_LOGD("SDM", "End reading");
  }
};
