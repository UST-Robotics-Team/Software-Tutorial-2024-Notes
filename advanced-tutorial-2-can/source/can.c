/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

#include "main.h"

/* USER CODE BEGIN 0 */

int16_t rm_ctrl_cmd[MAX_CAN_RM * NUM_OF_CAN] = {0};
MotorStats rm_fb_cmd[MAX_CAN_RM * NUM_OF_CAN] = {0};

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void) {
  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */
}
/* CAN2 init function */
void MX_CAN2_Init(void) {
  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 3;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */
}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED = 0;

void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (canHandle->Instance == CAN1) {
    /* USER CODE BEGIN CAN1_MspInit 0 */

    /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if (HAL_RCC_CAN1_CLK_ENABLED == 1) {
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
     PA11     ------> CAN1_RX
     PA12     ------> CAN1_TX
     */
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN CAN1_MspInit 1 */

    /* USER CODE END CAN1_MspInit 1 */
  } else if (canHandle->Instance == CAN2) {
    /* USER CODE BEGIN CAN2_MspInit 0 */

    /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if (HAL_RCC_CAN1_CLK_ENABLED == 1) {
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
     PB12     ------> CAN2_RX
     PB13     ------> CAN2_TX
     */
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USER CODE BEGIN CAN2_MspInit 1 */

    /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle) {
  if (canHandle->Instance == CAN1) {
    /* USER CODE BEGIN CAN1_MspDeInit 0 */

    /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if (HAL_RCC_CAN1_CLK_ENABLED == 0) {
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
     PA11     ------> CAN1_RX
     PA12     ------> CAN1_TX
     */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

    /* USER CODE BEGIN CAN1_MspDeInit 1 */

    /* USER CODE END CAN1_MspDeInit 1 */
  } else if (canHandle->Instance == CAN2) {
    /* USER CODE BEGIN CAN2_MspDeInit 0 */

    /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if (HAL_RCC_CAN1_CLK_ENABLED == 0) {
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
     PB12     ------> CAN2_RX
     PB13     ------> CAN2_TX
     */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12 | GPIO_PIN_13);

    /* USER CODE BEGIN CAN2_MspDeInit 1 */

    /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void can_filter_enable(CAN_HandleTypeDef *hcan) {
  CAN_FilterTypeDef CAN_FilterConfigStructure;

  CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterConfigStructure.FilterActivation = ENABLE;
  CAN_FilterConfigStructure.SlaveStartFilterBank = 27;

  CAN_FilterConfigStructure.FilterBank = 0;

  HAL_CAN_ConfigFilter(hcan, &CAN_FilterConfigStructure);
}

void can_filter_disable(CAN_HandleTypeDef *hcan) {
  CAN_FilterTypeDef CAN_FilterConfigStructure;

  CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterConfigStructure.FilterActivation = DISABLE;
  CAN_FilterConfigStructure.SlaveStartFilterBank = 27;

  CAN_FilterConfigStructure.FilterBank = 0;

  HAL_CAN_ConfigFilter(hcan, &CAN_FilterConfigStructure);
}

void can_init() {
  CAN_FilterTypeDef CAN_FilterConfigStructure;

  CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
  CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
  CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterConfigStructure.FilterActivation = ENABLE;
  CAN_FilterConfigStructure.FilterBank = 0;

  HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterConfigStructure);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  HAL_CAN_ConfigFilter(&hcan2, &CAN_FilterConfigStructure);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

#define GET_MOTOR_FEEDBACK(ptr, data)                                          \
  {                                                                            \
    (ptr)->pos_rad = (uint16_t)((data)[0] << 8 | (data)[1]);                   \
    (ptr)->vel_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);                   \
    (ptr)->actual_current = (uint16_t)((data)[4] << 8 | (data)[5]);            \
    (ptr)->temperature = (data)[6];                                            \
  }

__forceinline void __from_bigendian(uint8_t *in, void *out) {
  uint8_t *o = out;
  *o = *(in + 1);
  *(o + 1) = *in;
}

__forceinline void __get_motor_fb(MotorFeedback *ptr, uint8_t *data) {
  __from_bigendian(data, &(ptr->encoder));
  __from_bigendian(data + 2, &(ptr->vel_rpm));
  __from_bigendian(data + 4, &(ptr->raw_current));
  ptr->temperature = data[6];
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  CAN_RxHeaderTypeDef rx_header;
  uint8_t rx_data[8];
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
  uint8_t base_id = rx_header.StdId - CAN_3508_M1_ID;
  if (hcan == &hcan2) {
    base_id += 8;
  }
  MotorFeedback fb;
  __get_motor_fb(&fb, rx_data);
  rm_fb_cmd[base_id].encoder = fb.encoder;
  rm_fb_cmd[base_id].vel_rpm = fb.vel_rpm;
  rm_fb_cmd[base_id].actual_current = fb.raw_current;
  rm_fb_cmd[base_id].temperature = fb.temperature;
}

void can_transmit(CAN_HandleTypeDef *hcan, uint16_t id, int16_t msg1,
                  int16_t msg2, int16_t msg3, int16_t msg4) {
  CAN_TxHeaderTypeDef tx_header;
  uint8_t data[8];
  uint32_t pTxMailbox;

  tx_header.StdId = id;
  tx_header.IDE = CAN_ID_STD;
  tx_header.RTR = CAN_RTR_DATA;
  tx_header.DLC = CAN_DATA_SIZE;
  tx_header.TransmitGlobalTime = DISABLE;
  data[0] = msg1 >> 8;
  data[1] = msg1;
  data[2] = msg2 >> 8;
  data[3] = msg2;
  data[4] = msg3 >> 8;
  data[5] = msg3;
  data[6] = msg4 >> 8;
  data[7] = msg4;

  if (HAL_CAN_AddTxMessage(hcan, &tx_header, data, &pTxMailbox) == HAL_OK) {
    while (HAL_CAN_IsTxMessagePending(hcan, pTxMailbox))
      ;
  }
}

void can_ctrl_loop() {
  /* ======= TX ======= */
  // CAN1
  can_transmit(&hcan1, RM_TX_GRP1_ID, rm_ctrl_cmd[CAN1_MOTOR0],
               rm_ctrl_cmd[CAN1_MOTOR1], rm_ctrl_cmd[CAN1_MOTOR2],
               rm_ctrl_cmd[CAN1_MOTOR3]);
  can_transmit(&hcan1, RM_TX_GRP2_ID, rm_ctrl_cmd[CAN1_MOTOR4],
               rm_ctrl_cmd[CAN1_MOTOR5], rm_ctrl_cmd[CAN1_MOTOR6],
               rm_ctrl_cmd[CAN1_MOTOR7]);

  // CAN2
  can_transmit(&hcan2, RM_TX_GRP1_ID, rm_ctrl_cmd[CAN2_MOTOR0],
               rm_ctrl_cmd[CAN2_MOTOR1], rm_ctrl_cmd[CAN2_MOTOR2],
               rm_ctrl_cmd[CAN2_MOTOR3]);
  can_transmit(&hcan2, RM_TX_GRP2_ID, rm_ctrl_cmd[CAN2_MOTOR4],
               rm_ctrl_cmd[CAN2_MOTOR5], rm_ctrl_cmd[CAN2_MOTOR6],
               rm_ctrl_cmd[CAN2_MOTOR7]);

  /* ======= RX ======= */
  HAL_CAN_RxFifo0MsgPendingCallback(&hcan1);
  HAL_CAN_RxFifo0MsgPendingCallback(&hcan2);
}

/* USER FUNCTIONS */

MotorStats get_motor_feedback(Motor tar_motor) { return rm_fb_cmd[tar_motor]; }

void set_motor_current(Motor tar_motor, int16_t tar_current) {
  if (tar_current > 10000) {
    tar_current = 10000;
  } else if (tar_current < -10000) {
    tar_current = -10000;
  }
  rm_ctrl_cmd[tar_motor] = tar_current;
}

void set_motor_speed(Motor tar_motor, int16_t tar_vel) {
  // TODO: implement this (Tips: see PID notes)
}

/* USER CODE END 1 */
