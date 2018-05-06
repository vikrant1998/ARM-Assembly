/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "dic.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define LCD_DELAY 2

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
struct gpioPin data595 = {'B', 11};
struct gpioPin clock595 = {'B', 10};
struct gpioPin latch595 = {'B', 2};
struct gpioPin lcdRegSel = {'B', 1};
struct gpioPin lcdEn = {'C', 5};
struct gpioPin lcdRw = {'B', 0};


uint8_t mpuData[66] = {0};
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int valy = 1500;
int valL, valR, valC;
int clawState = -1;
volatile float Ax, Ay, Az;
volatile float accZ, laccZ;
volatile float lAz = 0;
volatile int tempFlag = 0;
int maxValL, minValL;
int maxValR, minValR;
int maxValC, minValC;
int maxValB, minValB;
int perR, perL, perB, perC;
int msCount = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);



void lcdFreshString(char* val, uint8_t line);
void lcdWriteChar(uint8_t val);
void lcdClear();
void lcdSetup();
void lcdCommand(uint8_t comm);
void shiftIn(struct gpioPin data, struct gpioPin clock, struct gpioPin latch, uint8_t val);
void pinWrite(struct gpioPin target, bool val);
void lcdFullDisplay(char* val1, char* val2);
void showMotorStatus();

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    minValC = 900;
    maxValC = 1300;
    minValB = 600;
    maxValB = 2300;
    minValL = 1300;
    maxValL = 1400;
    minValR = 1000;
    maxValR = 2300;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  lcdSetup();
  lcdFullDisplay("ARM ASSEMBLY", "L: XX% R: XX% B: XX%");
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1500); //Bottom motor (controls arm L/R rotate) (600-2400)
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 1000); //right motor (controls reach?) (1000-2000)
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1300); //left motor (controls reach?) (1000-2000) //1300 central
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1300); //claw motor (900 is closed, 1300 is open)
  valL = 1300;
  valR = 1300;
  valC = 1300;
  showMotorStatus();
  //full extension (left: 1400, right: 2300)
  //middle max height (left: 1300, right: 1000)

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      HAL_UART_Receive_IT(&huart1, mpuData, 66);



  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void showMotorStatus()
{
    char line1[16];
    char line2[16];
    perC = 100.0 * (valC - minValC) / (maxValC - minValC);
    perB = 100.0 * (valy - minValB) / (maxValB - minValB);
    perL = 100.0 * (valL - minValL) / (maxValL - minValL);
    perR = 100.0 * (valR - minValR) / (maxValR - minValR);
    sprintf(line1, "L %03d %% R %03d %%", perL, perR);
    sprintf(line2, "B %03d %% C %03d %%", perB, perC);
    lcdFullDisplay(line1, line2);
}

void myTIM1IRQ()
{
    if(Ax > 50 && Ax < 300){
           flag1 = -1;
           HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
           HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
    }

       else if(Ax < -50 && Ax > -300){
           flag1 = 1;
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);}
       else{
           flag1 = 0;
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
    }
    if(Ay > 50 && Ay < 300)
    {
        flag2 = 1;
    }
    else if(Ay < -50 && Ay > -300)
    {
        flag2 = -1;
    }
    else
    {
        flag2 = 0;
    }

    // state machine CLAW
    if(tempFlag == 2)
    {
        if(valC == 1300)
            valC = 900;
        else if(valC == 900)
            valC = 1300;
        tempFlag = 0;
    }
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4, valC);

    if (flag1 == 1){
        valy+=50;
        if(valy>=2300){
            valy=2300;
        }
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,valy);
    }
    else if (flag1 == -1){
         valy-=50;
         if(valy<=600){
             valy=600;
         }
         __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,valy);
    }
    //full extension (left: 1400, right: 2300)
    //middle max height (left: 1300, right: 1000)
    if (flag2 == 1){
        valL -= 10;
        valR -= 130;
        if(valL <= 1300)
            valL = 1300;
        if(valR <= 1000)
            valR = 1000;

        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,valR);
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,valL);
    }
    else if (flag2 == -1){
        valL += 10;
        valR += 130;
        if(valL >= 1400)
            valL = 1400;
        if(valR >= 2300)
            valR = 2300;
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,valR);
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,valL);
    }
    msCount += 50;
    if(msCount == 300)
    {
        showMotorStatus();
    }

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    for(int i=0; i<65;i++){
        if(mpuData[i] == 0x55 && mpuData[i+1]==0x52 && (i+7 <=65)){
            Ax = ((short)(mpuData[i+3]<<8 | mpuData[i+2]))/32768.0*2000;
            Ay = ((short)(mpuData[i+5]<<8 | mpuData[i+4]))/32768.0*2000;
            Az = ((short)(mpuData[i+7]<<8 | mpuData[i+6]))/32768.0*2000;
        }
        if(mpuData[i] == 0x55 && mpuData[i+1] == 0x51 && (i + 7) <= 65)
        {
            accZ = ((short)(mpuData[i+7] << 8 | mpuData[i+6]))/32768.0*16;
        }
        if(accZ > 0.5 && tempFlag == 0)
        {
            tempFlag = 1;
        }
        if(accZ < -0.5 && tempFlag == 1)
        {
            tempFlag = 2;
        }

    }

    return;
}

void lcdFullDisplay(char* val1, char* val2)
{
    char* lol = val1;
    lcdClear();
    while(*lol)
    {
        lcdWriteChar(*lol);
        lol++;
    }
    pinWrite(lcdRegSel, false);
    pinWrite(lcdRw, false);
    lcdCommand(0xC0);
    lol = val2;
    while(*lol)
    {
        lcdWriteChar(*lol);
        lol++;
    }
}

// Prints given string on particular line of the
// LCD display
void lcdFreshString(char* val, uint8_t line)
{
    char* lol = val;
    lcdClear();
    if(line == 1)
    {
        while(*lol != 0)// && *lol != '\n' && *lol != '\r')
        {
            lcdWriteChar(*lol);
            lol++;
        }
    }
    else
    {
        pinWrite(lcdRegSel, false);
        pinWrite(lcdRw, false);
        lcdCommand(0xC0);
        while(*lol)
        {
            lcdWriteChar(*lol);
            lol++;
        }
    }
}

// Writes a particular character to the LCD and advances the cursor
void lcdWriteChar(uint8_t val)
{
    pinWrite(lcdRw, false);
    pinWrite(lcdRegSel, true);
    lcdCommand(val);
}

// Clears the LCD and moves cursor to the beginning
void lcdClear()
{
    pinWrite(lcdRw, false);
    pinWrite(lcdRegSel, false);
    lcdCommand(0x01);
    pinWrite(lcdEn, true);
    pinWrite(lcdEn, false);
    HAL_Delay(LCD_DELAY);
}

// Initialises the LCD in 8-bit mode
void lcdSetup()
{
    HAL_Delay(LCD_DELAY * 8);
    pinWrite(lcdRegSel, false); // command mode enabled
    pinWrite(lcdRw, false); //write mode
    lcdCommand(0x38); //send function set
    lcdCommand(0x0C); //cursor off, display on
    lcdCommand(0x01); //clear
    lcdCommand(0x06);
    HAL_Delay(LCD_DELAY);

}

// Give a command to the LCD to execute
void lcdCommand(uint8_t comm)
{
    pinWrite(lcdEn, false);
    shiftIn(data595, clock595, latch595, comm);
    pinWrite(lcdEn, true);
    HAL_Delay(LCD_DELAY);
    pinWrite(lcdEn, false);
    HAL_Delay(LCD_DELAY);
}

// HC595 shift register instruction
void shiftIn(struct gpioPin data, struct gpioPin clock, struct gpioPin latch, uint8_t val)
{
    char x = 0;
    pinWrite(clock, false);
    pinWrite(latch, false);
    for(int i = 0; i < 8; ++i)
    {
        x = val & 0x80;
        if (x)
        {
            pinWrite(data, true);
        }
        else
        {
            pinWrite(data, false);
        }
        pinWrite(clock, true);
        pinWrite(clock, false);
        val = val << 1;
    }
    pinWrite(latch, true);
    pinWrite(latch, false);
}

// Write a value to the given pin
void pinWrite(struct gpioPin target, bool val)
{
    if(val == true)
    {
        HAL_GPIO_WritePin(gpioDecode(target.gpio), pinDecode(target.pin), GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(gpioDecode(target.gpio), pinDecode(target.pin), GPIO_PIN_RESET);
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
