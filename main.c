
/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32f4xx_hal.h" // Убедитесь, что это соответствует вашей серии STM32
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
// Определяем переменную для хранения состояния кнопки
uint8_t button_state = 0;

/* USER CODE BEGIN PV */
// ... (Другие ваши приватные переменные) ...
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void); // Функция инициализации GPIO, сгенерированная CubeMX
/* USER CODE BEGIN PFP */
// ... (Другие ваши прототипы функций) ...
/* USER CODE END PFP */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init(); // Инициализируем GPIO, сконфигурированный в CubeMX
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // **Опрос кнопки (Polling):**

    if (HAL_GPIO_ReadPin(BUTTON_PIN_GPIO_Port, BUTTON_PIN_Pin) == GPIO_PIN_RESET) // Кнопка нажата (активный низкий)
    {
      // Debouncing (устранение дребезга контактов)
      HAL_Delay(50); // Задержка 50 мс

      if (HAL_GPIO_ReadPin(BUTTON_PIN_GPIO_Port, BUTTON_PIN_Pin) == GPIO_PIN_RESET)
      {
        // Кнопка действительно нажата

        // Переключаем состояние светодиода (пример)
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // LD2 - обычно встроенный светодиод на плате Nucleo

        // Дополнительные действия при нажатии кнопки
        button_state = 1; // Устанавливаем флаг, чтобы знать, что кнопка была нажата

        // Ждем, пока кнопка будет отпущена
        while (HAL_GPIO_ReadPin(BUTTON_PIN_GPIO_Port, BUTTON_PIN_Pin) == GPIO_PIN_RESET);
        HAL_Delay(50); // Дополнительная задержка для устранения дребезга при отпускании
      }
    } else {
      // Кнопка отпущена
      button_state = 0;
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
// Обработчик прерывания (если используется EXTI):

#ifdef USE_FULL_ASSERT // Проверка на ошибки времени выполнения
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
