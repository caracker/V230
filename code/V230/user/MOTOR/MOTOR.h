void motor_init(void);
void motor_even(void);
void pwm_init(void);
#define motor_on 	tm2c = 0b_0001_10_1_0;	 // ϵͳʱ��, ��� = PA3, PWM ģʽ
#define motor_off 	tm2c = 0b_0001_00_1_0;	 // ϵͳʱ��, ��� = PA3, PWM ģʽ



#define motor_pin   	pb.2

#define motor2_pin   	pb.7

#define q6_pin 	pa.4
#define q4_pin	pb.2