#include "chassis_task.h"
#include "main.h"
#include "tim.h"

chassis_move_t chassis_move;

static void chassis_init(chassis_move_t *chassis_move_init);

static void chassis_set_control(chassis_move_t *chassis_move_init);

void chassis_task(void const *pvParameters)
{
    chassis_init(&chassis_move);
    while (1)
    {
        chassis_set_control(&chassis_move);
        //系统延时
        vTaskDelay(CHASSIS_CONTROL_TIME_MS);
    }
}

void chassis_init(chassis_move_t *chassis_move_init)
{
    chassis_move_init->chassis_RC = get_remote_control_point();
}

void chassis_set_control(chassis_move_t *chassis_move_mode)
{
    if (switch_is_up(chassis_move_mode->chassis_RC->rc.s[0]))
    {
        if (switch_is_up(chassis_move_mode->chassis_RC->rc.s[1])){
            //控制电机正反转
            HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_SET);
        }
        else{
            HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_RESET);
        }
        //这里是57两个步进电机的控制
        servo_pwm_set(500,2);
        servo_pwm_set(500,3);
    }
    else
    {
        servo_pwm_set(0,2);
        servo_pwm_set(0,3);
    }
}
